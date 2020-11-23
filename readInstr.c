#include "readInstr.h"

void lireEnreDonnees(char nomFichier1[],char nomFichier2[]){
	FILE * fic1;
	FILE * fic2;

	char *word;
	char *prevWord;
	int wLgth=0;
	int instrType=0;
	char line[30];

	char oppcode[10];
	int r1, r2, r3, value;
	int rd, rs, rt, imm, target, sa;
	int i = 0, rNb = 0;

	int hexTrad;

	/* Ouverture des fichiers */
	fic1 = fopen(nomFichier1, "r");
	if(fic1 == NULL) {
		perror("Probleme ouverture fichier monFichier.txt");
		exit(1);
	}
	fic2 = fopen(nomFichier2, "w");

	/* On parcourt les lignes du fichier */
	while(fgets(line, 30, fic1)){
		hexTrad = 0;
		rd = 0; rs = 0; rt = 0; imm = 0; target = 0; sa = 0; r1=0; r2=0; r3=0; value=0;
		word = line;
		prevWord = word;
		/* On parcout les caractères de notre ligne tant qu'on n'arrive pas à la fin de la ligne */
		while(word[0]!='\n' && word[0]!='#' && word[0]!='\0'){
			word++;
			wLgth++;
			/*Si on arrive à la fin d'un mot */
			if(word[0]==' ' || word[0]==',' || word[0]=='\n' || word[0]=='#' || word[0]=='\0'){
				/* On fait une copie du mot */
				char* tmpWord = (char *)malloc(wLgth * sizeof(char));
				for(int j = 0; j < wLgth; j++){
					tmpWord[j] = prevWord[j];
				}
				tmpWord[wLgth]='\0';
				/* Et on regarde ce que c'est */
				whatIsWord(tmpWord,oppcode,&r1,&r2,&r3,&value,i,&rNb);
				/* On incrémente "l'index" du mot */
				i++;
				wLgth=0;
				word++;
				prevWord=word;
			}
		}
		i=0;rNb=0;
		/* On identifie les termes de l'instruction */
		identifyRegister(oppcode,r1,r2,r3,value,&rd,&rs,&rt,&imm,&sa,&target);
		/* On identifie le type d'instruction */
		instrType = idInstrType(oppcode);
		/* On traduit l'instruction en héxadécimal */
		switch(instrType){
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
		/* On écrit dans le fichier destination l'héxadécimal de l'instruction */
		fprintf(fic2, "%08x\n",hexTrad);
	}

	/* Fermeture des fichiers */
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
		/* Si c'est le premier mot c'est l'opcode */
		strcpy(oppcode,mot);
	}else{
		/* Si il y a un dollard c'est un registre */
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
		/* sinon c'est une valeur immédiate */
		}else{
				*imm = atoi(mot);
		}
	}
	if(*rNb > 2){
		*rNb = 0;
	}
}

