#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "saisi_pseudo0.h"


typedef struct {
    char pseudo[100] ;
    int score ;
    SDL_Rect rect;
} JOUEUR ;

void drawInputRectangle(JOUEUR* joueur, SDL_Renderer* renderer, TTF_Font* gFont) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); 
    SDL_RenderFillRect(renderer, &joueur->rect);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 
    SDL_RenderDrawRect(renderer, &joueur->rect);

    SDL_Color textColor = {0, 0, 0}; 
    SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, joueur->pseudo, textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    int textWidth, textHeight;
    SDL_QueryTexture(textTexture, NULL, NULL, &textWidth, &textHeight);

    SDL_Rect textRect = {
        joueur->rect.x + (joueur->rect.w - textWidth) / 2,
        joueur->rect.y + (joueur->rect.h - textHeight) / 2,
        textWidth,
        textHeight
    };

    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

void drawInputRectangleRED(JOUEUR* joueur, SDL_Renderer* renderer, TTF_Font* gFont) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); 
    SDL_RenderFillRect(renderer, &joueur->rect);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &joueur->rect);

    SDL_Color textColor = {0, 0, 0}; 
    SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, joueur->pseudo, textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    int textWidth, textHeight;
    SDL_QueryTexture(textTexture, NULL, NULL, &textWidth, &textHeight);

    SDL_Rect textRect = {
        joueur->rect.x + (joueur->rect.w - textWidth) / 2,
        joueur->rect.y + (joueur->rect.h - textHeight) / 2,
        textWidth,
        textHeight
    };

    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

JOUEUR* notnulljoueur = NULL;

void handleInput(SDL_Event e, JOUEUR* joueur) {

    int isSelected = (notnulljoueur == joueur);

    if (e.type == SDL_MOUSEBUTTONDOWN) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        if (mouseX >= joueur->rect.x && mouseX <= (joueur->rect.x + joueur->rect.w) &&
            mouseY >= joueur->rect.y && mouseY <= (joueur->rect.y + joueur->rect.h)) {
            notnulljoueur = joueur;  
        } 
    }

    if (isSelected) {
        if (e.type == SDL_TEXTINPUT) {
            strcat(joueur->pseudo, e.text.text);
        } else if (e.type == SDL_KEYDOWN) {
            if (e.key.keysym.sym == SDLK_BACKSPACE && strlen(joueur->pseudo) > 0) {
                joueur->pseudo[strlen(joueur->pseudo) - 1] = '\0';
            }
        }
    }
}

void aff_rect (SDL_Renderer* renderer, SDL_Rect* rectangle )
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

    SDL_RenderFillRect(renderer, rectangle);
}

void aff_rect_red (SDL_Renderer* renderer, SDL_Rect* rectangle )
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);

    SDL_RenderFillRect(renderer, rectangle);
}




