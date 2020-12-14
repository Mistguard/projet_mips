#include "readInstr.h"

/*
	Cette procédure permet de lire une suite d'instruction dans un ficher texte et de sauvegarder leur valeurs hexadecimal dans un autre fichier texte.
	Les instructions seront décodés et chacune mise dans une structure.
	Les structures seront ensuite sauvegardés dans la mémoire des instructions pour qu'elles puissent être éxécuté par le programme principale.
	Paramètre :
		- nomFic : char[]	le nom du fichier dans lequel on lira les instructions
		- prog : instrList*	mémoire contenant les structures correspondantes à nos instructions
*/
void decodeProg(char nomFic[], instrList* prog){
	FILE * fic1;
	FILE * fic2;
	
	char line[30];
	int pc = 0;
	Instrct nouv = {0};
	
	/* Ouverture des fichiers d'entré et de sortie */
	fic1 = fopen(nomFic, "r");
	fic2 = fopen("instructions_tests/fichierRes.txt", "w");

	/* On parcourt les lignes du fichier */
	while(fgets(line, 30, fic1))
	{
		/* On décode une ligne dans notre structure */
		readLine(line, &nouv);
		/* On écrit dans le fichier destination l'héxadécimal de l'instruction */
		fprintf(fic2, "%08x\n",nouv.hexa);
		/* On affiche la ligne du programme avec sa valeur en hexa et le numéro de la ligne */
		printf("\t%08d", pc);
		printf("\t%08X", nouv.hexa);
		printf("\t%s", line);
		pc+=4;
		
		/* On ajoute notre instruction à la mémoire */
		prog->list[prog->size] = nouv;
		prog->size = prog->size + 1;
		/* On aggrandit la capacité de notre mémoire d'instruction si jamais on atteint sa limite */
		if(prog->size >= prog->capa){
			prog->capa = prog->capa + CAPACITY;
			prog->list = realloc(prog->list,(prog->capa)*sizeof(Instrct));
		}
	}

	/* Fermeture des fichiers texte */
	fclose(fic1);
	fclose(fic2);
}

/*
	Cette procédure permet de décoder l'instruction contenue dans la chaine de caractère line. 
	Elle va identifier les registres rt, rs et rd, ainsi que les paramètres sa, immediate et l'offset si présents.
	On identifie aussi le type de l'instruction, si c'est de type R, I ou J.
	On traduira aussi l'instruction en hexadecimal.
	Finalement on stockera toutes ces informations dans la structure nouv.
	Paramètre :
		- line : char[]		la chaine de caractère correspondant à notre instruction à décoder
		- nouv : Instrct*	structure d'instruction à remplir après le décodage de line
*/
void readLine(char line[30], Instrct* nouv)
{
	char oppcode[10];

	char *word;
	char *prevWord;
	int wLgth=0;

	int i = 0, rNb = 0;

	int hexTrad = 0;
	int instrType=0;
	int rd = 0, rs = 0, rt = 0, imm = 0, target = 0, sa = 0, r1=0, r2=0, r3=0, value=0;
	char offBase[30] = {0};
	
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
			whatIsWord(tmpWord,oppcode,&r1,&r2,&r3,&value,offBase,i,&rNb);
			/* On incrémente "l'index" du mot */
			i++;
			wLgth=0;
			word++;
			prevWord=word;
			free(tmpWord);
		}
	}
	i=0;rNb=0;
	/* On identifie les termes de l'instruction */
	identifyRegister(oppcode,r1,r2,r3,value,&rd,&rs,&rt,&imm,offBase,&sa,&target);
	/* On identifie le type d'instruction */
	instrType = idInstrType(oppcode);
	/* On traduit l'instruction en héxadécimal */
	switch(instrType){
		case 1:
		hexTrad = typeRToHex(oppcode, rs, rt, rd, sa);
		nouv->imm = sa;
		nouv->type = 'R';
		break;
		case 2:
		hexTrad = typeIToHex(oppcode, rs, rt, imm);
		nouv->imm = imm;
		nouv->type = 'I';
		break;
		case 3:
		hexTrad = typeJToHex(oppcode, target);
		nouv->imm = target;
		nouv->type = 'J';
		break;
		default:
		printf("Mauvaise écriture de votre code MIPS %d \n",instrType);
		break;
	}
	/* On écrit dans notre structure instruction les informations */
	nouv->oppcode = opcodeToHexa(oppcode);
	nouv->rs = rs;
	nouv->rd = rd;
	nouv->rt = rt;
	strncpy(nouv->fullInst, line, 30);
	nouv->hexa = hexTrad;
}

