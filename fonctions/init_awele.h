#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


#ifndef JEU_AWALE_INIT_AWELE_H
#define JEU_AWALE_INIT_AWELE_H

#define NB_SEEDS 3
#define PIXEL 20
#define NB_ROWS 2
#define NB_CASES 6
#define PLAY_AT_2 1
#define CONTRE_ORDI 2
#define SCORE 3
#define ABOUT  4
#define QUITTER -1

typedef struct{
    int num;
    int recolte;
    SDL_Texture *pseudo;
    SDL_Point last_case_played;
}JOUEUR;

SDL_bool Init_SDL_Functions(SDL_Window ** window,SDL_Renderer **renderer,SDL_Texture **texture);
void Destroy_SDL_Function(SDL_Window ** window,SDL_Renderer **renderer,SDL_Texture **texture);
void Charger_Image(SDL_Texture **background,SDL_Texture **tablier,SDL_Texture **graine, SDL_Renderer **renderer);
SDL_Rect * Initialse_Coor_Tablier(void);
int **Initialise_Graine_Tablier(void);


#endif //JEU_AWALE_INIT_AWELE_H
