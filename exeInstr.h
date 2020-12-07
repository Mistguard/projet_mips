#ifndef EXEINSTR_H
#define EXEINSTR_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    char opcode;
    int rd;
    int rs;
    int rt;
    int im; // sa == target == offset
}Instrct;

void execInstr(Instrct* instr, int[] regs, int[] mem);

#endif