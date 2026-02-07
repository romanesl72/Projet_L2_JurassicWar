/**
 * @file gestion_placement.h
 * @brief Fonctions de placement des dinosaures sur la matrice.
 */

#ifndef _GESTION_PLACEMENT_H_
#define _GESTION_PLACEMENT_H_

#include "types.h"

/**
 * @struct t_zone_depart
 * @brief Définit une zone contenant plusieurs points de spawn.
 */



typedef struct {
    t_coordonnee points[10];
    int nb_points;
    char nom_zone[30];
} t_zone_depart;

// Ta fonction d'origine reste inchangée
void placer_dino(t_dino *dino, t_zone_depart zone, int matrice[MAT_H][MAT_L]);

// Nouvelle fonction qui appelle placer_dino
void placer_equipe(t_joueur *joueur, t_zone_depart catalogue[5], int matrice[MAT_H][MAT_L]);

#endif