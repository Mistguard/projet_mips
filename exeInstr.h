#ifndef EXEINSTR_H
#define EXEINSTR_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "registerOps.h"

typedef struct
{
    char opcode;
    int rd;
    int rs;
    int rt;
    int imm; // sa == target == offset
}Instrct;

void execInstr(Instrct* instr, GPR* regs, int[] mem);

#endif