#include "memoryOps.h"

void printMemory(int mem[], int size)
{
	int k =1;
	printf("\nAddress | Value\n\n");
	for (int i = 0; i < size; ++i)
	{
		printf("@ %08d | %u\t\t", i*4, mem[i]);
		if (k%4==0){
			printf("\n");
		}
		k++;
	}
}