/*
	Cette procédure prend un mot venant d'une instruction et identifie si ça correspond à l'opcode, à un registre, un immediate ou a l'offset avec la base.
	Paramètre :
		- mot : char[]		le mot qui correspond soit à l'opcode soit au reste de la ligne qui sera donc à décomposer
		- oppcode : char[]	char dans lequel on mettra l'opcode
		- r1 : int*			entier dans lequel on mettra le premier registre trouvé
		- r2 : int*			entier dans lequel on mettra le deuxième registre trouvé
		- r3 : int*			entier dans lequel on mettra le troisième registre trouvé
		- imm : int*		entier dans lequel on mettra la valeur immédiate trouvé
		- offBase : char* 	chaine de caractère dans lequel on mettre l'offset avec la base
		- i : int			entier indiquant si on est sur l'opcode ou sur le reste de la ligne
		- rNb : int*		entier indiquant combien de registre on a compté
*/
void whatIsWord(char mot[], char oppcode[], int* r1, int* r2, int* r3, int* imm, char* offBase, int i, int *rNb){
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
				if(strcmp(oppcode,"LW")==0 || strcmp(oppcode,"SW")==0){
					strcpy(offBase,mot);
				}
		}
	}
	if(*rNb > 2){
		*rNb = 0;
	}
}

/*
	Cette procédure va identifier les registres rd, rs, rt, les valeurs immédiates ainsi que l'offset et sa base en fonction de l'opcode
	Paramètre :
		- oppcode 	: char[]	char contenant l'oppcode
		- r1 		: int		entier contenant le premier registre trouvé
		- r2 		: int		entier contenant le deuxième registre trouvé
		- r3 		: int		entier contenant le troisième registre trouvé
		- value 	: int		entier contenant la valeur immédiate trouvé
		- rd 		: int*		entier dans lequel on mettra le registre rd
		- rs 		: int*		entier dans lequel on mettra le registre trouvé
		- rt 		: int*		entier dans lequel on mettra le registre trouvé
		- imm 		: int*		entier dans lequel on mettra la valeur immédiate
		- offBase 	: char*		chaine qui contient l'offset et sa base
		- sa 		: int*		entier dans lequel on mettra la valeur sa
		- target 	: int*		entier dans lequel on mettra la valeur de target
*/
void identifyRegister(char oppcode[], int r1, int r2, int r3, int value, int* rd, int* rs, int* rt, int* imm, char* offBase, int* sa, int* target)
{
	if((strcmp(oppcode,"ADD")==0) || strcmp(oppcode,"AND")==0 || strcmp(oppcode,"OR")==0 || strcmp(oppcode,"SLT")==0 || strcmp(oppcode,"SUB")==0 || strcmp(oppcode,"XOR")==0){
		*rd = r1;
		*rs = r2;
		*rt = r3;
	}else if (strcmp(oppcode,"LW")==0 || strcmp(oppcode,"SW")==0){
		*rt = r1;
		/* On décortique l'offset et la base */
		char* car = offBase;
		char* prevCar = car;
		int wLgth = 0;
		/* On parcout les caractères de notre ligne tant qu'on n'arrive pas à la fin de la ligne */
		while(car[0]!='\n' && car[0]!='#' && car[0]!='\0'){
			car++;
			wLgth++;
			/* Si on arrive à la fin de l'offset ou à la fin du registre de base */
			if(car[0]=='(' || car[0]==')'){
				/* On fait une copie du sous-mot */
				char* tmpWord = (char *)malloc(wLgth * sizeof(char));
				for(int j = 0; j < wLgth; j++){
					tmpWord[j] = prevCar[j];
				}
				tmpWord[wLgth]='\0';
				if(car[0]=='('){
					/* On enregistre l'offset */
					*imm = atoi(tmpWord);
				}
				if(car[0]==')'){
					/* On enregistre le registre contenant la base */
					*rs = atoi(tmpWord);
				}
				wLgth=0;
				car++;
				prevCar=car+1;
				free(tmpWord);
			}
		}
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
		- oppcode : char[]	char contenant l'opcode dont on identifiera le type
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
