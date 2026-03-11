#ifndef _DEPLACEMENT_H_
#define _DEPLACEMENT_H_

#include "types.h"
#include "regression.h"
#include "chargerMatrice.h"
#include "placer_dinos.h"
#include "creation_nuage.h"
#include "collision_decor.h"
#include "fonctionsVerification.h"

#define VITESSE_BASE 0.05
#define GRAVITE 0.6
#define FORCE_SAUT -10.0

void supprimer_matrice_dino(t_dino *dino, int matrice[MAT_H][MAT_L]);
int chercherNouveauIndiceNuage(t_dino *dino, t_coordonnee *nuage, int *nb_pts, int matrice[MAT_H][MAT_L]);
int horsNuage(t_dino *dino, t_coordonnee *nuage, int nb_pts, int matrice[MAT_H][MAT_L], int mvt);
void gauche(t_dino *dino, t_coordonnee *nuage, int nb_pts, int matrice[MAT_H][MAT_L],const Uint8 *state);
void droite(t_dino *dino, t_coordonnee *nuage, int nb_pts, int matrice[MAT_H][MAT_L],const Uint8 *state);
void saut(t_dino *dino, t_coordonnee *nuage, int nb_pts, int matrice[MAT_H][MAT_L],const Uint8 *state);
#endif