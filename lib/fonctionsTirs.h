#ifndef _TIRER_H_
#define _TIRER_H_

#include "../lib/fonctionsMenuHIP.h"
#include "types.h"

/** 
 * @file fonctionsTirs.h
 * @brief Définitions des fonctions pour les tirs.
 * @author Romane Saint_Léger
 * @date Crée le 17/03/2026
 * @version 2.0
 */

/**
 * @fn void initialiserTirArcher(t_tir *tir, float departX, float departY, t_arme arme);
 * @brief Fonction qui initialise le tir avec une certaine position
 * @author Romane Saint-Léger
 * @date Crée le 17/03/2026
 * @version 1.0
 * @param tir pointeur sur la structure de tir afin d'accéder aux vecteurs et coordonnées du tir
 * @param departX coordonnée x du départ du tir
 * @param departY coordonnée y du départ du tir
 * @param arme structure de l'arme que l'on va utiliser
 */

void initialiserTirArcher(t_tir *tir, float departX, float departY, t_arme arme);

/**
 * @fn int collisionFrontiere(t_tir *tir);
 * @brief Fonction qui regarde si le tir entre en contact avec les frontières du jeu
 * @author Romane Saint-Léger
 * @date Crée le 17/03/2026
 * @version 1.0
 * @param tir pointeur sur la structure de tir afin d'avoir ses coordonnées
 * @return int Renvoie 1 si le tir est entré en collision avec les frontières, sinon 0
 */

int collisionFrontiere(t_tir *tir);

/**
 * @fn int collisionTerrain(int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], t_tir *tir);
 * @brief Fonction qui regarde si le tir entre en contact avec le terrain
 * @author Romane Saint-Léger
 * @date Crée le 17/03/2026
 * @version 1.0
 * @param matrice matrice d'entiers correspondant à la terre, l'eau, l'air ou les dinos
 * @param tir pointeur sur la structure de tir afin d'avoir ses coordonnées
 * @return int Renvoie 1 si le tir est entré en collision avec le terrain, sinon 0
 */

int collisionTerrain(int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], t_tir *tir);

/**
 * @fn int collisionEau(int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], t_tir *tir);
 * @brief Fonction qui regarde si le tir entre en contact avec l'eau
 * @author Romane Saint-Léger
 * @date Crée le 17/03/2026
 * @version 1.0
 * @param matrice matrice d'entiers correspondant à la terre, l'eau, l'air ou les dinos
 * @param tir pointeur sur la structure de tir afin d'avoir ses coordonnées
 * @return int Renvoie 1 si le tir est entré en collision avec l'eau, sinon 0
 */

int collisionEau(int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], t_tir *tir);

/**
 * @fn int collisionDino(int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], t_tir *tir);
 * @brief Fonction qui regarde si le tir entre en contact avec un dino
 * @author Romane Saint-Léger
 * @date Crée le 17/03/2026
 * @version 1.0
 * @param matrice matrice d'entiers correspondant à la terre, l'eau, l'air ou les dinos
 * @param tir pointeur sur la structure de tir afin d'avoir ses coordonnées
 * @return int Renvoie le numero du dino touché, sinon 0
 */

int collisionDino(int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], t_tir *tir);

/**
 * @fn int mettreAJourVol(t_tir *tir, int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], float gravite, int id_tireur);
 * @brief Fonction qui met à jour le vol du tir
 * @author Romane Saint-Léger
 * @date Crée le 17/03/2026
 * @version 1.3
 * @param tir pointeur sur la structure de tir afin d'avoir ses coordonnées et ses vecteurs
 * @param matrice matrice d'entiers correspondant à la terre, l'eau, l'air ou les dinos
 * @param gravite constante de gravite utilisé sur les armes
 * @param id_tireur numéro du dino entrain de tirer
 * @return 
 */

int mettreAJourVol(t_tir *tir, int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], float gravite, int id_tireur);

/**
 * @fn void tracerArme(SDL_Renderer *zoneAffichage, t_tir *tir);
 * @brief Fonction qui trace l'arme
 * @author Romane Saint-Léger
 * @date Crée le 17/03/2026
 * @version 1.3
 * @param zoneAffichage un pointeur sur la zone d'affichage
 * @param tir pointeur sur la structure de tir afin d'acceder à l'arme utilisé
 */

