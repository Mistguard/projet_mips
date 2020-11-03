###############################################################
# Makefile pour le programme de simulation de processeur MIPS #
###############################################################

main : main.o matrice.o
	gcc -o main main.o matrice.o

main.o : main.c hexaConv.h
	gcc -o main.o -c main.c

hexaConv.o : hexaConv.c hexaConv.h
	gcc -c hexaConv.c -Wall -ansi -pedantic -o hexaConv.o
