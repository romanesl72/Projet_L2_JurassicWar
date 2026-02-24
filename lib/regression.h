#ifndef _REGRESSION_H_
#define _REGRESSION_H_

#include "types.h"

t_coordonnee *nuage_de_points(int *nb_points,char nomFichier[]);


void moyenne(t_coordonnee *T, int n, float *x, float *y);

void calculPente(t_coordonnee *T, int n, float *a, float x, float y);

void regression(t_coordonnee dino, t_coordonnee * nuage, float *a, float *b, int indice, int nb_point);

int tracerCourbe( t_coordonnee *nuage, int nbPoints);

#endif
