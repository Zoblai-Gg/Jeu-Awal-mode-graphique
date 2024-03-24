
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "gameOver.h"
#include "init_awele.h"
#include "jouer_update.h"
#include "affiche_awele.h"
#include "menu.h"
#include "saisi_pseudo0.h"
#include "welcome.h"
#include "logo.h"
#include "contre_pc.h"




int jouer_a_2(PSEUDO_JOUEUR *player_mame)
{
    srand(time(NULL));
    int **contenu_tablier = NULL;
    int toplay,fin_de_partie = 0, over;
    int case_choisie, fin = 1;
    SDL_Window *window  = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *texture = NULL;
    SDL_Texture *background = NULL;
    SDL_Texture *tablier = NULL;
    SDL_Texture *graine = NULL;
    SDL_Rect *coor_tablier = NULL;
    SDL_Event event;
    SDL_bool quit = SDL_FALSE;
    JOUEUR joueur,joueur2;
    joueur.num = 1; joueur2.num = 2;
    joueur.recolte = 0; joueur2.recolte = 0;

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



    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Erreur sur initialisation de la SDL2 ! %s \n", SDL_GetError());
        goto Quit;
    }
    if (Init_SDL_Functions(&window, &renderer, &texture) == SDL_FALSE) {
        goto Quit;
    }

    Charger_Image(&background, &tablier, &graine, &renderer);
    coor_tablier = Initialse_Coor_Tablier();
    contenu_tablier = Initialise_Graine_Tablier();

    toplay = choix_du_joueur();//choisi aléatoirement qui va jouer en premier

    while (!quit) {
        //Affichier le tablier sans les pions
        SDL_RenderCopy(renderer, background, NULL, NULL);
        Charger_Affiche_pseudo(&renderer, &joueur, &joueur2, toplay,*player_mame);
        Charger_Affiche_score(&renderer, &joueur, &joueur2);
        for (int i = 0; i < 12; ++i) {
            SDL_RenderCopy(renderer, tablier, NULL, &coor_tablier[i]);
        }

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE) {
                quit = SDL_TRUE;
                fin = 0;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                SDL_Point point;

                point.x = event.button.x;
                point.y = event.button.y;
                case_choisie = Renvoyer_Choix_Joueur(point, coor_tablier);

                if (toplay == joueur.num && (case_choisie >= 0 && case_choisie < 6)) {
                    if (contenu_tablier[0][case_choisie] != 0) { // restreint la possibilité au joueurr de jouer dans une case vide

                        Toshow_click(&renderer, coor_tablier,case_choisie); // Montre la case sur laquelle nous avons cliqué
                        SDL_RenderPresent(renderer);
                        SDL_Delay(10);

                        Fonction_semer(contenu_tablier, &joueur, case_choisie);
                        if (recolter(contenu_tablier, &joueur) == 1) {
                            fin_de_partie = 0;
                        } else {
                            fin_de_partie++;
                        }
                        toplay = 2;
                    }
                } else if (toplay == joueur2.num && (case_choisie >= 6 && case_choisie < 12)) {
                    if (contenu_tablier[1][case_choisie - 6] != 0) {

                        Toshow_click(&renderer, coor_tablier,
                                     case_choisie); // Montre la case sur laquelle nous avons cliqué
                        SDL_RenderPresent(renderer);
                        SDL_Delay(10);

                        Fonction_semer(contenu_tablier, &joueur2, case_choisie - 6);
                        if (recolter(contenu_tablier, &joueur2) == 1) {
                            fin_de_partie = 0;
                        } else {
                            fin_de_partie++;
                        }
                        toplay = 1;
                    }
                }
            }
            SDL_Delay(10);
        }
        //Afficher le jeu
        charger_graine_tablier(&renderer, &graine, contenu_tablier);

        SDL_RenderPresent(renderer);
        SDL_Delay(10);

        //Tester fin de jeu

        over = TestergameOver(joueur, joueur2, contenu_tablier, fin_de_partie);
        if (over != -1) {
            quit = SDL_TRUE;
        }
    }

    if( fin != 0) {
        over = Game_Over(joueur, joueur2, over,*player_mame);

        player_mame->score1 = joueur.recolte ;
        player_mame->score2 = joueur2.recolte;
    } else{
        over = -1;
    }


    Quit :
    free(tablier);
    Mix_FreeMusic(music);
    Mix_CloseAudio();
   // Destroy_SDL_Function(&window, &renderer, &texture);
    return over;
}



