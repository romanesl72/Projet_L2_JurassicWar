#ifndef _FONCTIONSTUERDINOS_H_
#define _FONCTIONSTUERDINOS_H_

#include "types.h"

/**
 * @fn int collisionDinoBombe(t_case matriceTerrain[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], t_bombe *bombe);
 * @brief la fonction vérifie si la bombe heurte un dinosaure
 * @author Hannah Sergent
 * @date Crée le 18/03/2026
 * @param matriceTerrain matrice contenant les informations sur le terrain
 * @param bombe pointeur sur une structure de type bombe 
 */

int collisionDinoBombe(t_case matriceTerrain[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], t_bombe *bombe);

#endif