#ifndef _COLLISION_DECOR_H_
#define _COLLISION_DECOR_H_

#include "types.h"

 /** 
 * @file collision_decor.h
 * @brief Fonctions de détection de collision du dino avec la matrice.
 * @author Romane Saint_Léger
 * @date Crée le 08/02/2026
 */

/**
 * @fn int collision_decor(int tab_res[4], t_dino dino, int matrice[MAT_H][MAT_L]);
 * @brief Vérifie les collisions autour du dinosaure.
 * @author Romane Saint-Léger
 * @date Crée le 08/02/2026
 * @param tab_res Tableau de 4 entiers [SUD, OUEST, EST, NORD] à remplir (1 si collision).
 * @param dino La structure du dinosaure testé.
 * @param matrice La matrice représentant le terrain.
 * @return int Retourne 1 si au moins une collision (terre) est détectée, 0 sinon.
 */

int collision_decor(int tab_res[4], t_dino dino, int matrice[MAT_H][MAT_L]);

/**
 * @fn int collision_decor(int tab_res[4], t_dino dino, int matrice[MAT_H][MAT_L]);
 * @brief Vérifie les collisions sur les cotés du dinosaure.
 * @author Solène Orieux
 * @date Crée le 06/04/2026
 * @param dino La structure du dinosaure.
 * @param matrice La matrice représentant le terrain.
 * @return int Retourne 1 si la terre est détectée, 0 sinon.
 */
int collision_cote(t_dino dino, int matrice[MAT_H][MAT_L]);

#endif