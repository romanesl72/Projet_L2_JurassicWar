#ifndef _DEPLACEMENT_H_
#define _DEPLACEMENT_H_

#include "types.h"
#include "regression.h"
#include "chargerMatrice.h"
#include "placer_dinos.h"
#include "creation_nuage.h"
#include "collision_decor.h"
#include "fonctionsVerification.h"

void supprimer_matrice_dino(t_dino *dino, t_coordonnee p_sol, int matrice[MAT_H][MAT_L]);
void gauche(t_dino *dino, t_coordonnee *nuage, int nb_pts, int matrice[MAT_H][MAT_L]);
void droite(t_dino *dino, t_coordonnee *nuage, int nb_pts, int matrice[MAT_H][MAT_L]);

#endif