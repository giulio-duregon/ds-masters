#include "tokenizer.h"
#include <string>
#include <stdio.h>
#include <cstring>
#include <map>
#include <math.h>
#include <cmath>
Tokenizer::Tokenizer(std::string fpath)
{
    setFpath(fpath);
}

void Tokenizer::setFpath(std::string fpath)
{
    _fpath = fpath;
}

void Tokenizer::firstPass()
{
    // Reset position variables
    _line_number = 0;
    int module_number = 1;
    int running_inst_count = 0;
    // Open the inpuit file, get the first line and tokenize
    file.open(_fpath, std::ifstream::in);

    // Begin our procedure
    while ((!file.eof()) && (parse_error_flag == false))
    {
        std::set<std::string> def_set;
        int defcount = readInt();

        if (defcount > 16)
        {
            _parseerror(4);
            parse_error_flag = true;
            break;
        }

        for (int i = 0; i < defcount; i++)
        {
            std::string gname = readSym();

            // Use for a local / global def set for warnings / errors
            def_set.insert(gname);
            global_def_set.insert(gname);
            module_map[gname] = module_number;

            if (parse_error_flag)
            {
                break;
            }
            int value = readInt();
            if (parse_error_flag)
            {
                break;
            }
            int map_count = symbol_map.count(gname);
            if (map_count > 0)
            {
                printf("Warning: Module %d: %s redefined and ignored\n", module_number, gname.c_str());
                warning_map[gname] = "Error: This variable is multiple times defined; first value used";
            }
            else
            {
                symbol_map[gname] = value + running_inst_count;
            }
        }

        int usecount = readInt();
        if (parse_error_flag)
        {
            break;
        }
        if (usecount > 16)
        {
            _parseerror(5);
            parse_error_flag = true;
            break;
        }
        for (int i = 0; i < usecount; i++)
        {
            std::string gname = readSym();
            if (parse_error_flag)
            {
                break;
            }
        }

        int instcount = readInt();
        if (parse_error_flag)
        {
            break;
        }
        if (running_inst_count + instcount > MAX_WORDS)
        {
            parse_error_flag = true;
            _parseerror(6);
            break;
        }
        for (int i = 0; i < instcount; i++)
        {
            readIEAR();
            if (parse_error_flag)
            {
                break;
            }
            readInt();
            if (parse_error_flag)
            {
                break;
            }
        }
        for (std::string sym : def_set)
        {
            int temp_val = symbol_map[sym] - running_inst_count;
            if (temp_val > instcount)
            {
                printf("Warning: Module %d: %s too big %d (max=%d) assume zero relative\n", module_number, sym.c_str(), temp_val, instcount - 1);
                symbol_map[sym] = running_inst_count;
            }
            else
            {
                symbol_map[sym] = temp_val + running_inst_count;
            }
        }
        running_inst_count += instcount;

        module_number++;
    }
    file.close();
    return;
}

void Tokenizer::secondPass()
{
    // Reset position variables
    _line_number = 0;
    int module_number = 1;
    int running_inst_count = 0;
    int defcount, usecount, instcount;

    std::map<int, int> module_map;
    // Open the inpuit file, get the first line and tokenize
    file.open(_fpath, std::ifstream::in);

    // Begin our procedure
    while (!file.eof())
    {
        // Need to Keep track of how many instructions are in each module
        module_map[module_number] = running_inst_count;
        std::set<std::string> use_set;
        std::set<std::string> def_set;
        // First Step
        defcount = readInt();
        for (int i = 0; i < defcount; i++)
        {
            std::string gname = readSym();
            def_set.insert(gname);
            readInt();
        }

        // Second step
        std::vector<std::string> temp_use_list;
        usecount = readInt();

        for (int i = 0; i < usecount; i++)
        {
            std::string gname = readSym();
            temp_use_list.push_back(gname);
            use_set.insert(gname);
        }

        // Third Step
        instcount = readInt();
        for (int i = 0; i < instcount; i++)
        {
            char addressmode = readIEAR();
            int operantd = readInt();
            // Double check this
            operantd = resolveAddressInstruction(addressmode, operantd, running_inst_count, temp_use_list, instcount, use_set, def_set);
            memory_map[_instruction_count] = operantd;
            _instruction_count++;
        }

        running_inst_count += instcount;

        if (use_set.size() > 0)
        {
            std::string warning = "";
            for (std::string i : use_set)
            {

                warning = warning + "Warning: Module " + std::to_string(module_number) + ": " + i + " appeared in the uselist but was not actually used\n";
            }
            memory_module_warning_map[running_inst_count - 1] = warning;
        }

        // Keep track of how many instructions we've had / which module we're in
        module_number++;
    }
    file.close();
}

