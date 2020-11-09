#include "readInstr.h"

void lireEnreDonnees(char nomFichier1[],char nomFichier2[]){
	FILE * fic1;
	FILE * fic2;
	char mot[30],temp[30]={0};
	char oppcode[10];
	int r1, r2, r3, value;
	int rd, rs, rt, imm, offset, target, sa;
	int i = 0, rNb = 0;
	/* Ouverture du fichier */
	fic1 = fopen(nomFichier1, "r");
	if(fic1 == NULL) {
		perror("Probleme ouverture fichier monFichier.txt");
		exit(1);
	}

	fic2 = fopen(nomFichier2, "r+") ;
	/* Lecture dans le fichier */
	while(!feof(fic1)) {
		fscanf(fic1, "%s", mot);
		/*On evite la répétion de la dernière ligne*/
		if(strcmp(temp,mot)!=0){
			/*Pour avoir un affichage et une écriture en ligne et non coupé sur 2 lignes*/
			strcpy(temp,mot);
			if (i%2==0){
				printf("%s ",mot );
				fprintf(fic2, "%s ", mot) ;
			}else{
				printf("%s\n",mot);
				fprintf(fic2, "%s\n", mot) ;
			}
			whatIsWord(mot,oppcode,&r1,&r2,&r3,&value,i,&k);
			i++;
		}else{
			i++;
		}

	}
	/* Fermeture du fichier */
	fclose(fic1);
	fclose(fic2);
}

void whatIsWord(char mot[], char oppcode[], int* r1, int* r2, int* r3, int* imm, int i, int *rNb){
   //Baby don't 
   //Hurt me
	if(i==0){
		oppcode = mot;
	}else{
		if(mot[0]=='$'){
			switch(rNb)
			{
				case 0:
					r1 = atoi(mot+1);
					break;
				case 1:
					r2 = atoi(mot+1);
					break;
				case 2:
					r3 = atoi(mot+1);
					break;
				default:
					break;
			}
			rNb++;
		}else{
				imm = atoi(mot);
		}
	}
	if(rNb > 2){
		rNb = 0;
	}
}

void identifyRegister(char oppcode[], int* r1, int* r2, int* r3, int* value, int* rd, int* rs, int* rt, int* imm, int* offset, int* sa, int* target)
{
	if((strcmp(oppcode,"ADD")==0) || strcmp(oppcode,"AND")==0 || strcmp(oppcode,"OR")==0 || strcmp(oppcode,"SLT")==0 || strcmp(oppcode,"SUB")==0 || strcmp(oppcode,"XOR")==0){
		rd = r1;
		rs = r2;
		rt = r3;
	}else if (strcmp(oppcode,"LW")==0 || strcmp(oppcode,"SW")==0 )
	{
		rt = r1;
		offset = value;
	}else if (strcmp(oppcode,"ROTR")==0 || strcmp(oppcode,"SLL")==0 || strcmp(oppcode,"SRL")==0)
	{
		rd = r1;
		rt = r2;
		sa = value;
	}else if (strcmp(oppcode,"DIV")==0 || strcmp(oppcode,"MUL")==0)
	{
		rs = r1;
		rt = r2;
	}else if (strcmp(oppcode,"MFHI")==0 || strcmp(oppcode,"MFLO")==0)
	{
		rd = r1;
	}else if (strcmp(oppcode,"LUI")==0)
	{
		rt = r1;
		imm = value;
	}else if (strcmp(oppcode,"JR")==0)
	{
		rs = r1;
	}else if (strcmp(oppcode,"J")==0 || strcmp(oppcode,"JAL")==0)
	{
		target = value;
	}else if (strcmp(oppcode,"BEQ")==0 || strcmp(oppcode,"BNE")==0 || )
	{
		rs = r1;
		rt = r2;
		offset = value;
	}else if (strcmp(oppcode,"BGTZ")==0 || strcmp(oppcode,"BLEZ")==0)
	{
		rs = r1;
		offset = value;
	}
}

int idInstrType(char oppcode[])
{
	if((strcmp(oppcode,"ADD")==0) ||(strcmp(oppcode,"AND")==0) ||(strcmp(oppcode,"DIV")==0) ||(strcmp(oppcode,"MFHI")==0) 
	||(strcmp(oppcode,"MFLO")==0) ||(strcmp(oppcode,"MULT")==0) ||(strcmp(oppcode,"NOP")==0) ||(strcmp(oppcode,"OR")==0) 
	||(strcmp(oppcode,"ROTR")==0) ||(strcmp(oppcode,"SLL")==0) ||(strcmp(oppcode,"SLT")==0) ||(strcmp(oppcode,"SRL")==0) 
	||(strcmp(oppcode,"SUB")==0) ||(strcmp(oppcode,"XOR")==0) ||(strcmp(oppcode,"JR")==0) ||(strcmp(oppcode,"NOP")==0)){
		return 1;
	}else if ((strcmp(oppcode,"ADDI")==0) ||(strcmp(oppcode,"BEQ")==0) ||(strcmp(oppcode,"BGTZ")==0) ||(strcmp(oppcode,"BLEZ")==0) ||
	(strcmp(oppcode,"BNE")==0) ||(strcmp(oppcode,"LUI")==0) ||(strcmp(oppcode,"LW")==0) ||(strcmp(oppcode,"SW")==0))
	{
		return 2;
	}
	else if ((strcmp(oppcode,"J")==0) || (strcmp(oppcode,"JAL")==0) ||)
	{
		return 3;
	}else
	{
		return -1;
	}
		
}