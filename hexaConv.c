#include "hexaConv.h"

const tradHex T[TAILLEMAX]={
	{"ADD",0x20},{"ADDI",0x08},{"AND",0X24},{"BEQ",0X04},{"BGTZ",0X07},
	{"BLEZ",0X06},{"BNE",0X05},{"DIV",0X1A},{"J",0X02},{"JAL",0X03},
	{"JR",0X08},{"LUI",0X0F},{"LW",0X23},{"MFHI",0X10},{"MFLO",0X12},
	{"MULT",0X18},{"NOP",0X00},{"OR",0X25},{"ROTR",0X02},{"SLL",0X00},
	{"SLT",0X2A},{"SRL",0X02},{"SUB",0X22},{"SW",0X2B},{"SYSCALL",0X0C},
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
	la valeur de fin ici 26 et de debut ici 0, 
	et j'y rentre n qui represente le nombre de tour max nécessaire si on ne trouve pas le mot*/
	k = dichotomie(opcode,0,TAILLEMAX-1);
	printf("Pour l'oppcode %s avec k = %d on a hexa= %X\n",T[k].name,k,T[k].hexa);
	return T[k].hexa;
}

int dichotomie(char opcode[],int debut,int fin){
	int m;
	m = (fin + debut)/2;
	if (strcmp(opcode,T[m].name)==0){
		return m;
	}else if(strcmp(opcode,T[m].name)>0){
		return dichotomie(opcode,m+1,fin);
	}else{
		return dichotomie(opcode,debut,m-1);
	}
}
	
