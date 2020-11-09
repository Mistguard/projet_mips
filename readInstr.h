#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void lireEnreDonnees(char nomFichier1[],char nomFichier2[]);

void whatIsWord(char mot[], char oppcode[], char r1[], char r2[], char r3[], int imm, int i, int *k);

void identifyRegister(char oppcode[], int* r1, int* r2, int* r3, int* imm);

int idInstrType(char oppcode[]);