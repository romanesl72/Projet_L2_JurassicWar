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
 * @fn void choixHauteurLancer(SDL_Renderer* zoneAffichage, const Uint8 **etatClavier, t_bombe *bombe, float *vitesseX, float *vitesseY, float gravite);
 * @brief la fonction ajuste la hauteur du lancer en fonction des touches pressées par le joueur
 * @author Hannah Sergent
 * @date Crée le 11/02/2026
 * @param etatClavier un pointeur de pointeur sur l'état du clavier
 * @param bombe pointeur sur une structure de type bombe
 * @param vitesseX un pointeur sur la vitesse horizontale en pixel par seconde
 * @param vitesseY un pointeur sur la vitesse verticale en pixel par seconde
 * @param gravite la gravite choisie
 */

void choixHauteurLancer(SDL_Renderer* zoneAffichage, const Uint8 **etatClavier, t_bombe *bombe, float *vitesseX, float *vitesseY, float gravite);

/**
 * @fn void initialiserBombe(t_bombe *bombe, int coorChoisieX, int coorChoisieY, int rayon);
 * @brief la fonction initialise les valeurs d'une bombe
 * @author Hannah Sergent
 * @date Crée le 11/02/2026
 * @param bombe pointeur sur une structure de type bombe non initialisée
 * @param coorChoisieX coordonnée x de la bombe
 * @param coorChoisieX coordonnée y de la bombe
 * @param rayon rayon de la bombe
 */

void initialiserBombe(t_bombe *bombe, int coorChoisieX, int coorChoisieY, int rayon);

/**
 * @fn void initialiserVitesse(float *vitesseX, float *vitesseY, float vitesseChoisieX, float vitesseChoisieY);
 * @brief la fonction initialise les vitesses horizontales et verticales
 * @author Hannah Sergent
 * @date Crée le 11/02/2026
 * @param vitesseX pointeur qui va contenir la vitesse horizontale
 * @param vitesseY pointeur qui va contenir la vitesse verticale
 * @param vitesseChoisieX vitesse horizontale choisie
 * @param vitesseChoisieY vitesse verticale choisie
 */

void initialiserVitesse(float *vitesseX, float *vitesseY, float vitesseChoisieX, float vitesseChoisieY);

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
 * @fn int rebondFrontiereBombe(int largeurFenetre, int hauteurFenetre, t_bombe *bombe)
 * @brief la fonction vérifie si la bombe tape une extrémité de la fenêtre
 * @author Hannah Sergent
 * @date Crée le 6/02/2026
 * @param largeurFenetre largeur de la fenetre
 * @param hauteurFenetre hauteur de la fenetre
 * @param bombe pointeur sur une structure de type bombe 
 */

int rebondFrontiereBombe(int largeurFenetre, int hauteurFenetre, t_bombe *bombe);

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