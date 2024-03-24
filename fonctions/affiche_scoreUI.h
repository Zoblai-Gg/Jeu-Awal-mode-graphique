#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#ifndef JEU_AWALE_AFFICHE_SCOREUI_H
#define JEU_AWALE_AFFICHE_SCOREUI_H


extern char resultat1[1000];
extern char resultat2[1000];
extern char resultat3[1000];

int affiche_scoreUI(void);

void WriteOnWindow(SDL_Renderer **renderer);


#endif //JEU_AWALE_AFFICHE_SCOREUI_H
