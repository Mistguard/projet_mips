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
	for (int i = 0; i < 35; ++i)
	{
		printf("Reg %d => %d\n",i,regs->tReg[i]);
	}
}

void initialyzeGPR(GPR* regs)
{
	for (int i = 0; i < 35; ++i)
	{
		regs->tReg[i] = 0;
	}
}
