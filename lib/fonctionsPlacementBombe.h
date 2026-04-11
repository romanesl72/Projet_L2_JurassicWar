#ifndef _FONCTIONSPLACEMENTBOMBE_H_
#define _FONCTIONSPLACEMENTBOMBE_H_

#include "types.h"

/** 
 * @file fonctionsPlacementBombe.h
 * @brief Définitions des fonctions liées au placement de la bombe à côté des dinosaures.
 * @author Hannah Sergent
 * @date Crée le 20/03/2026
 * @version 1.0
 */

/**
 * @def EXPLOSION_NON_CONTROLEE
 * @brief Coefficient utilisé pour éviter que la bombe explose entre les pattes du dinosaure qui la lance.
*/

#define EXPLOSION_NON_CONTROLEE 1

/** 
 * @fn void placerBombeEntrePattes(t_dino *dino, t_bombe * bombe, t_cote *cote, t_case matriceTerrain[HAUTEUR_TERRAIN][LARGEUR_TERRAIN]);
 * @brief La fonction place la bombe entre les pattes du dinosaure précisé en paramètre.
 * @author Hannah Sergent
 * @date Crée le 20/03/2026
 * @version 1.2
 * @param dino un pointeur sur un dinosaure
 * @param bombe un pointeur sur une structure de type bombe
 * @param cote une structure de type côté qui indique si le dinosaure veut tirer vers la gauche ou la droite
 * @param matriceTerrain une matrice contenant les informations sur le terrain
 */

void placerBombeEntrePattes(t_dino *dino, t_bombe * bombe, t_cote *cote, t_case matriceTerrain[HAUTEUR_TERRAIN][LARGEUR_TERRAIN]);

#endif