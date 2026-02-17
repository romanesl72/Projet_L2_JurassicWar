#ifndef _REGRESSION_H_
#define _REGRESSION_H_

#include "types.h"

t_coordonnee *nuage_de_points(int *nb_points,char nomFichier[]);

int tracerCourbe( t_coordonnee *nuage, int nbPoints);
#endif
