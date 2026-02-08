#ifndef _FONCTIONSREBONDS_H_
#define _FONCTIONSREBONDS_H_

#include <SDL2/SDL.h>
#include "types.h"

/** 
 * @file fonctionsRebonds.h
 * @brief Définition des fonctions pour le lancer, la trajectoire et l'affichage d'une bombe
 */

/** 
 * @fn void tracerBombe(SDL_Renderer *zoneAffichage, t_coordonnee *coor, int rayon);
 * @brief la fonction trace une bombe dans une zone d'affichage
 * @param zoneAffichage pointeur sur la zone d'affichage
 * @param coor pointeur sur les coordonnées où l'on souhaite tracer la bombe 
 * @param rayon de la bombe
 */

void tracerBombe(SDL_Renderer *zoneAffichage, t_coordonnee *coor, int rayon);

/**
 * @fn int rebondFrontiereBombe(int largeurFenetre, int hauteurFenetre, t_coordonnee *coor, int rayon);
 * @brief la fonction vérifie si la bombe tape une extrémité de la fenêtre
 * @param largeurFenetre largeur de la fenetre
 * @param hauteurFenetre hauteur de la fenetre
 * @param coor pointeur sur les coordonnées de la bombe 
 * @param rayon de la bombe
 */

int rebondFrontiereBombe(int largeurFenetre, int hauteurFenetre, t_coordonnee *coor, int rayon);

#endif