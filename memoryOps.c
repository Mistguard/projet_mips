#include "memoryOps.h"

/*
	Cette procédure permet d'afficher les valeurs enregistrés dans la mémoire ainsi que leur adresse (ou index) en multiple de 4
	Paramètre :
		- mem 	: int[]		tableau d'entier représentant notre mémoire principal
		- size 	: int		taille de notre mémoire principale
*/
void printMemory(int mem[], int size)
{
	int k =1;
	printf("\nAddress | Value\n\n");
	for (int i = 0; i < size; ++i)
	{
		printf("@ %08d | %u\t\t", i*4, mem[i]);
		if(k%4==0){
			printf("\n");
		}
		k++;
	}
}
