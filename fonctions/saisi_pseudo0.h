
#ifndef SAISIE_PSEUDO0_H
#define SAISIE_PSEUDO0_H

typedef struct {
    char pseudo1[50] ;
    char pseudo2[50] ;
    int score1;
    int score2;
} PSEUDO_JOUEUR ;


PSEUDO_JOUEUR saisi_pseudo0(void);

#endif

