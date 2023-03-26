#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#ifndef TOKENIZER_H
#define TOKENIZER_H

const char _DELIM[] = "  \t \n";
class Tokenizer
{
private:
    // Necessary for instantiation
    const char *DELIM = _DELIM;
    std::string _fpath;
    std::ifstream file;
    std::string line;

    // Keep track of location within file placement
    int _line_number = 0;
    int _instruction_count = 0;
    int token_position;
    int last_successful_line;

    // Poiners necessary for parsing
    char *mutable_line;
    char *token;

    // Constant (for style)
    const int MAX_WORDS = 512;

    // Containers for storing symbol/memory/warnings to output
    std::map<std::string, int> symbol_map;
    std::map<int, int> memory_map;
    std::map<int, std::string> error_map;
    std::map<std::string, std::string> warning_map;
    std::map<int, std::string> memory_module_warning_map;
    std::set<std::string> global_def_set;
    std::map<std::string, int> module_map;

public:
    bool parse_error_flag = false;
    // Object Constructor
    Tokenizer(std::string fpath);

    // Setter for _fpath private variable - used in constructor
    void setFpath(std::string fpath);

    // First pass behavior abstracted into a single function
    void firstPass();
    void secondPass();

    // Token retrieval function
    void getToken();

    // Core functionality: Read in specific tokens, all call getToken()
    int readInt();
    char readIEAR();
    std::string readSym();

    // Helper functions
    bool validSymbol();
    int resolveAddressInstruction(char instruction, int address, int prior_instructions, std::vector<std::string> &temp_use_list, int module_size, std::set<std::string> &use_set, std::set<std::string> &def_set);
    void _parseerror(int errcode);

    // Output functions
    void printSymbolTable();
    void printMemoryMap();
};
#endif