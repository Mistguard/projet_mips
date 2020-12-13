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
	for (int i = 0; i < 32; ++i)
	{
		printf("$%02d => %u\t\t", i, regs->tReg[i]);
		if (k%4==0){
			printf("\n");
		}
		k++;
	}
	printf("\nHI => %u\nLO => %u\n",regs->tReg[33],regs->tReg[34]);
}

void initialyzeGPR(GPR* regs)
{
	for (int i = 0; i < 35; ++i)
	{
		regs->tReg[i] = 0;
	}
}
