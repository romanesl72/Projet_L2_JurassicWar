#ifndef _CREATION_NUAGE_H_
#define _CREATION_NUAGE_H_

#include "types.h"

/** 
 * @file creation_nuage.h
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
 * @fn int tracerCourbe( t_coordonnee *nuage, int nbPoints);
 * @author Solène Orieux
 * @date 
 * @brief 
 * @param nuage
 * @param nbPoints
 */
int tracerCourbe( t_coordonnee *nuage, int nbPoints);

#endif