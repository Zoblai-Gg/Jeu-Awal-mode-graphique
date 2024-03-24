#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "a_propos.h"





int a_propos() {

    SDL_Window *window = NULL;
    SDL_Rect rect_b = {680, 528, 200, 50};
    SDL_Rect rect_reppredre = {742, 540, 80, 30};
    SDL_Texture *btn_bleu = NULL;
    int val ;
    TTF_Font *font;

    SDL_Surface *surface = NULL;

    if(SDL_Init( SDL_INIT_AUDIO) != 0)
    {
        fprintf(stderr, "Erreur de SDL_init : %s ", SDL_GetError());
    }

    if(Mix_OpenAudio(96000, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur initialisation SDL_Mixer : %s ", Mix_GetError());
        SDL_Quit();
    }
    Mix_Music* music = Mix_LoadMUS("../musique/welcome_music.mp3");

    if(music == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur de chargelent de la musique : %s ", Mix_GetError());
        Mix_CloseAudio();
        SDL_Quit();
    }

    Mix_PlayMusic(music, -1);


    if(0 != SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
    {
        fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
        goto Quit;
    }
    window = SDL_CreateWindow("SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              920, 580, SDL_WINDOW_SHOWN);

    if(NULL == window)
    {
        fprintf(stderr, "Erreur SDL_CreateWindow : %s", SDL_GetError());
        goto Quit;
    }


    SDL_Renderer *renderer = NULL;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!renderer) {
        fprintf(stderr, "Erreur SDL_CreateRenderer : %s", SDL_GetError());
        goto Quit;
    }


    SDL_Surface *background_surf = NULL;
    char* background_image = NULL;
    background_image = "../image/about.bmp";
    background_surf = SDL_LoadBMP(background_image);

    SDL_Texture *texture =  SDL_CreateTextureFromSurface(renderer,background_surf);
    SDL_RenderCopy(renderer,texture,NULL,NULL);



    if (TTF_Init() != 0) {
        fprintf(stderr, "Erreur sur initialisation de la SDL2 ! %s \n", SDL_GetError());
       goto Quit;
    }

    SDL_Color blanc = {255, 255, 255, 255};


    font = TTF_OpenFont("../police/Brumery_Demo.ttf", 40);

    surface = SDL_LoadBMP("../image/buttn.bmp");
    btn_bleu = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_RenderCopy(renderer, btn_bleu, NULL, &rect_b);
    SDL_FreeSurface(surface);
    surface = TTF_RenderText_Solid(font, " Retour ", blanc);
    btn_bleu = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_RenderCopy(renderer, btn_bleu, NULL, &rect_reppredre);

    TTF_CloseFont(font);
    TTF_Quit();

    SDL_RenderPresent(renderer);

    SDL_Event event;
    SDL_bool running = SDL_FALSE;

    while(!running){
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                running = SDL_TRUE;
                val = 0;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                SDL_Point point;
                point.x = event.button.x ;point.y = event.button.y ;
                //renvoie 0 pour quitter le jeu et 1 pour rependre

                if((point.x > rect_b.x && point.x < rect_b.x+rect_b.w) && (point.y > rect_b.y && point.y <rect_b.y+rect_b.h)){
                    running = SDL_TRUE;
                    val = 1;
                }
            }
        }
    }

    Quit : 
    SDL_Delay(10);
    SDL_DestroyRenderer(renderer); 
    SDL_DestroyWindow(window);

    SDL_Quit();
    Mix_FreeMusic(music);
    Mix_CloseAudio();
    return val;
}





