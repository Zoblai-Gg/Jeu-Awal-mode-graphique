#ifndef SAVE_H_INCLUDED
#define SAVE_H_INCLUDED


typedef struct
{
    char pseudo[50];
    int score;  

}JOUEUR_SCORE;

// extern int max;
// int maxscore;
// char* mpsuedo;
// char maximum[10];
// extern char resultat[1000];

void enregister(JOUEUR_SCORE joueur1, JOUEUR_SCORE joueur2);
void trifplayer();
#endif