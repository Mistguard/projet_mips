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

	/* Affichage de l'en-tête */
	printf("\n\t\t\t\t******* MIPS EMMULATOR *******\n\n");
	printf("CS351 : TOURNABIEN Alan, POLO Etienne\n\n");

	/* Si il y a plus qu'un seul argument */
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

		/* On décode notre programme et on écrit dans le fichier de sortie le programme en hexa et dans notre mémoire d'instruction les instructions du programme */
		decodeProg(argv[1], &prog);
		printf("\n\n*** Starting program execution ***\n\n\n");

		/* Tant qu'on est pas arrivé au bout du programme */
		while(regs.mReg.pc < prog.size)
		{
			printf("---> Processing instruction:\n%08X\t%s\n",prog.list[regs.mReg.pc].hexa, prog.list[regs.mReg.pc].fullInst);
			/* On execute l'instruction courante */
			execInstr(&prog.list[regs.mReg.pc], &regs, mem);
			/* Et on passe à l'instruction suivante */
			regs.mReg.pc++;
			/* Si on est en mode pas à pas on affiche l'état actuel des registres et de la mémoire puis on attend l'entrée utilisateur pour continuer */
			if(argc > 2){
				if(strcmp(argv[2],"-pas") == 0){
					printRegisters(&regs);
					printMemory(mem, 16);
					printf("(Appuyez sur n'importe quelle touche pour continuer l'exécution)\n");
					getchar();
				}
			}
		}
		/* On affiche l'état finale des registres et de la mémoire */
		printf("*** Final register states: ***\n\n");
		printRegisters(&regs);
		printf("\n*** Final memory state: ***\n\n");
		printMemory(mem, 16);

		free(prog.list);
	}
	/* Sinon c'est qu'en est en mode interactif */
	else{
		char ans[30];
		Instrct inst = {0};
		/* Tant que l'utilisateur n'écrit pas 'exit' */
		while(strcmp(ans,"exit\n") != 0)
		{
			printf("*** Waiting for instruction to execute ***\n");
			printf("(Be aware that only sequencial instructions are allowed)\n");
			fgets(ans, 30, stdin);
			/* On récupère l'entrée utilisateur et si ce n'est pas 'exit' */
			if(strcmp(ans,"exit\n") != 0){
				/* On décode l'instruction, on l'exécute et on attend la prochaine instruction */
				readLine(ans, &inst);
				execInstr(&inst, &regs, mem);
				regs.mReg.pc++;

				/* On affiche l'état actuel des registres et de la mémoire */ 
				printf("\n*** Register states: ***\n\n");
				printRegisters(&regs);
				printf("\n*** Memory state: ***\n\n");
				printMemory(mem, 16);
			}
		}
	}
	
	return 0;
}

