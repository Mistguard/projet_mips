#ifndef HEXA_CONV_H
#define HEXA_CONV_H



#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TAILLEMAX 26

#define ADD 0x20
#define ADDI 0x8
#define AND 0X24
#define	BEQ 0X4
#define BGTZ 0X7
#define BLEZ 0X6
#define	BNE 0X5
#define DIV 0X1A
#define J 0X2
#define	JAL 0X3
#define JR 0X8
#define	LUI 0XF
#define LW 0X23
#define MFHI 0X10
#define MFLO 0X12
#define MULT 0X18
#define NOP 0X0
#define OR 0X25
#define ROTR 0X2
#define SLL 0X0
#define SLT 0X2A
#define SRL 0X2
#define SUB 0X22
#define SW 0X2B
#define SYSCALL 0XC
#define XOR 0X26

typedef struct 
{
	char* name;
	int hexa;
}tradHex;

const tradHex T[TAILLEMAX];

int typeRToHex(char opcode[], int rs, int rt, int rd, int sa);
int typeIToHex(char opcode[], int rs, int rt, int imm);
int typeJToHex(char opcode[], int target);
int opcodeToHexa(char opcode[]);
int dichotomie(char opcode[], int debut,int fin,int n);

#endif