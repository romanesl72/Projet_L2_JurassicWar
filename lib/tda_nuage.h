#ifndef _TDA_NUAGE_H_
#define _TDA_NUAGE_H_

#include "types.h"

/**
 * @file tda_nuage.h
 * @brief
 * @author Solène Orieux
 * @date 14/03/2026
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

#endif