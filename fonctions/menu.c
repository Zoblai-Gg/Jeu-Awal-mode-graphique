#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "init_awele.h"




SDL_bool effet ;

int Menu(void)
{
    //int status = EXIT_FAILURE;
    SDL_Window *window  = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *texture = NULL;
    SDL_Texture *background = NULL;
    SDL_Texture * texture_bttn_blue= NULL;
    SDL_Texture * texture_bttn_red= NULL;
    SDL_Texture *texture_texte[NB_BOUTON_MAX];
    SDL_Rect rect_bouton[NB_BOUTON_MAX];
    SDL_Rect rect_bouton_effet[NB_BOUTON_MAX];
    SDL_Event event;
    SDL_bool quit = SDL_FALSE ;
    int deplacer =1;
    int val_retour;

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



    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        fprintf(stderr,"Erreur sur initialisation de la SDL2 ! %s \n",SDL_GetError());
        goto Quit;
    }

    if (Init_SDL_Functions(&window,&renderer,&texture) == SDL_FALSE){
        goto Quit;
    }
     intilise_Coor_Bouton(rect_bouton,rect_bouton_effet);

    Charger_Image_menu(&background,&texture_bttn_blue,&texture_bttn_red,&renderer);

    Charger_menu_texte(&renderer,texture_texte);

    while (!quit){
        SDL_RenderCopy(renderer,background,NULL,NULL);
        if(effet == SDL_TRUE){
            Deplacer_Bouton(&texture_bttn_blue,&texture_bttn_red, &renderer, deplacer,rect_bouton,rect_bouton_effet);

        } else{
            Deplacer_Bouton(&texture_bttn_blue,&texture_bttn_red, &renderer, deplacer,rect_bouton,rect_bouton_effet);

        }

        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT ||event.key.keysym.sym == SDLK_ESCAPE ){
                quit = SDL_TRUE;
                val_retour = -1;
            }
            else if(event.type == SDL_KEYDOWN)
            {
                if(event.key.keysym.sym == SDLK_UP){
                    deplacer--;
                    if(deplacer < 1) deplacer =1 ;

                }
                else if (event.key.keysym.sym == SDLK_DOWN){

                    deplacer++;
                    if(deplacer >5) deplacer =NB_BOUTON_MAX ;
                }
                // On va d'accéder aux fonctionalités du menu par la souris
                if (event.key.keysym.sym == SDLK_RETURN){
                    // Appel de la fonction permettant de determiner le bouton selectioné coté clavier
                    val_retour = Click_button_keyboard(deplacer);
                    quit = SDL_TRUE;
                }
            }
            else if(event.type == SDL_MOUSEMOTION){

                SDL_Point mouse_position;
                SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
                Envoyer_Emplacemnt_Souris(mouse_position, &deplacer);
                effet =SDL_TRUE;
            }
            else if(event.type == SDL_MOUSEBUTTONDOWN){
                // On va d'accéder aux fonctionalités du menu par la souris
                if((event.button.button == SDL_BUTTON_LEFT && event.button.clicks >= 1) || event.button.button == SDL_BUTTON_RIGHT){

                    SDL_Point pos; pos.x = event.button.x; pos.y = event.button.y;
                    // Appel de la fonction permettant de determiner le bouton selectioné coté souris
                    val_retour = Click_button_mouse(pos);
                    if( val_retour != 0 ){
                        quit = SDL_TRUE;
                    }
                }
            }
        }
        Afficher_menu_texte(texture_texte,&renderer);

        SDL_RenderPresent(renderer);
    }

   // status =EXIT_SUCCESS;
    Quit :
    Mix_FreeMusic(music);
    Mix_CloseAudio();
    Destroy_SDL_Function(&window,&renderer,&texture);
    return val_retour;
}




void intilise_Coor_Bouton(SDL_Rect *rect,SDL_Rect *rect1)
{
    // Pour 1er tableau
    rect[0].x = 260; rect[0].y = 180;rect[0].w = 400;rect[0].h = 60;
    rect[1].x = 260; rect[1].y = 260;rect[1].w = 400;rect[1].h = 60;
    rect[2].x = 260; rect[2].y = 340;rect[2].w = 400;rect[2].h = 60;
    rect[3].x = 260; rect[3].y = 420;rect[3].w = 400;rect[3].h = 60;
    rect[4].x = 710; rect[4].y = 480;rect[4].w = 150;rect[4].h = 60;

    // Pour le 2e tableau
    rect1[0].x = 240; rect1[0].y = 180;rect1[0].w = 440;rect1[0].h = 60;
    rect1[1].x = 240; rect1[1].y = 260;rect1[1].w = 440;rect1[1].h = 60;
    rect1[2].x = 240; rect1[2].y = 340;rect1[2].w = 440;rect1[2].h = 60;
    rect1[3].x = 240; rect1[3].y = 420;rect1[3].w = 440;rect1[3].h = 60;
    rect1[4].x = 690; rect1[4].y = 480;rect1[4].w = 190;rect1[4].h = 60;

    return ;
}




