###############################################################
# Makefile pour le programme de simulation de processeur MIPS #
###############################################################

CSRC = $(wildcard *.c)
COBJ = $(CSRC:.c=.o)

all : $(COBJ)
	gcc $^ -o emul-mips 

%.o : %.c
	gcc -c $< -o $@ -Wall -ansi -pedantic --std=c11



