#ifndef _FONCTIONSREBONDS_H_
#define _FONCTIONSREBONDS_H_

#include <SDL2/SDL.h>
#include "types.h"

/** 
 * @file fonctionsRebonds.h
 * @brief Définition des fonctions pour le lancer, la trajectoire et l'affichage d'une bombe
 * @author Hannah Sergent
 * @date Crée le 5/02/2026
 */

/**
 * @def COEF_RESTITUTION
 * @brief Coefficient utilisé pour faire ralentir la bombe lorsqu'elle rebondit sur le terrain
*/

#define COEF_RESTITUTION 0.9

/**
 * @fn void choixHauteurLancer(SDL_Renderer* zoneAffichage, SDL_Texture *texMap, SDL_Rect *rect, const Uint8 **etatClavier, t_bombe *bombe, t_vect *vectVitesse, float gravite);
 * @brief la fonction ajuste la hauteur du lancer en fonction des touches pressées par le joueur
 * @author Hannah Sergent
 * @date Crée le 11/02/2026
 * @param zoneAffichage pointeur sur la zone d'affichage
 * @param texMap l'image de la map sous forme de texture
 * @param rect les coordonnées pour placer la map dans la fenetre
 * @param etatClavier un pointeur de pointeur sur l'état du clavier
 * @param bombe pointeur sur une structure de type bombe
 * @param vectVitesse un pointeur sur un vecteur vitesse
 * @param gravite la gravite choisie
 */

void choixHauteurLancer(SDL_Renderer* zoneAffichage, SDL_Texture *texMap, SDL_Rect *rect, const Uint8 **etatClavier, t_bombe *bombe, t_vect *vectVitesse, float gravite);

/**
 * @fn void initialiserBombe(t_bombe *bombe, float coorChoisieX, float coorChoisieY, int rayon);
 * @brief la fonction initialise les valeurs d'une bombe
 * @author Hannah Sergent
 * @date Crée le 11/02/2026
 * @param bombe pointeur sur une structure de type bombe non initialisée
 * @param coorChoisieX coordonnée x de la bombe
 * @param coorChoisieX coordonnée y de la bombe
 * @param rayon rayon de la bombe
 */

void initialiserBombe(t_bombe *bombe, float coorChoisieX, float coorChoisieY, int rayon);

/**
 * @fn void initialiserVitesse(float *vitesseX, float *vitesseY, float vitesseChoisieX, float vitesseChoisieY);
 * @brief la fonction initialise les vitesses horizontales et verticales
 * @author Hannah Sergent
 * @date Crée le 11/02/2026
 * @param vectVitesse  un pointeur sur un vecteur vitesse
 * @param vitesseChoisieX vitesse horizontale choisie
 * @param vitesseChoisieY vitesse verticale choisie
 */

void initialiserVitesse(t_vect *vectVitesse, float vitesseChoisieX, float vitesseChoisieY);

 /**
 * @fn void miseAjourTemps(Uint32 *tempsPrecedent, float *tempsEcoule);
 * @brief la fonction met à jour le temps écoulé
 * @author Hannah Sergent
 * @date Crée le 11/02/2026
 * @param tempsPrecedent un pointeur sur le temps précédent
 * @param tempsEcoule un pointeur sur le temps écoulé
 */

void miseAjourTemps(Uint32 *tempsPrecedent, float *tempsEcoule);

/**
 * @fn int collisionFrontiereBombe(int largeurFenetre, int hauteurFenetre, t_bombe *bombe)
 * @brief la fonction vérifie si la bombe tape une extrémité de la fenêtre
 * @author Hannah Sergent
 * @date Crée le 6/02/2026
 * @param largeurFenetre largeur de la fenetre
 * @param hauteurFenetre hauteur de la fenetre
 * @param bombe pointeur sur une structure de type bombe 
 */

int collisionFrontiereBombe(int largeurFenetre, int hauteurFenetre, t_bombe *bombe);

/**
 * @fn collisionTerrainBombe(t_case matriceTerrain[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], t_bombe *bombe);
 * @brief la fonction vérifie si la bombe percute la terre
 * @author Hannah Sergent
 * @date Crée le 17/02/2026
 * @param matriceTerrain matrice contenant les informations sur le terrain
 * @param bombe pointeur sur une structure de type bombe 
 */

int collisionTerrainBombe(t_case matriceTerrain[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], t_bombe *bombe, t_vect *vectVitesse);

/**
 * @fn int collisionEauBombe(t_case matriceTerrain[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], t_bombe *bombe);
 * @brief la fonction vérifie si la bombe plonge
 * @author Hannah Sergent
 * @date Crée le 23/02/2026
 * @param matriceTerrain matrice contenant les informations sur le terrain
 * @param bombe pointeur sur une structure de type bombe 
 */

int collisionEauBombe(t_case matriceTerrain[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], t_bombe *bombe);

/** 
 * @fn void tracerBombe(SDL_Renderer *zoneAffichage, t_bombe *bombe);
 * @brief la fonction trace une bombe dans une zone d'affichage
 * @author Hannah Sergent
 * @date Crée le 5/02/2026
 * @param zoneAffichage pointeur sur la zone d'affichage
 * @param bombe pointeur sur une structure de type bombe
 */

void tracerBombe(SDL_Renderer *zoneAffichage, t_bombe *bombe);

#endif