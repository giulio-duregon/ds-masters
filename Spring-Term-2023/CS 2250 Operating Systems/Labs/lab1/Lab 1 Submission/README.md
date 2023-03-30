# OS-Lab1 - Linker - Giulio Duregon - gjd9961

## How to run `linker`
**Short answer: run `make` from the CLI.**
My code uses the gcc compiler with the following flags:
```c++
CXX=g++
CXXFLAGS=-g -std=c++11 -Wall -pedantic -lstdc++
BIN=linker
```
If running on linserv1, make sure to load in gcc version 9.2.0:

```bash
> module load gcc-9.2.0
> module unload gcc-4.8.5 # Unload the old version
```

To run `linker`, simply call the executible with the input file you would like it to run on:
```bash
# How to run:
> ./linker <your_input_file_name>
# i.e.
> ./linker input-1.txt 
```

## Dependencies
`linker.cpp` has two dependencies: `tokenizer.h` and `tokenizer.cpp`. `tokenizer.h` is the header file containing the linker class's public and private instance variable / methods, while `tokenizer.cpp` contains the implementation.

## Quick Notes:
This program is a complete mess and held together by duct tape to implement the various error/warning checking logic. It's my first project using the c++ coding language, and as such many things are done in an unoptimal fashion. One flaw of the program is that it uses more memory than it needs: several data structures are included in the tokenizer class that exclusively hold error/warning message strings such that they get output at the correct location (not tokens! not breaking any rules here...)

Ideally I would have written a smarter algorithm to check for the correct errors in the correct location, and have them output then and there and not hold them in memory to be output to `std::cout` at a later time. Unfortunately, I did not feel like this was possible without refactoring a ton of spaghetti code, and after hours of debugging, I decided this was good enough as my first c++ project.