void Tokenizer::getToken()
{
    token = strtok(nullptr, DELIM);

    // If we have it, great, we're continuing reading a line
    if (token && ((token != NULL) || (token != NULL)))
    {
        token_position = token - line.c_str() + 1;
        return;
    }

    // Token pointer is nullptr, meaninig we've exhausted the tokens of
    // The last line. Get a new line and see if there's anything there.
    while (!file.eof())
    {
        std::getline(file, line);
        _line_number++;
        if (!line.empty())
        {
            mutable_line = const_cast<char *>(line.c_str());
            token = strtok(mutable_line, DELIM);
            token_position = token - line.c_str() + 1;
            return;
        }
    }
    return;
}

int Tokenizer::readInt()
{
    getToken();
    if (!token)
    {
        return 0;
    }
    int temp = atoi(token);
    if (*token == '0')
    {
        return 0;
    }
    if ((temp == 0) || (temp >= (std::pow(2, 30))))
    {
        _parseerror(0);
        parse_error_flag = true;
        return 0;
    }
    last_successful_line = _line_number;
    return temp;
}

char Tokenizer::readIEAR()
{
    getToken();
    if (!token)
    {
        parse_error_flag = true;
        _parseerror(2);
        return 'X';
    }

    switch (*token)
    {
    case 'I':
        last_successful_line = _line_number;
        return *token;
    case 'E':
        last_successful_line = _line_number;
        return *token;
    case 'A':
        last_successful_line = _line_number;
        return *token;
    case 'R':
        last_successful_line = _line_number;
        return *token;
    default:
        _parseerror(2);
        parse_error_flag = true;
    }
    return 'X';
}
std::string Tokenizer::readSym()
{
    getToken();

    if (!token)
    {
        parse_error_flag = true;
        _parseerror(1);
        return "X";
    }
    if (validSymbol())
    {
        std::string gname = token;
        last_successful_line = _line_number;
        return gname;
    }
    _parseerror(1);
    parse_error_flag = true;
    return "X";
}

bool Tokenizer::validSymbol()
{
    int len = 1;
    char *temp = token;
    if (isalpha(*temp) == 0)
    {
        return 0;
    }
    temp++;
    while (*temp)
    {
        if (isalnum(*temp) == 0)
        {
            parse_error_flag = true;
            _parseerror(1);
            return 0;
        }

        if (len > 16)
        {
            parse_error_flag = true;
            _parseerror(3);
            return 0;
        }
        temp++, len++;
    }
    return 1;
}
void Tokenizer::printMemoryMap()
{
    std::cout << "Memory Map" << std::endl;
    if (memory_map.size() > 0)
    {
        for (auto item = memory_map.begin(); item != memory_map.end(); item++)
        {
            int inst_number = item->first;
            int addr = item->second;
            int error_flag = error_map.count(inst_number);
            int module_warning_flag = memory_module_warning_map.count(inst_number);
            if ((error_flag > 0) && (module_warning_flag > 0))
            {
                // Print out module warning after message + error
                const char *error_message = error_map[inst_number].c_str();
                printf("%03d: %04d %s \n", inst_number, addr, error_message);
                std::string warning = memory_module_warning_map[inst_number];
                printf("%s", warning.c_str());
            }
            else if (error_flag > 0)
            {
                // print out memory map item, then warning
                const char *error_message = error_map[inst_number].c_str();
                printf("%03d: %04d %s \n", inst_number, addr, error_message);
            }
            else if (module_warning_flag > 0)
            {
                // Print memory map item combo, then new line, then warning
                printf("%03d: %04d\n", inst_number, addr);
                std::string warning = memory_module_warning_map[inst_number];
                printf("%s", warning.c_str());
            }
            else
            {
                // Default case just memory item combo
                printf("%03d: %04d\n", inst_number, addr);
            }
        }
    }
    if (global_def_set.size() > 0)
    {
        for (std::string sym : global_def_set)
        {
            int temp_module_number = module_map[sym];
            printf("Warning: Module %d: %s was defined but never used\n", temp_module_number, sym.c_str());
        }
    }
}

