#include "readInstr.h"

int main(int argc, char *argv[])
{
	int memoireRegistre[32];
	/* ici on récupère le nom du fichier a lire lors de l'execution de la commande dans l'invité de commande grace a argv[]*/
	lireEnreDonnees(argv[1],argv[2]);
	return 0;
}