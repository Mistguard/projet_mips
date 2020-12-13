#include "readInstr.h"
#include "registerOps.h"
#include "exeInstr.h"
#include "hexaConv.h"

int main(int argc, char *argv[])
{
	/* Initialisation de la mémoire principale */
	int mem[200];

	/* Initialisation de la mémoire des instructions */
	instrList prog;
	prog.list = (Instrct*)malloc(CAPACITY*sizeof(Instrct));
	prog.size = 0;
	prog.capa = CAPACITY;

	/* Initialisation de la mémoire des registres */
	GPR regs;
	initialyzeGPR(&regs);

	printf("\t\t\t\t*** MIPS EMMULATOR ***\n\n");
	printf("CS351 : TOURNABIEN Alan, POLO Etienne\n\n");
	printf("Assembling file : %s\n", argv[1]);
	printf("Output will be writtent in hexified/%s\n",argv[2]);
	printf("\n*** Text segment loaded - Ready to execute *** \n\n");

	/* ici on récupère le nom du fichier a lire lors de l'execution de la commande dans l'invité de commande grace a argv[] */
	decodeProg(argv[1],argv[2], &prog);

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
	for (int i = 0; i < prog.size; ++i)
	{
		//printf("rs = %d rd = %d rt = %d oppcode = %d imm = %d type = %c\n",prog.list[i].rs, prog.list[i].rd, prog.list[i].rt, prog.list[i].oppcode, prog.list[i].imm, prog.list[i].type);
		execInstr(&prog.list[i], &regs, mem);
	}

	printRegisters(&regs);

	free(prog.list);

	return 0;
}