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

/**
 * @def RADIANS
 * @brief permet de convertir un degrés en radian (3.14=pi)
*/
#define RADIANS 3.14/180


/**
 * @fn int collision_grapin(t_coordonnee pos, int matrice[MAT_H][MAT_L]);
 * @author Solène Orieux
 * @date 3/04/2006
 * @brief regarde si le grapin accroche
 * @param pos coordonnée du bout du grapin
 * @param matrice représentation du terrain sous forme de matrice
 */
int collision_grapin(t_coordonnee pos, int matrice[MAT_H][MAT_L]);


/**
 * @fn int chute(t_dino **dino, int nb_pts, t_coordonnee *nuage, int matrice[MAT_H][MAT_L], SDL_Renderer* zoneAffichage, 
    TTF_Font *police, SDL_Texture *texMap, SDL_Texture *texDinos[], SDL_Texture *texObjets[], char *nomsObjets[],
    t_joueur *equipe1, t_joueur *equipe2);
 * @author Solène Orieux
 * @date 07/04/2006
 * @brief Le dino chute lorsqu'il percute une colinne
 * @param dino pointeur de pointeur sur un dino
 * @param nb_pts nombre de points dans le nuage
 * @param nuage pointeur sur le nuage de points
 * @param matrice représentation du terrain sous forme de matrice
 * @param zoneAffichage pointeur sur la zone d'affichage
 * @param police un pointeur sur la police du jeu
 * @param texMap pointeur sur l'image de la map
 * @param texDino un tableau de pointeur sur les images représentant le dinosaure
 * @param texObjets un tableau de pointeur sur les images des différants objets
 * @param nomObjets un tableau de pointeur sur les noms des images des différants objets
 * @param equipe1 pointeur sur la structure correspondant aux dinosaures du joueur 1
 * @param equipe2 pointeur sur la structure correspondant aux dinosaures du joueur 2
 */


int chute(t_dino **dino, int nb_pts, t_coordonnee *nuage, int matrice[MAT_H][MAT_L], SDL_Renderer* zoneAffichage, 
    TTF_Font *police, SDL_Texture *texMap, SDL_Texture *texDinos[], SDL_Texture *texObjets[], char *nomsObjets[],
    t_joueur *equipe1, t_joueur *equipe2);


/**
 * @fn void balancier(int matrice[MAT_H][MAT_L], t_dino *dino, SDL_Renderer* zoneAffichage, 
               const Uint8 *state, TTF_Font *police, SDL_Texture *texMap, 
               SDL_Texture *texDinos[], SDL_Texture *texObjets[], char *nomsObjets[], 
               t_joueur *equipe1, t_joueur *equipe2, t_coordonnee *pts_rotation);
 * @author Solène Orieux
 * @date 07/04/2006
 * @brief on balance le dino pour qu'il se positionne sur le dessu de la colline
 * @param matrice représentation du terrain sous forme de matrice
 * @param dino pointeur de pointeur sur un dino
 * @param zoneAffichage pointeur sur la zone d'affichage
 * @param state pointeur sur le détecteur de touche du clavier
 * @param police un pointeur sur la police du jeu
 * @param texMap pointeur sur l'image de la map
 * @param texDino un tableau de pointeur sur les images représentant le dinosaure
 * @param texObjets un tableau de pointeur sur les images des différants objets
 * @param nomObjets un tableau de pointeur sur les noms des images des différants objets
 * @param equipe1 pointeur sur la structure correspondant aux dinosaures du joueur 1
 * @param equipe2 pointeur sur la structure correspondant aux dinosaures du joueur 2
 * @param pts_rotation pointeur sur la coordonnée du points de rotation du grapin
 */

void balancier(int matrice[MAT_H][MAT_L], t_dino *dino, SDL_Renderer* zoneAffichage, 
               const Uint8 *state, TTF_Font *police, SDL_Texture *texMap, 
               SDL_Texture *texDinos[], SDL_Texture *texObjets[], char *nomsObjets[], 
               t_joueur *equipe1, t_joueur *equipe2, t_coordonnee *pts_rotation);


               
/**
 * @fn float choixAngleLancer(t_dino *dino, SDL_Renderer* zoneAffichage,  const Uint8 *state, TTF_Font *police, SDL_Texture *texMap,
     SDL_Texture *texDinos[], SDL_Texture *texObjets[], char *nomsObjets[],
     t_joueur equipe1, t_joueur equipe2);
 * @author Solène Orieux
 * @date 3/04/2006
 * @brief on choisit l'angle du lancers du grapin
 * @param dino pointeur de pointeur sur un dino
 * @param zoneAffichage pointeur sur la zone d'affichage
 * @param state pointeur sur le détecteur de touche du clavier
 * @param police un pointeur sur la police du jeu
 * @param texMap pointeur sur l'image de la map
 * @param texDino un tableau de pointeur sur les images représentant le dinosaure
 * @param texObjets un tableau de pointeur sur les images des différants objets
 * @param nomObjets un tableau de pointeur sur les noms des images des différants objets
 * @param equipe1 structure correspondant aux dinosaures du joueur 1
 * @param equipe2 structure correspondant aux dinosaures du joueur 2
 */
