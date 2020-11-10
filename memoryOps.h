#ifndef MEMORYOPS_H
#define MEMORYOPS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char readMemory(int adresse);
void writeMemory(int adresse, char block);

#endif