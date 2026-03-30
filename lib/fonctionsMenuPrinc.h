#ifndef _FONCTIONSMENUPRINC_H_
#define _FONCTIONSMENUPRINC_H_

#include "types.h"

/** 
 * @file fonctionsMenuPrinc.h
 * @brief Définitions des fonctions pour l'affichage du menu principal.
 * @author Hannah Sergent
 * @date Crée le 26/03/2026
 */

/**
 * @def LARGEUR_FEN_MENU
 * @brief Largeur du menu principal du jeu.
*/

#define LARGEUR_FEN_MENU 400

/**
 * @def HAUTEUR_FEN_MENU
 * @brief Hauteur du menu principal du jeu.
*/

#define HAUTEUR_FEN_MENU 700

/**
 * @def TAILLE_POLICE_TITRE
 * @brief Taille de police choisie pour le titre du menu principal.
*/

#define TAILLE_POLICE_TITRE 32

/**
 * @def TAILLE_POLICE_BOUTONS
 * @brief Taille de police choisie pour les boutons du menu principal.
*/

#define TAILLE_POLICE_BOUTONS 27

/**
 * @def LARGEUR_BOUTON
 * @brief Largeur des boutons du menu principal.
*/

#define LARGEUR_BOUTON 290

/**
 * @def HAUTEUR_BOUTON
 * @brief Hauteur des boutons du menu principal.
*/

#define HAUTEUR_BOUTON 70

/**
 * @def ESPACEMENT_BOUTONS
 * @brief Espacement entre chaque bouton dans le menu principal.
*/

#define ESPACEMENT_BOUTONS 30

/**
 * @fn void initialiserBoutons(SDL_Rect *boutons);
 * @brief La fonction initialise la liste des boutons du menu.
 * @author Hannah Sergent
 * @date Crée le 28/03/2026
 * @param boutons un tableau de type SDL_Rect représentant chaque bouton
 */

void initialiserBoutons(SDL_Rect *boutons);

/**
 * @fn int creerMenuPrincipal(SDL_Window **menuPrincipal, SDL_Renderer **zoneMenu, SDL_Texture **texImg, SDL_Texture **texImgMiroir);
 * @brief La fonction initialise le menu principal du jeu.
 * @author Hannah Sergent
 * @date Crée le 29/03/2026
 * @param menuPrincipal un pointeur de pointeur sur la fenêtre du menu principal
 * @param zoneMenu un pointeur de pointeur sur la zone du menu
 * @param texImg un pointeur de pointeur sur la texture de la première image à afficher dans le menu
 * @param texImgMiroir un pointeur de pointeur sur la texture de la deuxième image à afficher dans le menu
 */

int creerMenuPrincipal(SDL_Window **menuPrincipal, SDL_Renderer **zoneMenu, SDL_Texture **texImg, SDL_Texture **texImgMiroir);

/**
 * @fn void afficherMenuPrincipal(SDL_Renderer* zoneMenu, SDL_Rect *boutons, SDL_Texture *texImg, SDL_Texture *texImgMiroir);
 * @brief La fonction affiche le menu principal du jeu.
 * @author Hannah Sergent
 * @date Crée le 29/03/2026
 * @param zoneMenu un pointeur sur la zone du menu
 * @param boutons un tableau de type SDL_Rect représentant chaque bouton
 * @param texImg un pointeur sur la texture de la première image à afficher dans le menu
 * @param texImgMiroir un pointeur sur la texture de la deuxième image à afficher dans le menu
 */

void afficherMenuPrincipal(SDL_Renderer* zoneMenu, SDL_Rect *boutons, SDL_Texture *texImg, SDL_Texture *texImgMiroir);

/**
 * @fn void detecterEvenementMenuPrincipal(int *enCours, SDL_Rect *boutons);
 * @brief La fonction détecte si l'utilisateur réalise une action dans la fenêtre (cliquer sur un bouton, sur la croix pour fermer).
 * @author Hannah Sergent
 * @date Crée le 29/03/2026
 * @param enCours un pointeur qui indique si la fenetre doit rester ouverte
 * @param boutons un tableau de type SDL_Rect représentant chaque bouton
 */

void detecterEvenementMenuPrincipal(int *enCours, SDL_Rect *boutons);

/**
 * @fn void detruireMenuPrincipal(SDL_Window **menuPrincipal, SDL_Renderer **zoneMenu, SDL_Texture **texImg, SDL_Texture **texImgMiroir);
 * @brief La fonction détruit le menu principal du jeu.
 * @author Hannah Sergent
 * @date Crée le 29/03/2026
 * @param menuPrincipal un pointeur de pointeur sur la fenêtre du menu principal
 * @param zoneMenu un pointeur de pointeur sur la zone du menu
 * @param texImg un pointeur de pointeur sur la texture de la première image à afficher dans le menu
 * @param texImgMiroir un pointeur de pointeur sur la texture de la deuxième image à afficher dans le menu
 */

void detruireMenuPrincipal(SDL_Window **menuPrincipal, SDL_Renderer **zoneMenu, SDL_Texture **texImg, SDL_Texture **texImgMiroir);

#endif