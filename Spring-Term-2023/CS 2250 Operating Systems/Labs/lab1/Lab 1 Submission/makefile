CXX=g++
CXXFLAGS=-g -std=c++11 -Wall -pedantic -lstdc++
BIN=linker

SRC=$(wildcard *.cpp)
OBJ=$(SRC:%.cpp=%.o)

all: $(OBJ)
	$(CXX) -o $(BIN) $^

%.o: %.c
	$(CXX) $@ -c $<

	
run: all
	./linker ./given_inputs/input-1

clean:
	rm -f *.o
	rm $(BIN)