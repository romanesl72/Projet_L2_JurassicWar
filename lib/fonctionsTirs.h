#ifndef _TIRER_H_
#define _TIRER_H_

#include "../lib/fonctionsMenuHIP.h"
#include "types.h"

void initialiserTirArcher(t_tir *tir, float departX, float departY, t_arme arme);
/*void miseAjourTemps(Uint32 *tempsPrecedent, float *tempsEcoule);*/

int collisionFrontiere(t_tir *tir);

int collisionTerrain(int matrice[MAT_H][MAT_L], t_tir *tir);
int collisionEau(int matrice[MAT_H][MAT_L], t_tir *tir);
int collisionDino(int matrice[MAT_H][MAT_L], t_tir *tir);
int mettreAJourVol(t_tir *tir, int matrice[MAT_H][MAT_L], float gravite, int id_tireur);
void tracerArme(SDL_Renderer *zoneAffichage, t_tir *tir);
void tracerTrajectoireTir(SDL_Renderer *zoneAffichage, t_tir *tir, float graviteBase);

void AncienviserArcher(SDL_Renderer* zoneAffichage, SDL_Texture *texMap, t_tir *tir, const Uint8 **etatClavier, float gravite, t_joueur *e1, t_joueur *e2);
void viserArcher(SDL_Renderer* zoneAffichage, SDL_Texture *texMap, SDL_Texture **texObjets, TTF_Font *police, int armeSelectionnee, t_tir *tir, const Uint8 *etatClavier, float gravite, t_joueur *e1, t_joueur *e2);
void appliquerDegats(int numDinoTouche, int degats, t_joueur *equipe1, t_joueur *equipe2, int matrice[MAT_H][MAT_L]);
#endif