void tracerArme(SDL_Renderer *zoneAffichage, t_tir *tir);

/**
 * @fn void tracerTrajectoireTir(SDL_Renderer *zoneAffichage, t_tir *tir, float gravite);
 * @brief Fonction qui trace la trajectoire du tir avant que celui-ci ne soit effectué
 * @author Romane Saint-Léger
 * @date Crée le 17/03/2026
 * @version 1.3
 * @param zoneAffichage un pointeur sur la zone d'affichage
 * @param tir pointeur sur la structure de tir afin d'acceder à l'arme utilisé
 * @param gravite constante de gravite utilisé sur les armes
 */

void tracerTrajectoireTir(SDL_Renderer *zoneAffichage, t_tir *tir, float gravite);

/**
 * @fn void AncienviserArcher(SDL_Renderer* zoneAffichage, SDL_Texture *texMap, t_tir *tir, const Uint8 **etatClavier, float gravite, t_joueur *e1, t_joueur *e2);
 * @brief Ancienne version d'une fonction qui permet de viser
 * @author Romane Saint-Léger
 * @date Crée le 06/04/2026
 * @version 1.0
 * @param zoneAffichage un pointeur sur la zone d'affichage
 * @param texMap pointeur sur la texture de la map
 * @param tir pointeur sur la structure de tir
 * @param etatClavier un pointeur de pointeur sur l'état du clavier
 * @param gravite constante de gravite utilisé sur les armes
 * @param e1 pointeur sur la structure de l'équipe 1
 * @param e2 pointeur sur la structure de l'équipe 2
 */

void AncienviserArcher(SDL_Renderer* zoneAffichage, SDL_Texture *texMap, t_tir *tir, const Uint8 **etatClavier, float gravite, t_joueur *e1, t_joueur *e2);

/**
 * @fn void viserArcher(SDL_Renderer* zoneAffichage, SDL_Texture *texMap, SDL_Texture **texObjets, TTF_Font *police, t_tir *tir, const Uint8 *etatClavier, float gravite, t_joueur *e1, t_joueur *e2, t_case numDinoCourant);
 * @brief 
 * @author Romane Saint-Léger
 * @date Crée le 17/03/2026
 * @version 3.1
 * @param zoneAffichage un pointeur sur la zone d'affichage
 * @param texMap pointeur sur la texture de la map
 * @param texObjets pointeur sur la texture des Objets
 * @param police pointeur sur la police d'écriture
 * @param tir pointeur sur la structure de tir
 * @param etatClavier un pointeur de pointeur sur l'état du clavier
 * @param gravite constante de gravite utilisé sur les armes
 * @param e1 pointeur sur la structure de l'équipe 1 afin de pouvoir accéder aux dinos de leur équipe
 * @param e2 pointeur sur la structure de l'équipe 2 afin de pouvoir accéder aux dinos de leur équipe
 * @param numDinoCourant Numéro du dinosaure en train de tirer
 */

void viserArcher(SDL_Renderer* zoneAffichage, SDL_Texture *texMap, SDL_Texture **texObjets, TTF_Font *police, t_tir *tir, const Uint8 *etatClavier, float gravite, t_joueur *e1, t_joueur *e2, t_case numDinoCourant);

/**
 * @fn appliquerDegats(int numDinoTouche, int degats, t_joueur *equipe1, t_joueur *equipe2, int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN]);
 * @brief 
 * @author Romane Saint-Léger
 * @date Crée le 01/04/2026
 * @version 1.2
 * @param numDinoTouche Numéro du dinosaure touché
 * @param degats Entier pour le nombre de degats effectuer par l'arme de tir
 * @param equipe1 pointeur sur la structure de l'équipe 1 afin de pouvoir accéder aux dinos de leur équipe
 * @param equipe2 pointeur sur la structure de l'équipe 1 afin de pouvoir accéder aux dinos de leur équipe
 * @param matrice matrice d'entiers du jeu afin de supprimer les numéros du dino si il meurt
 */

void appliquerDegats(int numDinoTouche, int degats, t_joueur *equipe1, t_joueur *equipe2, int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN]);

#endif