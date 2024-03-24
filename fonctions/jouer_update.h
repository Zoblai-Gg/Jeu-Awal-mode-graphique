#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "init_awele.h"

#ifndef JEU_AWALE_JOUER_UPDATE_H
#define JEU_AWALE_JOUER_UPDATE_H

#define NB_SEEDS 3
#define PIXEL 20
#define NB_ROWS 2
#define NB_CASES 6

void charger_graine_tablier( SDL_Renderer ** renderer, SDL_Texture **texture, int ** contenu_tablier);
void update_coor_Case(SDL_Renderer **renderer, SDL_Texture **texture,int nb_graine,int rang_case);
void Fonction_semer(int **contenu_tablier,JOUEUR *joueur,int case_choisie);
int Renvoyer_Choix_Joueur(SDL_Point coor, SDL_Rect *coor_tablier);
int choix_du_joueur(void);
int recolter(int **contenu_tablier,JOUEUR *joueur);
void Toshow_click(SDL_Renderer **renderer ,SDL_Rect *coor_tablier,int case_choisie);


#endif //JEU_AWALE_JOUER_UPDATE_H
