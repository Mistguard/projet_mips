#ifndef READINSTR_H
#define READINSTR_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hexaConv.h"
#include "exeInstr.h"
#include "memoryOps.h"

void decodeProg(char nomFichier1[], instrList* prog);
void readLine(char line[30], Instrct* nouv);
void whatIsWord(char mot[], char oppcode[], int* r1, int* r2, int* r3, int* imm, char* offBase, int i, int *rNb);
void identifyRegister(char oppcode[], int r1, int r2, int r3, int value, int* rd, int* rs, int* rt, int* imm, char* offBase, int* sa, int* target);
int idInstrType(char oppcode[]);
void printInstrLoaded ( char instr[],int hexa,int pc);

#endif