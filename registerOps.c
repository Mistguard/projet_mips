#include "registerOps.h"

int readRegister(int T[],int address){
	return T[address];
}

void writeRegistrer(int T[], int adress, int value){
	T[adress] = value;
}
