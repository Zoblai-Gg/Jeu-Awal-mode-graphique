#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"save.h"
#define FALSE 0
#define TRUE  1
#define N 100
int trouve_j1 = FALSE;
int trouve_j2 = FALSE;
int *tabscore = NULL;

int maxscore1;
int maxscore2;
int maxscore3;
char* mpsuedo1;
char* mpsuedo2;
char* mpsuedo3;
extern char resultat1[1000];// Resultat de joueur de score max
extern char resultat2[1000];
extern char resultat3[1000];
char maximum1[1000];
char maximum2[1000];
char maximum3[1000];



int j = 0;
char resultat1[1000];// Resultat de joueur de score max
char resultat2[1000];
char resultat3[1000];
JOUEUR_SCORE joueur;

// Structure des données et stockage dans un tableau
JOUEUR_SCORE joueurs[200];
// char maxid[200];


int count = 0; // Variable de compteur
// Fonction de comparaison de tri
int mycompare(const void *j1, const void*j2 ){

   const JOUEUR_SCORE *joueur1 = (JOUEUR_SCORE *)j1;
   const JOUEUR_SCORE *joueur2 = (JOUEUR_SCORE *)j2;
   return joueur2->score - joueur1->score;

}

void enregister(JOUEUR_SCORE joueur1, JOUEUR_SCORE joueur2){

    FILE *file = NULL; // Pointeur vers le fichier existant
    FILE *file_maj = NULL; // Pointeur vers le fichier de MAJ
    file = fopen("score.txt", "r"); // Ouverture du fichier en lecture seule
    file_maj = fopen("score_maj.txt", "a"); // Ouverture du fichier d'ajout pour la MAJ

// joueur_tmp = joueur1.score > joueur2.score ? joueur1 : joueur2;

    if(file == NULL){
        printf("Ouverture Impossible du fichier \n");
        exit(-1);
    }
    else {

        while (fscanf(file, "%s %d", joueur.pseudo, &joueur.score) != EOF) // Tant que on est pas à la fin du fichier
        {

            if((strcmp(joueur.pseudo,joueur1.pseudo) == 0 && trouve_j1 == FALSE ) ) {
                // Mise à jour du score du joueur 1
                trouve_j1 = TRUE;
                joueur.score = joueur1.score > joueur.score ? joueur1.score : joueur.score;
            }else if(strcmp(joueur.pseudo,joueur2.pseudo) == 0 && trouve_j2 == FALSE ){
                trouve_j2 = TRUE;
                joueur.score = joueur2.score > joueur.score ? joueur2.score : joueur.score;
            }

            fprintf(file_maj,"%s %d\n",joueur.pseudo,joueur.score);

            // i++; 
            // Ajout de code

        }

        if (trouve_j1 == FALSE){
            // On ecrit le nouveau score et le pseudo du Joueur 1
            fprintf(file_maj,"%s %d\n",joueur1.pseudo,joueur1.score);
        }
        if (trouve_j2 == FALSE){
            // On ecrit le nouveau score et le pseudo du Joueur 2
            fprintf(file_maj,"%s %d\n",joueur2.pseudo,joueur2.score);
        }
        if(remove("score.txt") == 0){
            //printf("fichier supprimé avec succès\n");
            // Renommage du fichier score_maj en score
            rename("score_maj.txt","score.txt");
        }



    }

// Fermeture des fichiers
    fclose(file);
    fclose(file_maj);
}


void trifplayer(){
FILE *fichier = NULL;
fichier = fopen("score.txt", "r");
// Retourne du curseur au début du fichier.
fseek(fichier, 0 , 0);
if(fichier == NULL){
    printf("Impossible d'ouvrir le fichier");
}else {
  while (fscanf(fichier, "%s %d", joueurs[count].pseudo, &joueurs[count].score) != EOF ) { // Tant que on est pas à la fin du fichier
    count = count + 1;
    }
  // Fermerture des fichiers
  fclose(fichier);
  // Tri du tableau des structures des joueurs
  qsort(joueurs, count, sizeof(JOUEUR_SCORE), mycompare);
  // Réouverture du fichier en mode écriture
  fichier = fopen("score.txt","w");
  if(fichier == NULL){
    printf("Ouverture Impossible du fichier\n");
    exit(-1);
 }  
 // Ecriture de données triées dans le fichier socre.txt
 for(int i = 0; i < count ; i++){
    fprintf(fichier, "%s  %d\n", joueurs[i].pseudo, joueurs[i].score);  
 }
 
 fclose(fichier);

}
//printf("les données ont été mis à jour avec succès dans le fichier\n");
maxscore1 = joueurs[0].score;
mpsuedo1 = malloc(N*sizeof(char));
mpsuedo1 = joueurs[0].pseudo;
maxscore2 = joueurs[1].score;
mpsuedo2 = malloc(N*sizeof(char));
mpsuedo2 = joueurs[1].pseudo;
maxscore3 = joueurs[2].score;
mpsuedo3 = malloc(N*sizeof(char));
mpsuedo3= joueurs[2].pseudo;

//printf("Meilleur score: pseudo:%s, score:%d\n", joueurs[0].pseudo, joueurs[0].score);
// Conversion de type int max en chaine de caractere
snprintf(maximum1, sizeof(maximum1), "%d", maxscore1);
snprintf(maximum2, sizeof(maximum2), "%d", maxscore2);
snprintf(maximum3, sizeof(maximum3), "%d", maxscore3);
// Formattage du resultat de meilleur score
// Pour le premier score
strcpy(resultat1, mpsuedo1);
strcat(resultat1, " ");
strcat(resultat1, maximum1);
//printf("resultat1: %s\n",resultat1);
// Pour la deuxieme score
strcpy(resultat2, mpsuedo2);
strcat(resultat2, " ");
strcat(resultat2, maximum2);
//printf("resultat2: %s\n",resultat2);
// Pour le troisieme score
strcpy(resultat3, mpsuedo3);
strcat(resultat3, " ");
strcat(resultat3, maximum3);
//printf("resultat3: %s\n",resultat3);
}
