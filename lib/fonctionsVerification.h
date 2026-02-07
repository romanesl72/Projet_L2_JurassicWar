/**
 * @file fonctionsVerification.h
 * @brief Fonctions d'initialisation de la bibliothèque SDL2.
 */

#ifndef _FONCTIONSVERIFICATION_H_
#define _FONCTIONSVERIFICATION_H_

#include <SDL2/SDL.h>
//#include <SDL2/SDL_image.h>
//#include <SDL2/SDL_ttf.h>

/**
 * @brief Initialise les modules SDL2, IMG et TTF.
 * @return 1 si succès, 0 si erreur.
 */
int initialisationCorrecte();

/**
 * @brief Charge une image en texture SDL.
 * @param zoneAffichage Le renderer où la texture sera utilisée.
 * @param img Pointeur sur le pointeur de texture à charger.
 * @param nomFichier Chemin vers le fichier image.
 * @param imgLongueur Pointeur pour stocker la largeur de l'image chargée.
 * @param imgHauteur Pointeur pour stocker la hauteur de l'image chargée.
 */
void chargerImage(SDL_Renderer *zoneAffichage, SDL_Texture **img, char *nomFichier, int *imgLongueur, int *imgHauteur);


/**
 * @brief Crée une fenêtre SDL centrée.
 * @param fenetre Pointeur sur le pointeur de fenêtre à créer.
 * @param nomFenetre Titre de la fenêtre.
 * @param fenLargeur Largeur en pixels.
 * @param fenHauteur Hauteur en pixels.
 */
void creerFenetre(SDL_Window **fenetre, char* nomFenetre, int fenLargeur, int fenHauteur);


/**
 * @brief Initialise une police TTF.
 * @param police Pointeur sur le pointeur de police à initialiser.
 * @param nomFichier Chemin vers le fichier de police.
 * @param taillePolice Taille de la police.
 */
//void initialiserPolice(TTF_Font **police, char *nomFichier, int taillePolice);

#endif