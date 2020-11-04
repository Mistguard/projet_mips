#include "hexaConv.h"

int main(int argc, char *argv[])
{
	int nb;
	/* ici on récupère le nom du fichier a lire lors de l'execution de la commande dans l'invité de commande grace a argv[]*/
	nb = lireEnreDonnees(argv[1],argv[2]);
	printf("%d\n",nb);
	return 0;
}