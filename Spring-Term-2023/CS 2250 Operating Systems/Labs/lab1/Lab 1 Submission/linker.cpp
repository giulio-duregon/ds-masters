#include "tokenizer.h"
#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>

int main(int argc, char *argv[])
{
    if (!argv[1])
    {
        std::cout << "Must enter a valid file name!" << std::endl;
        return 1;
    }
    std::string fname = argv[1];
    //  Initialize our tokenizer object, begin first pass
    Tokenizer tokenizer(fname);
    tokenizer.firstPass();

    // Check for parse errors - terminate program if found
    if (tokenizer.parse_error_flag)
    {
        return 1;
    }
    // Begin Second Pass
    tokenizer.secondPass();

    // Output Symbol Table, Memory Map, and Warnings
    tokenizer.printSymbolTable();
    tokenizer.printMemoryMap();
    return 0;
}