###############################################################
# Makefile pour le programme de simulation de processeur MIPS #
###############################################################

all : main.o readInstr.o hexaConv.o
	gcc -o main main.o readInstr.o hexaConv.o

main.o : main.c readInstr.h
	gcc -c main.c -Wall -ansi -pedantic --std=c11 -o main.o

readInstr.o : readInstr.c readInstr.h hexaConv.h
	gcc -c readInstr.c -Wall -ansi -pedantic --std=c11 -o readInstr.o

hexaConv.o : hexaConv.c hexaConv.h
	gcc -c hexaConv.c -Wall -ansi -pedantic --std=c11 -o hexaConv.o