PSEUDO_JOUEUR saisi_pseudo0(){ 

    PSEUDO_JOUEUR pseudos_finaux = {"", ""};

    SDL_Window *window = NULL; 
 
    if(0 != SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) 
    {
        fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
        goto Quit_awale;
    }

    window = SDL_CreateWindow("Joueurs AWELE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              920, 580, SDL_WINDOW_SHOWN);

    if(NULL == window)
        {
            fprintf(stderr, "Erreur SDL_CreateWindow : %s", SDL_GetError());
            goto Quit_awale;
        }

    SDL_Renderer *renderer = NULL; 

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    if (!renderer) {
        fprintf(stderr, "Erreur SDL_CreateRenderer : %s", SDL_GetError());
        goto Quit_awale;
    }



    
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        fprintf(stderr, "Erreur lors de l'initialisation de SDL: %s\n", SDL_GetError());
        goto Quit_awale;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        fprintf(stderr, "Erreur lors de l'initialisation de SDL_mixer: %s\n", Mix_GetError());
        SDL_Quit();
        goto Quit_awale;
    }

   
    Mix_Music *audio = Mix_LoadMUS("../musique/welcome_music.mp3");


    if (audio == NULL) {
        fprintf(stderr, "Erreur lors du chargement du fichier audio: %s\n", Mix_GetError());
        Mix_CloseAudio();
        SDL_Quit();
        goto Quit_awale;
    }

    if (TTF_Init() < 0) {
        fprintf(stderr, "Erreur lors de l'initialisation de SDL_ttf : %s\n", TTF_GetError());
        goto Quit_awale;
    }


    TTF_Font* police = TTF_OpenFont("../police/ARLRDBD.TTF", 40);
    if (police == NULL) {
        fprintf(stderr, "Erreur lors du chargement de la police : %s\n", TTF_GetError());
        TTF_Quit();
        goto Quit_awale;
    }

    SDL_Color couleurTexte = {255, 255, 255};

    SDL_Surface* surface = TTF_RenderText_Blended(police, "AWELE", couleurTexte);
    if (surface == NULL) {
        fprintf(stderr, "Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
        goto Quit_awale;
    }

    SDL_Texture* texteTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    SDL_Rect texteRect;
    texteRect.x = 360;
    texteRect.y = 55;

    SDL_QueryTexture(texteTexture, NULL, NULL, &texteRect.w, &texteRect.h);

    SDL_Rect rectangle1;
    rectangle1.x = 385;
    rectangle1.y = 242;
    rectangle1.w = 250;
    rectangle1.h = 3;

    SDL_Rect rectangle2;
    rectangle2.x = 385;
    rectangle2.y = 388;
    rectangle2.w = 250;
    rectangle2.h = 3;


    char* chemin_complet2 = "../image/bouton_valider0.bmp";


    SDL_Surface *buton_valider = NULL;
    buton_valider = SDL_LoadBMP(chemin_complet2);
    SDL_Texture *buton_text = NULL;
    buton_text = SDL_CreateTextureFromSurface(renderer, buton_valider);

    SDL_Rect destRect = {460, 430, 100, 100};

    TTF_Font* police_joueur = TTF_OpenFont("../police/ARLRDBD.TTF", 20);
    if (police_joueur == NULL) {
        fprintf(stderr, "Erreur lors du chargement de la police : %s\n", TTF_GetError());
        TTF_Quit();
        goto Quit_awale;
    }

    SDL_Color couleurTexteJoueur = {255, 255, 255};

    SDL_Surface* texteSurfaceJoueur1 = TTF_RenderText_Blended(police, "PSEUDO 1 : ", couleurTexteJoueur);
    if (texteSurfaceJoueur1 == NULL) {
        fprintf(stderr, "Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
        goto Quit_awale;
    }

    SDL_Surface* texteSurfaceJoueur2 = TTF_RenderText_Blended(police, "PSEUDO 2 :", couleurTexteJoueur);
    if (texteSurfaceJoueur2 == NULL) {
        fprintf(stderr, "Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
        goto Quit_awale;
    }

    SDL_Texture* texteTextureJoueur1 = SDL_CreateTextureFromSurface(renderer, texteSurfaceJoueur1);
    SDL_FreeSurface(texteSurfaceJoueur1);

    SDL_Texture* texteTextureJoueur2 = SDL_CreateTextureFromSurface(renderer, texteSurfaceJoueur2);
    SDL_FreeSurface(texteSurfaceJoueur2);

    SDL_Rect texteRectJoueur1 ;
    SDL_Rect texteRectJoueur2 ;

    texteRectJoueur1.x = 135;
    texteRectJoueur1.y = 204;

    texteRectJoueur2.x = 135;
    texteRectJoueur2.y = 349;

    SDL_QueryTexture(texteTextureJoueur1, NULL, NULL, &texteRectJoueur1.w, &texteRectJoueur1.h);
    SDL_QueryTexture(texteTextureJoueur2, NULL, NULL, &texteRectJoueur2.w, &texteRectJoueur2.h);


    TTF_Font* police_saisie = TTF_OpenFont("../police/ARLRDBD.TTF", 30);
    if (police_saisie == NULL) {
        fprintf(stderr, "Erreur lors du chargement de la police : %s\n", TTF_GetError());
        TTF_Quit();
        goto Quit_awale;
    }


    Mix_PlayMusic(audio, -1);

    SDL_Surface *surfaceimg = NULL;
    char* image_saisie_joueur = NULL;
    image_saisie_joueur = "../image/background.bmp";
    surfaceimg = SDL_LoadBMP(image_saisie_joueur);
    SDL_Texture *image_text = NULL;
    image_text = SDL_CreateTextureFromSurface(renderer, surfaceimg);
    SDL_FreeSurface(surfaceimg);


    if(NULL == surfaceimg)
    {
    fprintf(stderr, "Erreur SDL_LoadBMP : %s", SDL_GetError());
    goto Quit_awale;
    }
    
    SDL_Event e; 
    
    SDL_bool running = SDL_TRUE;
    
    JOUEUR joueur1 = {"", 0, {385, 187, 250, 50}}; 
    JOUEUR joueur2 = {"", 0, {385, 335, 250, 50}}; 

    int statutRect1 = 0;
    int statutRect2 = 0;

    while(running)
    {
        while(SDL_PollEvent(&e))
        {
            handleInput(e, &joueur1);
            handleInput(e, &joueur2);

            if(e.type == SDL_QUIT)
            {
                running = SDL_FALSE;
            } else if(e.type == SDL_MOUSEBUTTONDOWN) {
                if(e.button.button == SDL_BUTTON_LEFT)
                {
                    int a = e.button.x;
                    int b = e.button.y;
                    if ((a>=460 && a <= 560) && (b>=430 && b <= 530))
                    {
                        
                        if(strcmp(joueur1.pseudo, "") == 0)
                        {
                            statutRect1 = 1;
                            Mix_PlayMusic(audio, 1);
                        }else{
                            statutRect1 = 0;
                        }

                        if(strcmp(joueur2.pseudo, "") == 0)
                        {
                            statutRect2 = 1;
                            Mix_PlayMusic(audio, 1);
                        }else{
                            statutRect2 = 0;
                        }
                        

                        if ( (strcmp(joueur1.pseudo, "") != 0) && (strcmp(joueur2.pseudo, "") != 0) ) {

                            statutRect1 = 0;
                            statutRect2 = 0;
                            strcpy(pseudos_finaux.pseudo1, joueur1.pseudo);
                            strcpy(pseudos_finaux.pseudo2, joueur2.pseudo);

                            goto Quit_awale ;

                        }
                        
                    }
                   
                }

            }


            SDL_RenderCopy(renderer, image_text, NULL, NULL);

            SDL_RenderCopy(renderer, texteTexture, NULL, &texteRect);

            SDL_RenderCopy(renderer, texteTextureJoueur1, NULL, &texteRectJoueur1);

            SDL_RenderCopy(renderer, texteTextureJoueur2, NULL, &texteRectJoueur2);

            SDL_RenderCopy(renderer, buton_text, NULL, &destRect); 
            
            if(statutRect1 == 1)
            {
                drawInputRectangleRED(&joueur1, renderer, police_saisie);
                aff_rect_red(renderer,&rectangle1);
            }else {
                drawInputRectangle(&joueur1, renderer, police_saisie);
                aff_rect(renderer, &rectangle1);
            }
            
            if (statutRect2 == 1) {
                drawInputRectangleRED(&joueur2, renderer, police_saisie);
                aff_rect_red(renderer, &rectangle2);
            } else {
                drawInputRectangle(&joueur2, renderer, police_saisie);
                aff_rect(renderer, &rectangle2);
            }
        

            SDL_RenderPresent(renderer);
        }

    }

    Quit_awale : 

    SDL_Delay(10); 
    SDL_DestroyRenderer(renderer);   
    SDL_DestroyWindow(window);     

    Mix_FreeMusic(audio);  
    Mix_CloseAudio();  

    SDL_Quit();  
   

    return pseudos_finaux;

}




