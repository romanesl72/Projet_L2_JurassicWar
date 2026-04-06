#ifndef _FONCTIONSAFFICHAGE_H_
#define _FONCTIONSAFFICHAGE_H_

#include "types.h"

/** 
 * @file fonctionsAffichages.h
 * @brief Permet d'afficher la map'
 * @author Solène Orieux
 * @date 4/04/2006
 */

#define LARGEUR_FEN 1300
#define HAUTEUR_HIP 100
#define HAUTEUR_JEU 700
#define HAUTEUR_TOTALE (HAUTEUR_HIP + HAUTEUR_JEU)


/**
 * @fn void afficher(SDL_Renderer *rendu, TTF_Font *police, SDL_Texture *texMap,
     SDL_Texture *texDinos[], SDL_Texture *texObjets[], char *nomsObjets[],
    t_joueur equipe1, t_joueur equipe2);
 * @author Solène Orieux
 * @date 4/04/2006
 * @brief affiche la map
 * @param rendu
 * @param police
 * @param texMap
 * @param texDino
 * @param texObjets
 * @param nomObjets
 * @param equipe1
 * @param equipe2
 */
void afficher(SDL_Renderer *rendu, TTF_Font *police, SDL_Texture *texMap,
     SDL_Texture *texDinos[], SDL_Texture *texObjets[], char *nomsObjets[],
    t_joueur equipe1, t_joueur equipe2);


#endif