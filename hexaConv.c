#include "hexaConv.h"

const tradHex T[TAILLEMAX]={
	{"ADD",0x20},{"ADDI",0x8},{"AND",0X24},{"BEQ",0X4},{"BGTZ",0X7},
	{"BLEZ",0X6},{"BNE",0X5},{"DIV",0X1A},{"J",0X2},{"JAL",0X3},
	{"JR",0X8},{"LUI",0XF},{"LW",0X23},{"MFHI",0X10},{"MFLO",0X12},
	{"MULT",0X18},{"NOP",0X0},{"OR",0X25},{"ROTR",0X2},{"SLL",0X0},
	{"SLT",0X2A},{"SRL",0X2},{"SUB",0X22},{"SW",0X2B},{"SYSCALL",0XC},
	{"XOR",0X26}
};

int typeRToHex(char opcode[], int rs, int rt, int rd, int sa)
{
	int hexOp = opcodeToHexa(opcode);
	int hexInstr = 0;
	hexInstr += rs << 21;
	hexInstr += rt << 16;
	hexInstr += rd << 11;
	hexInstr += sa << 6;
	hexInstr += hexOp;
	return hexInstr;
}

int typeIToHex(char opcode[], int rs, int rt, int imm)
{
	int hexOp = opcodeToHexa(opcode);
	int hexInstr = 0;
	hexInstr += hexOp << 26;
	hexInstr += rs << 21;
	hexInstr += rt << 16;
	hexInstr += imm;
	return hexInstr;
}

int typeJToHex(char opcode[], int target)
{
	int hexOp = opcodeToHexa(opcode);
	int hexInstr = 0;
	hexInstr += hexOp << 26;
	hexInstr += target;
	return hexInstr;
}

int opcodeToHexa(char opcode[])
{
	int k;
	/*Je rentre dans dichotomie avec le mot, 
	la valeur de début ici 26 et de fin ici 0, 
	et j'y rentre n qui represente le nombre de tour max nécessaire si on ne trouve pas le mot*/
	k = dichotomie(opcode,TAILLEMAX,0,4);
	return k;
}

int dichotomie(char opcode[], int debut,int fin,int n){
	if (n!=0){
		if (strcmp(opcode,T[(debut-fin)/2].name)==0){
			return(debut-fin)/2;
		}else if (strcmp(opcode,T[(debut-fin)/2].name)<0){
			return dichotomie(opcode,(debut-fin)/2,fin,n-1);
		}else{
			return dichotomie(opcode,debut,(debut-fin)/2,n-1);
		}
	}else{
		return -1;
	}
}
