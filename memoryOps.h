#ifndef MEMORYOPS_H
#define MEMORYOPS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define CAPACITY 10

struct instrList{
	Instrct* list;
	int size;
	int capa;
};

typedef struct instrList instrList;

char readMemory(int adresse);
void writeMemory(int adresse, char block);

#endif