#ifndef _DEPLACEMENT_H_
#define _DEPLACEMENT_H_

#include "types.h"
#include "regression.h"
#include "chargerMatrice.h"
#include "placer_dinos.h"
#include "creation_nuage.h"
#include "collision_decor.h"
#include "fonctionsVerification.h"

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

#define GRAVITE 0.8

/**
 * @def FORCE_SAUT
 * @brief
*/

#define FORCE_SAUT -12.0

/**
 * @fn int init_deplacement(t_dino **dino, int matrice[MAT_H][MAT_L], char *nomNuage[], int nb_nuage, ...);
 * @author Solène Orieux
 * @date 14/03/2026
 * @brief
 * @param dino
 * @param nb_pts
 * @param matrice
 * @param dino
 * @param matrice
 * @param nomNuage
 * @param nb_nuage
 * @param nuage
 */

int init_deplacement(t_dino **dino, int *nb_pts,int matrice[MAT_H][MAT_L], char *nomNuage[], t_coordonnee **nuage_principal, int nb_nuage, ...);


/**
 * @fn void supprimer_matrice_dino(t_dino *dino, int matrice[MAT_H][MAT_L]);
 * @author Solène Orieux
 * @date 
 * @brief
 * @param dino
 * @param matrice
 */

void supprimer_matrice_dino(t_dino *dino, int matrice[MAT_H][MAT_L]);

/**
 * @fn int chercherNouveauIndiceNuage(t_dino *dino, t_coordonnee *nuage, int *nb_pts, int matrice[MAT_H][MAT_L]);
 * @author Solène Orieux
 * @date 
 * @brief
 * @param dino
 * @param nuage
 * @param nb_pts
 * @param matrice
 */
int chercherNouveauIndiceNuage(t_dino *dino, t_coordonnee *nuage, int *nb_pts, int matrice[MAT_H][MAT_L]);

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

int horsNuage(t_dino *dino, t_coordonnee *nuage, int nb_pts, int matrice[MAT_H][MAT_L], int mvt);

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

void saut(t_dino *dino, t_coordonnee *nuage, int nb_pts, int matrice[MAT_H][MAT_L],const Uint8 *state);
#endif