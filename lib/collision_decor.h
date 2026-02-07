/**
 * @file collision_decor.h
 * @brief Fonctions de détection de collision avec la matrice.
 */

#ifndef _COLLISION_DECOR_H_
#define _COLLISION_DECOR_H_

#include "types.h"

/**
 * @brief Vérifie les collisions autour du dinosaure.
 * @param tab_res Tableau de 4 entiers [SUD, OUEST, EST, NORD] à remplir (1 si collision).
 * @param dino La structure du dinosaure testé.
 * @param matrice La matrice représentant le terrain.
 * @return int Retourne 1 si au moins une collision (terre) est détectée, 0 sinon.
 */
int collision_decor(int tab_res[4], t_dino dino, int matrice[MAT_H][MAT_L]);

#endif