#ifndef _REGRESSION_H_
#define _REGRESSION_H_

#include "types.h"
#include "tda_nuage.h"

/**
 * @file regression.h
 * @brief fonctions permettant de calculer la pente d'un points donné
 * @author Solène Orieux
 * @date 24/03/2026
 */


/**
 * @fn t_coordonnee *nuage_de_points(int *nb_points,char nomFichier[]);
 * @author Solène Orieux
 * @date 24/03/2026
 * @brief
 * @param nb_points pointeur sur le nombre de points du nuage de points
 * @param nomFichier nom de l'image où l'on pourra extraire le nuage de points
 */


t_coordonnee *nuage_de_points(int *nb_points,char nomFichier[]);

/**
 * @fn void moyenne(t_coordonnee *T, int n, float *x, float *y);
 * @author Solène Orieux
 * @date 24/03/2026
 * @brief Calcule la moyenne des coordonnées X et Y d'un échantillon de points.
 * @param T Tableau de coordonnées (échantillon).
 * @param n Nombre de points dans l'échantillon.
 * @param x Pointeur pour stocker la moyenne des abscisses (X) calculée.
 * @param y Pointeur pour stocker la moyenne des ordonnées (Y) calculée.
 */

void moyenne(t_coordonnee *T, int n, float *x, float *y);


/**
 * @fn void calculPente(t_coordonnee *T, int n, float *a, float x, float y);
 * @author Solène Orieux
 * @date 24/03/2026
 * @brief Calcule le coefficient directeur par la méthode des moindres carrées* 
 * @param T Tableau de coordonnées (échantillon).
 * @param n Nombre de points dans l'échantillon.
 * @param a Pointeur pour stocker le coefficient directeur résultant.
 * @param x Moyenne des abscisses (X) de l'échantillon.
 * @param y Moyenne des ordonnées (Y) de l'échantillon.
 */

void calculPente(t_coordonnee *T, int n, float *a, float x, float y);


/**
 * @fn void regression(t_coordonnee dino, t_coordonnee * nuage, float *a, float *b, int indice, int nb_point);
 * @author Solène Orieux
 * @date 24/03/2026
 * @brief calcul la régression d'un échantillon de 10 points
 * @param dino structure du dinosaure
 * @param nuage pointeur sur le nuage de points
 * @param a coefficient directeur
 * @param b ordonnée à l'origine
 * @param indice indice du point dont on veut calculer la pente
 * @param nb_points nombre de points sur le nuage
 */


void regression(t_coordonnee dino, t_coordonnee * nuage, float *a, float *b, int indice, int nb_point);

/**
 * @fn int tracerCourbe( t_coordonnee *nuage, int nbPoints);
 * @author Solène Orieux
 * @date 24/03/2026
 * @brief permet d'afficher la pente
 * @param nuage pointeur sur le nuage de points
 * @param nbPoints nombre de points sur le nuage
 */

int tracerCourbe( t_coordonnee *nuage, int nbPoints);

#endif
