#include "jouer_update.h"
#include "gameOver.h"


void charger_graine_tablier( SDL_Renderer ** renderer, SDL_Texture **texture, int ** contenu_tablier)
{
    for (int i = 0; i < NB_ROWS; ++i) {
        for (int j = 0; j <NB_CASES ; ++j) {
            if(i == 0){
                update_coor_Case(renderer,texture,contenu_tablier[i][j],j);

            } else{
                update_coor_Case(renderer,texture,contenu_tablier[i][j],j + NB_CASES);

            }
        }
    }
}

int Renvoyer_Choix_Joueur(SDL_Point coor, SDL_Rect *coor_tablier)
{
    //Permetde detecter la case choisi par le joueur
    for (int i = 0; i < 12; ++i) {
        if ((coor.x > coor_tablier[i].x && coor.x < coor_tablier[i].x + coor_tablier[i].w) && (coor.y > coor_tablier[i].y && coor.y < coor_tablier[i].y + coor_tablier[i].h)) {
            return i;
        }
    }
    return 1;
}

void Fonction_semer(int **contenu_tablier,JOUEUR *joueur,int case_choisie)
{
    int nb_pion,i,j,k;

    if(joueur->num == 1){
        nb_pion = contenu_tablier[0][case_choisie];
        contenu_tablier[0][case_choisie]=0;
        j=0;
        for (i = 1; i <= nb_pion; ++i) {
            k=case_choisie-i;
            if(k >= 0){
                contenu_tablier[0][k]++;
                joueur->last_case_played.x=0;
                joueur->last_case_played.y= k;

            }else if (j < 6){
                contenu_tablier[1][j]++;
                joueur->last_case_played.x=1;
                joueur->last_case_played.y= j; j++;
            } else{
                i--; case_choisie = 6; j=0;
            }
        }
    } else if(joueur->num == 2){
        nb_pion = contenu_tablier[1][case_choisie];
        contenu_tablier[1][case_choisie]=0;
        j=5;
        for (i = 1; i <= nb_pion; ++i) {
            k=case_choisie+i;
            if(k < 6){
                contenu_tablier[1][k]++;
                joueur->last_case_played.x=1;
                joueur->last_case_played.y= k;

            }else if (j >= 0){
                contenu_tablier[0][j]++;
                joueur->last_case_played.x=0;
                joueur->last_case_played.y= j;     j--;
            } else{
                i--; case_choisie = -1; j=5;
            }
        }
    }

}

// return 1 pour remttre le compteur de fin de jeu à 0;
int recolter(int **contenu_tablier,JOUEUR *joueur)
{
    int nb_graine = contenu_tablier[joueur->last_case_played.x][joueur->last_case_played.y];
    // 	Cette fonction fait la récolte si la dernère case contient 2 ou 3 boules, et si c'est le cas elle ajoute le nombre au gain du joueur
    if(nb_graine == 2 || nb_graine == 3 ){
        joueur->recolte+=nb_graine;
        contenu_tablier[joueur->last_case_played.x][joueur->last_case_played.y]=0;
        return 1;
    }
    return 0;
}

int choix_du_joueur(void)
{
    int valeur =(rand()%10);
    if(valeur%2 == 0){
        return 1;
    }
    return 2;
}

