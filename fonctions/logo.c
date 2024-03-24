
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "SDL2/SDL_main.h"


int logo() 
{

    int val = 0; 

    SDL_Window *window = NULL; 
 
    if(0 != SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) 
    {
        fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
        return EXIT_FAILURE;
    }
    
    window = SDL_CreateWindow("BIENVENUE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              920, 580, SDL_WINDOW_SHOWN);

    if(NULL == window)
    {
        fprintf(stderr, "Erreur SDL_CreateWindow : %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    if (Mix_OpenAudio(96000, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur initialisation SDL_mixer : %s", Mix_GetError());
        SDL_Quit();
        return -1;
    }

    Mix_Music* music = Mix_LoadMUS("../musique/musique_logo.mp3");


    if (music == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur chargement de la musique : %s", Mix_GetError());
        Mix_CloseAudio();
        SDL_Quit();
        return -1;
    }

    Mix_PlayMusic(music, -1);

    SDL_Renderer *renderer = NULL;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!renderer) {
        fprintf(stderr, "Erreur SDL_CreateRenderer : %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    char* chemin_complet = "../image/logo.bmp";

    SDL_Surface *image_surf = NULL;  
    image_surf = SDL_LoadBMP(chemin_complet);
    SDL_Texture *image_text = NULL;
    image_text = SDL_CreateTextureFromSurface(renderer, image_surf);

    SDL_Event e;

    if(SDL_PollEvent(&e))
    {
        if(e.type == SDL_QUIT)
        {
            val = -1;
            goto Quit;
        }
    }
    // SDL_Rect rect = {200,200,300,400};
    SDL_Rect rect = {((920/2)-170),((580/2)-170),(image_surf->w)/3,(image_surf->h)/3};
    SDL_RenderCopy(renderer, image_text, NULL, &rect);

    SDL_RenderPresent(renderer);


    
    SDL_Delay(3000);

    Quit :

    SDL_DestroyRenderer(renderer);   
    SDL_DestroyWindow(window);
    Mix_FreeMusic(music); 
    Mix_CloseAudio();   

    SDL_Quit();  
    return val;

}


























