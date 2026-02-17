/**
 * @file placer_dinos.h
 * @brief Fonctions de placement des dinosaures sur la matrice.
 */

#ifndef _PLACER_DINOS_H_
#define _PLACER_DINOS_H_

#include "types.h"

// Place UN dino précis
void remplir_matrice_dino(t_dino *dino, t_coordonnee p_sol, int matrice[MAT_H][MAT_L]);

// Place TOUS les dinos d'une équipe
void placer_une_equipe(t_joueur *joueur, t_zone_depart points_spawn[10], int matrice[MAT_H][MAT_L], int id_depart);

#endif