#include "readInstr.h"

void lireEnreDonnees(char nomFichier1[],char nomFichier2[]){
	FILE * fic1;
	FILE * fic2;

	char *word;
	char *prevWord;
	char *tmpWord;
	char *tempWord;
	int wLgth=0;
	int instrType=0;
	char line[30];

	char oppcode[10];
	int r1, r2, r3, value;
	int rd, rs, rt, imm, offset, target, sa;
	int i = 0, rNb = 0;

	int hexTrad;

	/* Ouverture du fichier */
	fic1 = fopen(nomFichier1, "r");
	if(fic1 == NULL) {
		perror("Probleme ouverture fichier monFichier.txt");
		exit(1);
	}

	fic2 = fopen(nomFichier2, "w");
	/* Lecture dans le fichier */
	/* On parcourt les lignes du fichier */
	while(fgets(line, 30, fic1)){
		rd = 0; rs = 0; rt = 0; imm = 0; offset = 0; target = 0; sa = 0;
		word = line;
		prevWord = word;
		/* On parcout les caractères de notre ligne tant qu'on n'arrive pas à la fin de la ligne */
		while(word[0]!='\n' && word[0]!='#' && word[0]!='\0'){
			word++;
			wLgth++;
			/*Si on arrive à la fin d'un mot */
			if(word[0]==' ' || word[0]==','){
				/* On copie juste le mot */

				tmpWord = prevWord;

				/*ton strcpy ne tronc pas la chaine donc whatisword ne fonctionne pas et je pense que meme si ca tronque 
				whatisword ne va pas faire ce qu'on veut*/
				/*Je pense qu'il faut clear prevWord car il doit garder les autres caractères mêmes si tu troncques*/
				
				strncpy(prevWord, tmpWord, wLgth);
				printf("%s\n",prevWord );

				/* Et on regarde ce que c'est */
				whatIsWord(prevWord,oppcode,&r1,&r2,&r3,&value,i,&rNb);
				printf("oppcode :%s\n",oppcode );
				/* On incrémente "l'index" du mot */
				/*i++;*/
				wLgth=0;
				prevWord=word+1;
			}
		}
		i=0;
		/* On identifie les termes de l'instruction */
		identifyRegister(oppcode,r1,r2,r3,value,&rd,&rs,&rt,&imm,&offset,&sa,&target);
		/* On identifie le type d'instruction */
		instrType = idInstrType(oppcode);
		switch(instrType)
		{
		case 0:
			printf("ca fait rien\n");
		case 1:
			hexTrad = typeRToHex(oppcode, rs, rt, rd, sa);
			break;
		case 2:
			hexTrad = typeIToHex(oppcode, rs, rt, imm);
			break;
		case 3:
			hexTrad = typeJToHex(oppcode, target);
			break;
		default:
			printf("Mauvaise écriture de votre code MIPS %d \n",instrType);
			break;
		}
		fprintf(fic2, "%X\n",hexTrad);
	}

	/* Fermeture du fichier */
	fclose(fic1);
	fclose(fic2);
}

/*
	Cette fonction va décomposer l'instruction lu dans le fichier texte pour placer les termes de l'instruction dans des variables
	Paramètre :
		- mot : char[]		le mot qui correspond soit à l'opcode soit au reste de la ligne qui sera donc à décomposer
		- oppcode : char[]	char dans lequel on mettra l'oppcode
		- r1 : int*			entier dans lequel on mettra le premier registre trouvé
		- r2 : int*			entier dans lequel on mettra le deuxième registre trouvé
		- r3 : int*			entier dans lequel on mettra le troisième registre trouvé
		- imm : int*		entier dans lequel on mettra la valeur immédiate trouvé
		- i : int			entier indiquant si on est sur l'opcode ou sur le reste de la ligne
		- rNb : int*		entier indiquant combien de registre on a compté
*/
void whatIsWord(char mot[], char oppcode[], int* r1, int* r2, int* r3, int* imm, int i, int *rNb){
   //Baby don't 
   //Hurt me
	if(i==0){
		oppcode = mot;
		printf("%s\n",mot );
	}else{
		if(mot[0]=='$'){
			switch(*rNb)
			{
				case 0:
					*r1 = atoi(mot+1);
					break;
				case 1:
					*r2 = atoi(mot+1);
					break;
				case 2:
					*r3 = atoi(mot+1);
					break;
				default:
					break;
			}
			(*rNb)++;
		}else{
				*imm = atoi(mot);
		}
	}
	if(*rNb > 2){
		*rNb = 0;
	}
}

