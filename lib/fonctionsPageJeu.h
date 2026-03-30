#ifndef _FONCTIONSPAGEJEU_H_
#define _FONCTIONSPAGEJEU_H_

#include "../lib/types.h"

/** 
 * @file fonctionsPageJeu.h
 * @brief Définitions des fonctions liées à la page du jeu.
 * @author Hannah Sergent
 * @date Crée le 29/03/2026
 */

int creerPageJeu(SDL_Window **fenJeu, SDL_Renderer **zoneAffichage, SDL_Texture **texMap);

void initialiserEquipes(t_joueur *equipe1, t_joueur *equipe2, t_catalogue_zones *catalogue, t_case matriceTerrain[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], SDL_Renderer *zoneAffichage);

void detecterEvenementMenuPrincipal(
    int *enCours, 
    int *bombeLancee, 
    int *nombreRebonds, 
    SDL_Renderer *zoneAffichage, 
    SDL_Texture *texMap, 
    SDL_Rect *rectFen, 
    t_bombe *bombe, 
    t_vect *vectVitesse,
    t_joueur *equipe1, 
    t_joueur *equipe2, 
    t_case dinoCourant, 
    t_case matriceTerrain[HAUTEUR_TERRAIN][LARGEUR_TERRAIN] );

void afficherJeuSansBombe(t_joueur *equipe1, t_joueur *equipe2, SDL_Rect *rectFen, SDL_Renderer *zoneAffichage, SDL_Texture *texMap);
void afficherJeuAvecBombe(t_joueur *equipe1, t_joueur *equipe2, t_bombe * bombe, SDL_Rect *rectFen, SDL_Renderer *zoneAffichage, SDL_Texture *texMap);

void destruireElementsJeu(t_joueur *equipe1, t_joueur *equipe2, t_case matriceTerrain[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], SDL_Texture *texMap, SDL_Renderer *zoneAffichage, SDL_Window *fenJeu);

void lancerBombe(Uint32 *tempsPrecedent, int * bombeLancee, int *nombreRebonds, t_bombe * bombe, t_vect *vectVitesse, 
    t_case matriceTerrain[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], t_joueur *equipe1, t_joueur *equipe2, t_tour *gestionTours,
    SDL_Rect *rectFen, SDL_Renderer * zoneAffichage, SDL_Texture *texMap
    );

#endif