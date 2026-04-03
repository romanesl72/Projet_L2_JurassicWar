#ifndef _FONCTIONSREBONDS2_H_
#define _FONCTIONSREBONDS2_H_

#include "types.h"
#include "../lib/fonctionsMenuHIP.h"

/** 
 * @file fonctionsRebonds.h
 * @brief Définition des fonctions pour le lancer, la trajectoire et l'affichage d'une bombe.
 * @author Hannah Sergent
 * @date Crée le 5/02/2026
 * @version 5.0
 */

/**
 * @def RAYON
 * @brief Taille du rayon de la bombe.
*/

#define RAYON 15

/**
 * @def VITESSE_X
 * @brief Vitesse horizontale initiale de la bombe.
*/

#define VITESSE_X 90

/**
 * @def VITESSE_Y
 * @brief Vitesse verticale initiale de la bombe.
*/

#define VITESSE_Y -90

/**
 * @def GRAVITE
 * @brief Gravite choisie pour la bombe.
*/

#define GRAVITE 140

/**
 * @def COEF_RESTITUTION
 * @brief Coefficient de restitution (0 pas de rebond, 1 rebond parfait).
*/

#define COEF_RESTITUTION 0.8

/**
 * @def PI
 * @brief Valeur remarquable pi.
*/

#define PI 3.1415

/**
 * @fn void choixHauteurLancer(SDL_Renderer* zoneAffichage, SDL_Texture *texMap, SDL_Rect *rect, const Uint8 **etatClavier, t_bombe *bombe, t_vect *vectVitesse, float gravite);
 * @brief La fonction ajuste la hauteur du lancer en fonction des touches pressées par le joueur.
 * @author Hannah Sergent
 * @date Crée le 11/02/2026
 * @param zoneAffichage un pointeur sur la zone d'affichage
 * @param texMap l'image de la map sous forme de texture
 * @param rect les coordonnées pour placer la map dans la fenêtre
 * @param etatClavier un pointeur de pointeur sur l'état du clavier
 * @param bombe un pointeur sur une structure de type bombe
 * @param vectVitesse un pointeur sur un vecteur vitesse
 */

void choixHauteurLancer(SDL_Renderer* zoneAffichage, SDL_Texture *texMap, SDL_Rect *rect, const Uint8 **etatClavier, t_bombe *bombe, t_vect *vectVitesse);

/**
 * @fn void choixHauteurLancerAvecDinos(SDL_Renderer* zoneAffichage, SDL_Texture *texMap, SDL_Rect *rect, const Uint8 **etatClavier, t_bombe *bombe, t_vect *vectVitesse, float gravite, t_joueur * equipe1, t_joueur * equipe2);
 * @brief La fonction ajuste la hauteur du lancer en fonction des touches pressées par le joueur. Les dinosaures sont présents à l'affichage.
 * @author Hannah Sergent
 * @date Crée le 17/03/2026
 * @param zoneAffichage un pointeur sur la zone d'affichage
 * @param texMap l'image de la map sous forme de texture
 * @param rect les coordonnées pour placer la map dans la fenetre
 * @param etatClavier un pointeur de pointeur sur l'état du clavier
 * @param bombe un pointeur sur une structure de type bombe
 * @param vectVitesse un pointeur sur un vecteur vitesse
 * @param equipe1 l'équipe1 dont on veut afficher les dinosaures
 * @param equipe2 l'équipe2 dont on veut afficher les dinosaures
 */

void choixHauteurLancerAvecDinos(SDL_Renderer* zoneAffichage, SDL_Texture *texMap, SDL_Rect *rect, const Uint8 **etatClavier, t_bombe *bombe, t_vect *vectVitesse, t_joueur * equipe1, t_joueur * equipe2);

/**
 * @fn void choixHauteurLancerDinoCourant(SDL_Renderer* zoneAffichage, SDL_Texture *texMap, SDL_Rect *rect, const Uint8 **etatClavier, t_bombe *bombe, t_vect *vectVitesse, float gravite, t_joueur * equipe1, t_joueur * equipe2, t_case numDinoCourant,  t_case matriceTerrain[HAUTEUR_TERRAIN][LARGEUR_TERRAIN]);
 * @brief la fonction ajuste la hauteur du lancer en fonction des touches pressées par le joueur. Les dinosaures sont présents à l'affichage et la bombe est lancée depuis la position d'un dinosaure.
 * @author Hannah Sergent
 * @date Crée le 22/03/2026
 * @param zoneAffichage pointeur sur la zone d'affichage
 * @param texMap l'image de la map sous forme de texture
 * @param rect les coordonnées pour placer la map dans la fenetre
 * @param etatClavier un pointeur de pointeur sur l'état du clavier
 * @param bombe pointeur sur une structure de type bombe
 * @param vectVitesse un pointeur sur un vecteur vitesse
 * @param equipe1 l'équipe1 dont on veut afficher les dinosaures
 * @param equipe2 l'équipe2 dont on veut afficher les dinosaures
 * @param matriceTerrain une matrice contenant les informations sur le terrain
 */

