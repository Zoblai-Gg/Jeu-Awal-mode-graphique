#include "init_awele.h"
#include "gameOver.h"

//Cette fonctio renvoie 1 ou 2 pour designer le gagnant, renvoie <à en cas d'égalité sion renvoie -1
int TestergameOver(JOUEUR joueur1,JOUEUR joueur2,int **plateau,int fin_de_partie)
{
    if(joueur1.recolte >= 19|| joueur2.recolte >=19){
        if ( joueur1.recolte >= 19){
            return 1;
        } else {
            return 2;
        }

    } else if( verifCaseVide(plateau) || fin_de_partie == 20){
        if(joueur1.recolte == joueur2.recolte ){
            return 0;
        }
        else if ( joueur1.recolte > joueur2.recolte  ){
            return 1;
        }
        else {
            return 2;
        }
    }
    return -1 ;
}
// vérifie si toutes les case d'un jour est vide

SDL_bool verifCaseVide(int **plateau)
{
    SDL_bool bool ;

    for (int i = 0; i < NB_ROWS; ++i) {
        bool= SDL_TRUE ;
        for (int j = 0; j < NB_CASES; ++j) {
            if(plateau[i][j] != 0){
                bool = SDL_FALSE;
            }
            if(bool == SDL_FALSE)
                break;
        }
        if(bool == SDL_TRUE){
            return bool;
        }
    }

    return bool ;
}

int Game_Over(JOUEUR joueur1,JOUEUR joueur2, int over,PSEUDO_JOUEUR player_mame)
{
    int val;
    SDL_Surface *surface = NULL;
    SDL_Texture *texture = NULL;
    SDL_Texture *btn_bleu = NULL;
    SDL_Texture *btn_rouge = NULL;
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Color blanc = {255, 255, 255, 255};
    SDL_Rect rect = {150, 70, 0, 0};
    SDL_Rect rect_r = {90, 350, 0, 0};
    SDL_Rect rect_b = {590, 350, 0, 0};
    SDL_Rect rect_quitter = {125, 355, 0, 0};
    SDL_Rect rect_reppredre = {600, 355, 0, 0};


    SDL_bool quit = SDL_FALSE;


    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Erreur sur initialisation de la SDL2 ! %s \n", SDL_GetError());
        goto Quit;
    }

    if (Init_SDL_Functions(&window, &renderer, &texture) == SDL_FALSE) {
        goto Quit;
    }


    if (TTF_Init() != 0) {
        fprintf(stderr, "Erreur sur initialisation de la SDL2 ! %s \n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    TTF_Font *font;

    font = TTF_OpenFont("../police/arial.TTF", 40);

    surface = SDL_LoadBMP("../image/over.bmp");
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);


    surface = SDL_LoadBMP("../image/buttn.bmp");
    btn_bleu = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_QueryTexture(btn_bleu, NULL, NULL, &rect_b.w, &rect_b.h);
    SDL_RenderCopy(renderer, btn_bleu, NULL, &rect_b);
    SDL_FreeSurface(surface);
    surface = TTF_RenderText_Solid(font, " Reprendre ", blanc);
    btn_bleu = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_QueryTexture(btn_bleu, NULL, NULL, &rect_reppredre.w, &rect_reppredre.h);
    SDL_RenderCopy(renderer, btn_bleu, NULL, &rect_reppredre);

    surface = SDL_LoadBMP("../image/buttn2.bmp");
    btn_rouge = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_QueryTexture(btn_rouge, NULL, NULL, &rect_r.w, &rect_r.h);
    SDL_RenderCopy(renderer, btn_rouge, NULL, &rect_r);
    SDL_FreeSurface(surface);
    surface = TTF_RenderText_Solid(font, " Quitter ", blanc);
    btn_rouge = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_QueryTexture(btn_rouge, NULL, NULL, &rect_quitter.w, &rect_quitter.h);
    SDL_RenderCopy(renderer, btn_rouge, NULL, &rect_quitter);


    char info[100] ="";

    SDL_FreeSurface(surface);
    // apres on pour concatener les noms aux textes ...
    if (over == 1) {
        strcpy(info,player_mame.pseudo1);
        strcat(info," remporte la partie");
        surface = TTF_RenderText_Solid(font, info, blanc);
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
        SDL_RenderCopy(renderer, texture, NULL, &rect);

    } else if (over == 2) {
        strcpy(info,player_mame.pseudo1);
        strcat(info," remporte la partie");
        surface = TTF_RenderText_Solid(font, info, blanc);
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
        SDL_RenderCopy(renderer, texture, NULL, &rect);

    } else {
        surface = TTF_RenderText_Solid(font, " Vous avez fait egalite", blanc);
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
        SDL_RenderCopy(renderer, texture, NULL, &rect);
    }

    SDL_RenderPresent(renderer);
    SDL_Event event;

    while (!quit) {

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE) {
                quit = SDL_TRUE;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {

                SDL_Point point;
                point.x = event.button.x ;point.y = event.button.y ;
                //renvoie 0 pour quitter le jeu et 1 pour rependre

                if((point.x > rect_b.x && point.x < rect_b.x+rect_b.w) && (point.y > rect_b.y && point.y <rect_b.y+rect_b.h)){
                    val = 0 ;
                    quit = SDL_TRUE;
                }else if((point.x >= rect_r.x && point.x <rect_r.x+rect_r.w) && (point.y > rect_r.y && point.y <rect_r.y+rect_r.h)){
                    val = -1;
                    quit = SDL_TRUE;
                }

            }
        }

    }

    Quit :
    Destroy_SDL_Function(&window,&renderer,&texture);
    return val;

}


