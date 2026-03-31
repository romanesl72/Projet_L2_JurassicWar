#ifndef _FONCTIONSMENUHIP_H_
#define _FONCTIONSMENUHIP_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "types.h"





void afficherInventaire(SDL_Renderer *rendu, SDL_Texture **texObjets, int nbObjets);
void afficherBarrePV(SDL_Renderer *rendu, t_dino dino, int x, int y);
void afficherMenuPVDinos(SDL_Renderer *rendu, TTF_Font *police, t_joueur e1, t_joueur e2);
void afficherTexte(SDL_Renderer *rendu, TTF_Font *police, char *message, int x, int y, SDL_Color couleur);



#endif