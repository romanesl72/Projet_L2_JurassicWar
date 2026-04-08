#include "../lib/fonctionsPlacementBombe.h"
#include "../lib/fonctionsRebonds.h"
#include "../lib/fonctionsStructJoueur.h"
#include "../lib/placer_dinos.h"
#include <stdio.h>
#include <math.h>

/** 
 * @file fonctionsRebonds.c
 * @brief Corps des fonctions pour le lancer, la trajectoire et l'affichage d'une bombe.
 * @author Hannah Sergent
 * @date Crée le 5/02/2026
 */

void initialiserBombe(t_bombe *bombe, float coorChoisieX, float coorChoisieY, int rayon) {
    bombe->coor.x = coorChoisieX;
    bombe->coor.y = coorChoisieY;
    bombe->rayon = rayon;
}

void initialiserRayonBombe(t_bombe *bombe, int rayon) {
    bombe->rayon = rayon;
}

void initialiserVitesse(t_vect *vectVitesse, float vitesseChoisieX, float vitesseChoisieY){
    vectVitesse->u = vitesseChoisieX;
    vectVitesse->v = vitesseChoisieY;
}

void miseAjourTemps(Uint32 *tempsPrecedent, float *tempsEcoule){
    Uint32 tempsCourant = SDL_GetTicks();
    printf("%ld %ld \n", tempsCourant, *tempsPrecedent);
    *tempsEcoule = (tempsCourant - *tempsPrecedent)/1000.0f;
    *tempsPrecedent = tempsCourant;
}

int collisionFrontiereBombe(t_bombe *bombe){
    return ((bombe->coor.x + bombe->rayon > LARGEUR_TERRAIN) || (bombe->coor.x - bombe->rayon < 0) || (bombe->coor.y + bombe->rayon > HAUTEUR_TERRAIN) || (bombe->coor.y - bombe->rayon < 0));
}

/**
 * @fn int dansLimites(int x, int y);
 * @brief La fonction vérifie si des coordonnées sont dans les limites de la matrice ou du terrain.
 * @author Hannah Sergent
 * @date Crée le 23/02/2026
 * @param x coordoonnée des absisses
 * @param y coordonnée des ordonnées
 * @return 1 si les coordonnées sont dans les limites et 0 sinon
 */

int dansLimites(int x, int y){
    return ((x >= 0) && (x < LARGEUR_TERRAIN) && (y < HAUTEUR_TERRAIN) && (y >= 0));
}

/**
 * @fn int estTerrain(t_case pixel);
 * @brief La fonction indique si un pixel contient de la terre.
 * @author Hannah Sergent
 * @date Crée le 23/02/2026
 * @param pixel contenu d'une case de la matrice
 * @return TERRE si le pixel est de la terre et 0 sinon
 */

int estTerrain(t_case pixel){
    return (pixel == TERRE);
}

/**
 * @fn void calculerNormale(t_case matriceTerrain[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], t_coordonnee_calcul *extremiteBombe, t_vect *normal);
 * @brief La fonction détermine un vecteur normal au terrain à partir des coordonnées d'un point.
 * @author Hannah Sergent
 * @date Crée le 23/02/2026
 * @param matriceTerrain une matrice contenant les informations sur le terrain
 * @param extremiteBombe les coordonnées flottantes d'une des extremités de la bombe
 * @param normal un vecteur qui contient les coordonnées du vecteur normal calculé
 */

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

void tracerBombeHIP(SDL_Renderer *zoneAffichage, t_bombe *bombe){
    int largeur;
    int hauteur;

    // Bombe de couleur blanche
    SDL_SetRenderDrawColor(zoneAffichage, 255, 255, 255, 255);

    for(largeur = -bombe->rayon; largeur <= bombe->rayon; largeur++){
        for(hauteur = -bombe->rayon; hauteur <= bombe->rayon; hauteur++){

            if (largeur*largeur + hauteur*hauteur <= bombe->rayon*bombe->rayon) {
                SDL_RenderDrawPoint(zoneAffichage, roundf(bombe->coor.x) + largeur, round(bombe->coor.y) + hauteur + HAUTEUR_HIP);
            }
        }
    }
}

