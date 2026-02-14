#include "../lib/fonctionsRebonds.h"
#include <stdio.h>

/** 
 * @file fonctionsRebonds.c
 * @brief Corps des fonctions pour le lancer, la trajectoire et l'affichage d'une bombe
 * @author Hannah Sergent
 * @date Crée le 5/02/2026
 */

void initialiserBombe(t_bombe *bombe, int coorChoisieX, int coorChoisieY, int rayon) {
    bombe->coor.x = coorChoisieX;
    bombe->coor.y = coorChoisieY;
    bombe->rayon = rayon;
}

void initialiserVitesse(float *vitesseX, float *vitesseY, float vitesseChoisieX, float vitesseChoisieY){
    *vitesseX = vitesseChoisieX;
    *vitesseY = vitesseChoisieY;
}

void miseAjourTemps(Uint32 *tempsPrecedent, float *tempsEcoule){
    Uint32 tempsCourant = SDL_GetTicks();
    *tempsEcoule = (tempsCourant - *tempsPrecedent)/1000.0f;
    *tempsPrecedent = tempsCourant;
}

int rebondFrontiereBombe(int largeurFenetre, int hauteurFenetre, t_bombe *bombe){
    return ((bombe->coor.x + bombe->rayon > largeurFenetre) || (bombe->coor.x - bombe->rayon < 0) || (bombe->coor.y + bombe->rayon > hauteurFenetre) || (bombe->coor.y - bombe->rayon < 0));
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

/* Fonction tracerBombe
 * Rôle : tracer un cercle dans une fenêtre représentant une bombe
 * Paramètres : un pointeur sur la zone d'affichage, les coordonnées où tracer la bombe et son rayon
 * Valeur de retour : aucune
*/

void tracerBombe(SDL_Renderer *zoneAffichage, t_bombe *bombe){
    int largeur;
    int hauteur;

    // Bombe de couleur blanche
    SDL_SetRenderDrawColor(zoneAffichage, 255, 255, 255, 255);

    for(largeur = -bombe->rayon; largeur <= bombe->rayon; largeur++){
        for(hauteur = -bombe->rayon; hauteur <= bombe->rayon; hauteur++){

            if (largeur*largeur + hauteur*hauteur <= bombe->rayon*bombe->rayon) {
                SDL_RenderDrawPoint(zoneAffichage, bombe->coor.x + largeur, bombe->coor.y + hauteur);
            }
        }
    }
}

/* La fonction trace un trait rouge indiquant la direction de la bombe */
/*
void tracerDirectionLancer(SDL_Renderer *zoneAffichage, t_coordonnee *coor, float vitesseX, float vitesseY){
    int x2 = coor->x + vitesseX * 5;
    int y2 = coor->y + vitesseY * 5;

    SDL_SetRenderDrawColor(zoneAffichage, 255, 0, 0, 255);
    SDL_RenderDrawLine(zoneAffichage, coor->x, coor->y, x2, y2);
} */

void tracerTrajectoireLancer(SDL_Renderer *zoneAffichage, t_coordonnee *coor, float vitesseX, float vitesseY, float gravite){
    float temps = 0;
    float dt = 0.02;
    int precedentX = coor->x;
    int precedentY = coor->y;
    float courantX;
    float courantY;

    SDL_SetRenderDrawColor(zoneAffichage, 255, 0, 0, 255);

    while(temps < 2.0){

        courantX = coor->x + vitesseX * temps;
        courantY = coor->y + vitesseY * temps + 0.5 * gravite * temps*temps;
        SDL_RenderDrawLine(zoneAffichage, precedentX, precedentY, courantX, courantY);

        precedentX = courantX;
        precedentY = courantY;
        temps += dt;
    }
}

void choixHauteurLancer(SDL_Renderer* zoneAffichage, const Uint8 **etatClavier, t_bombe *bombe, float *vitesseX, float *vitesseY, float gravite){
    
    SDL_PumpEvents();
    *etatClavier = SDL_GetKeyboardState(NULL);

    while (!(*etatClavier)[SDL_SCANCODE_SPACE]){

        SDL_PumpEvents();
        *etatClavier = SDL_GetKeyboardState(NULL);

        if ((*etatClavier)[SDL_SCANCODE_UP]){
            *vitesseY -= 0.3;
        }
        if ((*etatClavier)[SDL_SCANCODE_DOWN]){
            *vitesseY += 0.3;
        }

        SDL_SetRenderDrawColor(zoneAffichage, 0, 0, 0, 255);
        SDL_RenderClear(zoneAffichage);

        tracerBombe(zoneAffichage, bombe);
        tracerTrajectoireLancer(zoneAffichage, &(bombe->coor), *vitesseX, *vitesseY, gravite);

        SDL_RenderPresent(zoneAffichage);

        SDL_Delay(50);

    }
}