void choixHauteurLancerDinoCourant(SDL_Renderer* zoneAffichage, SDL_Texture *texMap, SDL_Rect *rect, const Uint8 **etatClavier, t_bombe *bombe, t_vect *vectVitesse, t_joueur * equipe1, t_joueur * equipe2, t_case numDinoCourant,  t_case matriceTerrain[HAUTEUR_TERRAIN][LARGEUR_TERRAIN]);

void choixHauteurLancerDinoCourantHIP(SDL_Renderer* zoneAffichage, SDL_Texture *texMap, SDL_Texture **texObjets, TTF_Font *policeMenuHIP, SDL_Rect *rect, const Uint8 **etatClavier, t_bombe *bombe, t_vect *vectVitesse, t_joueur * equipe1, t_joueur * equipe2, t_case numDinoCourant,  t_case matriceTerrain[HAUTEUR_TERRAIN][LARGEUR_TERRAIN]);

/**
 * @fn void initialiserBombe(t_bombe *bombe, float coorChoisieX, float coorChoisieY, int rayon);
 * @brief La fonction initialise toutes les valeurs d'une bombe.
 * @author Hannah Sergent
 * @date Crée le 11/02/2026
 * @param bombe un pointeur sur une structure de type bombe non initialisée
 * @param coorChoisieX coordonnée x de la bombe
 * @param coorChoisieX coordonnée y de la bombe
 * @param rayon le rayon de la bombe
 */

void initialiserBombe(t_bombe *bombe, float coorChoisieX, float coorChoisieY, int rayon);

/**
 * @fn void initialiserRayonBombe(t_bombe *bombe, int rayon);
 * @brief La fonction initialise uniquement le rayon de la bombe.
 * @author Hannah Sergent
 * @date Crée le 22/03/2026
 * @param bombe un pointeur sur une structure de type bombe non initialisée
 * @param rayon le rayon de la bombe
 */

void initialiserRayonBombe(t_bombe *bombe, int rayon);

/**
 * @fn void initialiserVitesse(t_vect *vectVitesse, float vitesseChoisieX, float vitesseChoisieY);
 * @brief La fonction initialise les vitesses horizontales et verticales.
 * @author Hannah Sergent
 * @date Crée le 11/02/2026
 * @param vectVitesse  un pointeur sur un vecteur vitesse
 * @param vitesseChoisieX la vitesse horizontale choisie
 * @param vitesseChoisieY la vitesse verticale choisie
 */

void initialiserVitesse(t_vect *vectVitesse, float vitesseChoisieX, float vitesseChoisieY);

 /**
 * @fn void miseAjourTemps(Uint32 *tempsPrecedent, float *tempsEcoule);
 * @brief La fonction met à jour le temps écoulé.
 * @author Hannah Sergent
 * @date Crée le 11/02/2026
 * @param tempsPrecedent un pointeur sur le temps précédent
 * @param tempsEcoule un pointeur sur le temps écoulé
 */

void miseAjourTemps(Uint32 *tempsPrecedent, float *tempsEcoule);

/**
 * @fn int collisionFrontiereBombe(t_bombe *bombe);
 * @brief La fonction vérifie si la bombe heurte une extrémité de la fenêtre.
 * @author Hannah Sergent
 * @date Crée le 6/02/2026
 * @param bombe un pointeur sur une structure de type bombe
 * @return 1 si la bombe a atteint la limite de la fenêtre et 0 sinon 
 */

int collisionFrontiereBombe(t_bombe *bombe);

/**
 * @fn int collisionTerrainBombe(t_case matriceTerrain[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], t_bombe *bombe, t_vect *vectVitesse);
 * @brief La fonction analyse si une bombe heurte le terrain. 
 * Si tel est le cas, elle calcule un vecteur normal au terrain et fait rebondir la bombe par rapport à ce vecteur.
 * @author Hannah Sergent
 * @date Crée le 17/02/2026
 * @param matriceTerrain matrice contenant les informations sur le terrain
 * @param bombe un pointeur sur une structure de type bombe 
 * @param vectVitesse un pointeur sur le vecteur vitesse de la bombe
 */

int collisionTerrainBombe(t_case matriceTerrain[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], t_bombe *bombe, t_vect *vectVitesse);

/**
 * @fn int collisionEauBombe(t_case matriceTerrain[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], t_bombe *bombe);
 * @brief La fonction vérifie si la bombe plonge dans la mer.
 * @author Hannah Sergent
 * @date Crée le 23/02/2026
 * @param matriceTerrain une matrice contenant les informations sur le terrain
 * @param bombe un pointeur sur une structure de type bombe 
 */

int collisionEauBombe(t_case matriceTerrain[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], t_bombe *bombe);

/** 
 * @fn void tracerBombe(SDL_Renderer *zoneAffichage, t_bombe *bombe);
 * @brief La fonction trace une bombe dans une zone d'affichage.
 * @author Hannah Sergent
 * @date Crée le 5/02/2026
 * @param zoneAffichage un pointeur sur la zone d'affichage
 * @param bombe un pointeur sur une structure de type bombe
 */

void tracerBombe(SDL_Renderer *zoneAffichage, t_bombe *bombe);

void tracerBombeHIP(SDL_Renderer *zoneAffichage, t_bombe *bombe);

#endif