/*
	Cette fonction va identifier les registres en fonction des instructions ainsi que les valeurs immédiates
	Paramètre :
		- oppcode : char[]	char contenant l'oppcode
		- r1 : int			entier contenant le premier registre trouvé
		- r2 : int			entier contenant le deuxième registre trouvé
		- r3 : int			entier contenant le troisième registre trouvé
		- value : int		entier contenant la valeur immédiate trouvé
		- rd : int*			entier dans lequel on mettra le registre rd
		- rs : int*			entier dans lequel on mettra le registre trouvé
		- rt : int*			entier dans lequel on mettra le registre trouvé
		- imm : int*		entier dans lequel on mettra la valeur immédiate
		- sa : int*			entier dans lequel on mettra la valeur sa
		- target : int*		entier dans lequel on mettra la valeur de target
*/
void identifyRegister(char oppcode[], int r1, int r2, int r3, int value, int* rd, int* rs, int* rt, int* imm, int* sa, int* target)
{
	if((strcmp(oppcode,"ADD")==0) || strcmp(oppcode,"AND")==0 || strcmp(oppcode,"OR")==0 || strcmp(oppcode,"SLT")==0 || strcmp(oppcode,"SUB")==0 || strcmp(oppcode,"XOR")==0){
		*rd = r1;
		*rs = r2;
		*rt = r3;
	}else if (strcmp(oppcode,"LW")==0 || strcmp(oppcode,"SW")==0 ){
		*rt = r1;
		*imm = value;
	}else if (strcmp(oppcode,"ROTR")==0 || strcmp(oppcode,"SLL")==0 || strcmp(oppcode,"SRL")==0){
		*rd = r1;
		*rt = r2;
		*sa = value;
	}else if (strcmp(oppcode,"DIV")==0 || strcmp(oppcode,"MULT")==0){
		*rs = r1;
		*rt = r2;
	}else if (strcmp(oppcode,"MFHI")==0 || strcmp(oppcode,"MFLO")==0){
		*rd = r1;
	}else if (strcmp(oppcode,"LUI")==0){
		*rt = r1;
		*imm = value;
	}else if (strcmp(oppcode,"JR")==0){
		*rs = r1;
	}else if (strcmp(oppcode,"J")==0 || strcmp(oppcode,"JAL")==0){
		*target = value;
	}else if (strcmp(oppcode,"BEQ")==0 || strcmp(oppcode,"BNE")==0 ){
		*rs = r1;
		*rt = r2;
		*imm = value;
	}else if (strcmp(oppcode,"BGTZ")==0 || strcmp(oppcode,"BLEZ")==0){
		*rs = r1;
		*imm = value;
	}else if(strcmp(oppcode,"ADDI")==0){
		*rt = r1;
		*rs = r2;
		*imm = value;
	}else if(strcmp(oppcode,"NOP")==0){
		*rd = 0;
		*rs = 0;
		*rt = 0;
		*sa = 0; 	
	}else{
		printf("Fonction non trouvé\n");
	}
}

/*
	Cette fonction va identifier le type d'instruction compris dans la chaine de caractères oppcode.
	Paramètre :
		- oppcode : char[]	char contenant l'oppcode dont on identifiera le type
	Retourne un entier :
		- 1 : si l'instruction est de type R
		- 2 : si l'instruction est de type I
		- 3 : si l'instruction est de type J
		- -1 : si l'instruction est de type inconnue
*/
int idInstrType(char oppcode[])
{
	if((strcmp(oppcode,"ADD")==0) ||(strcmp(oppcode,"AND")==0) ||(strcmp(oppcode,"DIV")==0) ||(strcmp(oppcode,"MFHI")==0) 
	||(strcmp(oppcode,"MFLO")==0) ||(strcmp(oppcode,"MULT")==0) ||(strcmp(oppcode,"NOP")==0) ||(strcmp(oppcode,"OR")==0) 
	||(strcmp(oppcode,"ROTR")==0) ||(strcmp(oppcode,"SLL")==0) ||(strcmp(oppcode,"SLT")==0) ||(strcmp(oppcode,"SRL")==0) 
	||(strcmp(oppcode,"SUB")==0) ||(strcmp(oppcode,"XOR")==0) ||(strcmp(oppcode,"JR")==0)){
		return 1;
	}else if ((strcmp(oppcode,"ADDI")==0) ||(strcmp(oppcode,"BEQ")==0) ||(strcmp(oppcode,"BGTZ")==0) ||(strcmp(oppcode,"BLEZ")==0) ||
	(strcmp(oppcode,"BNE")==0) ||(strcmp(oppcode,"LUI")==0) ||(strcmp(oppcode,"LW")==0) ||(strcmp(oppcode,"SW")==0)){
		return 2;
	}else if ((strcmp(oppcode,"J")==0) || (strcmp(oppcode,"JAL")==0)){
		return 3;
	}else{
		return -1;
	}
}