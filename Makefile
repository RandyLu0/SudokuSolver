main: main.o funcs.o
	g++ -o main main.o funcs.o

main.o: main.cpp

funcs.o: funcs.cpp funcs.h

clean:
	rm -f main.o funcs.o