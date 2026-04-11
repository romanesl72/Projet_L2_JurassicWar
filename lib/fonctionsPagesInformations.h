#ifndef _FONCTIONSPAGESINFORMATIONS_H_
#define _FONCTIONSPAGESINFORMATIONS_H_

#include "types.h"

/** 
 * @file fonctionsPagesInformations.h
 * @brief Définitions des fonctions liées aux fenêtres d'informations, c'est à dire la liste des touches et les règles du jeu.
 * @author Hannah Sergent
 * @date Crée le 01/04/2026
 * @version 1.0
 */

/**
 * @def TAILLE_POLICE_PARAGRAPHE
 * @brief Taille de police choisie pour les paragraphes des fenêtres d'information.
*/

#define TAILLE_POLICE_PARAGRAPHE 20

/**
 * @def TAILLE_POLICE_SOUS_TITRE
 * @brief Taille de police choisie pour les sous-titres des fenêtres d'information.
*/

#define TAILLE_POLICE_SOUS_TITRE 23

/**
 * @fn int creerFenInfos(SDL_Window **fenInfos, SDL_Renderer **zoneInfos, char * titreFen);
 * @brief La fonction crée une fenêtre qui contient des informations pour l'utilisateur.
 * @author Hannah Sergent
 * @date Crée le 01/04/2026
 * @version 1.0
 * @param fenInfos un pointeur de pointeur sur la fenêtre du menu principal
 * @param zoneInfos un pointeur de pointeur sur la zone dans laquelle les informations seront affichées
 * @param titreFen le titre à afficher en haut de la fenêtre
 */

int creerFenInfos(SDL_Window **fenInfos, SDL_Renderer **zoneInfos, char *titreFen);

/**
 * @fn void detruireFenInfos(SDL_Window **fenInfos, SDL_Renderer **zoneInfos);
 * @brief La fonction détruit une fenêtre d'information sur le jeu.
 * @author Hannah Sergent
 * @date Crée le 01/04/2026
 * @version 1.0
 * @param fenInfos un pointeur de pointeur sur la fenêtre du menu
 * @param zoneMenu un pointeur de pointeur sur la zone d'affichage d'informations
 */

void detruireFenInfos(SDL_Window **fenInfos, SDL_Renderer **zoneInfos);

/**
 * @fn void ouvrirFenInfos(char *nomFen, char *nomFichier);
 * @brief La fonction ouvre une fenêtre d'information sur le jeu.
 * @author Hannah Sergent
 * @date Crée le 01/04/2026
 * @version 1.0
 * @param nomFen le nom de la fenêtre
 * @param nomFichier le nom du fichier contenant les informations à afficher dans le jeu
 */

void ouvrirFenInfos(char *nomFen, char *nomFichier);

#endif