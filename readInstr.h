#ifndef READINSTR_H
#define READINSTR_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hexaConv.h"
#include "exeInstr.h"
#include "memoryOps.h"

void decodeProg(char nomFichier1[],char nomFichier2[], instrList* prog);
void whatIsWord(char mot[], char oppcode[], int* r1, int* r2, int* r3, int* imm, int i, int *rNb);
void identifyRegister(char oppcode[], int r1, int r2, int r3, int value, int* rd, int* rs, int* rt, int* imm, int* sa, int* target);
int idInstrType(char oppcode[]);
void printPresentation (char nameOpenFolder[],char nameOutputFolder[]);
void printInstrLoaded ( char instr[],int hexa,int pc);

#endif