#include <stdio.h>
#include <stdlib.h>
#include "../lib/tda_nuage.h"

int main(){
    int nb_pts1;
    t_coordonnee *nuage1=nuage_de_points(&nb_pts1,"../img/test1_c.jpg");
    if(!nuageExiste(nuage1)){
        printf("erreur d'allocation du nuage\n");
        return 1;
    }
    afficherNuage(nuage1,nb_pts1);
    printf("nb=%d\n",nb_pts1);

    if(nuageDetruire(&nuage1)){
        printf("Destruction réussi\n");
        return 0;
    }
    return 1;
}