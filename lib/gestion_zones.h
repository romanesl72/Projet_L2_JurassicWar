#ifndef _GESTION_ZONES_H_
#define _GESTION_ZONES_H_

#include "types.h"

// Fonction qui calcule la distance entre deux points
float distance(t_coordonnee p1, t_coordonnee p2);

// Fonction pour remplir le catalogue sans chevauchement
void generer_catalogue_depuis_nuage(t_coordonnee *nuage, int nb_points, t_catalogue_zones *catalogue, int *nb_E1, int *nb_E2, int id_n);
#endif