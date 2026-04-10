#ifndef _FONCTIONSVERIFICATION_H_
#define _FONCTIONSVERIFICATION_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

/**
 * @file fonctionsVerification.h
 * @brief Définition de fonctions pour initialiser différents objets SDL.
 * @author Hannah Sergent
 * @date Crée le 27/01/2026
 * @version 1.5
 */
 
 /** 
 * @fn int initialisationCorrecte();
 * @brief La fonction initialise SDL2, SDL2_image et SDL_ttf.
 * @author Hannah Sergent
 * @date Crée le 27/01/2026
 * @version 1.0
 * @return 1 si tout s'est bien passé et 0 sinon
 */

int initialisationCorrecte();

/**
 * @fn void chargerImage(SDL_Renderer *zoneAffichage, SDL_Texture **img, char *nomFichier, int *imgLargeur, int *imgHauteur);
 * @brief La fonction charge une image comme une texture SDL et indique sa taille.
 * @author Hannah Sergent
 * @date Crée le 27/01/2026
 * @version 1.0
 * @param zoneAffichage un pointeur sur la zone d'affichage
 * @param img un pointeur sur un pointeur de la texture image à charger
 * @param nomFichier le nom du fichier contenant l'image
 * @param imgLargeur un pointeur recevant la largeur de l'image
 * @param imgHauteur un pointeur recevant la hauteur de l'image
 */

void chargerImage(SDL_Renderer *zoneAffichage, SDL_Texture **img, char *nomFichier, int *imgLargeur, int *imgHauteur);

/**
 * @fn void chargerImageSansTaille(SDL_Renderer *zoneAffichage, SDL_Texture **img, char *nomFichier);
 * @brief La fonction charge une image comme une texture SDL sans indiquer sa taille.
 * @author Hannah Sergent
 * @date Crée le 28/03/2026
 * @version 1.0
 * @param zoneAffichage un pointeur sur la zone d'affichage
 * @param img un pointeur sur un pointeur de la texture de l'image à charger
 * @param nomFichier le nom du fichier contenant l'image
 */

void chargerImageSansTaille(SDL_Renderer *zoneAffichage, SDL_Texture **img, char *nomFichier);

/**
 * @fn void creerFenetre(SDL_Window **fenetre, char *nomFenetre, int fenLargeur, int fenHauteur);
 * @brief La fonction crée une fenêtre centrée sur l'écran.
 * @author Hannah Sergent
 * @date Crée le 27/01/2026
 * @version 1.0
 * @param fenetre un pointeur de pointeur sur la fenêtre
 * @param nomFenetre le titre de la fenêtre
 * @param fenLargeur la largeur de la fenêtre
 * @param fenHauteur la hauteur de la fenêtre
 */

void creerFenetre(SDL_Window **fenetre, char *nomFenetre, int fenLargeur, int fenHauteur);

/**
 * @fn void initialiserPolice(TTF_Font **police, char *nomFichier, int taillePolice);
 * @brief La fonction charge une police
 * @author Hannah Sergent
 * @date Crée le 27/01/2026
 * @version 1.0
 * @param police un pointeur de pointeur sur la police à initialiser
 * @param nomFichier le nom du fichier contenant la police
 * @param taillePolice la taille de la police
 */

void initialiserPolice(TTF_Font **police, char *nomFichier, int taillePolice);

#endif