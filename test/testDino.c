#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../lib/types.h"
#include "../lib/placer_dinos.h"
#include "../lib/deplacement.h"



int main(){

    int matrice_test[MAT_H][MAT_L];
    int i,j;
    t_dino d; 
    d.d = D1;
    t_coordonnee p_sol={50,50};

    for(i=0; i<100;i++){
        for(j=0; j<100;j++){
            matrice_test[i][j]=0;
        }
    }
    remplir_matrice_dino(&d, p_sol, matrice_test);
    printf("----------matrice1---------------------\n");
    for(i=0; i<100;i++){
        for(j=0; j<100;j++){
            printf("%d", matrice_test[i][j]);
        }
        printf("\n");
    }

    supprimer_matrice_dino(&d, matrice_test);
    printf("----------matrice2---------------------");
    for(i=0; i<100;i++){
        for(j=0; j<100;j++){
            printf("%d", matrice_test[i][j]);
        }
        printf("\n");
    }
}