#ifndef _GRAPIN_H_
#define _GRAPIN_H_

#include <SDL2/SDL_ttf.h>
#include "types.h"

/** 
 * @file grapin.h
 * @brief Permet de lancer un grapin pour faciliter les déplacements
 * @author Solène Orieux
 * @date 3/04/2006
 */

/**
 * @def LONGUEUR
 * @brief longueur du trait affiché lorqu'on choisit l'angle pour lancer le grapin
*/
#define LONGUEUR 200

#define RADIANS 3.14/180


/**
 * @fn int collision_grapin(t_coordonnee pos, int matrice[MAT_H][MAT_L]);
 * @author Solène Orieux
 * @date 3/04/2006
 * @brief regarde si le grapin accroche
 * @param pos
 * @param matrice
 */
int collision_grapin(t_coordonnee pos, int matrice[MAT_H][MAT_L]);

int chute(t_dino **dino, int nb_pts, t_coordonnee *nuage, int matrice[MAT_H][MAT_L], SDL_Renderer* zoneAffichage, 
    TTF_Font *police, SDL_Texture *texMap, SDL_Texture *texDinos[], SDL_Texture *texObjets[], char *nomsObjets[],
    t_joueur *equipe1, t_joueur *equipe2);

void balancier(int matrice[MAT_H][MAT_L], t_dino *dino, SDL_Renderer* zoneAffichage, 
               const Uint8 *state, TTF_Font *police, SDL_Texture *texMap, 
               SDL_Texture *texDinos[], SDL_Texture *texObjets[], char *nomsObjets[], 
               t_joueur *equipe1, t_joueur *equipe2, t_coordonnee *pts_rotation);
               
/**
 * @fn float choixAngleLancer(t_dino *dino, SDL_Renderer* zoneAffichage,  const Uint8 *state);
 * @author Solène Orieux
 * @date 3/04/2006
 * @brief on choisit l'angle du lancers du grapin
 * @param dino pointeur sur un dino
 * @param zoneAffichage pointeur sur la zone d'affichage
 * @param state pointeur sur le détecteur de touche du clavier
 * @param police
 * @param texMap pointeur sur l'image de la map
 * @param texDino
 * @param texObjets
 * @param nomObjets
 * @param equipe1
 * @param equipe2
 */
float choixAngleLancer(t_dino *dino, SDL_Renderer* zoneAffichage,  const Uint8 *state, TTF_Font *police, SDL_Texture *texMap,
     SDL_Texture *texDinos[], SDL_Texture *texObjets[], char *nomsObjets[],
     t_joueur equipe1, t_joueur equipe2);


/**
 * @fn int lancer(t_coordonnee pos_initial, int angle, int matrice[MAT_H][MAT_L], int *collision_initial, int *collision);
 * @author Solène Orieux
 * @date 3/04/2006
 * @brief on lance le grapin
 * @param pos_precise pointeur sur la dernière position ajouté dans la file
 * @param angle
 * @param matrice
 * @param collision pointeur sur une variable booléenne qui permet de savoir si on à touché une nouvelle colline
 * @param distance_parcourue
 */
int lancer(t_coordonnee_calcul *pos_precise, float angle, int matrice[MAT_H][MAT_L], int *collision, int distance_parcourue);

/**
 * @fn int choixAngleLancer(t_dino *dino, SDL_Renderer* zoneAffichage,  const Uint8 *state);
 * @author Solène Orieux
 * @date 3/04/2006
 * @brief on monte le dino en rappel
 * @param matrice
 * @param dino pointeur sur un dino
 * @param collision pointeur sur une variable booléenne qui permet de savoir si on à touché une nouvelle colline
 * @param state pointeur sur le détecteur de touche du clavier
 * @param distance_parcourue
 * @param zoneAffichage pointeur sur la zone d'affichage
 */


int rappel(int matrice[MAT_H][MAT_L], t_dino **dino, const Uint8 *state, int distance_parcourue, 
     SDL_Renderer* zoneAffichage, int *nb_pts, t_coordonnee **nuage, int nb_nuage, char *nomNuage[]);


/**
 * @fn int grapin(int matrice[MAT_H][MAT_L], SDL_Renderer* zoneAffichage, t_dino **dino, const Uint8 *state);
 * @author Solène Orieux
 * @date 3/04/2006
 * @brief on utilise le grapin
 * @param matrice
 * @param zoneAffichage pointeur sur la zone d'affichage
 * @param dino pointeur de pointeur sur un dino
 * @param state pointeur sur le détecteur de touche du clavier
 * @param texMap pointeur sur l'image de la map
 * @param police
 * @param texDino
 * @param texObjets
 * @param nomObjets
 * @param equipe1
 * @param equipe2
 */
int grapin(int matrice[MAT_H][MAT_L], SDL_Renderer* zoneAffichage, t_dino **dino, 
           const Uint8 *state, SDL_Texture *texMap, TTF_Font *police,
           SDL_Texture *texDinos[], SDL_Texture *texObjets[], char *nomsObjets[],
           t_joueur *equipe1, t_joueur *equipe2,int *nb_pts, t_coordonnee **nuage, 
           int nb_nuage, char *nomNuage[]);
#endif