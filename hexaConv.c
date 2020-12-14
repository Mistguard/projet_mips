#include "hexaConv.h"

/* Le tableau de structure contenant les fonctions et leur valeur hexa */
const tradHex T[TAILLEMAX]={
	{"ADD",0x20},{"ADDI",0x08},{"AND",0X24},{"BEQ",0X04},{"BGTZ",0X07},
	{"BLEZ",0X06},{"BNE",0X05},{"DIV",0X1A},{"J",0X02},{"JAL",0X03},
	{"JR",0X08},{"LUI",0X0F},{"LW",0X23},{"MFHI",0X10},{"MFLO",0X12},
	{"MULT",0X18},{"NOP",0X00},{"OR",0X25},{"ROTR",0X02},{"SLL",0X00},
	{"SLT",0X2A},{"SRL",0X02},{"SUB",0X22},{"SW",0X2B},{"SYSCALL",0X0C},
	{"XOR",0X26}
};

/*
	Cette fonction retourne la valeur hexadecimal correspondant à une instruction de type R
	Là traduction ce fait en fonction de l'opcode, des registres rs, rt, rd et de la valeur de sa
	Paramètre :
		- opcode 	: char[]	char contenant l'opcode de l'instruction
		- rs 		: int 		entier contenant la valeur du registre rs
		- rt 		: int 		entier contenant la valeur du registre rt
		- rd 		: int 		entier contenant la valeur du registre rd
		- sa 		: int 		entier contenant la valeur du immediate sa
	Retourne un entier correspondant à la valeur hexadecimal de l'instruction de type R
*/
int typeRToHex(char opcode[], int rs, int rt, int rd, int sa)
{
	int hexOp = opcodeToHexa(opcode);
	int hexInstr = 0;
	hexInstr += rs << 21;
	if(strcmp(opcode,"ROTR")==0){
		hexInstr += 1 << 21;
	}
	hexInstr += rt << 16;
	hexInstr += rd << 11;
	hexInstr += sa << 6;
	hexInstr += hexOp;
	return hexInstr;
}

/*
	Cette fonction retourne la valeur hexadecimal correspondant à une instruction de type I
	Là traduction ce fait en fonction de l'opcode, des registres rs, rt et de la valeur de imm
	Paramètre :
		- opcode 	: char[]	char contenant l'opcode de l'instruction
		- rs 		: int 		entier contenant la valeur du registre rs
		- rt 		: int 		entier contenant la valeur du registre rt
		- imm 		: int 		entier contenant la valeur du immediate imm
	Retourne un entier correspondant à la valeur hexadecimal de l'instruction de type I
*/
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

/*
	Cette fonction retourne la valeur hexadecimal correspondant à une instruction de type J
	Là traduction ce fait en fonction l'opcode et de la valeur de imm
	Paramètre :
		- opcode 	: char[]	char contenant l'opcode de l'instruction
		- target 	: int 		entier contenant la valeur du immediate target
	Retourne un entier correspondant à la valeur hexadecimal de l'instruction de type J
*/
int typeJToHex(char opcode[], int target)
{
	int hexOp = opcodeToHexa(opcode);
	int hexInstr = 0;
	hexInstr += hexOp << 26;
	hexInstr += target;
	return hexInstr;
}

/*
	Cette fonction retourne la valeur hexadecimal correspondant à un opcode donné
	La traduction en hexa de tout les opcode est contenu dans la constante tradHex
	Paramètre :
		- opcode 	: char[]	char contenant l'opcode à traduire en hexadecimal
	Retourne un entier correspondant à la valeur hexadecimal de l'opcode
*/
int opcodeToHexa(char opcode[])
{
	int k;
	k = dichotomie(opcode,0,TAILLEMAX-1);
	return T[k].hexa;
}

/*
	Cette fonction recursive retourne permet de chercher la valeur hexadecimal de l'opcode dans le tableau tradHex
	en utilisant la méthode de recherche dichotomique.
	Paramètre :
		- opcode 	: char[]	char contenant l'opcode à traduire en hexadecimal
		- debut		: int 		entier correspondant à l'index de début du tableau
		- fin 		: int 		entier correspondant à l'index de fin du tableau
	Retourne un entier correspondant à l'index de l'hexa décimal correspondant à l'opcode
*/
int dichotomie(char opcode[],int debut,int fin)
{
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
	
