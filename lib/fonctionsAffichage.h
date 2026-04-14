#ifndef _FONCTIONSAFFICHAGE_H_
#define _FONCTIONSAFFICHAGE_H_

#include "types.h"

/** 
 * @file fonctionsAffichage.h
 * @brief Définitions des fonctions permettant d'afficher la map.
 * @author Solène Orieux
 * @date 4/04/2026
 * @version 1.0
 */

/**
 * @fn void afficher(SDL_Renderer *rendu, TTF_Font *police, SDL_Texture *texMap, SDL_Texture *texDinos[], SDL_Texture *texObjets[], char *nomsObjets[], t_joueur equipe1, t_joueur equipe2);
 * @brief La fonction affiche la map.
 * @author Solène Orieux
 * @date 4/04/2026
 * @version 1.0
 * @param rendu un pointeur sur la fenêtre du jeu
 * @param police un pointeur sur la police du jeu
 * @param texMap un pointeur l'image principal du jeu
 * @param texObjets un tableau de pointeur sur les images des différants objets
 * @param equipe1 pointeur de structure correspondant aux dinosaures du joueur 1
 * @param equipe2 pointeur de structure correspondant aux dinosaures du joueur 2
 */

void afficher(SDL_Renderer *rendu, TTF_Font *police, SDL_Texture *texMap, SDL_Texture *texObjets[], t_joueur *equipe1, t_joueur *equipe2);

#endif