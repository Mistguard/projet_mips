#include "hexaConv.h"
#include "readInstr.h"


int typeRToHex(char opcode[], int rs, int rt, int rd, int sa)
{
	int hexOp = opcode(opcode);
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
	int hexOp = opcode(opcode);
	int hexInstr = 0;
	hexInstr += hexOp << 26;
	hexInstr += rs << 21;
	hexInstr += rt << 16;
	hexInstr += imm;
	return hexInstr;
}

int typeJToHex(char opcode[], int target)
{
	int hexOp = opcode(opcode);
	int hexInstr = 0;
	hexInstr += hexOp << 26;
	hexInstr += target;
	return hexInstr;
}

int opcodeToHexa(char opcode[])
{
	
	return 0;
}

/*
void inAtoHex(char inst[], int hexa)
{
	int l = strlen(inst);

	if(strstr(inst,"ADD ")){
		hex = ADD;
		hex += atoi(strchr(inst,' ')+1);
	}else if(strstr(inst, "ADDI ")){
		hex = ADDI << 26;
		hex += atoi(strchr(inst,' ')+1);
	}else if(strstr(inst, "AND ")){
		hex = AND;
		hex += atoi(strchr(inst,' ')+1);
	}
}

void inBtoHex(char inst[], int hexa)
{
	int l = strlen(inst);

	if(strstr(inst,"BEQ ")){
		hex = BEQ << 26;
		hex += atoi(strchr(inst,' ')+1);
	}else if(strstr(inst, "BGTZ" )){
		hex = BGTZ << 26;
		hex += atoi(strchr(inst,' ')+1);
	}else if(strstr(inst, "BLEZ ")){
		hex = BLEZ << 26;
		hex += atoi(strchr(inst,' ')+1);
	}else if(strstr(inst, "BNE ")){
		hex = BNE << 26;
		hex += atoi(strchr(inst,' ')+1);
	}
}

void inDtoHex(char inst[], int hexa)
{
	int l = strlen(inst);

	if(strstr(inst,"DIV ")){
		hex = DIV;
		hex += atoi(strchr(inst,' ')+1);
	}
}

void inJtoHex(char inst[], int hexa);
{
	int l = strlen(inst);

	if(strstr(inst,"JAL ")){
		hex = JAL << 26;
		hex += atoi(strchr(inst,' ')+1);
	}else if(strstr(inst, "J ")){
		hex = J << 26;
		hex += atoi(strchr(inst,' ')+1);
	}else if(strstr(inst, "JR ")){
		hex = JR;
		hex += atoi(strchr(inst,' ')+1);
	}
}

void inLtoHex(char inst[], int hexa)
{
	int l = strlen(inst);

	if(strstr(inst,"LUI ")){
		hex = LUI << 26;
		hex += atoi(strchr(inst,' ')+1);
	}else if(strstr(inst, "LW ")){
		hex = LW << 26;
		hex += atoi(strchr(inst,' ')+1);
	}
}

void inMtoHex(char inst[], int hexa)
{
	int l = strlen(inst);

	if(strstr(inst,"MFHI ")){
		hex = MFHI;
		hex += atoi(strchr(inst,' ')+1);
	}else if(strstr(inst, "MFLO ")){
		hex = MFLO;
		hex += atoi(strchr(inst,' ')+1);
	}else if(strstr(inst, "MULT ")){
		hex = MULT;
		hex += atoi(strchr(inst,' ')+1);
	}
}

void inNtoHex(char inst[], int hexa)
{
	int l = strlen(inst);

	if(strstr(inst,"NOP ")){
		hex = NOP;
		hex += atoi(strchr(inst,' ')+1);
	}
}

void inOtoHex(char inst[], int hexa)
{
	int l = strlen(inst);

	if(strstr(inst,"OR ")){
		hex = OR;
		hex += atoi(strchr(inst,' ')+1);
	}
}

void inRtoHex(char inst[], int hexa)
{
	int l = strlen(inst);

	if(strstr(inst,"ROTR ")){
		hex = ROTR;
		hex += atoi(strchr(inst,' ')+1);
	}
}

void inStoHex(char inst[], int hexa)
{
	int l = strlen(inst);

	if(strstr(inst,"SLL ")){
		hex = SLL;
		hex += atoi(strchr(inst,' ')+1);
	}else if(strstr(inst, "SLT ")){
		hex = SLT;
		hex += atoi(strchr(inst,' ')+1);
	}else if(strstr(inst, "SRL ")){
		hex = SRL;
		hex += atoi(strchr(inst,' ')+1);
	}else if(strstr(inst, "SUB ")){
		hex = SUB;
		hex += atoi(strchr(inst,' ')+1);
	}else if(strstr(inst, "SW ")){
		hex = SW << 26;
		hex += atoi(strchr(inst,' ')+1);
	}else if(strstr(inst, "SYSCALL ")){
		hex = SYSCALL;
		hex += atoi(strchr(inst,' ')+1);
	}
}

void inXtoHex(char inst[], int hexa)
{
	int l = strlen(inst);

	if(strstr(inst,"XOR ")){
		hex = XOR;
		hex += atoi(strchr(inst,' ')+1);
	}
}
*/


