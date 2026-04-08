#ifndef _FONCTIONSMENUHIP_H_
#define _FONCTIONSMENUHIP_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "types.h"


/** 
 * @file 
 * @brief Définitions des fonctions 
 * @author Romane Saint_Léger Hannah Sergent
 * @date Crée le 31/03/2026
 * @version 1.2
 */

/**
 * @fn void afficherInventaire(SDL_Renderer *rendu, SDL_Texture **texObjets, int nbObjets);
 * @brief Fonction qui affiche les 7 Objets en haut à gauche
 * @author Romane Saint-Léger
 * @date Crée le 31/03/2026
 * @version 1.0
 * @param rendu un pointeur sur le rendu de l'affichage
 * @param texObjets un pointeur sur la texture des objets
 * @param nbObjets nombre d'objets à afficher
 */


void afficherInventaire(SDL_Renderer *rendu, SDL_Texture **texObjets, int nbObjets);

/**
 * @fn void afficherBarrePV(SDL_Renderer *rendu, t_dino dino, int x, int y);
 * @brief Fonction qui affiche une barre de vie en fonction d'un dinosaure
 * @author Romane Saint-Léger
 * @date Crée le 31/03/2026
 * @version 1.0
 * @param rendu un pointeur sur le rendu de l'affichage
 * @param dino structure du dino afin d'accéder à ses points de vie
 * @param x coordonnée x de la barre de PV
 * @param y coordonnée y de la barre de PV
 */

void afficherBarrePV(SDL_Renderer *rendu, t_dino dino, int x, int y);

/**
 * @fn void afficherMenuPVDinos(SDL_Renderer *rendu, TTF_Font *police, t_joueur e1, t_joueur e2);
 * @brief Fonction qui affiche le menu des PV des dinosaures
 * @author Romane Saint-Léger
 * @date Crée le 31/03/2026
 * @version 1.0
 * @param rendu un pointeur sur le rendu de l'affichage
 * @param police pointeur sur la police d'écriture
 * @param e1 structure de l'équipe 1
 * @param e2 structure de l'équipe 2
 */

void afficherMenuPVDinos(SDL_Renderer *rendu, TTF_Font *police, t_joueur e1, t_joueur e2);

/**
 * @fn void afficherTexte(SDL_Renderer *rendu, TTF_Font *police, char *message, int x, int y, SDL_Color couleur);
 * @brief Fonction qui affiche du texte sur le menu du Haut (HIP)
 * @author Romane Saint-Léger
 * @date Crée le 31/03/2026
 * @version 1.0
 * @param rendu un pointeur sur le rendu de l'affichage
 * @param police pointeur sur la police d'écriture
 * @param message le message que l'on souhaite afficher
 * @param x coordonnée x du début du message
 * @param y coordonnée y du début du message
 * @param couleur la couleur du message
 */

void afficherTexte(SDL_Renderer *rendu, TTF_Font *police, char *message, int x, int y, SDL_Color couleur);


/**
 * @struct t_texte_cache
 * @brief 
 * @author Hannah Sergent
 * @date Crée le 06/04/2026
 * @version 1.0
 * @param 
 * @param 
 */

typedef struct {
    SDL_Texture *tex;
    int largeurTex; 
    int hauteurTex;
} t_texte_cache;

/**
 * @fn void chargerTexteDinos(SDL_Renderer *rendu, TTF_Font *police, t_texte_cache *cache);
 * @brief 
 * @author Hannah Sergent
 * @date Crée le 06/04/2026
 * @version 1.0
 * @param rendu
 * @param police 
 * @param cache 
 */


void chargerTexteDinos(SDL_Renderer *rendu, TTF_Font *police, t_texte_cache *cache);

/**
 * @fn void afficherMenuPVDinosOp(SDL_Renderer *rendu, TTF_Font *police, t_joueur e1, t_joueur e2, t_texte_cache *cache);
 * @brief 
 * @author Hannah Sergent
 * @date Crée le 06/04/2026
 * @version 1.0
 * @param rendu
 * @param police
 * @param e1
 * @param e2
 * @param cache
 */
 
void afficherMenuPVDinosOp(SDL_Renderer *rendu, TTF_Font *police, t_joueur e1, t_joueur e2, t_texte_cache *cache);



#endif