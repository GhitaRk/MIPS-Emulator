all :  fonctions.o main.o
	gcc -g fonctions.o main.o -o emul-mips -lm

fonctions.o: fonctions.c fonctions.h
	gcc -g -c fonctions.c -Wall -o fonctions.o -lm

main.o: main.c
	gcc -g -c main.c -Wall -o main.o -lm
