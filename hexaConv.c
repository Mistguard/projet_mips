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
		/*On evite la répétion de la dernière ligne*/
		if(strcmp(temp,mot)!=0){
			/*Pour avoir un affichage et une écriture en ligne et non coupé sur 2 lignes*/
			if (i%2==0){
				strcpy(temp,mot);
				printf("%s ",mot );
				fprintf(fic2, "%s ", mot) ;
				i++;
			}else{
				strcpy(temp,mot);
				printf("%s\n",mot);
				fprintf(fic2, "%s\n", mot) ;
				i++;
			}
		}else{
			i++;
		}

	}
/* Fermeture du fichier */
	fclose(fic1);
	fclose(fic2);
}

