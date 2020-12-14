#include <stdio.h>
#include <stdlib.h>

#include "readInstr.h"
#include "registerOps.h"
#include "exeInstr.h"
#include "hexaConv.h"
#include "memoryOps.h"

int main(int argc, char *argv[])
{
	/* Initialisation de la mémoire principale */
	int mem[16] = {0};

	/* Initialisation de la mémoire des registres */
	GPR regs;
	initialyzeGPR(&regs);

	printf("\n\t\t\t\t******* MIPS EMMULATOR *******\n\n");
	printf("CS351 : TOURNABIEN Alan, POLO Etienne\n\n");

	if(argc > 1)
	{
		/* Initialisation de la mémoire des instructions */
		instrList prog;
		prog.list = (Instrct*)malloc(CAPACITY*sizeof(Instrct));
		prog.size = 0;
		prog.capa = CAPACITY;

		printf("Assembling file : %s\n", argv[1]);
		printf("Output will be writtent in instruction_tests/fichierRes.txt\n");
		printf("\n*** Text segment loaded - Ready to execute *** \n\n");

		decodeProg(argv[1], &prog);
		printf("\n\n*** Starting program execution ***\n\n\n");

		while(regs.mReg.pc < prog.size)
		{
			printf("---> Processing instruction:\n%08X\t%s\n",prog.list[regs.mReg.pc].hexa, prog.list[regs.mReg.pc].fullInst);
			execInstr(&prog.list[regs.mReg.pc], &regs, mem);
			regs.mReg.pc++;
			if(argc > 2){
				if(strcmp(argv[2],"-pas") == 0){
					printRegisters(&regs);
					printMemory(mem, 16);
					getchar();
				}
			}
		}

		printf("*** Final register states: ***\n\n");
		printRegisters(&regs);
		printf("\n*** Final memory state: ***\n\n");
		printMemory(mem, 16);

		free(prog.list);
	}else{
		char ans[30];
		Instrct inst = {0};
		while(strcmp(ans,"exit\n") != 0)
		{
			printf("*** Waiting for instruction to execute ***\n");
			printf("(Be aware that only sequencial instructions are allowed)\n");
			fgets(ans, 30, stdin);
			if(strcmp(ans,"exit\n") != 0){
				readLine(ans, &inst);
				execInstr(&inst, &regs, mem);
				regs.mReg.pc++;

				printf("\n*** Register states: ***\n\n");
				printRegisters(&regs);
				printf("\n*** Memory state: ***\n\n");
				printMemory(mem, 16);
			}
		}
	}
	return 0;
}

