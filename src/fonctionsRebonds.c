#include "../lib/fonctionsRebonds.h"
#include <stdio.h>
#include <math.h>

/** 
 * @file fonctionsRebonds.c
 * @brief Corps des fonctions pour le lancer, la trajectoire et l'affichage d'une bombe
 * @author Hannah Sergent
 * @date Crée le 5/02/2026
 */

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
/* v' = v - 2<v,n>n*/

/*
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
                val = estTerrain(matriceTerrain[posBombe.y + i][posBombe.x + j]);
            }
            poidsX = (i == 0) ? 2 * j : i;
            poidsY = (j == 0) ? 2 * i : j;

            gradient.u += poidsX * val;
            gradient.v += poidsY * val;
        }
    }

     norme 2 du gradient
    longueur = sqrt(gradient.u * gradient.u + gradient.v * gradient.v);

    Pour éviter une division par 0 ou une valeur trop faible 
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

    int nombrePoints = 32;
    int i;
    float angle;
    float produitScalaire;
    float penetration;
    t_coordonnee_calcul extremiteBombe;
    t_coordonnee extremiteBombeMat;
    t_vect normal;
    t_vect normaleMoyenne = {0, 0};
    t_vect profondeurEnfoncement;
    int collision = 1;
    int nbIter;
    int collisionDetectee = 0;
    int nbNormales = 0;

    for (nbIter = 0; (nbIter < 20) && (collision); nbIter++){

        collision = 0;

        for(i = 0; i < nombrePoints; i++){

             Representation de la bombe comme un cercle trigonométrique 

            angle = i * (PI * 2 / nombrePoints);
            extremiteBombe.x = bombe->coor.x + cos(angle)*bombe->rayon;
            extremiteBombe.y = bombe->coor.y + sin(angle)*bombe->rayon;

            extremiteBombeMat.x = roundf(extremiteBombe.x);
            extremiteBombeMat.y = roundf(extremiteBombe.y);

            if (matriceTerrain[extremiteBombeMat.y][extremiteBombeMat.x] == TERRE){

                collision = 1;
                collisionDetectee = 1;
                calculerNormale(matriceTerrain, &extremiteBombe, &normal);

                normaleMoyenne.u += normal.u;
                normaleMoyenne.v += normal.v;
                nbNormales ++;

                profondeurEnfoncement.u = extremiteBombe.x - bombe->coor.x;
                profondeurEnfoncement.v = extremiteBombe.y - bombe->coor.y;
                penetration = bombe->rayon - sqrt(profondeurEnfoncement.u*profondeurEnfoncement.u + profondeurEnfoncement.v*profondeurEnfoncement.v);

                if (penetration < 0){
                    penetration = 0;
                }

                la
                bombe->coor.x += normal.u*15;
                bombe->coor.y += normal.v*15; 

                bombe->coor.x += normal.u*penetration;
                bombe->coor.y += normal.v*penetration;

            }

        }
    }

    if (collisionDetectee){

        if (nbNormales > 0){

            float longueur = sqrt(normaleMoyenne.u * normaleMoyenne.u + normaleMoyenne.v * normaleMoyenne.v);

             Pour éviter une division par 0 ou une valeur trop faible 
            if (longueur > 0.001){
                normaleMoyenne.u /= longueur;
                normaleMoyenne.v /= longueur;
            }
            else {
                normaleMoyenne.u = 0;
                normaleMoyenne.v = -1;
            }

        }

        produitScalaire = vectVitesse->u*normaleMoyenne.u + vectVitesse->v*normaleMoyenne.v;

        if (produitScalaire < 0){

            vectVitesse->u -= 2*produitScalaire*normaleMoyenne.u;
            vectVitesse->v -= 2*produitScalaire*normaleMoyenne.v;
        }

        if (collision){
            printf("ici \n");
        }
        return 1;
    }
    return 0;
} */

