#include <stdio.h>
#include <stdlib.h>
#include "../lib/types.h"
#include "../lib/tda_nuage.h"
#include "../lib/regression.h"

/** 
 * @file test_deplacement.c
 * @brief Test des fonctions crées dans le fichier tda_nuage.c
 * @author Solène Orieux
 * @date Crée le 17/03/2026
 */


int main() {
    // code à modifier si le nombre d'image est différent de 2
    //pour compiler dans bin: gcc -Wall ../src/creation_nuage.c -Ilib -o nuage -lSDL2 -lm
    int n1,n2;
    char img1[25];
    char img2[25];

    t_coordonnee *nuage1=NULL;
    t_coordonnee *nuage2=NULL;
        
    // appel l'image ../img/test1_c.jpg ou ../img/test2_c.jpg
    printf("Donner le nom de la première image:");
    if (scanf("%24s", img1) != 1) return 1;

    printf("Donner le nom de la deuxième image:");
    if (scanf("%24s", img2) != 1) return 1;

    nuage1=nuage_de_points(&n1,img1);
    nuage2=nuage_de_points(&n2,img2);

    tracerCourbe(nuage1,n1);//permet de vérifier que le nuage de points est correct
    
    free(nuage1);
    nuage1=NULL;
    free(nuage2);
    nuage2=NULL;

    return 0;
}