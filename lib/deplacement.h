#ifndef _DEPLACEMENT_H_
#define _DEPLACEMENT_H_

#include "types.h"

/** 
 * @file deplacement.h
 * @brief fonctions permettant au dino de se déplacer
 * @author Solène Orieux
 * @date 25/02/2026
 */


/**
 * @def VITESSE_BASE
 * @brief vitesse du dino lorsqu'il est sur du plas
*/

#undef VITESSE_BASE
#define VITESSE_BASE 0.1

/**
 * @def GRAVITE
 * @brief diminue la vitesse des sauts/chute pour faire tomber de plus en plus vite le dino
*/

#undef GRAVITE
#define GRAVITE 0.4 

/**
 * @def FORCE_SAUT
 * @brief force initia appliqué au saut
*/

#undef FORCE_SAUT
#define FORCE_SAUT -7.0



/**
 * @fn int horsNuage(t_dino *dino, int nb_pts, int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN]);
 * @author Solène Orieux
 * @date 11/03/2026
 * @brief renvoie vraie l'indice du dino n'est plus dans le nuage, faux sinon
 * @param dino pointeur sur dino
 * @param nb_pts nombre de points dans le nuage
 */

int horsNuage(t_dino *dino, int nb_pts);

/**
 * @fn int replacementNuage(t_dino *dino, int *nb_pts, t_coordonnee **nuage, int nb_nuage, char *nomNuage[], int sens);
 * @author Solène Orieux
 * @date 06/04/2026
 * @brief permet de retrouver la position du dino sur le nuage de points lorsqu'on change de colline
 * @param dino pointeur sur dino
 * @param nb_pts nombre de points dans le nuage
 * @param nuage pointeur de pointeur sur le nuage de points
 * @param matrice représentation du terrain sous forme de matrice
 * @param nb_nuage nombre de nuage présent dans la map
 * @param nomNuage liste des différents noms d'image permettant de créer le nuage
 * @param sens permet de savoir vers quels nuage on se dirige
 */
int replacementNuage(t_dino *dino, int *nb_pts, t_coordonnee **nuage, int nb_nuage, char *nomNuage[], int sens);

/**
 * @fn int noyade(t_dino *dino, int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN]);
 * @author Solène Orieux
 * @date 01/04/2026
 * @brief renvoie vraie si le dino s'est noyé, faux sinon
 * @param dino pointeur sur dino
 * @param matrice représentation du terrain sous forme de matrice
 */
int noyade(t_dino *dino, int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN]);

/**
 * @fn void tomberNuage(t_dino *dino, t_coordonnee **nuage, char *nomNuage[], int nb_nuage, int *nb_pts, int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], int sens);
 * @author Solène Orieux
 * @date 01/04/2026
 * @brief permet de retrouver la position du dino sur le nuage de points lorsqu'on change de colline
 * @param dino pointeur sur dino
 * @param nuage pointeur de pointeur sur le nuage de points
 * @param nomNuage liste des différents noms d'image permettant de créer le nuage
 * @param nb_nuage nombre de nuage présent dans la map
 * @param nb_pts pointeur sur le nombre de points dans le nuage
 * @param matrice représentation du terrain sous forme de matrice
 * @param sens permet de savoir vers quels nuage on se dirige
 */
void tomberNuage(t_dino *dino, t_coordonnee **nuage, char *nomNuage[], int nb_nuage, int *nb_pts, int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], int sens);

/**
 * @fn void marcher(t_dino *dino, t_coordonnee **nuage, char *nomNuage[], int nb_nuage, int *nb_pts, int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], const Uint8 *state, int sens, int booleen);
 * @date 08/04/2026
 * @brief permet au dino de marcher plus ou moins vite en fonction de la pente
 * @param dino pointeur sur dino
 * @param nuage pointeur de pointeur sur le nuage de points
 * @param nomNuage liste des différents noms d'image permettant de créer le nuage
 * @param nb_nuage nombre de nuage présent dans la map
 * @param nb_pts pointeur sur le nombre de points dans le nuage
 * @param matrice représentation du terrain sous forme de matrice
 * @param state pointeur sur l'état du clavier
 * @param sens permet de savoir vers quels nuage on se dirige
 * @param booleen permet de savoir si l'on n'est pas hors nuage
 */
