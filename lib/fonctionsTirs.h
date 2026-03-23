#ifndef _TIRER_H_
#define _TIRER_H_

#include <SDL2/SDL.h>
#include "types.h"

void initialiserTirArcher(t_tir *tir, float departX, float departY, t_arme arme);
void miseAjourTemps(Uint32 *tempsPrecedent, float *tempsEcoule);

int collisionFrontiere(t_tir *tir);

int collisionTerrain(int matrice[MAT_H][MAT_L], t_tir *tir);
int collisionEau(int matrice[MAT_H][MAT_L], t_tir *tir);
int collisionDino(int matrice[MAT_H][MAT_L], t_tir *tir);
int mettreAJourVol(t_tir *tir, int matrice[MAT_H][MAT_L], float gravite, int id_tireur);
void tracerFleche(SDL_Renderer *zoneAffichage, t_tir *tir);
void tracerTrajectoireArcher(SDL_Renderer *zoneAffichage, t_tir *tir, float graviteBase);


void viserArcher(SDL_Renderer* rendu, SDL_Texture *texMap, t_tir *tir, const Uint8 **etatClavier, float gravite, t_joueur *e1, t_joueur *e2);
#endif