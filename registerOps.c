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
	printf("*** Final register states: ***\n");
	for (int i = 0; i < 32; ++i)
	{
		printf("Reg %d => %u\n",i,regs->tReg[i]);
	}
}

void initialyzeGPR(GPR* regs)
{
	for (int i = 0; i < 35; ++i)
	{
		regs->tReg[i] = 0;
	}
}
