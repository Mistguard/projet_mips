#ifndef MEMORYOPS_H
#define MEMORYOPS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "exeInstr.h"

#define CAPACITY 16

struct instrList{
	Instrct* list;
	int size;
	int capa;
};

typedef struct instrList instrList;

void printMemory(int mem[], int size);

#endif