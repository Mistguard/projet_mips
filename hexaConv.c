#include "hexaConv.h"


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
