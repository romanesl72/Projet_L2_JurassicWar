#ifndef _DEPLACEMENT_H_
#define _DEPLACEMENT_H_

#include "types.h"

/** 
 * @file deplacement.h
 * @brief 
 * @author Solène Orieux
 * @date 
 */


/**
 * @def VITESSE_BASE
 * @brief
*/

#define VITESSE_BASE 0.05

/**
 * @def GRAVITE
 * @brief
*/

// Diminue la vitesse de chute (ex: de 0.8 à 0.4)
#undef GRAVITE
#define GRAVITE 0.4 

/**
 * @def FORCE_SAUT
 * @brief
*/

// Diminue la puissance de l'impulsion (ex: de -10.0 à -7.0)
#undef FORCE_SAUT
#define FORCE_SAUT -7.0



/**
 * @fn int horsNuage(t_dino *dino, t_coordonnee *nuage, int nb_pts, int matrice[MAT_H][MAT_L], int mvt);
 * @author Solène Orieux
 * @date 
 * @brief
 * @param dino
 * @param nuage
 * @param nb_pts
 * @param matrice
 * @param mvt
 */

int horsNuage(t_dino *dino, t_coordonnee *nuage, int *nb_pts, int matrice[MAT_H][MAT_L], int mvt);

/**
 * @fn void gauche(t_dino *dino, t_coordonnee *nuage, int nb_pts, int matrice[MAT_H][MAT_L],const Uint8 *state);
 * @author Solène Orieux
 * @date 
 * @brief
 * @param dino
 * @param nuage
 * @param nb_pts
 * @param matrice
 * @param state
 */

void gauche(t_dino *dino, t_coordonnee *nuage, int nb_pts, int matrice[MAT_H][MAT_L],const Uint8 *state);

/**
 * @fn void droite(t_dino *dino, t_coordonnee *nuage, int nb_pts, int matrice[MAT_H][MAT_L],const Uint8 *state);
 * @author Solène Orieux
 * @date 
 * @brief
 * @param dino
 * @param nuage
 * @param nb_pts
 * @param matrice
 * @param state
 */

void droite(t_dino *dino, t_coordonnee *nuage, int nb_pts, int matrice[MAT_H][MAT_L],const Uint8 *state);

/**
 * @fn void saut(t_dino *dino, t_coordonnee *nuage, int nb_pts, int matrice[MAT_H][MAT_L],const Uint8 *state);
 * @author Solène Orieux
 * @date 
 * @brief
 * @param dino
 * @param nuage
 * @param nb_pts
 * @param matrice
 * @param state
 */

void saut(t_dino *dino, t_coordonnee **nuage, char *nomNuage[], int nb_nuage, int *nb_pts, int matrice[MAT_H][MAT_L], const Uint8 *state);


/**
 * @fn void deplacement_dino();
 * @author Solène Orieux
 * @date 26/03/2026
 * @brief fonction qui déplace le dino
 */

void deplacement_dino(t_dino *dino, char *nomNuage[], int nb_nuage, int matrice[MAT_H][MAT_L]);

#endif