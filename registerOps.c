#include "registerOps.h"

/*
	Cette procédure permet d'afficher les valeurs des 32 registres principaux ainsi que des deux registres HIGH et LOW
	Paramètre :
		- regs 	: GPR*	structure union contenant nos registres
*/
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

/*
	Cette procédure permet d'initialiser notre structure contenant nos registres.
	On initialise tous les contenus à 0
	Paramètre :
		- regs 	: GPR*	structure union contenant nos registres
*/
void initialyzeGPR(GPR* regs)
{
	for (int i = 0; i < 35; ++i)
	{
		regs->tReg[i] = 0;
	}
}
