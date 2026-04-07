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
 * @param rendu un pointeur sur la fenêtre du jeu
 * @param police un pointeur sur la police du jeu
 * @param texMap un pointeur l'image principal du jeu
 * @param texDino un tableau de pointeur sur les images représentant le dinosaure
 * @param texObjets un tableau de pointeur sur les images des différants objets
 * @param nomObjets un tableau de pointeur sur les noms des images des différants objets
 * @param equipe1 structure correspondant aux dinosaures du joueur 1
 * @param equipe2 structure correspondant aux dinosaures du joueur 2
 */
void afficher(SDL_Renderer *rendu, TTF_Font *police, SDL_Texture *texMap,
     SDL_Texture *texDinos[], SDL_Texture *texObjets[], char *nomsObjets[],
    t_joueur equipe1, t_joueur equipe2);


#endif