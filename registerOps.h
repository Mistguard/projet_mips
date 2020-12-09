#ifndef REGISTEROPS_H
#define REGISTEROPS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    int zero;
    int at;
    int v0;
    int v1;
    int a0;
    int a1;
    int a2;
    int a3;
    int t0;
    int t1;
    int t2;
    int t3;
    int t4;
    int t5;
    int t6;
    int t7;
    int s0;
    int s1;
    int s2;
    int s3;
    int s4;
    int s5;
    int s6;
    int s7;
    int t8;
    int t9;
    int k0;
    int k1;
    int gp;
    int sp;
    int fp;
    int ra;
    int pc;
    int hi;
    int lo;
}regsCst;

typedef union
{
    int tReg[35];
    regsCst mReg;
}GPR;


int readRegister(GPR* regs, int index);
void writeRegistrer(GPR* regs, int index, int value);
void printRegisters(GPR* regs);
void initialyzeGPR(GPR* regs);

#endif