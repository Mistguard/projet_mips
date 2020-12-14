#include "readInstr.h"
#include "registerOps.h"
#include "exeInstr.h"
#include "hexaConv.h"
#include "memoryOps.h"

int main(int argc, char *argv[])
{
	/* Initialisation de la mémoire principale */
	int mem[16] = {0};

	/* Initialisation de la mémoire des instructions */
	instrList prog;
	prog.list = (Instrct*)malloc(CAPACITY*sizeof(Instrct));
	prog.size = 0;
	prog.capa = CAPACITY;

	/* Initialisation de la mémoire des registres */
	GPR regs;
	initialyzeGPR(&regs);

	printf("\n\t\t\t\t*** MIPS EMMULATOR ***\n\n");
	printf("CS351 : TOURNABIEN Alan, POLO Etienne\n\n");
	printf("Assembling file : %s\n", argv[1]);
	printf("Output will be writtent in instruction_tests/fichierRes.txt\n");
	printf("\n*** Text segment loaded - Ready to execute *** \n\n");

	if (argv[1] == NULL){
		decodeProg("\n", &prog);
	}else{
	/* ici on récupère le nom du fichier a lire lors de l'execution de la commande dans l'invité de commande grace a argv[] */
		decodeProg(argv[1], &prog);
		printf("\n\n*** Starting program execution ***\n\n\n");

		while(regs.mReg.pc < prog.size)
		{
			printf("Processing instruction:\n%08X\t%s\n\n",prog.list[regs.mReg.pc].hexa, prog.list[regs.mReg.pc].fullInst);
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
	}

	

	printf("\n*** Final register states: ***\n\n");
	printRegisters(&regs);
	printf("\n*** Final memory state: ***\n\n");
	printMemory(mem, 16);

	free(prog.list);

	return 0;
}

/* Quelques tests
	Instrct inst1;
	inst1.oppcode = ADDI;
	inst1.rd = 0;
	inst1.rs = 0;
	inst1.rt = 2;
	inst1.imm = 218015;
	inst1.type = 'I';

	Instrct inst2;
	inst2.oppcode = ADDI;
	inst2.rd = 0;
	inst2.rs = 0;
	inst2.rt = 3;
	inst2.imm = 13;
	inst2.type = 'I';

	Instrct inst3;
	inst3.oppcode = JR;
	inst3.rd = 1;
	inst3.rs = 3;
	inst3.rt = 4;
	inst3.imm = 20;
	inst3.type = 'R';
	

	execInstr(&inst1, &regs, mem);
	execInstr(&inst2, &regs, mem);
	execInstr(&inst3, &regs, mem);*/
