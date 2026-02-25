#ifndef _DEPLACEMENT_H_
#define _DEPLACEMENT_H_

#include "types.h"
#include "regression.h"
#include "chargerMatrice.h"
#include "creation_nuage.h"
#include "fonctionsVerification.h"

void gauche(t_dino *dino, t_coordonnee *nuage, int nb_pts);
void droite(t_dino *dino, t_coordonnee *nuage, int nb_pts);

#endif