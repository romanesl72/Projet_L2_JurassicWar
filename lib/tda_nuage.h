#ifndef _TDA_NUAGE_H_
#define _TDA_NUAGE_H_

#include "types.h"

/**
 * @file tda_nuage.h
 * @brief fonctions permettant de créer/utiliser un nuage de points
 * @author Solène Orieux
 * @date 14/03/2026
 */


/**
 * @fn t_coordonnee *nuage_de_points(int *nb_points,char nomFichier[]);
 * @author Solène Orieux
 * @date 14/03/2026
 * @brief permet de créer le nuage
 * @param nb_points pointeurs sur le nombre d'éléments dans le nuage de points
 * @param nomFichier nom de l'image permettant d'extraire le nuage de points
 */


t_coordonnee *nuage_de_points(int *nb_points,char nomFichier[]);

/**
 * @fn int nuageExiste( t_coordonnee * const nuage );
 * @author Solène Orieux
 * @date 14/03/2026
 * @brief retourne 1 si le nuage existe, 0 sinon
 * @param nuage pointeur sur le nuage de points
 */

int nuageExiste( t_coordonnee * const nuage );

/**
 * @fn int nuageDetruire( t_coordonnee ** nuage)
 * @author Solène Orieux
 * @date 14/03/2026
 * @brief permet de détruire le nuage
 * @param nuage pointeur de pointeur sur le nuage de points
 */

int nuageDetruire( t_coordonnee ** nuage);


/**
 * @fn void afficherNuage(t_coordonnee *nuage, int nb_pts);
 * @author Solène Orieux
 * @date 20/03/2026
 * @brief permet d'afficher la globalité du nuage
 * @param nuage pointeur sur le nuage de points
 * @param nb_pts nombre de points dans le nuage
 */

void afficherNuage(t_coordonnee *nuage, int nb_pts);


#endif