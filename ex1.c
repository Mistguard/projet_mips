#include <stdio.h>
#include <stdlib.h>

int lireDonnees(char nomFichier[], int T[]){
	FILE * fic;
	int nb;
	int i =0;
/* Ouverture du fichier */
	fic = fopen(nomFichier, "r");
	if(fic == NULL) {
		perror("Probleme ouverture fichier monFichier.txt");
		exit(1);
	}
/* Lecture dans le fichier */
	while(!feof(fic)) {
		fscanf(fic, "%d", &nb);
		T[i] = nb ;
		i++;
	}
/* Fermeture du fichier */
	fclose(fic);
	printf("Le tableau est de taille %d \n",i-1);
	return i-1;
}

void afficherTableau(int T[], int nb){
	int i;
	for (i=0;i<nb;i++){
		printf ("la valeur de la %dième case est %d \n",i,T[i]);
	}
}

void triABulles(int T[], int nb){
	int i;
	int j;
	int temp=0;
/* on compare la ième valeur avec la (i+1)ème et on vérifie que l'ordre du tri reste inchangé avec les valeurs précédentes*/
	for (i=0;i<nb;i++){
		for(j=0;j<nb-i-1;j++){
			if (T[j]>T[j+1]){
				temp =T[j];
				T[j]=T[j+1];
				T[j+1]=temp;
			}
		}
	}
}

void enregistrerDonnees(char nomFichier[],int T[], int nb){
	int i;
	FILE * fic = fopen(nomFichier, "r+") ;
	for (i=0;i<nb;i++){
		fprintf(fic, "Valeur = %d\n", T[i]) ;
	}
	fclose(fic);
}

int main(int argc, char * argv[]) {
	int nb=0;
	int T[20];
	/* ici on récupère le nom du fichier a lire lors de l'execution de la commande dans l'invité de commande grace a argv[]*/
	nb = lireDonnees(argv[1],T);
	afficherTableau(T,nb);
	triABulles(T,nb);
	enregistrerDonnees(argv[2],T,nb);
	return 0;
}