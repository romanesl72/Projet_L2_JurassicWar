#include "../lib/tirer_archer.h"
#include <math.h>


void initialiserTirArcher(t_tir *tir, float departX, float departY, t_arme arme) {
    tir->pos.x = departX;
    tir->pos.y = departY;
    tir->velo.u = 10.0f;
    tir->velo.v = -10.0f;
    tir->actif = 0;
    tir->arme_source = arme;
}


void miseAjourTemps(Uint32 *tempsPrecedent, float *tempsEcoule){
    Uint32 tempsCourant = SDL_GetTicks();
    *tempsEcoule = (tempsCourant - *tempsPrecedent)/1000.0f;
    *tempsPrecedent = tempsCourant;
}

int collisionFrontiere(t_tir *tir){
    return ((tir->pos.x < 0) || (tir->pos.x >= MAT_L) || (tir->pos.y < 0) || (tir->pos.y >= MAT_H));
}

int collisionTerrain(int matrice[MAT_H][MAT_L], t_tir *tir) {
    int mx = (int)roundf(tir->pos.x);
    int my = (int)roundf(tir->pos.y);
    if (collisionFrontiere(tir)) {
        return 0;
    }
    return (matrice[my][mx] == TERRE);
}

int collisionEau(int matrice[MAT_H][MAT_L], t_tir *tir) {
    int mx = (int)roundf(tir->pos.x);
    int my = (int)roundf(tir->pos.y);
    if (collisionFrontiere(tir)) {
        return 0;
    }
    return (matrice[my][mx] == EAU);
}

int collisionDino(int matrice[MAT_H][MAT_L], t_tir *tir) {
    int mx = (int)roundf(tir->pos.x);
    int my = (int)roundf(tir->pos.y);
    if (collisionFrontiere(tir)) {
        return 0;
    }
    if (matrice[my][mx] >= 3) return matrice[my][mx];
    return 0;
}

void mettreAJourVol(t_tir *tir, int matrice[MAT_H][MAT_L], float gravite) {
    if (!tir->actif) return;

    /* On applique la gravité */
    float g_effet= gravite * tir->arme_source.poids_projectile;
    tir->pos.x += tir->velo.u;
    tir->pos.y += tir->velo.v;
    tir->velo.v += g_effet;

    /* Détection pour arrêter le vol */
    if (collisionFrontiere(tir) || collisionTerrain(matrice, tir) || collisionEau(matrice, tir) || collisionDino(matrice, tir)) {
        
        tir->actif = 0;
    }
}


void tracerFleche(SDL_Renderer *zoneAffichage, t_tir *tir) {
    if (!tir->actif) return;
    float longueur;
    float norme;
    float arriereX;
    float arriereY;

    /* Couleur blanche pour la flèche */
    SDL_SetRenderDrawColor(zoneAffichage, 255, 255, 255, 255);
    
    longueur = 20.0; /* Longueur du trait */
    norme = sqrt(tir->velo.u * tir->velo.u + tir->velo.v * tir->velo.v);
    
    if (norme > 0.1f) {
        arriereX = tir->pos.x - (tir->velo.u / norme) * longueur;
        arriereY = tir->pos.y - (tir->velo.v / norme) * longueur;
        
        SDL_RenderDrawLine(zoneAffichage, (int)roundf(tir->pos.x), (int)roundf(tir->pos.y), (int)roundf(arriereX), (int)roundf(arriereY));
    }
}

void tracerTrajectoireArcher(SDL_Renderer *zoneAffichage, t_tir *tir, float graviteBase) {
    float temps = 0;
    float dt = 1.0f/120.0f;
    float g_effet;

    t_vect courant;

    float vitY = tir->velo.v;
    float vitX = tir->velo.u;

    g_effet  = graviteBase * tir->arme_source.poids_projectile;
    courant.u = tir->pos.x;
    courant.v = tir->pos.y;

    /* Trajectoire de couleur rouges */
    SDL_SetRenderDrawColor(zoneAffichage, 255, 0, 0, 255);

    while(temps < 2.0) {
        courant.u += dt*vitX;
        courant.v += dt*vitY;
        vitY += g_effet*dt;
        /*
        courant.u += vitX;
        courant.v += vitY;
        vitY += g_effet;
        */

        SDL_RenderDrawPoint(zoneAffichage, (int)roundf(courant.u), (int)roundf(courant.v));

        temps += dt;
    }
}

void viserArcher(SDL_Renderer* zoneAffichage, SDL_Texture *texMap, t_tir *tir, const Uint8 **etatClavier, float gravite) {
    SDL_Rect rectMap = {0, 0, 1300, 700};

    do {

        SDL_PumpEvents();
        *etatClavier = SDL_GetKeyboardState(NULL);

        if ((*etatClavier)[SDL_SCANCODE_UP]){
            tir->velo.v -= 0.5;
        }
        if ((*etatClavier)[SDL_SCANCODE_DOWN]){
            tir->velo.v += 0.5;
        }

        /* Pour tracer la courbe de trajectoire vers la gauche, il faut une vitesse horizontale négative */
        if ((*etatClavier)[SDL_SCANCODE_LEFT]){
            tir->velo.u = -fabs(tir->velo.u);
        }

        /* Pour tracer la courbe de trajectoire vers la droite, il faut une vitesse horizontale positive */
        if ((*etatClavier)[SDL_SCANCODE_RIGHT]){
            tir->velo.u = fabs(tir->velo.u);
        }

        SDL_RenderClear(zoneAffichage);
        SDL_RenderCopy(zoneAffichage, texMap, NULL, &rectMap);

        tracerFleche(zoneAffichage, tir);

        float g_effet = gravite * tir->arme_source.poids_projectile;
        tracerTrajectoireArcher(zoneAffichage, tir, g_effet);

        SDL_RenderPresent(zoneAffichage);
        SDL_Delay(16);

    } while(!(*etatClavier)[SDL_SCANCODE_SPACE]);


    tir->actif = 1; 
}