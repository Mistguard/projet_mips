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
	execInstr(&inst3, &regs, mem);


	printRegisters(&regs);


	return 0;
}