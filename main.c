#include "readInstr.h"
#include "registerOps.h"
#include "exeInstr.h"
#include "hexaConv.h"

int main(int argc, char *argv[])
{
	/*int memoireRegistre[32] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	ici on récupère le nom du fichier a lire lors de l'execution de la commande dans l'invité de commande grace a argv[]
	lireEnreDonnees(argv[1],argv[2]);*/

	int mem[200];

	GPR regs;
	initialyzeGPR(&regs);

	Instrct inst1;
	inst1.oppcode = ADDI;
	inst1.rs = 0;
	inst1.imm = 4;
	inst1.rt = 2;

	execInstr(&inst1, &regs, mem);

	printRegisters(&regs);

	return 0;
}