void update_coor_Case(SDL_Renderer **renderer, SDL_Texture **texture,int nb_graine,int rang_case)
{
    //On prend le notre de pion et on alloue un tableau avec le nombre de pion !
    int distance = 140;

    SDL_Rect *rect = malloc(nb_graine*sizeof(SDL_Rect));

    for (int i = 0; i < nb_graine; ++i) {

        if(rang_case < 6){
            if(i == 0){
                rect[0].x = 60 + distance*rang_case; rect[0].y = 210; rect[0].w = 35; rect[0].h = 35;
                SDL_RenderCopy(*renderer,*texture,NULL,&rect[0]);
            }else if(i == 1){
                rect[1].x = 60 + 10 + distance*rang_case; rect[1].y = 210 - 15; rect[1].w = 35; rect[1].h = 35;
                SDL_RenderCopy(*renderer,*texture,NULL,&rect[1]);
            }else if(i == 2){
                rect[2].x = 60 + 10 + distance*rang_case; rect[2].y = 210 + 15; rect[2].w = 35; rect[2].h = 35;
                SDL_RenderCopy(*renderer,*texture,NULL,&rect[2]);
            }else if(i == 3){
                rect[3].x = 60 + 10 +10 + 10 + distance*rang_case; rect[3].y = 210 - 15 - 15; rect[3].w = 35; rect[3].h = 35;
                SDL_RenderCopy(*renderer,*texture,NULL,&rect[3]);
            }else if(i == 4){
                rect[4].x = 60 + 10 +10 + 10 + distance*rang_case; rect[4].y = 210 - 15 ;     rect[4].w = 35; rect[4].h = 35;
                SDL_RenderCopy(*renderer,*texture,NULL,&rect[4]);
            }else if(i == 5){
                rect[5].x = 60 + 10 +10 + distance*rang_case;      rect[5].y = 210 ;      rect[5].w = 35; rect[5].h = 35;
                SDL_RenderCopy(*renderer,*texture,NULL,&rect[5]);
            }else if(i == 6){
                rect[6].x = 60 + 10 +10 + 10 + distance*rang_case; rect[6].y = 210 + 15 ;     rect[6].w = 35; rect[6].h = 35;
                SDL_RenderCopy(*renderer,*texture,NULL,&rect[6]);
            }else if(i == 7){
                rect[7].x = 60 + 10 +10 + 10 + distance*rang_case; rect[7].y = 210 + 15 +15;  rect[7].w = 35; rect[7].h = 35;
                SDL_RenderCopy(*renderer,*texture,NULL,&rect[7]);
            }else if(i == 8){
                rect[8].x = 60 + 10 +10 + 10 + 10 + 10 + distance*rang_case;  rect[8].y = 210 - 15;  rect[8].w = 35;  rect[8].h = 35;
                SDL_RenderCopy(*renderer,*texture,NULL,&rect[8]);
            }else if(i == 9){
                rect[9].x = 60 + 10 +10 + 10 + 10 + distance*rang_case;       rect[9].y = 210 ;      rect[9].w = 35;  rect[9].h = 35;
                SDL_RenderCopy(*renderer,*texture,NULL,&rect[9]);
            }else if(i == 10){
                rect[10].x = 60 + 10 +10 + 10 + 10 + 10 + distance*rang_case; rect[10].y = 210 +15;  rect[10].w = 35; rect[10].h = 35;
                SDL_RenderCopy(*renderer,*texture,NULL,&rect[10]);
            }else if(i == 11){
                rect[11].x = 60 + 10 +10 + 10 + 10 + 10 + 10 + distance*rang_case;      rect[11].y = 210 ;      rect[11].w = 35;  rect[11].h = 35;
                SDL_RenderCopy(*renderer,*texture,NULL,&rect[11]);
            }
        }
        else{

            if (i == 0){
                rect[0].x = 60 + distance* (rang_case-6); rect[0].y = 210 + distance; rect[0].w = 35; rect[0].h = 35 ;
                SDL_RenderCopy(*renderer,*texture,NULL,&rect[0]);
            }else if(i == 1){
                rect[1].x = 60 + 10 + distance* (rang_case -6); rect[1].y = 210 - 15 + distance; rect[1].w = 35; rect[1].h = 35 ;
                SDL_RenderCopy(*renderer,*texture,NULL,&rect[1]);
            }else if(i == 2){
                rect[2].x = 60 + 10 + distance* (rang_case -6); rect[2].y = 210 + 15 + distance; rect[2].w = 35; rect[2].h = 35 ;
                SDL_RenderCopy(*renderer,*texture,NULL,&rect[2]);
            }else if(i == 3){
                rect[3].x = 60 + 10 +10 + 10 + distance* (rang_case -6); rect[3].y = 210 - 15 - 15 + distance; rect[3].w = 35; rect[3].h = 35 ;
                SDL_RenderCopy(*renderer,*texture,NULL,&rect[3]);
            }else if(i == 4){
                rect[4].x = 60 + 10 +10 + 10 + distance* (rang_case -6); rect[4].y = 210 - 15 + distance;     rect[4].w = 35; rect[4].h = 35 ;
                SDL_RenderCopy(*renderer,*texture,NULL,&rect[4]);
            }else if(i == 5){
                rect[5].x = 60 + 10 +10 + distance*(rang_case -6);      rect[5].y = 210 + distance;      rect[5].w = 35; rect[5].h = 35 ;
                SDL_RenderCopy(*renderer,*texture,NULL,&rect[5]);
            }else if(i == 6){
                rect[6].x = 60 + 10 +10 + 10 + distance*(rang_case -6); rect[6].y = 210 + 15 + distance;     rect[6].w = 35; rect[6].h = 35;
                SDL_RenderCopy(*renderer,*texture,NULL,&rect[6]);
            }else if(i == 7){
                rect[7].x = 60 + 10 +10 + 10 + distance* (rang_case -6); rect[7].y = 210 + 15 +15 + distance;  rect[7].w = 35; rect[7].h = 35 ;
                SDL_RenderCopy(*renderer,*texture,NULL,&rect[7]);
            }else if(i == 8){
                rect[8].x = 60 + 10 +10 + 10 + 10 + 10 + distance* (rang_case -6);  rect[8].y = 210 - 15 + distance;  rect[8].w = 35;  rect[8].h = 35 ;
                SDL_RenderCopy(*renderer,*texture,NULL,&rect[8]);
            }else if(i == 9){
                rect[9].x = 60 + 10 +10 + 10 + 10 + distance* (rang_case -6);       rect[9].y = 210 + distance;      rect[9].w = 35;  rect[9].h = 35 ;
                SDL_RenderCopy(*renderer,*texture,NULL,&rect[9]);
            }else if(i == 10){
                rect[10].x = 60 + 10 +10 + 10 + 10 + 10 + distance* (rang_case -6); rect[10].y = 210 +15 + distance;  rect[10].w = 35; rect[10].h = 35 ;
                SDL_RenderCopy(*renderer,*texture,NULL,&rect[10]);
            }else if(i == 11){
                rect[11].x = 60 + 10 +10 + 10 + 10 + 10 + 10 + distance* (rang_case -6);      rect[11].y = 210 + distance ;      rect[11].w = 35;  rect[11].h = 35 ;
                SDL_RenderCopy(*renderer,*texture,NULL,&rect[11]);
            }
        }
    }
    free(rect);

}

void Toshow_click(SDL_Renderer **renderer ,SDL_Rect *coor_tablier,int case_choisie)
{

    SDL_Color noir = {0,0,0,100};

    SDL_SetRenderDrawColor(*renderer, noir.r, noir.g, noir.b, noir.a);
    SDL_RenderFillRect(*renderer, &coor_tablier[case_choisie]);
    SDL_SetRenderDrawBlendMode(*renderer, SDL_BLENDMODE_BLEND);

}