/**
 * @fn void tracerTrajectoireLancer(SDL_Renderer *zoneAffichage, t_coordonnee_calcul *coor, t_vect *vectVitesse);
 * @brief La fonction trace la trajectoire de lancer de la bombe sous la forme d'un laser de couleur rouge.
 * @author Hannah Sergent
 * @date Crée le 11/02/2026
 * @param zoneAffichage un pointeur sur la zone d'affichage
 * @param coor un pointeur sur une structure contenant les coordonnées flottantes de la bombe
 * @param vectVitesse un pointeur sur le vecteur vitesse de la bombe
 */

void tracerTrajectoireLancer(SDL_Renderer *zoneAffichage, t_coordonnee_calcul *coor, t_vect *vectVitesse){

    float temps = 0;
    float dt = 1.0f/250.0f;
    t_vect precedent;
    t_vect courant;
    float vitY = vectVitesse->v;

    precedent.u = courant.u = coor->x;
    precedent.v = courant.v = coor->y;

    // Trajectoire de couleur rouge
    SDL_SetRenderDrawColor(zoneAffichage, 255, 0, 0, 255);

    while(temps < 3.5){

        courant.u += dt*vectVitesse->u;
        courant.v += dt*vitY;
        vitY += GRAVITE_BOMBE*dt;

        if (dansLimites(courant.u, courant.v)){
            SDL_RenderDrawLine(zoneAffichage, roundf(precedent.u), roundf(precedent.v), roundf(courant.u), roundf(courant.v));
        }

        precedent = courant;
        temps += dt;
    }
}

void tracerTrajectoireLancerHIP(SDL_Renderer *zoneAffichage, t_coordonnee_calcul *coor, t_vect *vectVitesse){

    float temps = 0;
    float dt = 1.0f/120.0f;
    t_vect precedent;
    t_vect courant;
    float vitY = vectVitesse->v;

    precedent.u = courant.u = coor->x;
    precedent.v = courant.v = coor->y;

    // Trajectoire de couleur rouge
    SDL_SetRenderDrawColor(zoneAffichage, 255, 0, 0, 255);

    while(temps < 3.5){

        courant.u += dt*vectVitesse->u;
        courant.v += dt*vitY;
        vitY += GRAVITE_BOMBE*dt;

        if (dansLimites(courant.u, courant.v)){
            SDL_RenderDrawLine(zoneAffichage, roundf(precedent.u), roundf(precedent.v) + HAUTEUR_HIP, roundf(courant.u), roundf(courant.v) + HAUTEUR_HIP);
        }

        precedent = courant;
        temps += dt;
    }
}

void choixHauteurLancer(SDL_Renderer* zoneAffichage, SDL_Texture *texMap, SDL_Rect *rect, const Uint8 **etatClavier, t_bombe *bombe, t_vect *vectVitesse){
    
    do {

        SDL_PumpEvents();
        *etatClavier = SDL_GetKeyboardState(NULL);

        /* Ajuster la hauteur */

        if ((*etatClavier)[SDL_SCANCODE_UP]){
            vectVitesse->v -= 0.8;
        }
        if ((*etatClavier)[SDL_SCANCODE_DOWN]){
            vectVitesse->v += 0.8;
        }

        /* Ajuster la puissance */

        if ((*etatClavier)[SDL_SCANCODE_LEFT]){
            vectVitesse->u -= 0.8;
        }

        if ((*etatClavier)[SDL_SCANCODE_RIGHT]){
            vectVitesse->u += 0.8;
        }

        SDL_RenderClear(zoneAffichage);
        SDL_RenderCopy(zoneAffichage, texMap, NULL, rect);

        tracerBombe(zoneAffichage, bombe);
        tracerTrajectoireLancer(zoneAffichage, &(bombe->coor), vectVitesse);

        SDL_RenderPresent(zoneAffichage);

        SDL_Delay(4);

    } while(!(*etatClavier)[SDL_SCANCODE_SPACE]);
}

