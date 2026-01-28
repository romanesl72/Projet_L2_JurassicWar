#ifndef _FONCTIONSVERIFICATION_H_
#define _FONCTIONSVERFICATION_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

int initialisationCorrecte();
void chargerImage(SDL_Renderer *zoneAffichage, SDL_Texture **img, char *nomFichier, int *imgLongueur, int *imgHauteur);
void creerFenetre(SDL_Window **fenetre, char* nomFenetre, int fenLargeur, int fenHauteur);
void initialiserPolice(TTF_Font **police, char *nomFichier, int taillePolice);

#endif