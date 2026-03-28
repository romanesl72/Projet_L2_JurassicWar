#ifndef _FONCTIONSVERIFICATION_H_
#define _FONCTIONSVERIFICATION_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

/**
 * @file fonctionsVerification.h
 * @brief Définition de fonctions pour initialiser différents objets SDL
 * @author Hannah Sergent
 * @date Crée le 27/01/2026
 */
 
 /** 
 * @fn int initialisationCorrecte();
 * @brief La fonction initialise SDL2, SDL2_image et SDL_ttf.
 * @author Hannah Sergent
 * @date Crée le 27/01/2026
 * @return 1 si tout s'est bien passé et 0 sinon
 */

int initialisationCorrecte();

/**
 * @fn void chargerImage(SDL_Renderer *zoneAffichage, SDL_Texture **img, char *nomFichier, int *imgLongueur, int *imgHauteur);
 * @brief La fonction charge une image comme une texture SDL et indique sa taille.
 * @author Hannah Sergent
 * @date Crée le 27/01/2026
 * @param zoneAffichage  un pointeur sur la zone d'affichage
 * @param img  un pointeur sur un pointeur de la texture image à charger
 * @param nomFichier le nom du fichier contenant l'image
 * @param imgLongueur un pointeur recevant la largeur de l'image
 * @param imgHauteur un pointeur recevant la hauteur de l'image
 */
void chargerImage(SDL_Renderer *zoneAffichage, SDL_Texture **img, char *nomFichier, int *imgLongueur, int *imgHauteur);

/**
 * @fn void chargerImageSansTaille(SDL_Renderer *zoneAffichage, SDL_Texture **img, char *nomFichier);
 * @brief La fonction charge une image comme une texture SDL sans indiquer sa taille.
 * @author Hannah Sergent
 * @date Crée le 28/03/2026
 * @param zoneAffichage pointeur sur la zone d'affichage
 * @param img pointeur sur un pointeur de la texture image à charger
 * @param nomFichier nom du fichier contenant l'image
 */
void chargerImageSansTaille(SDL_Renderer *zoneAffichage, SDL_Texture **img, char *nomFichier);

/**
 * @fn void creerFenetre(SDL_Window **fenetre, char* nomFenetre, int fenLargeur, int fenHauteur);
 * @brief La fonction crée une fenêtre centrée sur l'écran
 * @author Hannah Sergent
 * @date Crée le 27/01/2026
 * @param fenetre pointeur sur un pointeur de la fenêtre
 * @param nomFenetre titre de la fenêtre
 * @param fenLargeur largeur de la fenêtre
 * @param fenHauteur hauteur de la fenêtre
 */
void creerFenetre(SDL_Window **fenetre, char* nomFenetre, int fenLargeur, int fenHauteur);

/**
 * @fn void initialiserPolice(TTF_Font **police, char *nomFichier, int taillePolice);
 * @brief La fonction charge une police
 * @author Hannah Sergent
 * @date Crée le 27/01/2026
 * @param police pointeur sur le pointeur de police à initialiser
 * @param nomFichier nom du fichier contenant la police
 * @param taillePolice taille de la police
 */
void initialiserPolice(TTF_Font **police, char *nomFichier, int taillePolice);

#endif