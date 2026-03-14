#ifndef _REGRESSION_H_
#define _REGRESSION_H_

#include "types.h"

/**
 * @file regression.h
 * @brief
 * @author Solène Orieux
 * @date
 */


/**
 * @fn t_coordonnee *nuage_de_points(int *nb_points,char nomFichier[]);
 * @author Solène Orieux
 * @date 
 * @brief
 * @param nb_points
 * @param nomFichier
 */


t_coordonnee *nuage_de_points(int *nb_points,char nomFichier[]);

/**
 * @fn void moyenne(t_coordonnee *T, int n, float *x, float *y);
 * @author Solène Orieux
 * @date 
 * @brief
 * @param T
 * @param n
 * @param x
 * @param y
 */

void moyenne(t_coordonnee *T, int n, float *x, float *y);


/**
 * @fn void calculPente(t_coordonnee *T, int n, float *a, float x, float y);
 * @author Solène Orieux
 * @date 
 * @brief
 * @param T
 * @param n
 * @param a
 * @param x
 * @param y
 */

void calculPente(t_coordonnee *T, int n, float *a, float x, float y);


/**
 * @fn void regression(t_coordonnee dino, t_coordonnee * nuage, float *a, float *b, int indice, int nb_point);
 * @author Solène Orieux
 * @date 
 * @brief
 * @param dino
 * @param nuage
 * @param a
 * @param b
 * @param indice
 * @param nb_points
 */


void regression(t_coordonnee dino, t_coordonnee * nuage, float *a, float *b, int indice, int nb_point);

/**
 * @fn int nuageExiste( t_coordonnee * const nuage );
 * @author Solène Orieux
 * @date 14/03/2026
 * @brief
 * @param nuage
 */

int nuageExiste( t_coordonnee * const nuage );

/**
 * @fn int nuageDetruire( t_coordonnee ** nuage)
 * @author Solène Orieux
 * @date 14/03/2026
 * @brief
 * @param nuage
 */

int nuageDetruire( t_coordonnee ** nuage);

/**
 * @fn int nuageCopier(t_coordonnee **nuage_cible, t_coordonnee *nuage_source, int nb_points);
 * @author Solène Orieux
 * @date 14/03/2026
 * @brief
 * @param nuage_cible
 * @param nuage_source
 * @param nb_points
 */

int nuageCopier(t_coordonnee **nuage_cible, t_coordonnee *nuage_source, int nb_points);

/**
 * @fn int tracerCourbe( t_coordonnee *nuage, int nbPoints);
 * @author Solène Orieux
 * @date 
 * @brief
 * @param nuage
 * @param nbPoints
 */

int tracerCourbe( t_coordonnee *nuage, int nbPoints);

#endif
