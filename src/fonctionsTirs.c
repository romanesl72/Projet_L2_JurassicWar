#include "../lib/fonctionsTirs.h"
#include "../lib/placer_dinos.h"
#include <math.h>


void initialiserTirArcher(t_tir *tir, float departX, float departY, t_arme arme) {
    tir->pos.x = departX;
    tir->pos.y = departY;
    tir->velo.u = 5.0f;
    tir->velo.v = -5.0f;
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
    int valeur = matrice[my][mx];
    if (collisionFrontiere(tir)) {
        return 0;
    }
    if (valeur >= D1) return valeur;
    return 0;
}

int mettreAJourVol(t_tir *tir, int matrice[MAT_H][MAT_L], float gravite, int id_tireur) {
    if (!tir->actif) return 0;

    int resDino = collisionDino(matrice, tir);
    /* On applique la gravité */
    float g_effet= gravite * tir->arme_source.poids_projectile;
    tir->pos.x += tir->velo.u;
    tir->pos.y += tir->velo.v;
    tir->velo.v += g_effet;

    /* Détection pour arrêter le vol par ordre de priorité*/
    if(collisionFrontiere(tir)){
        tir->actif = 0;
        return -2;
    }
    if(resDino >= D1 && resDino != id_tireur){
        tir->actif = 0;
        return resDino;
    }
    if(collisionTerrain(matrice, tir)){
        tir->actif = 0;
        return TERRE;
    }
    if(collisionEau(matrice, tir)){
        tir->actif = 0;
        return EAU;
    }

    return 0;
}


void tracerFleche(SDL_Renderer *zoneAffichage, t_tir *tir) {
    if (!tir->actif) return;
    float longueur;
    float norme;
    float arriereX;
    float arriereY;

    /* Couleur blanche pour la flèche */
    SDL_SetRenderDrawColor(zoneAffichage, 255, 255, 255, 255);
    
    if (tir->arme_source.nom == FUSIL || tir->arme_source.nom == REVOLVER) {
        SDL_RenderDrawPoint(zoneAffichage, (int)roundf(tir->pos.x), (int)roundf(tir->pos.y));
    }
    else {
        longueur = 20.0; /* Longueur du trait */
        norme = sqrt(tir->velo.u * tir->velo.u + tir->velo.v * tir->velo.v);
    }
    if (norme > 0.1f) {
        arriereX = tir->pos.x - (tir->velo.u / norme) * longueur;
        arriereY = tir->pos.y - (tir->velo.v / norme) * longueur;
        
        SDL_RenderDrawLine(zoneAffichage, (int)roundf(tir->pos.x), (int)roundf(tir->pos.y), (int)roundf(arriereX), (int)roundf(arriereY));
    }
}

void tracerTrajectoireArcher(SDL_Renderer *zoneAffichage, t_tir *tir, float graviteBase) {
    int i;
    float g_effet;
    float precX;
    float precY;

    float simuX = tir->pos.x;
    float simuY = tir->pos.y;
    float simuVitY = tir->velo.v;
    float simuVitX = tir->velo.u;

    g_effet  = graviteBase * tir->arme_source.poids_projectile;

    /* Trajectoire de couleur rouges */
    SDL_SetRenderDrawColor(zoneAffichage, 255, 0, 0, 255);

    for (i = 0; i < 50; i++) {
        precX = simuX;
        precY = simuY;

        simuX += simuVitX;
        simuY += simuVitY;
        simuVitY += g_effet;

        /* On dessine un trait entre chaque point simulé pour une belle courbe */
        SDL_RenderDrawLine(zoneAffichage, (int)roundf(precX), (int)roundf(precY), (int)roundf(simuX), (int)roundf(simuY));
        

    }
}

void viserArcher(SDL_Renderer* zoneAffichage, SDL_Texture *texMap, t_tir *tir, const Uint8 **etatClavier, float gravite, t_joueur *e1, t_joueur *e2) {
    

    tir->velo.u = tir->arme_source.puissance_propulsion;
    tir->velo.v = -tir->arme_source.puissance_propulsion;

    float g_effet = gravite * tir->arme_source.poids_projectile;
    float vMax = tir->arme_source.vitesse_max;

    do {

        SDL_PumpEvents();
        *etatClavier = SDL_GetKeyboardState(NULL);

        if ((*etatClavier)[SDL_SCANCODE_UP]){
            tir->velo.v -= 0.1;
        }
        if ((*etatClavier)[SDL_SCANCODE_DOWN]){
            tir->velo.v += 0.1;
        }

        if ((*etatClavier)[SDL_SCANCODE_LEFT]){
            tir->velo.u -= 0.1;
        }
        if ((*etatClavier)[SDL_SCANCODE_RIGHT]){
            tir->velo.u += 0.1;
        }

        if (tir->velo.u > 15.0f) tir->velo.u = vMax;
        if (tir->velo.u < -15.0f) tir->velo.u = -vMax;

        SDL_SetRenderDrawColor(zoneAffichage, 50, 50, 50, 255);
        SDL_RenderClear(zoneAffichage);
        
        if (texMap != NULL) {
            SDL_Rect rectMap = {0, 0, LARGEUR_TERRAIN, HAUTEUR_TERRAIN};
            SDL_RenderCopy(zoneAffichage, texMap, NULL, &rectMap);
        }

        
        if (e1 != NULL) {
            afficherDinos(zoneAffichage, e1);
        }
        if (e2 != NULL){
            afficherDinos(zoneAffichage, e2);
        }

        tracerFleche(zoneAffichage, tir);

        tracerTrajectoireArcher(zoneAffichage, tir, g_effet);

        SDL_RenderPresent(zoneAffichage);
        SDL_Delay(16);

    } while(!(*etatClavier)[SDL_SCANCODE_SPACE]);


    tir->actif = 1; 
}