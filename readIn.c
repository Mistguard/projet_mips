#include "readIn.h"
#include "hexaConv.h"

void inJtoHex(char inst[], int hexa)
{
	int l = strlen(inst);

	if(strstr(inst,"JAL")){
		hex = JAL << 26;
		hex += atoi(strchr(inst,' ')+1);
	}else if(strstr(inst, "J ")){
		hex = J << 26;
		hex += atoi(strchr(inst,' ')+1);
	}
}

void inItoHex(char inst[], int hexa)
{
	
}

void inRtoHex(char inst[], int hexa)
{

}