#ifndef _PLACER_DINOS_H_
#define _PLACER_DINOS_H_

#include "types.h"

/** 
 * @file placer_dinos.h
 * @brief Fonctions de placement des dinosaures sur la matrice.
 * @author Romane Saint_Léger
 * @date Crée le 21/02/2026
 */

/**
 * @fn void remplir_matrice_dino(t_dino *dino, t_coordonnee p_sol, int matrice[MAT_H][MAT_L]);
 * @author Romane Saint-Léger
 * @date Crée le 21/02/2026
 * @brief Place un dinosaure aléatoirement dans une zone de spawn valide en le remplissant de son ID.
 * @param dino Pointeur vers la structure du dino à placer.
 * @param p_sol Coordonnées du point sol o`u les pieds du dinosaure doivent se poser.
 * @param matrice La matrice (terrain) à mettre à jour avec l'ID du dino.
 */

void remplir_matrice_dino(t_dino *dino, t_coordonnee p_sol, int matrice[MAT_H][MAT_L]);


/**
 * @fn void placer_une_equipe(t_joueur *joueur, t_zone_depart points_spawn[10], int matrice[MAT_H][MAT_L], int id_depart);
 * @author Romane Saint-Léger
 * @date Crée le 21/02/2026
 * @brief Initialise et place tous les dinosaures d'une équipe sur le terrain.
 * @param joueur Pointeur vers la structure du joueur (l'équipe).
 * @param points_spawn Tableau des points de spawn disponibles.
 * @param matrice Matrice de jeu à modifier
 * @param id_depart Indice de départ pour chaque dinosaure afin de les différencier.
 */


void placer_une_equipe(t_joueur *joueur, t_zone_depart points_spawn[10], int matrice[MAT_H][MAT_L], int id_depart);

#endif