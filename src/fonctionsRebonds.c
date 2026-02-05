#include "../lib/fonctionsRebonds.h"

/* Fonction tracerBombe
 * Rôle : tracer un cercle dans une fenêtre représentant une bombe
 * Paramètres : un pointeur sur la zone d'affichage, les coordonnées où tracer la bombe et son rayon
 * Valeur de retour : aucune
*/

// Remarque : utiliser type coordonnées

void tracerBombe(SDL_Renderer *zoneAffichage, int coorX, int coorY, int rayon){
    int largeur;
    int hauteur;

    // Bombe de couleur blanche
    SDL_SetRenderDrawColor(zoneAffichage, 255, 255, 255, 255);

    for(largeur = -rayon; largeur <= rayon; largeur++){
        for(hauteur = -rayon; hauteur <= rayon; hauteur++){

            if (largeur*largeur + hauteur*hauteur <= rayon*rayon) {
                SDL_RenderDrawPoint(zoneAffichage, coorX + largeur, coorY + hauteur);
            }
        }
    }
}