void identifyRegister(char oppcode[], int r1, int r2, int r3, int value, int* rd, int* rs, int* rt, int* imm, int* offset, int* sa, int* target)
{
	if((strcmp(oppcode,"ADD")==0) || strcmp(oppcode,"AND")==0 || strcmp(oppcode,"OR")==0 || strcmp(oppcode,"SLT")==0 || strcmp(oppcode,"SUB")==0 || strcmp(oppcode,"XOR")==0){
		*rd = r1;
		*rs = r2;
		*rt = r3;
	}else if (strcmp(oppcode,"LW")==0 || strcmp(oppcode,"SW")==0 )
	{
		*rt = r1;
		*offset = value;
	}else if (strcmp(oppcode,"ROTR")==0 || strcmp(oppcode,"SLL")==0 || strcmp(oppcode,"SRL")==0)
	{
		*rd = r1;
		*rt = r2;
		*sa = value;
	}else if (strcmp(oppcode,"DIV")==0 || strcmp(oppcode,"MUL")==0)
	{
		*rs = r1;
		*rt = r2;
	}else if (strcmp(oppcode,"MFHI")==0 || strcmp(oppcode,"MFLO")==0)
	{
		*rd = r1;
	}else if (strcmp(oppcode,"LUI")==0)
	{
		*rt = r1;
		*imm = value;
	}else if (strcmp(oppcode,"JR")==0)
	{
		*rs = r1;
	}else if (strcmp(oppcode,"J")==0 || strcmp(oppcode,"JAL")==0)
	{
		*target = value;
	}else if (strcmp(oppcode,"BEQ")==0 || strcmp(oppcode,"BNE")==0 )
	{
		*rs = r1;
		*rt = r2;
		*offset = value;
	}else if (strcmp(oppcode,"BGTZ")==0 || strcmp(oppcode,"BLEZ")==0)
	{
		*rs = r1;
		*offset = value;
	}
}

int idInstrType(char oppcode[])
{
	if((strcmp(oppcode,"ADD")==0) ||(strcmp(oppcode,"AND")==0) ||(strcmp(oppcode,"DIV")==0) ||(strcmp(oppcode,"MFHI")==0) 
	||(strcmp(oppcode,"MFLO")==0) ||(strcmp(oppcode,"MULT")==0) ||(strcmp(oppcode,"NOP")==0) ||(strcmp(oppcode,"OR")==0) 
	||(strcmp(oppcode,"ROTR")==0) ||(strcmp(oppcode,"SLL")==0) ||(strcmp(oppcode,"SLT")==0) ||(strcmp(oppcode,"SRL")==0) 
	||(strcmp(oppcode,"SUB")==0) ||(strcmp(oppcode,"XOR")==0) ||(strcmp(oppcode,"JR")==0)){
		return 1;
	}else if ((strcmp(oppcode,"ADDI")==0) ||(strcmp(oppcode,"BEQ")==0) ||(strcmp(oppcode,"BGTZ")==0) ||(strcmp(oppcode,"BLEZ")==0) ||
	(strcmp(oppcode,"BNE")==0) ||(strcmp(oppcode,"LUI")==0) ||(strcmp(oppcode,"LW")==0) ||(strcmp(oppcode,"SW")==0))
	{
		return 2;
	}
	else if ((strcmp(oppcode,"J")==0) || (strcmp(oppcode,"JAL")==0))
	{
		return 3;
	}else
	{
		return -1;
	}
}