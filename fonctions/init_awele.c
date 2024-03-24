#include "gameOver.h"
#include "init_awele.h"


SDL_bool Init_SDL_Functions(SDL_Window ** window,SDL_Renderer **renderer,SDL_Texture **texture)
{
    *window = SDL_CreateWindow("Awelé",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,46*PIXEL,29*PIXEL,SDL_WINDOW_SHOWN);
    if(*window == NULL){
        fprintf(stderr,"Erreur sur couverture de window %s",SDL_GetError());
        return SDL_FALSE;
    }

    *renderer = SDL_CreateRenderer(*window,-1,SDL_RENDERER_ACCELERATED);
    if(*renderer == NULL){
        fprintf(stderr,"Erreur sur création de rendu %s",SDL_GetError());
        return SDL_FALSE;
    }
    *texture = SDL_CreateTexture(*renderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,PIXEL,PIXEL);
    if(*texture == NULL){
        fprintf(stderr,"Erreur sur création de la texture %s",SDL_GetError());
        return SDL_FALSE;
    }
    return SDL_TRUE;
}

void Destroy_SDL_Function(SDL_Window ** window,SDL_Renderer **renderer,SDL_Texture **texture){

    if(texture != NULL)
        SDL_DestroyTexture(*texture);
    if(renderer != NULL)
        SDL_DestroyRenderer(*renderer);
    if(window != NULL)
        SDL_DestroyWindow(*window);
    SDL_Quit();

}

void Charger_Image(SDL_Texture **background,SDL_Texture **tablier,SDL_Texture **graine, SDL_Renderer **renderer)
{
    SDL_Surface *surface;

    surface = SDL_LoadBMP("../image/fond.bmp");
    *background = SDL_CreateTextureFromSurface(*renderer,surface);
    SDL_FreeSurface(surface);
    surface = SDL_LoadBMP("../image/tbl.bmp");
    *tablier = SDL_CreateTextureFromSurface(*renderer,surface);
    SDL_FreeSurface(surface);
    surface = SDL_LoadBMP("../image/graine_de_conique.bmp");
    *graine = SDL_CreateTextureFromSurface(*renderer,surface);
    SDL_FreeSurface(surface);

}

SDL_Rect * Initialse_Coor_Tablier(void)
{
    SDL_Rect *rect = (SDL_Rect* )malloc(12 * sizeof(SDL_Rect)) ;
    rect[0].x = 40; rect[0].y = 160;rect[0].w = 140;rect[0].h = 140;
    rect[6].x = 40; rect[6].y = 300 ;rect[6].w = 140;rect[6].h = 140;

    for (int i = 1; i < 12; ++i) {
        if(i<6){
            rect[i].x = rect[i-1].x +  rect[i-1].w;
            rect[i].y = rect[i-1].y;
            rect[i].w = 140;
            rect[i].h = 140;
        }
        else if (i>6){

            rect[i].x = rect[i-1].x +  rect[i-1].w;
            rect[i].y = rect[i-1].y;
            rect[i].w = 140;
            rect[i].h = 140;
        }
    }
    return rect;
}

int **Initialise_Graine_Tablier(void)
{
    int **plateau = (int **)malloc(NB_ROWS * sizeof(int *));
    for (int i = 0; i < NB_ROWS; i++){

        plateau[i] = (int *)malloc(NB_CASES * sizeof(int));
        for (int j = 0; j < NB_CASES; j++)
        {
            plateau[i][j] = NB_SEEDS;
        }
    }
    return plateau;
}