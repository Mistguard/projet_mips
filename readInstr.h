#ifndef READINSTR_H
#define READINSTR_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hexaConv.h"
#include "exeInstr.h"

void lireEnreDonnees(char nomFichier1[],char nomFichier2[]);
void whatIsWord(char mot[], char oppcode[], int* r1, int* r2, int* r3, int* imm, int i, int *rNb);
void identifyRegister(char oppcode[], int r1, int r2, int r3, int value, int* rd, int* rs, int* rt, int* imm, int* sa, int* target);
int idInstrType(char oppcode[]);

#endif