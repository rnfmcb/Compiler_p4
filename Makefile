output:	main.o scanner.o parser.o stack.o runtime.o
	g++ -std=c++0x -Wall main.o scanner.o parser.o stack.o runtime.o -o input1

main.o: main.cpp
	g++ -c main.cpp

scanner.o: scanner.cpp  scanner.h
	g++ -c scanner.cpp
parser.o: parser.cpp parser.h
	g++ -c parser.cpp 
stack.o: stack.cpp stack.h 
	g++ -c stack.cpp
runtime.o: runtime.cpp runtime.h 
	g++ -c runtime.cpp 
clean:
	rm *.o input1 output.asm