float choixAngleLancer(t_dino *dino, SDL_Renderer* zoneAffichage,  const Uint8 *state, TTF_Font *police, SDL_Texture *texMap,
     SDL_Texture *texDinos[], SDL_Texture *texObjets[], char *nomsObjets[],
     t_joueur equipe1, t_joueur equipe2);


/**
 * @fn int lancer(t_coordonnee_calcul *pos_precise, float angle, int matrice[MAT_H][MAT_L], int *collision, int distance_parcourue);
 * @author Solène Orieux
 * @date 3/04/2006
 * @brief on lance le grapin
 * @param pos_precise pointeur sur la dernière position ajouté dans la file
 * @param angle angle choisi pour lancer le grapin
 * @param matrice représentation du terrain sous forme de matrice
 * @param collision pointeur sur une variable booléenne qui permet de savoir si on à touché une nouvelle colline
 * @param distance_parcourue On s'assure que le grapin ne va pas détecter une colision avec l'emplacement initial
 */
int lancer(t_coordonnee_calcul *pos_precise, float angle, int matrice[MAT_H][MAT_L], int *collision, int distance_parcourue);

/**
 * @fn int rappel(int matrice[MAT_H][MAT_L], t_dino **dino, const Uint8 *state, int distance_parcourue, 
     SDL_Renderer* zoneAffichage, int *nb_pts, t_coordonnee **nuage, int nb_nuage, char *nomNuage[]);
 * @author Solène Orieux
 * @date 3/04/2006
 * @brief on monte le dino en rappel
 * @param matrice représentation du terrain sous forme de matrice
 * @param dino pointeur de pointeur sur un dino
 * @param state pointeur sur le détecteur de touche du clavier
 * @param distance_parcourue On s'assure que le grapin ne va pas détecter une colision avec l'emplacement initial
 * @param zoneAffichage pointeur sur la zone d'affichage
 * @param nb_pts pointeur sur le nombre de points dans le nuage
 * @param nuage pointeur de pointeur sur le nuage de points
 * @param nb_nuage nombre de nuage présent dans la map
 * @param nomNuage liste des différents noms d'image permettant de créer le nuage
 */


int rappel(int matrice[MAT_H][MAT_L], t_dino **dino, const Uint8 *state, int distance_parcourue, 
     SDL_Renderer* zoneAffichage, int *nb_pts, t_coordonnee **nuage, int nb_nuage, char *nomNuage[]);


/**
 * @fn int grapin(int matrice[MAT_H][MAT_L], SDL_Renderer* zoneAffichage, t_dino **dino, 
           const Uint8 *state, SDL_Texture *texMap, TTF_Font *police,
           SDL_Texture *texDinos[], SDL_Texture *texObjets[], char *nomsObjets[],
           t_joueur *equipe1, t_joueur *equipe2,int *nb_pts, t_coordonnee **nuage, 
           int nb_nuage, char *nomNuage[]);
 * @author Solène Orieux
 * @date 3/04/2006
 * @brief on utilise le grapin
 * @param matrice représentation du terrain sous forme de matrice
 * @param zoneAffichage pointeur sur la zone d'affichage
 * @param dino pointeur de pointeur sur un dino
 * @param state pointeur sur le détecteur de touche du clavier
 * @param texMap pointeur sur l'image de la map
 * @param police un pointeur sur la police du jeu
 * @param texDino un tableau de pointeur sur les images représentant le dinosaure
 * @param texObjets un tableau de pointeur sur les images des différants objets
 * @param nomObjets un tableau de pointeur sur les noms des images des différants objets
 * @param equipe1 structure correspondant aux dinosaures du joueur 1
 * @param equipe2 structure correspondant aux dinosaures du joueur 2
 */

 
int grapin(int matrice[MAT_H][MAT_L], SDL_Renderer* zoneAffichage, t_dino **dino, 
           const Uint8 *state, SDL_Texture *texMap, TTF_Font *police,
           SDL_Texture *texDinos[], SDL_Texture *texObjets[], char *nomsObjets[],
           t_joueur *equipe1, t_joueur *equipe2,int *nb_pts, t_coordonnee **nuage, 
           int nb_nuage, char *nomNuage[]);
#endif