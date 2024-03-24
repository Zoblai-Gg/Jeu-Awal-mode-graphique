#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "init_awele.h"
#include "saisi_pseudo0.h"
#ifndef JEU_AWALE_AFFICHE_AWELE_H
#define JEU_AWALE_AFFICHE_AWELE_H

void Charger_Affiche_pseudo(SDL_Renderer **renderer,JOUEUR *joueur1,JOUEUR *joueur2,int toplay,PSEUDO_JOUEUR player_mame);
void Charger_Affiche_score(SDL_Renderer **renderer,JOUEUR *joueur1,JOUEUR *joueur2);

#endif //JEU_AWALE_AFFICHE_AWELE_H