void choixHauteurLancerAvecDinos(SDL_Renderer* zoneAffichage, SDL_Texture *texMap, SDL_Rect *rect, const Uint8 **etatClavier, t_bombe *bombe, t_vect *vectVitesse, t_joueur * equipe1, t_joueur * equipe2){
    
    do {

        SDL_PumpEvents();
        *etatClavier = SDL_GetKeyboardState(NULL);

        /* Ajuster la hauteur */

        if ((*etatClavier)[SDL_SCANCODE_UP]){
            vectVitesse->v -= 0.8;
        }
        if ((*etatClavier)[SDL_SCANCODE_DOWN]){
            vectVitesse->v += 0.8;
        }

        /* Ajuster la puissance */

        if ((*etatClavier)[SDL_SCANCODE_LEFT]){
            vectVitesse->u -= 0.8;
        }

        if ((*etatClavier)[SDL_SCANCODE_RIGHT]){
            vectVitesse->u += 0.8;
        }

        SDL_RenderClear(zoneAffichage);
        SDL_RenderCopy(zoneAffichage, texMap, NULL, rect);

        tracerBombe(zoneAffichage, bombe);
        afficherDinos(zoneAffichage, equipe1);
        afficherDinos(zoneAffichage, equipe2);
        tracerTrajectoireLancer(zoneAffichage, &(bombe->coor), vectVitesse);

        SDL_RenderPresent(zoneAffichage);
        SDL_Delay(4);

    } while(!(*etatClavier)[SDL_SCANCODE_SPACE]);
}

/** 
 * @fn void retournerLaser(t_vect *vectVitesse, t_cote cote)
 * @brief La fonction détermine s'il faut retourner le laser ou non en fonction de la direction dans laquelle se trouve le dinosaure.
 * Le laser désigne la trajectoire de lancer de la bombe.
 * @author Hannah Sergent
 * @date Crée le 28/03/2026
 * @param vectVitesse un pointeur sur le vecteur vitesse de la bombe
 * @param cote la direction attendue du laser
 */

void retournerLaser(t_vect *vectVitesse, t_cote cote){

    /* Pour tracer la courbe de trajectoire vers la gauche, il faut une vitesse horizontale négative */

    if (cote == GAUCHE){
        vectVitesse->u = -fabs(vectVitesse->u);
    }

    /* Pour tracer la courbe de trajectoire vers la droite, il faut une vitesse horizontale positive */

    else {
        vectVitesse->u = fabs(vectVitesse->u);
    }

}

void choixHauteurLancerDinoCourant(SDL_Renderer* zoneAffichage, SDL_Texture *texMap, SDL_Rect *rect, const Uint8 **etatClavier, t_bombe *bombe, t_vect *vectVitesse, t_joueur * equipe1, t_joueur * equipe2, t_case numDinoCourant,  t_case matriceTerrain[HAUTEUR_TERRAIN][LARGEUR_TERRAIN]){
    
    t_cote cote = recupererDinoDirection(equipe1, equipe2, numDinoCourant);
    t_cote ancienCote = cote;

    t_dino *dino = recupererDinoNumero(equipe1, equipe2, numDinoCourant);

    placerBombeEntrePattes(dino, bombe, &cote, matriceTerrain);

    retournerDino(equipe1, equipe2, numDinoCourant, cote, &ancienCote);
    retournerLaser(vectVitesse, cote);

    do {

        SDL_PumpEvents();
        *etatClavier = SDL_GetKeyboardState(NULL);

        /* Changer de direction pour lancer la bombe */

        if ((*etatClavier)[SDL_SCANCODE_G]){
            cote = GAUCHE;
        }

        if ((*etatClavier)[SDL_SCANCODE_D]){
            cote = DROITE;
        }

        /* Ajuster la hauteur */

        if ((*etatClavier)[SDL_SCANCODE_UP]){
            vectVitesse->v -= 0.8;
        }
        if ((*etatClavier)[SDL_SCANCODE_DOWN]){
            vectVitesse->v += 0.8;
        }

        /* Ajuster la puissance */

        if ((*etatClavier)[SDL_SCANCODE_LEFT]){
            vectVitesse->u -= 0.8;
        }

        if ((*etatClavier)[SDL_SCANCODE_RIGHT]){
            vectVitesse->u += 0.8;
        }

        /* Le joueur veut changer de côté pour lancer la bombe */

        if (cote != ancienCote){

            placerBombeEntrePattes(dino, bombe, &cote, matriceTerrain);

            /* S'il y a assez de place pour lancer la bombe dans l'autre sens, le dinosaure se retourne */

            retournerDino(equipe1, equipe2, numDinoCourant, cote, &ancienCote);
            retournerLaser(vectVitesse, cote);

        }

        /* Affichage de la map, de la bombe, des dinos, de la trajectoire */
        SDL_RenderClear(zoneAffichage);
        SDL_RenderCopy(zoneAffichage, texMap, NULL, rect);

        tracerBombe(zoneAffichage, bombe);
        afficherDinos(zoneAffichage, equipe1);
        afficherDinos(zoneAffichage, equipe2);
        tracerTrajectoireLancer(zoneAffichage, &(bombe->coor), vectVitesse);

        SDL_RenderPresent(zoneAffichage);
        SDL_Delay(4);

    } while(!(*etatClavier)[SDL_SCANCODE_SPACE]);
}

