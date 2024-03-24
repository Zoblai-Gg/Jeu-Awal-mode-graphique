#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "welcome.h"

int welcome() {

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




    int val = 0;

    SDL_Window *window = NULL;

    if(0 != SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) // initialise la vidéo et l'audio
    {
        fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
        return EXIT_FAILURE;
    }
    window = SDL_CreateWindow("Awélé", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              920, 580, SDL_WINDOW_SHOWN);

    // Vérification de la création ou l'echec de la création de la fenêtre window
    if(NULL == window)
    {
        fprintf(stderr, "Erreur SDL_CreateWindow : %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    // Iitialisation de l'espace où allons dessiner
    SDL_Renderer *renderer = NULL;

    //Attribution des valeurs à l'espace de dessin
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // Vérification de la création ou l'echec de la création de l'espace de dessin  (SDL_Renderer)
    if (!renderer) {
        fprintf(stderr, "Erreur SDL_CreateRenderer : %s", SDL_GetError());
        return EXIT_FAILURE;
    }


    SDL_Surface *image_surf = NULL;
    image_surf = SDL_LoadBMP("../image/bgwelcome.bmp");
    SDL_Texture *image_text = NULL;
    image_text = SDL_CreateTextureFromSurface(renderer, image_surf);

    SDL_Surface *welcome_button = NULL;
    welcome_button = SDL_LoadBMP("../image/start.bmp");
    SDL_Texture *welcome_text = NULL;
    welcome_text = SDL_CreateTextureFromSurface(renderer, welcome_button);
    SDL_Rect destRect = {250 , 400 ,0, 0};
    SDL_QueryTexture(welcome_text,NULL,NULL,&destRect.w,&destRect.h);
    SDL_bool running = SDL_TRUE;
    SDL_Event e; // Initialisation d'un évènement

          while(running)
          {
              while(SDL_PollEvent(&e))
              {
                  if(e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)
                  {
                      running = SDL_FALSE;
                      val = -1;
                  } else if(e.type == SDL_MOUSEBUTTONDOWN) {
                      // SDL_Log("\n +clic");   // click enfoncé
                      if(e.button.button == SDL_BUTTON_LEFT)
                      {
                          int x = e.button.x;
                          int y = e.button.y;
                          if((x>=299 && x <= 685) && (y>=467 && y <= 540))
                          {
                              running = SDL_FALSE; // ONCLICK SUR LE BOUTTON COMMENCER
                              val = 0;
                          }

                      }
                  } 
              }
              SDL_RenderCopy(renderer, image_text, NULL, NULL); // affiche l'aimage de l'écran
              SDL_RenderCopy(renderer, welcome_text, NULL, &destRect); // affiche le boutton de bienvenue

              // Mettre à jour l'affichage
              SDL_RenderPresent(renderer);

          }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
    Mix_FreeMusic(music);
    Mix_CloseAudio();
    return val;

}









