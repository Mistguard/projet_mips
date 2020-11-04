#include "hexaConv.h"


void lireEnreDonnees(char nomFichier1[],char nomFichier2[]){
	FILE * fic1;
	FILE * fic2;
	char mot[30],temp[30]={0};
	int i =0;
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
		if(strcmp(temp,mot)!=0){
			strcpy(temp,mot);
			printf("%s\n",mot );
			fprintf(fic2, "%s\n", mot) ;
			i++;
		}else{
			i++;
		}

	}
/* Fermeture du fichier */
	fclose(fic1);
	fclose(fic2);
	printf("Le tableau est de taille %d \n",i-1);
}
