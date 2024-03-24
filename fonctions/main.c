#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <SDL2/SDL_mixer.h>

#include "gameOver.h"
#include "init_awele.h"
#include "jouer_update.h"
#include "affiche_awele.h"
#include "menu.h"
#include "saisi_pseudo0.h"
#include "welcome.h"
#include "logo.h"
#include "awele.h"
#include "save.h"
#include "affiche_scoreUI.h"
#include "a_propos.h"
#include "contre_pc.h"

int main(int argc, char const *argv[])
{

    int choix, retour, fin =1;
    PSEUDO_JOUEUR player_mame;
    JOUEUR_SCORE joueur1, joueur2;

    choix = logo(); // affiche logo
    if(choix == -1){
        goto Quit;
    }
    choix = welcome(); // Affiche la fenetre de bienvenue ... Return -1 si le joueur ferme la fenêtre
    if(choix == -1){
        goto Quit;
    }


    do{
        choix  = Menu(); // Affichier menu

        if (choix == PLAY_AT_2) {
            do{
                player_mame = saisi_pseudo0();

                retour = jouer_a_2(&player_mame);

                strcpy(joueur1.pseudo,player_mame.pseudo1);
                joueur1.score = player_mame.score1;
                strcpy(joueur2.pseudo,player_mame.pseudo2);
                joueur2.score = player_mame.score2;

                enregister( joueur1, joueur2);
                trifplayer();


            } while (retour != -1 );
        }
        else if( choix ==  CONTRE_ORDI ){

            do{

                retour = jouerContre_PC(&player_mame);

                strcpy(joueur1.pseudo,player_mame.pseudo1);
                joueur1.score = player_mame.score1;
                strcpy(joueur2.pseudo,player_mame.pseudo2);
                joueur2.score = player_mame.score2;
                if(retour ==-1)
                    fin = 0;

            } while (retour != -1);
        }
        else if( choix ==  SCORE ){
            fin =affiche_scoreUI() ;

        } else if( choix ==  ABOUT ){

            fin = a_propos();
        }else if( choix ==  QUITTER ){
            fin =0;
        }

   } while (fin);

Quit :

    return 0;
}

