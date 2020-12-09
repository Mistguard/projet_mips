#ifndef EXEINSTR_H
#define EXEINSTR_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "registerOps.h"
#include "hexaConv.h"

typedef struct
{
    int oppcode;
    int rd;
    int rs;
    int rt;
    int imm; // sa == target == offset
    char type;
}Instrct;

void execInstr(Instrct* instr, GPR* regs, int mem[]);

#endif