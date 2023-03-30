CXX=g++
CXXFLAGS=-std=c++11 -Wall -pedantic -lstdc++
BIN=gjd9961.calc

all: 
	g++  util.h -o util.o
	g++ -std=c++11  MemoryMap.h -o MemoryMap.o
	bison -d $(BIN).y 
	flex $(BIN).l 
	$(CXX) $(CXXFLAGS) lex.yy.c $(BIN).tab.c -o $(BIN)

clean: 
	rm -f *.o
	rm $(BIN)