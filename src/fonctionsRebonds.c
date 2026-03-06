#include "../lib/fonctionsRebonds.h"
#include <stdio.h>
#include <math.h>

/** 
 * @file fonctionsRebonds.c
 * @brief Corps des fonctions pour le lancer, la trajectoire et l'affichage d'une bombe
 * @author Hannah Sergent
 * @date Crée le 5/02/2026
 */

#define PI 3.1415

void initialiserBombe(t_bombe *bombe, float coorChoisieX, float coorChoisieY, int rayon) {
    bombe->coor.x = coorChoisieX;
    bombe->coor.y = coorChoisieY;
    bombe->rayon = rayon;
}

void initialiserVitesse(t_vect *vectVitesse, float vitesseChoisieX, float vitesseChoisieY){
    vectVitesse->u = vitesseChoisieX;
    vectVitesse->v = vitesseChoisieY;
}

void miseAjourTemps(Uint32 *tempsPrecedent, float *tempsEcoule){
    Uint32 tempsCourant = SDL_GetTicks();
    *tempsEcoule = (tempsCourant - *tempsPrecedent)/1000.0f;
    *tempsPrecedent = tempsCourant;
}

int collisionFrontiereBombe(int largeurFenetre, int hauteurFenetre, t_bombe *bombe){
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

int dansLimites(int x, int y){
    return ((x >= 0) && (x < LARGEUR_TERRAIN) && (y < HAUTEUR_TERRAIN) && (y >= 0));
}

int estTerrain(t_case pixel){
    return (pixel == TERRE);
}

/*
void calculerNormale(t_case matriceTerrain[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], t_bombe *bombe, t_vect *normal) {
    t_vect gradient = {0, 0};
    float longueur;
    t_coordonnee posBombe;
    posBombe.x = (int)round(bombe->coor.x);
    posBombe.y = (int)round(bombe->coor.y);

    // condition sortie terrain à faire
    if (!dansLimites(posBombe.x, posBombe.y)){
        normal->u = 0;
        normal->v = -1;
        return;
    }

    if (dansLimites(posBombe.x + 1, posBombe.y) && dansLimites(posBombe.x - 1, posBombe.y)){
        gradient.u = estTerrain(matriceTerrain[posBombe.y][posBombe.x + 1]) - estTerrain(matriceTerrain[posBombe.y][posBombe.x - 1]);
    }
    if (dansLimites(posBombe.x, posBombe.y + 1) && dansLimites(posBombe.x, posBombe.y - 1)){
        gradient.v = estTerrain(matriceTerrain[posBombe.y + 1][posBombe.x]) - estTerrain(matriceTerrain[posBombe.y - 1][posBombe.x]);
    }

    longueur = sqrt(gradient.u * gradient.u + gradient.v * gradient.v);

    if (longueur > 0.001){
        normal->u = -gradient.u/longueur;
        normal->v = -gradient.v/longueur;
    }
    else {
        normal->u = 0;
        normal->v = -1;
    }

} */

/*
int collisionTerrainBombe(t_case matriceTerrain[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], t_bombe *bombe, t_vect *vectVitesse) {
    t_vect normal;
    calculerNormale(matriceTerrain, bombe, vectVitesse, &normal);
    float produitScalaire = vectVitesse->u*normal.u + vectVitesse->v*normal.v;

    normal.u *= 2*produitScalaire;
    normal.v *= 2*produitScalaire;

    if (matriceTerrain[bombe->coor.y][bombe->coor.x + bombe->rayon] == TERRE){
        bombe->coor.x -= bombe->rayon;
         vectVitesse->u = -COEF_RESTITUTION*vectVitesse->u; 
        vectVitesse->u = vectVitesse->u - normal.u;
        vectVitesse->v = vectVitesse->v - normal.v;
        return 1;
    }
    else if (matriceTerrain[bombe->coor.y][bombe->coor.x - bombe->rayon] == TERRE){
        bombe->coor.x += bombe->rayon;
         vectVitesse->u = -COEF_RESTITUTION*vectVitesse->u; 
        vectVitesse->u = vectVitesse->u - normal.u;
        vectVitesse->v = vectVitesse->v - normal.v;
        return 1;
    }
    else if (matriceTerrain[bombe->coor.y + bombe->rayon][bombe->coor.x] == TERRE) {
        bombe->coor.y -= bombe->rayon;
         vectVitesse->v = -COEF_RESTITUTION*vectVitesse->v; 
        vectVitesse->u = vectVitesse->u - normal.u;
        vectVitesse->v = vectVitesse->v - normal.v;
        return 1;
    }
    else if (matriceTerrain[bombe->coor.y - bombe->rayon][bombe->coor.x] == TERRE) {
        bombe->coor.y += bombe->rayon;
         vectVitesse->v = -COEF_RESTITUTION*vectVitesse->v; 
        vectVitesse->u = vectVitesse->u - normal.u;
        vectVitesse->v = vectVitesse->v - normal.v;
        return 1;
    }
    return 0;
} */

/*
int collisionTerrainBombe(t_case matriceTerrain[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], t_bombe *bombe, t_vect *vectVitesse) {
    int voisinsX[8] = {1, -1, 0, 0, 1, 1, -1, -1};
    int voisinsY[8] = {0, 0, 1, -1, 1, -1, 1, -1};
    int coorVoisineX;
    int coorVoisineY;
    int i;
    t_vect normal;

    for (i = 0; i < 8; i++){
        coorVoisineX = (int)round(bombe->coor.x) + voisinsX[i]* bombe->rayon;
        coorVoisineY = (int)round(bombe->coor.y) + voisinsY[i]* bombe->rayon;

        if (matriceTerrain[coorVoisineY][coorVoisineX] == TERRE){
            bombe->coor.x -= voisinsX[i] * 0.5;
            bombe->coor.y -= voisinsY[i] * 0.5;

            calculerNormale(matriceTerrain, bombe, &normal);
            float produitScalaire = vectVitesse->u*normal.u + vectVitesse->v*normal.v;

            vectVitesse->u -= 2*produitScalaire*normal.u;
            vectVitesse->v -= 2*produitScalaire*normal.v;

            return 1;
        }
    }
    return 0;
} */

/* Noyau de Sobel*/
void calculerNormale(t_case matriceTerrain[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], t_coordonnee_calcul *extremiteBombe, t_vect *normal) {

    t_vect gradient = {0, 0};
    float longueur;
    t_coordonnee posBombe;
    posBombe.x = (int)roundf(extremiteBombe->x);
    posBombe.y = (int)roundf(extremiteBombe->y);
    int i;
    int j;
    int val;
    int poidsX;
    int poidsY;

    for (i = -1; i <=1; i++){
        for (j = -1; j <= 1; j++){
            if (dansLimites(posBombe.x + j, posBombe.y + i)){
                val = estTerrain(matriceTerrain[posBombe.y + j][posBombe.x + i]);
            }
            poidsX = (i == 0) ? 2 * j : i;
            poidsY = (j == 0) ? 2 * i : j;

            gradient.u += poidsX * val;
            gradient.v += poidsY * val;
        }
    }

    longueur = sqrt(gradient.u * gradient.u + gradient.v * gradient.v);

    if (longueur > 0.001){
        normal->u = -gradient.u/longueur;
        normal->v = -gradient.v/longueur;
    }
    else {
        normal->u = 0;
        normal->v = -1;
    }

}

int collisionTerrainBombe(t_case matriceTerrain[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], t_bombe *bombe, t_vect *vectVitesse) {

    int nombrePoints = 16;
    int i;
    float angle;
    float produitScalaire;
    t_coordonnee_calcul extremiteBombe;
    t_coordonnee extremiteBombeMat;
    t_vect normal;

    for(i = 0; i < nombrePoints; i++){

        /* Representation de la bombe comme un cercle trigonométrique */

        angle = i * (PI * 2 / nombrePoints);
        extremiteBombe.x = bombe->coor.x + cos(angle)*bombe->rayon;
        extremiteBombe.y = bombe->coor.y + sin(angle)*bombe->rayon;

        extremiteBombeMat.x = roundf(extremiteBombe.x);
        extremiteBombeMat.y = roundf(extremiteBombe.y);

        if (matriceTerrain[extremiteBombeMat.y][extremiteBombeMat.x] == TERRE){

            calculerNormale(matriceTerrain, &extremiteBombe, &normal);
            bombe->coor.x += normal.u*15;
            bombe->coor.y += normal.v*15;

            produitScalaire = vectVitesse->u*normal.u + vectVitesse->v*normal.v;

            if (produitScalaire < 0){

                vectVitesse->u -= 2*produitScalaire*normal.u;
                vectVitesse->v -= 2*produitScalaire*normal.v;
            }
            return 1;
        }

    }
    return 0;
}

int collisionEauBombe(t_case matriceTerrain[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], t_bombe *bombe) {

    t_coordonnee posBombe;

    posBombe.x = roundf(bombe->coor.x);
    posBombe.y = roundf(bombe->coor.y);

    return ((matriceTerrain[posBombe.y][posBombe.x + bombe->rayon] == EAU) || (matriceTerrain[posBombe.y][posBombe.x - bombe->rayon] == EAU) || (matriceTerrain[posBombe.y + bombe->rayon][posBombe.x] == EAU) || (matriceTerrain[posBombe.y - bombe->rayon][posBombe.x] == EAU));
}

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
                SDL_RenderDrawPoint(zoneAffichage, ceil(bombe->coor.x) + largeur, ceil(bombe->coor.y) + hauteur);
            }
        }
    }
}

