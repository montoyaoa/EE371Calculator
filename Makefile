all: main

SRC= region.cpp
OBJ= $(SRC:.cpp=.o)
HDR= $(SRC:.cpp=.hpp)

main: main.cpp main.o $(OBJ)
	g++ -o $@ main.o $(OBJ)

clean:
	rm -f *.o main
