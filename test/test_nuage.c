#include <stdio.h>
#include <stdlib.h>
#include "../lib/tda_nuage.h"

int main(){
    int nb_pts1;
    t_coordonnee *nuage1=nuage_de_points(&nb_pts1,"../img/test1_c.jpg");
    t_coordonnee *nuage2=NULL;
    if(!nuageExiste(nuage1)){
        printf("erreur d'allocation du nuage\n");
        return 1;
    }
    afficherNuage(nuage1,nb_pts1);
    if(nuageCopier(&nuage2, nuage1, &nb_pts1)){
        printf("Copie réussi\n");
        afficherNuage(nuage2,nb_pts1);
    }

    if(nuageDetruire(&nuage1) && nuageDetruire(&nuage2)){
        printf("Destruction réussi\n");
        return 0;
    }
    return 1;
}