void Deplacer_Bouton(SDL_Texture **button_blue,SDL_Texture **button_red, SDL_Renderer **renderer, int deplace,SDL_Rect *rect,SDL_Rect *rect1)
{
    if(deplace == 1){

        for (int i = 0; i < NB_BOUTON_MAX; ++i) {

            if(i == 0 && effet == SDL_TRUE){
                SDL_RenderCopy(*renderer,*button_red,NULL,&rect1[i]);
            }
            else{
                SDL_RenderCopy(*renderer,*button_blue,NULL,&rect[i]);
            }
        }
    }
    else if(deplace == 2){

        for (int i = 0; i < NB_BOUTON_MAX; ++i) {

            if(i == 1 && effet == SDL_TRUE){
                SDL_RenderCopy(*renderer,*button_red,NULL,&rect1[i]);
            }
            else{
                SDL_RenderCopy(*renderer,*button_blue,NULL,&rect[i]);
            }
        }
    }
    else if(deplace == 3){
        for (int i = 0; i < NB_BOUTON_MAX; ++i) {

            if(i == 2  && effet == SDL_TRUE){
                SDL_RenderCopy(*renderer,*button_red,NULL,&rect1[i]);
            }
            else{
                SDL_RenderCopy(*renderer,*button_blue,NULL,&rect[i]);
            }
        }
    }
    else if(deplace == 4){
        for (int i = 0; i < NB_BOUTON_MAX; ++i) {

            if(i == 3 && effet == SDL_TRUE){
                SDL_RenderCopy(*renderer,*button_red,NULL,&rect1[i]);
            }
            else{
                SDL_RenderCopy(*renderer,*button_blue,NULL,&rect[i]);
            }
        }
    }
    else if(deplace == 5){
        for (int i = 0; i < NB_BOUTON_MAX; ++i) {

            if(i == 4 && effet == SDL_TRUE){
                SDL_RenderCopy(*renderer,*button_red,NULL,&rect1[i]);
            }
            else{
                SDL_RenderCopy(*renderer,*button_blue,NULL,&rect[i]);
            }
        }
    }

    return;
}
void Charger_Image_menu(SDL_Texture **background,SDL_Texture **button_blue,SDL_Texture **button_red, SDL_Renderer **renderer)
{
    SDL_Surface *surface = NULL;

    surface = SDL_LoadBMP("../image/bckgr2.bmp");
    *background = SDL_CreateTextureFromSurface(*renderer,surface);
    SDL_FreeSurface(surface);
    surface = SDL_LoadBMP("../image/buttn.bmp");
    *button_blue = SDL_CreateTextureFromSurface(*renderer,surface);
    SDL_FreeSurface(surface);
    surface = SDL_LoadBMP("../image/buttn2.bmp");
    *button_red = SDL_CreateTextureFromSurface(*renderer,surface);
    SDL_FreeSurface(surface);

    return;
}


void Envoyer_Emplacemnt_Souris(SDL_Point coor, int *deplacer)
{
    SDL_Rect rect = {260,180,400,60};
    SDL_Rect rect2 = {260,260,400,60};
    SDL_Rect rect3 = {260,340,400,60};
    SDL_Rect rect4 = {260,420,400,60};
    SDL_Rect rect5 = {710,480,150,60};

    if ((coor.x >rect.x && coor.x < rect.x + rect.w) && (coor.y >rect.y && coor.y < rect.y + rect.h)){
        *deplacer = 1;
    }
    else  if ((coor.x >rect2.x && coor.x < rect2.x + rect2.w) && (coor.y >rect2.y && coor.y < rect2.y + rect2.h)){
        *deplacer = 2;
    }
    else  if ((coor.x >rect3.x && coor.x < rect3.x + rect3.w) && (coor.y >rect3.y && coor.y < rect3.y + rect3.h)){
        *deplacer = 3;
    }
    else  if ((coor.x >rect4.x && coor.x < rect4.x + rect4.w) && (coor.y >rect4.y && coor.y < rect4.y + rect4.h)){
        *deplacer = 4;
    }
    else  if ((coor.x >rect5.x && coor.x < rect5.x + rect5.w) && (coor.y >rect5.y && coor.y < rect5.y + rect5.h)){
        *deplacer = 5;
    }
    return;
}

