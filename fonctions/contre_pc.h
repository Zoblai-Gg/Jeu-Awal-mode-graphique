#include "init_awele.h"

#ifndef JEU_AWALE_CONTRE_PC_H
#define JEU_AWALE_CONTRE_PC_H

#define True 1
#define False 0

int est_trbnc_prfn(int i, int j,int **T);
int est_bnc_prfn(int i, int j,int **T);
int est_trbon_ch(JOUEUR* pc, int c,int **T);
int est_bon_ch(JOUEUR* pc, int c,int **T);
int choix_du_case_pc(JOUEUR* pc,int **T);


#endif //JEU_AWALE_CONTRE_PC_H
