###############################################################
# Makefile pour le programme de simulation de processeur MIPS #
###############################################################

all : main.o hexaConv.o
	gcc -o main main.o hexaConv.o

main.o : main.c hexaConv.h
	gcc -o main.o -Wall -ansi -pedantic -c main.c

hexaConv.o : hexaConv.c hexaConv.h
	gcc -c hexaConv.c -Wall -ansi -pedantic -o hexaConv.o
