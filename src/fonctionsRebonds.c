#include "../lib/fonctionsRebonds.h"

/* Fonction tracerBombe
 * Rôle : tracer un cercle dans une fenêtre représentant une bombe
 * Paramètres : un pointeur sur la zone d'affichage, les coordonnées où tracer la bombe et son rayon
 * Valeur de retour : aucune
*/

void tracerBombe(SDL_Renderer *zoneAffichage, t_coordonnee * coor, int rayon){
    int largeur;
    int hauteur;

    // Bombe de couleur blanche
    SDL_SetRenderDrawColor(zoneAffichage, 255, 255, 255, 255);

    for(largeur = -rayon; largeur <= rayon; largeur++){
        for(hauteur = -rayon; hauteur <= rayon; hauteur++){

            if (largeur*largeur + hauteur*hauteur <= rayon*rayon) {
                SDL_RenderDrawPoint(zoneAffichage, coor->x + largeur, coor->y + hauteur);
            }
        }
    }
}

int rebondFrontiereBombe(int largeurFenetre, int hauteurFenetre, t_coordonnee *coor, int rayon){
    return ((coor->x + rayon > largeurFenetre) || (coor->x - rayon < 0) || (coor->y + rayon > hauteurFenetre) || (coor->y - rayon < 0));
}

/*
void rebondirFrontiere(int largeurFenetre, int hauteurFenetre, t_coordonnee *coor, int rayon, float *vitesseX, float *vitesseY){
    if (coor->x + rayon > largeurFenetre) {
        coor->x = largeurFenetre - rayon;
        *vitesseX = -*vitesseX;
    }
    if (coor->x - rayon < 0) {
        coor->x = rayon;
        *vitesseX = -*vitesseX;
    }
    if (coor->y + rayon > hauteurFenetre) {
        coor->y = hauteurFenetre - rayon;
        *vitesseY = -*vitesseY;
    }
    if (coor->y - rayon < 0) {
        coor->y = rayon;
        *vitesseY = -*vitesseY;
    }

}
*/