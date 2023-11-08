all: tests.exe main.exe

tests.exe: tests.o reconocedor_automata.o
	gcc tests.o reconocedor_automata.o -o tests
	./tests.exe

tests.o: tests.c reconocedor_automata.o
	gcc -c tests.c reconocedor_automata.o -o tests.o

reconocedor_automata.o: reconocedor_automata.c
	gcc -c reconocedor_automata.c -o reconocedor_automata.o
 
main.exe: main.o reconocedor_automata.o
	gcc main.o reconocedor_automata.o -o main

main.o: main.c reconocedor_automata.o
	gcc -c main.c reconocedor_automata.o -o main.o

clean:
	rm -rf tests.exe main.exe *.o