int jouerContre_PC(PSEUDO_JOUEUR *player_mame)
{
    srand(time(NULL));
    int **contenu_tablier = NULL;
    int toplay,fin_de_partie = 0, over;
    int case_choisie, fin = 1;
    SDL_Window *window  = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *texture = NULL;
    SDL_Texture *background = NULL;
    SDL_Texture *tablier = NULL;
    SDL_Texture *graine = NULL;
    SDL_Rect *coor_tablier = NULL;
    SDL_Event event;
    SDL_bool quit = SDL_FALSE;
    JOUEUR joueur,joueur2;
    joueur.num = 1; joueur2.num = 2;
    joueur.recolte = 0; joueur2.recolte = 0;


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



    strcpy(player_mame->pseudo1, "Ordi");
    strcpy(player_mame->pseudo2, "Hote");

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Erreur sur initialisation de la SDL2 ! %s \n", SDL_GetError());
        goto Quit;
    }
    if (Init_SDL_Functions(&window, &renderer, &texture) == SDL_FALSE) {
        goto Quit;
    }

    Charger_Image(&background, &tablier, &graine, &renderer);
    coor_tablier = Initialse_Coor_Tablier();
    contenu_tablier = Initialise_Graine_Tablier();

    toplay = choix_du_joueur();//choisi aléatoirement qui va jouer en premier



    while (!quit) {
        //Affichier le tablier sans les pions
        SDL_RenderCopy(renderer, background, NULL, NULL);
        Charger_Affiche_pseudo(&renderer, &joueur, &joueur2, toplay,*player_mame);
        Charger_Affiche_score(&renderer, &joueur, &joueur2);

        for (int i = 0; i < 12; ++i) {
            SDL_RenderCopy(renderer, tablier, NULL, &coor_tablier[i]);
        }

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE) {
                quit = SDL_TRUE;
                fin = 0;
            }

            if (toplay == joueur.num) {
                SDL_Delay(500);
                case_choisie = choix_du_case_pc(&joueur, contenu_tablier); //Choix d'une case par le PC
                case_choisie = case_choisie - 1;
                if (toplay == joueur.num && (case_choisie >= 0 && case_choisie < 6)) {
                    if (contenu_tablier[0][case_choisie] != 0) { // restreint la possibilité au joueurr de jouer dans une case vide

                        Toshow_click(&renderer, coor_tablier,case_choisie); // Montre la case sur laquelle nous avons cliqué
                        SDL_RenderPresent(renderer);
                        SDL_Delay(10);

                        Fonction_semer(contenu_tablier, &joueur, case_choisie);
                        if (recolter(contenu_tablier, &joueur) == 1) {
                            fin_de_partie = 0;
                        } else {
                            fin_de_partie++;
                        }
                        toplay = 2;
                    }
                }

            } else if (toplay == joueur2.num) {

                while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE) {
                        quit = SDL_TRUE;
                        fin = 0;
                    }else if (event.type == SDL_MOUSEBUTTONDOWN) {
                        SDL_Point point;
                        point.x = event.button.x;
                        point.y = event.button.y;

                        case_choisie = Renvoyer_Choix_Joueur(point, coor_tablier);

                        if (case_choisie >= 6 && case_choisie < 12) {
                            if (contenu_tablier[1][case_choisie - 6] != 0) {

                                Toshow_click(&renderer, coor_tablier,
                                             case_choisie); // Montre la case sur laquelle nous avons cliqué
                                SDL_RenderPresent(renderer);
                                SDL_Delay(10);

                                Fonction_semer(contenu_tablier, &joueur2, case_choisie - 6);
                                if (recolter(contenu_tablier, &joueur2) == 1) {
                                    fin_de_partie = 0;
                                } else {
                                    fin_de_partie++;
                                }
                                toplay = 1;
                            }
                        }
                    }
                }
            }
        }

        //Afficher le jeu
        charger_graine_tablier(&renderer, &graine, contenu_tablier);
        SDL_RenderPresent(renderer);
        SDL_Delay(500);

        //Tester fin de jeu
        over = TestergameOver(joueur, joueur2, contenu_tablier, fin_de_partie);
        if (over != -1) {
            quit = SDL_TRUE;
        }
    }

    if( fin != 0) {
        over = Game_Over(joueur, joueur2, over,*player_mame);

        player_mame->score1 = joueur.recolte ;
        player_mame->score2 = joueur2.recolte;

    } else{
        over = -1;
    }


    Quit :
    free(tablier);
    Mix_FreeMusic(music);
    Mix_CloseAudio();
    //Destroy_SDL_Function(&window, &renderer, &texture);

    return over;
}