void choixHauteurLancerDinoCourantHIP(SDL_Renderer* zoneAffichage, SDL_Texture *texMap, SDL_Texture **texObjets, TTF_Font *policeMenuHIP, SDL_Rect *rect, const Uint8 **etatClavier, t_bombe *bombe, t_vect *vectVitesse, t_joueur * equipe1, t_joueur * equipe2, t_case numDinoCourant,  t_case matriceTerrain[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], t_texte_cache *cache){
    
    t_cote cote = recupererDinoDirection(equipe1, equipe2, numDinoCourant);
    t_cote ancienCote = cote;

    t_dino *dino = recupererDinoNumero(equipe1, equipe2, numDinoCourant);

    placerBombeEntrePattes(dino, bombe, &cote, matriceTerrain);

    retournerDino(equipe1, equipe2, numDinoCourant, cote, &ancienCote);
    retournerLaser(vectVitesse, cote);

    do {

        SDL_PumpEvents();
        *etatClavier = SDL_GetKeyboardState(NULL);

        /* Changer de direction pour lancer la bombe */

        if ((*etatClavier)[SDL_SCANCODE_G]){
            cote = GAUCHE;
        }

        if ((*etatClavier)[SDL_SCANCODE_D]){
            cote = DROITE;
        }

        /* Ajuster la hauteur */

        if ((*etatClavier)[SDL_SCANCODE_UP]){
            vectVitesse->v -= 0.8;
        }
        if ((*etatClavier)[SDL_SCANCODE_DOWN]){
            vectVitesse->v += 0.8;
        }

        /* Ajuster la puissance */

        if ((*etatClavier)[SDL_SCANCODE_LEFT]){
            vectVitesse->u -= 0.8;
        }

        if ((*etatClavier)[SDL_SCANCODE_RIGHT]){
            vectVitesse->u += 0.8;
        }

        /* Le joueur veut changer de côté pour lancer la bombe */

        if (cote != ancienCote){

            placerBombeEntrePattes(dino, bombe, &cote, matriceTerrain);

            /* S'il y a assez de place pour lancer la bombe dans l'autre sens, le dinosaure se retourne */

            retournerDino(equipe1, equipe2, numDinoCourant, cote, &ancienCote);
            retournerLaser(vectVitesse, cote);

        }

        /* Affichage de la map, de la bombe, des dinos, de la trajectoire */
        SDL_RenderClear(zoneAffichage);
        SDL_RenderCopy(zoneAffichage, texMap, NULL, rect);

        tracerBombeHIP(zoneAffichage, bombe);
        afficherDinosAvecJeu(zoneAffichage, equipe1);
        afficherDinosAvecJeu(zoneAffichage, equipe2);
        tracerTrajectoireLancerHIP(zoneAffichage, &(bombe->coor), vectVitesse);

        afficherInventaire(zoneAffichage, texObjets, 7);
        afficherMenuPVDinosOp(zoneAffichage, policeMenuHIP, *equipe1, *equipe2, cache);

        SDL_RenderPresent(zoneAffichage);
        SDL_Delay(4);

    } while(!(*etatClavier)[SDL_SCANCODE_SPACE]);
}



