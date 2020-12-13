#include "registerOps.h"

int readRegister(GPR* regs, int index)
{
	return regs->tReg[index];
}

void writeRegister(GPR* regs, int index, int value)
{
	regs->tReg[index] = value;
}

void printRegisters(GPR* regs)
{
	int k =1;
	printf("*** Final register states: ***\n");
	for (int i = 0; i < 32; ++i)
	{
		if (k%4==0){
			printf("Reg %d => %u\n",i,regs->tReg[i]);
			k++;
		}else{
			printf("Reg %d => %u		",i,regs->tReg[i]);
			k++;
		}
	}
	printf("Reg HI => %u\nReg LO => %u\n",regs->tReg[33],regs->tReg[34]);
}

void initialyzeGPR(GPR* regs)
{
	for (int i = 0; i < 35; ++i)
	{
		regs->tReg[i] = 0;
	}
}
