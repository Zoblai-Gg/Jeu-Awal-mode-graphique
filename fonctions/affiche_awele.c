#include "affiche_awele.h"
#include "init_awele.h"
#include <SDL2/SDL_mixer.h>


void Charger_Affiche_pseudo(SDL_Renderer **renderer,JOUEUR *joueur1,JOUEUR *joueur2, int toplay,PSEUDO_JOUEUR player_mame) {


    if (TTF_Init() != 0) {
        fprintf(stderr, "Erreur sur initialisation de la SDL2 ! %s \n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    TTF_Font *font;
    SDL_Texture *texture;
    SDL_Surface *surface_texte = NULL;
    SDL_Color blanc = {255, 255, 255, 255};
    SDL_Rect rect = {20, 20, 0, 0};
    SDL_Rect rect2 = {920-((int)strlen(player_mame.pseudo2)*22), 20, 0, 0};
    SDL_Rect rect_info = {200, 470, 0, 0};

    font = TTF_OpenFont("../police/regular.ttf", 50);

    surface_texte = TTF_RenderText_Solid(font, player_mame.pseudo1, blanc);
    joueur1->pseudo = SDL_CreateTextureFromSurface(*renderer, surface_texte);
    SDL_FreeSurface(surface_texte);
    surface_texte = TTF_RenderText_Solid(font, player_mame.pseudo2, blanc);
    joueur2->pseudo = SDL_CreateTextureFromSurface(*renderer, surface_texte);
    SDL_FreeSurface(surface_texte);

    TTF_CloseFont(font); // Charger police de la partie info
    font = TTF_OpenFont("../police/arial.TTF", 30);

    char info[100] ="";
    if(toplay == 1){
        strcpy(info,player_mame.pseudo1);
        strcat(info,", toi de jouer (partie haute)");
        surface_texte = TTF_RenderText_Solid(font, info, blanc);
        texture = SDL_CreateTextureFromSurface(*renderer, surface_texte);
        SDL_FreeSurface(surface_texte);

    } else if(toplay == 2){
        strcpy(info,player_mame.pseudo2);
        strcat(info,", toi de jouer (partie basse)");
        surface_texte = TTF_RenderText_Solid(font, info, blanc);
        texture = SDL_CreateTextureFromSurface(*renderer, surface_texte);
        SDL_FreeSurface(surface_texte);

    }

    SDL_QueryTexture(joueur1->pseudo, NULL, NULL, &rect.w, &rect.h);
    SDL_RenderCopy(*renderer, joueur1->pseudo, NULL, &rect);
    SDL_QueryTexture(joueur2->pseudo, NULL, NULL, &rect2.w, &rect2.h);
    SDL_RenderCopy(*renderer, joueur2->pseudo, NULL, &rect2);
    // Preciser sur le rendu le tour de celui qui doit jouer
    SDL_QueryTexture(texture, NULL, NULL, &rect_info.w, &rect_info.h);
    SDL_RenderCopy(*renderer, texture, NULL, &rect_info);

    TTF_CloseFont(font);
    TTF_Quit();

}

void Charger_Affiche_score(SDL_Renderer **renderer,JOUEUR *joueur1,JOUEUR *joueur2)
{
    char score[15];

    if (TTF_Init() != 0) {
        fprintf(stderr, "Erreur sur initialisation de la SDL2 ! %s \n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    TTF_Font *font;

    SDL_Surface *surface_texte = NULL;
    SDL_Color blanc = {255, 255, 255, 255};
    SDL_Rect rect = {40, 70, 0, 0};
    SDL_Rect rect2 = {850, 70, 0, 0};

    font = TTF_OpenFont("../police/Brumery_Demo.ttf", 40);

    sprintf(score, "%d", joueur1->recolte);
    surface_texte = TTF_RenderText_Solid(font,score , blanc);
    joueur1->pseudo = SDL_CreateTextureFromSurface(*renderer, surface_texte);
    SDL_FreeSurface(surface_texte);

    sprintf(score, "%d", joueur2->recolte);
    surface_texte = TTF_RenderText_Solid(font, score, blanc);
    joueur2->pseudo = SDL_CreateTextureFromSurface(*renderer, surface_texte);
    SDL_FreeSurface(surface_texte);

    SDL_QueryTexture(joueur1->pseudo, NULL, NULL, &rect.w, &rect.h);
    SDL_RenderCopy(*renderer, joueur1->pseudo, NULL, &rect);
    SDL_QueryTexture(joueur2->pseudo, NULL, NULL, &rect2.w, &rect2.h);
    SDL_RenderCopy(*renderer, joueur2->pseudo, NULL, &rect2);

    TTF_CloseFont(font);
    TTF_Quit();

}
