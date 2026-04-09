#include "../lib/fonctionsTuerDinos.h"
#include <math.h>

/** 
 * @file fonctionsTuerDinos.c
 * @brief Corps des fonctions pour le lancer d'une bombe sur un dinosaure.
 * @author Hannah Sergent
 * @date Crée le 11/03/2026
 * @version 1.0
 */

t_case collisionDinoBombe(t_case matriceTerrain[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], t_bombe *bombe) {

    t_coordonnee posBombe;

    posBombe.x = roundf(bombe->coor.x);
    posBombe.y = roundf(bombe->coor.y);

    t_case extremiteDroite = matriceTerrain[posBombe.y][posBombe.x + bombe->rayon];
    t_case extremiteGauche = matriceTerrain[posBombe.y][posBombe.x - bombe->rayon];
    t_case extremiteHaute = matriceTerrain[posBombe.y - bombe->rayon][posBombe.x];
    t_case extremiteBasse = matriceTerrain[posBombe.y + bombe->rayon][posBombe.x];

    if ((extremiteDroite >= D1) && (extremiteDroite <= D6)){
        return extremiteDroite;
    }
    if ((extremiteGauche >= D1) && (extremiteGauche <= D6)){
        return extremiteGauche;
    }
    if ((extremiteHaute >= D1) && (extremiteHaute <= D6)){
        return extremiteHaute;
    }
    if ((extremiteBasse >= D1) && (extremiteBasse <= D6)){
        return extremiteBasse;
    }
    return AIR;
}