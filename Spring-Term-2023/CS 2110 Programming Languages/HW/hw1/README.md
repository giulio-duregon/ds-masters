# gjd9961.calc
Prerequisites: 


Short answer: run make from the CLI. My code uses the gcc compiler with the following flags:
```make
CXX=g++
CXXFLAGS=-g -std=c++11 -Wall -pedantic -lstdc++
BIN=gjd9961.calc
```

If running on linserv1, make sure to load in gcc version 9.2.0:
``` bash
> module load gcc-9.2     # load the current version
> module unload gcc-4.8.5 # Unload the old version
```
Running instructions
```bash
# Make
> make clean && make
> ./gjd9961.calc
> (output) Enter `cli` for command line input parsing, `file` for file input parsing
> (input) file
> (output) File parsing selected, please enter a filename
> (input) gjd9961.input.txt
# This uses all the demos in the assingment
# with the exception of 2@3 that triggers a parsing error 
```

You must enter one of the two options, either `cli` or `file` when prompted. Invalid input will terminate the program. Likewise, if selecting `file` then your input file (`gjd9961.input.txt` as I used in the example) must be a valid file, otherwise the program will exit. `gjd9961.input.txt` is a working demo file included in this submission, it has all of the examples given in the homework assingment, with the exception of `2@3` as that throws a parsing error and it makes the demo look ugly.  