void marcher(t_dino *dino, t_coordonnee **nuage, char *nomNuage[], int nb_nuage, int *nb_pts, int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], const Uint8 *state, int sens, int booleen);


/**
 * @fn void gauche(t_dino *dino, t_coordonnee **nuage, char *nomNuage[], int nb_nuage, int *nb_pts, int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN],const Uint8 *state);
 * @author Solène Orieux
 * @date 25/02/2026
 * @brief Le dino se dirige à gauche
 * @param dino pointeur sur dino
 * @param nuage pointeur de pointeur sur le nuage de points
 * @param nomNuage liste des différents noms d'image permettant de créer le nuage
 * @param nb_nuage nombre de nuage présent dans la map
 * @param nb_pts pointeur sur le nombre de points dans le nuage
 * @param matrice représentation du terrain sous forme de matrice
 * @param state pointeur sur l'état du clavier
 */

void gauche(t_dino *dino, t_coordonnee **nuage, char *nomNuage[], int nb_nuage, int *nb_pts, int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN],const Uint8 *state);

/**
 * @fn void droite(t_dino *dino, t_coordonnee **nuage, char *nomNuage[], int nb_nuage, int *nb_pts, int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN],const Uint8 *state);
 * @author Solène Orieux
 * @date 25/022026
 * @brief Le dino se dirige à droite
 * @param dino pointeur sur dino
 * @param nuage pointeur de pointeur sur le nuage de points
 * @param nomNuage liste des différents noms d'image permettant de créer le nuage
 * @param nb_nuage nombre de nuage présent dans la map
 * @param nb_pts pointeur sur le nombre de points dans le nuage
 * @param matrice représentation du terrain sous forme de matrice
 * @param state pointeur sur l'état du clavier
 */

void droite(t_dino *dino, t_coordonnee **nuage, char *nomNuage[], int nb_nuage, int *nb_pts, int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN],const Uint8 *state);


/**
 * @fn void saut(t_dino *dino, t_coordonnee **nuage, char *nomNuage[], int nb_nuage, int *nb_pts, int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], const Uint8 *state);
 * @author Solène Orieux
 * @date 07/03/2026
 * @brief permet au dino de sauter
 * @param dino pointeur sur dino
 * @param nuage pointeur de pointeur sur le nuage de points
 * @param nomNuage liste des différents noms d'image permettant de créer le nuage
 * @param nb_nuage nombre de nuage présent dans la map
 * @param nb_pts pointeur sur le nombre de points dans le nuage
 * @param matrice représentation du terrain sous forme de matrice
 * @param state pointeur sur l'état du clavier
 */

void saut(t_dino *dino, t_coordonnee **nuage, char *nomNuage[], int nb_nuage, int *nb_pts, int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], const Uint8 *state);

/**
 * @fn void deplacement_dino();
 * @author Solène Orieux
 * @date 26/03/2026
 * @brief fonction qui appelle toutes les fonctions de déplacements
 * @param dino pointeur sur dino
 * @param nuage pointeur de pointeur sur le nuage de points
 * @param nomNuage liste des différents noms d'image permettant de créer le nuage
 * @param nb_nuage nombre de nuage présent dans la map
 * @param nb_pts pointeur sur le nombre de points dans le nuage
 * @param matrice représentation du terrain sous forme de matrice
 * @param equipe1 pointeur sur la structure correspondant aux dinosaures du joueur 1
 * @param equipe2 pointeur sur la structure correspondant aux dinosaures du joueur 2
 */

void deplacement_dino(t_dino *dino, t_coordonnee **nuage, char *nomNuage[], int nb_nuage, int *nb_pts, int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], t_joueur * equipe1, t_joueur * equipe2);

#endif