void Charger_menu_texte(SDL_Renderer **renderer,SDL_Texture **texture)
{
    char jouer[NB_BOUTON_MAX][115] = {"Jouer","Contre un PC","Meilleur Score","A propos du jeu", "Quitter"};

    if(TTF_Init() != 0){
        fprintf(stderr,"Erreur sur initialisation de la SDL2 ! %s \n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    TTF_Font * font;

    SDL_Surface *surface_texte = NULL;
    SDL_Color blanc = {255,255,255,255};
    font = TTF_OpenFont("../police/regular.ttf",50);


    for (int i = 0; i < NB_BOUTON_MAX; ++i) {
        surface_texte = TTF_RenderText_Solid(font,jouer[i],blanc);
        texture[i] = SDL_CreateTextureFromSurface(*renderer,surface_texte);
        SDL_FreeSurface(surface_texte);
    }

    TTF_CloseFont(font);
    TTF_Quit();

    return;
}

void Afficher_menu_texte(SDL_Texture *texture[],SDL_Renderer **renderer)
{
    SDL_Rect rect = {410,187,0,0};
    SDL_Rect rect2 = {360,267,0,0};
    SDL_Rect rect3 = {350,347,0,0};
    SDL_Rect rect4 = {350,427,0,0};
    SDL_Rect rect5 = {735,487,0,0};



    // On utilisera une boucle et un tableau pour optimiser;

    SDL_QueryTexture(texture[0], NULL,NULL,&rect.w,&rect.h);
    SDL_RenderCopy(*renderer,texture[0],NULL,&rect);
    SDL_QueryTexture(texture[1], NULL,NULL,&rect2.w,&rect2.h);
    SDL_RenderCopy(*renderer,texture[1],NULL,&rect2);
    SDL_QueryTexture(texture[2], NULL,NULL,&rect3.w,&rect3.h);
    SDL_RenderCopy(*renderer,texture[2],NULL,&rect3);
    SDL_QueryTexture(texture[3], NULL,NULL,&rect4.w,&rect4.h);
    SDL_RenderCopy(*renderer,texture[3],NULL,&rect4);
    SDL_QueryTexture(texture[4], NULL,NULL,&rect5.w,&rect5.h);
    SDL_RenderCopy(*renderer,texture[4],NULL,&rect5);

    return;
}

int Click_button_keyboard(int deplacer)
{
    int val_retour;
    if(deplacer == 1){ // Accéder à la partie mutijoueur
        val_retour = 1;
    } else if (deplacer == 2){ // Accéder à la partie jeu contre ordi
        val_retour = 2;
    }else if (deplacer == 3){ // Accéder à la partie meilleure score
        val_retour = 3;
    }else if (deplacer == 4){// Accéder à la partie à propos du jeu
        val_retour = 4;
    }else if (deplacer == 5){ // Quitter le jeu
        val_retour = -1;
    }

    return val_retour ;
}

int Click_button_mouse(SDL_Point coor)
{

    SDL_Rect rect = {260,180,400,60};
    SDL_Rect rect2 = {260,260,400,60};
    SDL_Rect rect3 = {260,340,400,60};
    SDL_Rect rect4 = {260,420,400,60};
    SDL_Rect rect5 = {710,480,150,60};

    if ((coor.x >rect.x && coor.x < rect.x + rect.w) && (coor.y >rect.y && coor.y < rect.y + rect.h)){
        return PLAY_AT_2;
    }
    else  if ((coor.x >rect2.x && coor.x < rect2.x + rect2.w) && (coor.y >rect2.y && coor.y < rect2.y + rect2.h)){
        return  CONTRE_ORDI;
    }
    else  if ((coor.x >rect3.x && coor.x < rect3.x + rect3.w) && (coor.y >rect3.y && coor.y < rect3.y + rect3.h)){
        return SCORE;
    }
    else  if ((coor.x >rect4.x && coor.x < rect4.x + rect4.w) && (coor.y >rect4.y && coor.y < rect4.y + rect4.h)){
        return ABOUT;
    }
    else  if ((coor.x >rect5.x && coor.x < rect5.x + rect5.w) && (coor.y >rect5.y && coor.y < rect5.y + rect5.h)){
        return QUITTER;
    }
    return 0;
}