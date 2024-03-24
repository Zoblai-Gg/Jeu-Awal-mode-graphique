//
// Created by zoblaigg on 17/01/24.
//
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#ifndef JEU_AWALE_MENU_H
#define JEU_AWALE_MENU_H

#define PIXEL 20
#define NB_BOUTON_MAX 5
#define PLAY_AT_2 1
#define CONTRE_ORDI 2
#define SCORE 3
#define ABOUT  4
#define QUITTER -1

void intilise_Coor_Bouton(SDL_Rect * rect,SDL_Rect *rect1);
void Charger_Image_menu(SDL_Texture **background,SDL_Texture **button_blue,SDL_Texture **button_red, SDL_Renderer **renderer);
void Deplacer_Bouton(SDL_Texture **button_blue,SDL_Texture **button_red, SDL_Renderer **renderer, int deplace,SDL_Rect *rect,SDL_Rect *rect1);
void Envoyer_Emplacemnt_Souris(SDL_Point coor, int *deplacer);
void Charger_menu_texte(SDL_Renderer **renderer,SDL_Texture **texture);
void Afficher_menu_texte(SDL_Texture *texture[],SDL_Renderer **renderer);
int Click_button_keyboard(int deplacer);
int Click_button_mouse(SDL_Point coor);
int Menu(void);

#endif //JEU_AWALE_MENU_H
