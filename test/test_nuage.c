#include <stdio.h>
#include <stdlib.h>
#include "../lib/tda_nuage.h"

int main(){
    int nb_pts1,nb_pts2;
    t_coordonnee *nuage1=nuage_de_points(&nb_pts1,"../img/test1_c.jpg");
    t_coordonnee *nuage2=nuage_de_points(&nb_pts2,"../img/test2_c.jpg");
    if(!nuageExiste(nuage1)||!nuageExiste(nuage1)){
        printf("erreur d'allocation du nuage\n");
        return 1;
    }
    afficherNuage(nuage1,nb_pts1);
    afficherNuage(nuage2,nb_pts2);
    if(regroupementNuage(&nuage1, nuage2, &nb_pts1, nb_pts2)){
        printf("Regroupement réussi\n");
        afficherNuage(nuage1,nb_pts1);
    }

    if(nuageDetruire(&nuage1)){
        printf("Destruction réussi\n");
        return 0;
    }
    return 1;
}