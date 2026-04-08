#ifndef _GESTION_ZONES_H_
#define _GESTION_ZONES_H_

#include "types.h"

/** 
 * @file gestion_zones.h
 * @brief Définitions des fonctions qui génère les zones de placement pour les dinosaures
 * @author Romane Saint_Léger
 * @date Crée le 17/02/2026
 * @version 1.5
 */

/**
 * @fn float distance(t_coordonnee p1, t_coordonnee p2);
 * @brief Fonction qui calcule la distance entre deux points
 * @author Romane Saint-Léger
 * @date Crée le 17/02/2026
 * @version 1.0
 * @param p1 Première coordonnée
 * @param p2 Seconde coordonnée
 */

float distance(t_coordonnee p1, t_coordonnee p2);

/**
 * @fn void generer_catalogue_depuis_nuage(t_coordonnee *nuage, int nb_points, t_catalogue_zones *catalogue, int *nb_E1, int *nb_E2, int id_n);
 * @brief Fonction pour remplir le catalogue de points de spawn sans chevauchement
 * @author Romane Saint-Léger
 * @date Crée le 17/02/2026
 * @version 1.5
 * @param nuage nuage de points afin d'avoir le "sol" pour les dinosaures
 * @param nb_points 
 * @param catalogue une structure qui contient les zones de spawn
 * @param nb_E1 nombre de zones de spawn pour l'équipe 1
 * @param nb_E2 nombre de zones de spawn pour l'équipe 2
 * @param id_n numéro du nuage de point utilisé
 */

void generer_catalogue_depuis_nuage(t_coordonnee *nuage, int nb_points, t_catalogue_zones *catalogue, int *nb_E1, int *nb_E2, int id_n);
#endif