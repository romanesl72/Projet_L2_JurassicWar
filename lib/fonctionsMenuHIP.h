#ifndef _FONCTIONSMENUHIP_H_
#define _FONCTIONSMENUHIP_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "types.h"


/** 
 * @file 
 * @brief 
 * @author Romane Saint_Léger Hannah Sergent
 * @date Crée le 31/03/2026
 * @version 1.2
 */

/**
 * @fn void afficherInventaire(SDL_Renderer *rendu, SDL_Texture **texObjets, int nbObjets);
 * @brief 
 * @author Romane Saint-Léger
 * @date Crée le 31/03/2026
 * @param rendu 
 * @param texObjets
 * @param nbObjets
 * @version 1.0
 */


void afficherInventaire(SDL_Renderer *rendu, SDL_Texture **texObjets, int nbObjets);

/**
 * @fn void afficherBarrePV(SDL_Renderer *rendu, t_dino dino, int x, int y);
 * @brief 
 * @author Romane Saint-Léger
 * @date Crée le 31/03/2026
 * @param rendu
 * @param dino
 * @param x
 * @param y
 * @version 1.0
 */

void afficherBarrePV(SDL_Renderer *rendu, t_dino dino, int x, int y);

/**
 * @fn void afficherMenuPVDinos(SDL_Renderer *rendu, TTF_Font *police, t_joueur e1, t_joueur e2);
 * @brief 
 * @author Romane Saint-Léger
 * @date Crée le 31/03/2026
 * @param rendu
 * @param police
 * @param e1
 * @param e2
 * @version 1.0
 */

void afficherMenuPVDinos(SDL_Renderer *rendu, TTF_Font *police, t_joueur e1, t_joueur e2);

/**
 * @fn void afficherTexte(SDL_Renderer *rendu, TTF_Font *police, char *message, int x, int y, SDL_Color couleur);
 * @brief 
 * @author Romane Saint-Léger
 * @date Crée le 31/03/2026
 * @param rendu
 * @param poilce
 * @param message
 * @param x
 * @param y
 * @param couleur
 * @version 1.0
 */

void afficherTexte(SDL_Renderer *rendu, TTF_Font *police, char *message, int x, int y, SDL_Color couleur);


/**
 * @struct t_texte_cache
 * @brief 
 * @author Hannah Sergent
 * @date Crée le 06/04/2026
 * @param 
 * @param 
 * @version 1.0
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
 * @param rendu
 * @param police 
 * @param cache 
 * @version 1.0
 */


void chargerTexteDinos(SDL_Renderer *rendu, TTF_Font *police, t_texte_cache *cache);

/**
 * @fn void afficherMenuPVDinosOp(SDL_Renderer *rendu, TTF_Font *police, t_joueur e1, t_joueur e2, t_texte_cache *cache);
 * @brief 
 * @author Hannah Sergent
 * @date Crée le 06/04/2026
 * @param rendu
 * @param police
 * @param e1
 * @param e2
 * @param cache
 * @version 1.0
 */
 
void afficherMenuPVDinosOp(SDL_Renderer *rendu, TTF_Font *police, t_joueur e1, t_joueur e2, t_texte_cache *cache);



#endif