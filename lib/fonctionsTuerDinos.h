#ifndef _FONCTIONSTUERDINOS_H_
#define _FONCTIONSTUERDINOS_H_

#include "types.h"

/** 
 * @file fonctionsTuerDinos.h
 * @brief Définition des fonctions pour le lancer d'une bombe sur un dinosaure.
 * @author Hannah Sergent
 * @date Crée le 11/03/2026
 * @version 1.0
 */

/**
 * @fn t_case collisionDinoBombe(t_case matriceTerrain[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], t_bombe *bombe);
 * @brief La fonction vérifie si la bombe heurte un dinosaure.
 * @author Hannah Sergent
 * @date Crée le 18/03/2026
 * @version 1.0
 * @param matriceTerrain la matrice contenant les informations sur le terrain
 * @param bombe un pointeur sur une structure de type bombe
 */

t_case collisionDinoBombe(t_case matriceTerrain[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], t_bombe *bombe);

#endif