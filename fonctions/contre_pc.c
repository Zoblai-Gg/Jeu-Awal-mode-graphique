#include <stdio.h>
#include <stdlib.h>
#include "contre_pc.h"


int est_trbnc_prfn(int i, int j,int **T)
{
    if(T[i][j] == 2) return True;
    return False;
}

int est_bnc_prfn(int i, int j,int **T)
{
    if(T[i][j]==1) return True;
    return False;
}

int est_trbon_ch(JOUEUR* pc, int c,int **T)
{
    // 	Cette fonction vérifie si la case dans laquelle on va terminer( en choisissant la case c) contient 2, et dans ce cas
    // la case est une très bonne case à choisir
    int nb = T[pc->num-1][c]; // le nombre de boules dans la case choisie //
    if( pc->num-1 == 0)
    {
        if(nb <= c)    // Dans le cas ou le nbre de boules est <= aux cases de la meme ligne //
        {
            return  est_trbnc_prfn(0,c-nb,T) ;
        }
        int N = nb-c;
        if(N<=6)
        {
            return est_trbnc_prfn(1,N-1,T);
        }
        int lg = ((N/6)%2+1)%2 ; // le ligne de la case là ou on termine l'assume //
        if(lg == 1)
        {
            if(N%6==0) return est_trbnc_prfn(lg,5,T);
            return est_trbnc_prfn(lg,N%6-1,T);
        }
        if(N%6 == 0) return est_trbnc_prfn(lg,0,T);
        return est_trbnc_prfn(lg,6-N%6,T);
    }
    else{
        if(nb <= 5-c) return est_trbnc_prfn(1,c+nb,T);
        int N1 = nb - 5 + c;
        if(N1<6) return est_trbnc_prfn(0,6-N1%6,T);
        else if(N1==6) return est_trbnc_prfn(0,0,T);
        int lg1 = (N1/6)%2;
        if(lg1 == 1)
        {
            if(N1%6==0) return est_trbnc_prfn(1,5,T);
            return est_trbnc_prfn(1,N1%6,T);
        }
        if(N1%6==0) return est_trbnc_prfn(0,0,T);
        return est_trbnc_prfn(0,6-N1%6,T);
    }
}

int est_bon_ch(JOUEUR* pc, int c,int **T)
{

    // 	Cette elle vérifie si la case dans laquelle on va terminer( en choisissant la case c) contient 2, et dans ce cas
    // la case c est une bonne case à choisir
    int nb = T[(pc->num)-1][c]; // le nombre de boules dans la case choisie //
    if((pc->num-1) == 0)
    {
        if(nb <= c)    // Dans le cas ou le nbre de boules est <= au cases de la meme ligne //
        {
            return  est_bnc_prfn(0,c-nb,T) ;
        }
        int N = nb-c;
        if(N<=6)
        {
            return est_bnc_prfn(1,N-1,T);
        }
        int lg = ((N/6)%2+1)%2 ; // le ligne de la case là ou on termine l'assume //
        if(lg == 1)
        {
            if(N%6==0) return est_bnc_prfn(lg,5,T);
            return est_bnc_prfn(lg,N%6-1,T);
        }
        if(N%6 == 0) return est_bnc_prfn(lg,0,T);
        return est_bnc_prfn(lg,6-N%6,T);
    }
    else{
        if(nb <= 5-c) return est_bnc_prfn(1,c+nb,T);
        int N1 = nb - 5 + c;
        if(N1<6) return est_bnc_prfn(0,6-N1%6,T);
        else if(N1==6) return est_bnc_prfn(0,0,T);
        int lg1 = (N1/6)%2;
        if(lg1 == 1)
        {
            if(N1%6==0) return est_bnc_prfn(1,5,T);
            return est_bnc_prfn(1,N1%6,T);
        }
        if(N1%6==0) return est_bnc_prfn(0,0,T);
        return est_bnc_prfn(0,6-N1%6,T);
    }
}

int choix_du_case_pc(JOUEUR* pc,int **T)
{
    int c=0;
    // La 1ére boucle c'est pour préferer la récolte de 3 points que celle de deux points //
    for(c=0;c<6;c++)
    {
        if(est_trbon_ch(pc,c,T)) return c+1;
    }
    for(c=0;c<6;c++)
    {
        if(est_bon_ch(pc,c,T)==1) return c+1;
    }
    //srand(time(NULL)); L'initialisation du seed doit etre unique //
    c=rand()%6;
    while(T[(pc->num-1)][c] == 0)
    {
        c=rand()%6;
    }
    return c+1;
}