void calculerNormale(t_case matriceTerrain[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], t_coordonnee_calcul *extremiteBombe, t_vect *normal) {

    t_vect gradient = {0.0f, 0.0f};
    t_coordonnee extremite;
    t_coordonnee voisin;

    int i;
    int j;
    float normeGradient;
    float distExtremiteVoisin;
    float poids;

    extremite.x = (int)roundf(extremiteBombe->x);
    extremite.y = (int)roundf(extremiteBombe->y);

    /* Choisir un rayon de 3 à 4 pour les terrains accidentés, une valeur plus faible suffit sinon*/
    int rayon = 4; 

    /* Exploration de toutes les cases dans un carré centré autour de l'extremité de la bombe */
    for (i = -rayon; i <= rayon; i++) {

        for (j = -rayon; j <= rayon; j++) {

            voisin.x = extremite.x + j;
            voisin.y = extremite.y + i;

            if (dansLimites(voisin.x, voisin.y)) {
                if (matriceTerrain[voisin.y][voisin.x] == TERRE) {

                    /* Calcul de la norme au carré */
                    distExtremiteVoisin = (float)(i*i + j*j);

                    /* Plus la case est loin du centre, plus le poids est faible
                    C'est un poids quadritique inverse qui donne plus d'importance aux cases proches et évite des angles abruptes dans la normale */
                    poids = 1.0f / (1.0f + distExtremiteVoisin); 
                    
                    /* Construction d'un vecteur gradient qui pointe vers la zone où il y a le plus de terre autour du point */

                    gradient.u += (float)j * poids;
                    gradient.v += (float)i * poids;
                }
            }
        }
    }

    /* On calcule la norme 2 du gradient */
    normeGradient = sqrtf(gradient.u * gradient.u + gradient.v * gradient.v);

    /* Si le gradient est trop faible, on est soit en plein vide, 
    soit totalement enterré. On utilise la direction verticale par défaut. */
    if (normeGradient > 0.1f) {

        /* La normale est l'opposé du gradient, puisque le gradient pointe la terre */

        normal->u = -gradient.u / normeGradient;
        normal->v = -gradient.v / normeGradient;
    } 

    /* On pointe vers le haut sinon */

    else {
        normal->u = 0.0f;
        normal->v = -1.0f;
    }
}

int collisionTerrainBombe(t_case matriceTerrain[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], t_bombe *bombe, t_vect *vectVitesse) {

    /* nombre de points échantillonnés sur le contour de la bombe*/
    int nombrePoints = 32;
    /* nombre de points du contour de la bombe qui sont dans la terre */
    int nbPointsEnCollision = 1;

    int i; 
    int nbIter;
    int collisionDetectee = 0;
    float produitScalaire;
    float angle;

    t_coordonnee_calcul extremiteBombe;
    t_coordonnee extremite;

    /* Moyenne des normales calculées*/
    t_vect normalCumul;
    t_vect normaleLocale;
    float normeNormalCumul;
    
    /* Itérations pour "extraire" la bombe du terrain */

    for (nbIter = 0; (nbIter < 10) && (nbPointsEnCollision); nbIter++) {

        normalCumul.u = 0;
        normalCumul.v = 0;
        nbPointsEnCollision = 0;

        for (i = 0; i < nombrePoints; i++) {

            /* Voir le contour de la bombe comme un cercle trigonométrique */
            angle = i * (PI * 2 / nombrePoints);

            /* Utilisation des formules polaires */
            extremiteBombe.x = bombe->coor.x + cos(angle) * bombe->rayon;
            extremiteBombe.y = bombe->coor.y + sin(angle) * bombe->rayon;

            extremite.x = (int)roundf(extremiteBombe.x);
            extremite.y = (int)roundf(extremiteBombe.y);

            // Vérification des limites pour éviter un crash
            if (dansLimites(extremite.x, extremite.y)) {
                if (matriceTerrain[extremite.y][extremite.x] == TERRE) {

                    collisionDetectee = 1;

                    calculerNormale(matriceTerrain, &extremiteBombe, &normaleLocale);
                    
                    normalCumul.u += normaleLocale.u;
                    normalCumul.v += normaleLocale.v;
                    nbPointsEnCollision++;

                    // Correction immédiate de la position (anti-enfoncement)
                    // On pousse très légèrement la bombe vers l'extérieur
                    bombe->coor.x += normaleLocale.u * 0.5f; 
                    bombe->coor.y += normaleLocale.v * 0.5f;
                }
            }
        }

        // Si on a accumulé des normales, on calcule le rebond sur la normale moyenne
        if (nbPointsEnCollision > 0) {
            normeNormalCumul = sqrt(normalCumul.u * normalCumul.u + normalCumul.v * normalCumul.v);
            if (normeNormalCumul > 0.001f) {
                normalCumul.u /= normeNormalCumul;
                normalCumul.v /= normeNormalCumul;

                produitScalaire = vectVitesse->u * normalCumul.u + vectVitesse->v * normalCumul.v;
                
                // On ne rebondit que si la vitesse va VERS le terrain
                if (produitScalaire < 0) {
                    
                    vectVitesse->u -= (1.0f + COEF_RESTITUTION) * produitScalaire * normalCumul.u;
                    vectVitesse->v -= (1.0f + COEF_RESTITUTION) * produitScalaire * normalCumul.v;
                    
                    // Friction optionnelle pour éviter que ça glisse indéfiniment (simulation d'une perte d'énergie)
                    vectVitesse->u *= 0.98f;
                    vectVitesse->v *= 0.98f;
                }
            }
        }
    }

    return collisionDetectee;
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