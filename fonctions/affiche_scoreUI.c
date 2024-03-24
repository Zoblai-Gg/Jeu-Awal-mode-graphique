#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include<string.h>

#include"affiche_scoreUI.h"
#include "init_awele.h"
#define WINDOW_WIDTH 920
#define WINDOW_HEIGHT 580


int affiche_scoreUI(void) {


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

    SDL_Window *window  = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *texture = NULL;
    SDL_Surface *surface = NULL;
    SDL_Rect rect_b = {680, 528, 200, 50};

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Erreur sur initialisation de la SDL2 ! %s \n", SDL_GetError());
        goto Quit;
    }
    if (Init_SDL_Functions(&window, &renderer, &texture) == SDL_FALSE) {
        goto Quit;
    }

    surface = SDL_LoadBMP("../image/background.bmp");
    texture = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_RenderCopy(renderer,texture, NULL,NULL);
    WriteOnWindow(&renderer);
    SDL_RenderPresent(renderer);


    SDL_Event event;
    SDL_bool quit = SDL_FALSE;
    int val;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = SDL_TRUE;
                val = 0;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN) {
                SDL_Point point;
                point.x = event.button.x ;point.y = event.button.y ;
                //renvoie 0 pour quitter le jeu et 1 pour rependre

                if((point.x > rect_b.x && point.x < rect_b.x+rect_b.w) && (point.y > rect_b.y && point.y <rect_b.y+rect_b.h)){
                    quit = SDL_TRUE;
                    val = 1;
                }
            }
        }
    }

    Quit :
    Mix_FreeMusic(music);
    Mix_CloseAudio();
    Destroy_SDL_Function(&window,&renderer,&texture);
    return val;
}


void WriteOnWindow(SDL_Renderer **renderer)
{
    TTF_Font *font;
    SDL_Texture *texture;
    FILE *fichier = NULL;
    SDL_Surface *surface  =NULL;
    SDL_Texture *btn_bleu = NULL;
    char pseudo[50] ="";

    if (TTF_Init() != 0) {
        fprintf(stderr, "Erreur sur initialisation de la SDL2 ! %s \n", SDL_GetError());
        exit(EXIT_FAILURE);
    }


    SDL_Surface *surface_texte = NULL;

    SDL_Color blanc = {255, 255, 255, 255};
    SDL_Rect rect[4]= {{320, 70, 0, 0},{400, 140, 0, 0},{400, 200, 0, 0},{400, 260, 0, 0}};
    SDL_Rect rect_b = {680, 528, 200, 50};
    SDL_Rect rect_reppredre = {742, 540, 80, 30};

    font = TTF_OpenFont("../police/Brumery_Demo.ttf", 40);

    surface_texte = TTF_RenderText_Solid(font,"Meilleurs Scores" , blanc);
    texture = SDL_CreateTextureFromSurface(*renderer, surface_texte);
    SDL_FreeSurface(surface_texte);
    SDL_QueryTexture(texture, NULL, NULL, &rect[0].w, &rect[0].h);
    SDL_RenderCopy(*renderer, texture, NULL, &rect[0]);


    surface = SDL_LoadBMP("../image/buttn.bmp");
    btn_bleu = SDL_CreateTextureFromSurface(*renderer, surface);
    SDL_RenderCopy(*renderer, btn_bleu, NULL, &rect_b);
    SDL_FreeSurface(surface);
    surface = TTF_RenderText_Solid(font, " Retour ", blanc);
    btn_bleu = SDL_CreateTextureFromSurface(*renderer, surface);
    SDL_RenderCopy(*renderer, btn_bleu, NULL, &rect_reppredre);





    fichier = fopen("score.txt", "r");

    if(fichier==NULL){
        printf("Erreur lors de l'ouverture d'un fichier");
        exit(1);
    }

    for (int i = 1; i <= 3; ++i) {

    fgets(pseudo,50 ,fichier);
    surface_texte = TTF_RenderText_Solid(font,pseudo , blanc);
    texture = SDL_CreateTextureFromSurface(*renderer, surface_texte);
    SDL_FreeSurface(surface_texte);
    SDL_QueryTexture(texture, NULL, NULL, &rect[i].w, &rect[i].h);
    SDL_RenderCopy(*renderer, texture, NULL, &rect[i]);
    }

    fclose(fichier);

    TTF_CloseFont(font);
    TTF_Quit();


}