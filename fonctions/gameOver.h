#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "init_awele.h"
#include "saisi_pseudo0.h"
#ifndef JEU_AWALE_GAMEOVER_H
#define JEU_AWALE_GAMEOVER_H


#define NB_SEEDS 3
#define PIXEL 20
#define NB_ROWS 2
#define NB_CASES 6
#define PLAY_AT_2 1
#define CONTRE_ORDI 2
#define SCORE 3
#define ABOUT  4
#define QUITTER -1


SDL_bool verifCaseVide(int **plateau);
int Game_Over(JOUEUR joueur1,JOUEUR joueur2, int over,PSEUDO_JOUEUR player_mame);
int TestergameOver(JOUEUR joueur1,JOUEUR joueur2,int **plateau,int fin_de_partie);
#endif //JEU_AWALE_GAMEOVER_H
