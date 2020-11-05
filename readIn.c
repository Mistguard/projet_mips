#include "readIn.h"
#include "hexaConv.h"

void inJtoHex(char in[], int hexa)
{
	int l = strlen(in);

	if(strstr(in,"JAL")){
		hex = JAL << 26;
		hex += atoi(strchr(in,' ')+1);
	}else if(strstr(in, "J ")){
		hex = J << 26;
		hex += atoi(strchr(in,' ')+1);
	}
}

void inItoHex(char in[], int hexa)
{
	
}

void inRtoHex(char in[], int hexa)
{

}