void tracerTrajectoireLancer(SDL_Renderer *zoneAffichage, t_coordonnee_calcul *coor, t_vect *vectVitesse, float gravite){

    float temps = 0;
    float dt = 1.0f/60.0f;
    t_vect precedent;
    t_vect courant;
    float vitY = vectVitesse->v;

    precedent.u = courant.u = coor->x;
    precedent.v = courant.v = coor->y;

    // Trajectoire de couleur rouge
    SDL_SetRenderDrawColor(zoneAffichage, 255, 0, 0, 255);

    while(temps < 2.0){

        courant.u += dt*vectVitesse->u;
        courant.v += dt*vitY;
        vitY += gravite*dt;
        SDL_RenderDrawLine(zoneAffichage, roundf(precedent.u), roundf(precedent.v), roundf(courant.u), roundf(courant.v));

        precedent = courant;
        temps += dt;
    }
}

void choixHauteurLancer(SDL_Renderer* zoneAffichage, SDL_Texture *texMap, SDL_Rect *rect, const Uint8 **etatClavier, t_bombe *bombe, t_vect *vectVitesse, float gravite){
    
    do {

        SDL_PumpEvents();
        *etatClavier = SDL_GetKeyboardState(NULL);

        if ((*etatClavier)[SDL_SCANCODE_UP]){
            vectVitesse->v -= 0.8;
        }
        if ((*etatClavier)[SDL_SCANCODE_DOWN]){
            vectVitesse->v += 0.8;
        }

        /* Pour tracer la courbe de trajectoire vers la gauche, il faut une vitesse horizontale négative */
        if ((*etatClavier)[SDL_SCANCODE_LEFT]){
            vectVitesse->u = -fabs(vectVitesse->u);
        }

        /* Pour tracer la courbe de trajectoire vers la droite, il faut une vitesse horizontale positive */
        if ((*etatClavier)[SDL_SCANCODE_RIGHT]){
            vectVitesse->u = fabs(vectVitesse->u);
        }

        SDL_RenderClear(zoneAffichage);
        SDL_RenderCopy(zoneAffichage, texMap, NULL, rect);

        tracerBombe(zoneAffichage, bombe);
        tracerTrajectoireLancer(zoneAffichage, &(bombe->coor), vectVitesse, gravite);

        SDL_RenderPresent(zoneAffichage);

        SDL_Delay(16);

    } while(!(*etatClavier)[SDL_SCANCODE_SPACE]);
}