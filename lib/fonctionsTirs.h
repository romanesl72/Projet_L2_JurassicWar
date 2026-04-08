#ifndef _TIRER_H_
#define _TIRER_H_

#include "../lib/fonctionsMenuHIP.h"
#include "types.h"

/** 
 * @file fonctionsTirs.h
 * @brief 
 * @author Romane Saint_Léger
 * @date Crée le 17/03/2026
 * @version 2.0
 */

/**
 * @fn void initialiserTirArcher(t_tir *tir, float departX, float departY, t_arme arme);
 * @brief 
 * @author Romane Saint-Léger
 * @date Crée le 17/03/2026
 * @param tir
 * @param departX
 * @param departY
 * @param arme
 * @version 1.0
 */

void initialiserTirArcher(t_tir *tir, float departX, float departY, t_arme arme);

/**
 * @fn int collisionFrontiere(t_tir *tir);
 * @brief 
 * @author Romane Saint-Léger
 * @date Crée le 17/03/2026
 * @param tir
 * @version 1.0
 */

int collisionFrontiere(t_tir *tir);

/**
 * @fn int collisionTerrain(int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], t_tir *tir);
 * @brief 
 * @author Romane Saint-Léger
 * @date Crée le 17/03/2026
 * @param matrice
 * @param tir
 * @version 1.0
 */

int collisionTerrain(int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], t_tir *tir);

/**
 * @fn int collisionEau(int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], t_tir *tir);
 * @brief 
 * @author Romane Saint-Léger
 * @date Crée le 17/03/2026
 * @param matrice
 * @param tir
 * @version 1.0
 */

int collisionEau(int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], t_tir *tir);

/**
 * @fn int collisionDino(int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], t_tir *tir);
 * @brief 
 * @author Romane Saint-Léger
 * @date Crée le 17/03/2026
 * @param matrice
 * @param tir
 * @version 1.0
 */

int collisionDino(int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], t_tir *tir);

/**
 * @fn int mettreAJourVol(t_tir *tir, int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], float gravite, int id_tireur);
 * @brief 
 * @author Romane Saint-Léger
 * @date Crée le 17/03/2026
 * @param tir
 * @param matrice
 * @param gravite
 * @param id_tireur
 * @version 1.3
 */

int mettreAJourVol(t_tir *tir, int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], float gravite, int id_tireur);

/**
 * @fn void tracerArme(SDL_Renderer *zoneAffichage, t_tir *tir);
 * @brief 
 * @author Romane Saint-Léger
 * @date Crée le 17/03/2026
 * @param zoneAffichage
 * @param tir
 * @version 1.3
 */

void tracerArme(SDL_Renderer *zoneAffichage, t_tir *tir);

/**
 * @fn void tracerTrajectoireTir(SDL_Renderer *zoneAffichage, t_tir *tir, float graviteBase);
 * @brief 
 * @author Romane Saint-Léger
 * @date Crée le 17/03/2026
 * @param zoneAffichage
 * @param graviteBase
 * @version 1.3
 */

void tracerTrajectoireTir(SDL_Renderer *zoneAffichage, t_tir *tir, float graviteBase);

/**
 * @fn void AncienviserArcher(SDL_Renderer* zoneAffichage, SDL_Texture *texMap, t_tir *tir, const Uint8 **etatClavier, float gravite, t_joueur *e1, t_joueur *e2);
 * @brief 
 * @author Romane Saint-Léger
 * @date Crée le 06/04/2026
 * @param zoneAffichage
 * @param texMap
 * @param tir
 * @param etatClavier
 * @param gravite
 * @param e1
 * @param e2
 * @version 1.0
 */

void AncienviserArcher(SDL_Renderer* zoneAffichage, SDL_Texture *texMap, t_tir *tir, const Uint8 **etatClavier, float gravite, t_joueur *e1, t_joueur *e2);

/**
 * @fn void viserArcher(SDL_Renderer* zoneAffichage, SDL_Texture *texMap, SDL_Texture **texObjets, TTF_Font *police, int armeSelectionnee, t_tir *tir, const Uint8 *etatClavier, float gravite, t_joueur *e1, t_joueur *e2, t_case numDinoCourant);
 * @brief 
 * @author Romane Saint-Léger
 * @date Crée le 17/03/2026
 * @param zoneAffichage
 * @param texMap
 * @param texObjets
 * @param police
 * @param armeSelectionnee
 * @param tir
 * @param etatClavier
 * @param e1
 * @param e2
 * @param numDinoCourant
 * @version 3.1
 */

void viserArcher(SDL_Renderer* zoneAffichage, SDL_Texture *texMap, SDL_Texture **texObjets, TTF_Font *police, int armeSelectionnee, t_tir *tir, const Uint8 *etatClavier, float gravite, t_joueur *e1, t_joueur *e2, t_case numDinoCourant);

/**
 * @fn appliquerDegats(int numDinoTouche, int degats, t_joueur *equipe1, t_joueur *equipe2, int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN]);
 * @brief 
 * @author Romane Saint-Léger
 * @date Crée le 01/04/2026
 * @param numDinoTouche
 * @param degats
 * @param equipe1
 * @param equipe2
 * @param matrice
 * @version 1.2
 */

void appliquerDegats(int numDinoTouche, int degats, t_joueur *equipe1, t_joueur *equipe2, int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN]);

#endif