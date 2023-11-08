OBJ = main.o d.o nd.h

part1: $(OBJ)
	g++ -o part1.out $(OBJ)

d.o = d.cpp d.h
main.o = main.cpp d.h nd.h