void Tokenizer::printSymbolTable()
{
    std::cout
        << "Symbol Table" << std::endl;
    if (symbol_map.size() > 0)
    {
        for (auto item = symbol_map.begin(); item != symbol_map.end(); item++)
        {
            std::string sym = item->first;
            int value = item->second;

            int warning_count = warning_map.count(sym);
            if (warning_count > 0)
            {
                std::string warning = warning_map[sym];
                printf("%s=%d %s\n", sym.c_str(), value, warning.c_str());
            }
            else
            {
                printf("%s=%d \n", sym.c_str(), value);
            }
        }
    }
}

int Tokenizer::resolveAddressInstruction(char instruction_type, int instruction, int prior_instructions, std::vector<std::string> &temp_use_list, int module_size, std::set<std::string> &use_set, std::set<std::string> &def_set)
{
    int opcode = instruction / 1000;
    int operand = instruction % 1000;

    // If an illegal immediate value (I) is encountered (i.e. >= 10000), print an error and convert the value to 9999.
    if ((instruction_type == 'I') && (opcode >= 10))
    {
        error_map[_instruction_count] = "Error: Illegal immediate value; treated as 9999";
        return 9999;
    }

    if (opcode >= 10)
    {
        error_map[_instruction_count] = "Error: Illegal opcode; treated as 9999";
        return 9999;
    }
    if (opcode == 'I')
    {
        if (opcode > 10)
        {
            operand = 999;
            opcode = 9;
        }
        error_map[_instruction_count] = "Error: Illegal immediate value; treated as 9999";
    }

    // A: operand is an absolute address which will never be changed in pass2; however it can’t be “>=” the machine size (512);
    if (instruction_type == 'A')
    {
        if (operand > 512)
        {
            operand = 0;
            error_map[_instruction_count] = "Error: Absolute address exceeds machine size; zero used";
        }
    }

    // R: operand is a relative address in the module which is relocated by replacing the relative address with
    // the absolute address of that relative address after the module’s global address has been determined
    // (absolute_addr = module_base+relative_addr).
    if (instruction_type == 'R')
    {
        if (operand > module_size)
        {
            error_map[_instruction_count] = "Error: Relative address exceeds module size; zero used";
            operand = prior_instructions;
        }
        else
        {
            operand += prior_instructions;
        }
    }
    if (instruction_type == 'E')
    {
        // Operand tells us index of use list
        // Use_list[index] maps to a symbol
        // Use the symbol map to find where it needs to point
        if ((operand > 16) || (operand + 1 > temp_use_list.size()))
        {
            error_map[_instruction_count] = "Error: External address exceeds length of uselist; treated as immediate";
        }
        else
        {
            // Get symbol from use list using index
            std::string symbol = temp_use_list[operand];
            // Retrieve the associated relevant address / change operand
            if (symbol_map.count(symbol) > 0)
            {
                operand = symbol_map[symbol];
                // Pop from use list set as not to generate any warnings
                use_set.erase(symbol);
                def_set.erase(symbol);
                global_def_set.erase(symbol);
            }
            else
            {
                error_map[_instruction_count] = "Error: " + symbol + " is not defined; zero used";
                use_set.erase(symbol);
                def_set.erase(symbol);
                global_def_set.erase(symbol);
                operand = 0;
            }
        }
    }

    int new_instruction = (opcode * 1000) + operand;
    return new_instruction;
}

void Tokenizer::_parseerror(int errcode)
{
    static const char *errstr[] = {
        "NUM_EXPECTED",           // Number expect, anything >= 2^30 is not a number either
        "SYM_EXPECTED",           // Symbol Expected
        "ADDR_EXPECTED",          // Addressing Expected which is A/E/I/R
        "SYM_TOO_LONG",           // Symbol Name is too long
        "TOO_MANY_DEF_IN_MODULE", //>16
        "TOO_MANY_USE_IN_MODULE", // > 16
        "TOO_MANY_INSTR"          // total num_instr exceeds memory size (512)
    };
    std::string error_to_print = errstr[errcode];
    if (file.eof())
    {
        // Super janky workaround to get offset of last good instruction if EOF
        file.close();
        file.open(_fpath, std::ifstream::in);
        int counter = 0;
        for (int i = 0; i < (_line_number - 1); i++)
        {
            std::getline(file, line);
            counter++;
        }
        int final_position = line.length() + 1;

        printf("Parse Error line %d offset %d: %s\n", counter, final_position, error_to_print.c_str());
    }
    else
    {
        printf("Parse Error line %d offset %d: %s\n", _line_number, token_position, error_to_print.c_str());
    }

    parse_error_flag = true;
}