#define STB_IMAGE_IMPLEMENTATION
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../lib/deplacement.h"
#include "../lib/fonctionsVerification.h"
#include "../lib/regression.h"
#include "../lib/tda_nuage.h"
#include "../lib/chargerMatrice.h"
#include "../lib/placer_dinos.h"
#include "../lib/tda_nuage.h"
#include "../lib/collision_decor.h"



int horsNuage(t_dino *dino, t_coordonnee *nuage, int *nb_pts, int matrice[MAT_H][MAT_L], int mvt) {
    int i;
    for(i=0; i<4; i++) {
        dino->deplacement->tab_res[i] = 1;
    }
    
    int booleen = collision_decor(dino->deplacement->tab_res, *dino, matrice);
    
    if((dino->deplacement->tab_res[0] == EAU)) {
        supprimer_matrice_dino(dino, matrice);
        dino->etat = 0;
        dino->deplacement->hors_nuage = 1;
        return 1;
    }
    
    return 0; 
}

void gauche(t_dino *dino, t_coordonnee *nuage, int nb_pts, int matrice[MAT_H][MAT_L],const Uint8 *state) {

    /* Le code utilise une fonction regression pour obtenir la pente locale (a) 
    de la courbe sur laquelle se déplace le dino.
    Si a > 0 : La courbe "descend" (vers la gauche).
    Si a < 0 : La courbe "monte" (vers la gauche).
    Si a = 0 : Le terrain est plat. */

    float a, b;
    int mvt =0;
    int booleen;
    if (state[SDL_SCANCODE_LEFT]){
        booleen=horsNuage(dino,nuage,&nb_pts,matrice,mvt);
        // Calculer la pente locale via la régression
        regression(nuage[dino->indice_nuage], nuage, &a, &b, dino->indice_nuage, nb_pts);
        
        float pas = VITESSE_BASE * (1.0f - (a * 0.5f));
        
        // Mise à jour de l'indice réel
        dino->deplacement->indice_reel -= pas;
        
        // Mise à jour des coordonnées

        dino->indice_nuage = (int)dino->deplacement->indice_reel;
        
        supprimer_matrice_dino(dino,matrice);
        if(booleen){
            dino->deplacement->v_y += GRAVITE;
            dino->pos.y += (int)dino->deplacement->v_y;
        }
        else{
        dino->pos=nuage[dino->indice_nuage];
        }
        remplir_matrice_dino(dino,dino->pos,matrice);
    }
}

void droite(t_dino *dino, t_coordonnee *nuage, int nb_pts, int matrice[MAT_H][MAT_L],const Uint8 *state) {

    /* Le code utilise une fonction regression pour obtenir la pente locale (a) 
    de la courbe sur laquelle se déplace le dino.
    Si a > 0 : La courbe "monte" (vers la droite).
    Si a < 0 : La courbe "descend" (vers la droite).
    Si a = 0 : Le terrain est plat. */

    float a, b;
    int mvt=0;
    int booleen;
    if (state[SDL_SCANCODE_RIGHT]){    
        booleen=horsNuage(dino,nuage,&nb_pts,matrice,mvt);
        // Calculer la pente locale
        regression(nuage[dino->indice_nuage], nuage, &a, &b, dino->indice_nuage, nb_pts);
        
        // Calcul du pas
        float pas = VITESSE_BASE * (1.0f + (a * 0.5f));


        // Mise à jour de l'indice réel
        dino->deplacement->indice_reel += pas;

        // Mise à jour des coordonnées

        dino->indice_nuage = (int)dino->deplacement->indice_reel;
        
        supprimer_matrice_dino(dino,matrice);
        if(booleen){
            dino->deplacement->v_y += GRAVITE;
            dino->pos.y += (int)dino->deplacement->v_y;
        }
        else{
            dino->pos=nuage[dino->indice_nuage];
        }
        remplir_matrice_dino(dino,dino->pos,matrice);
        
    }
}


// Fonction pour trouver l'indice le plus proche dans le nouveau nuage
int trouverIndiceProche(t_coordonnee *nuage, int nb_pts, int x_cible) {
    int proche = 0;
    int min_diff = abs(nuage[0].x - x_cible);
    for (int i = 1; i < nb_pts; i++) {
        int diff = abs(nuage[i].x - x_cible);
        if (diff < min_diff) {
            min_diff = diff;
            proche = i;
        }
    }
    return proche;
}


// --- Dans SAUT ---
void saut(t_dino *dino, t_coordonnee **nuage, char *nomNuage[], int nb_nuage, int *nb_pts, int matrice[MAT_H][MAT_L], const Uint8 *state) {
    int sens = 0; // Toujours initialiser

    if (dino->deplacement->wait == 0 && !dino->deplacement->sautBooleen) {
        if (state[SDL_SCANCODE_UP]) {
            dino->deplacement->v_y = FORCE_SAUT;
            dino->deplacement->sautBooleen = 1;
        }
    }

    if (dino->deplacement->sautBooleen) {
        supprimer_matrice_dino(dino, matrice);
        
        // On détermine le sens du mouvement
        if (state[SDL_SCANCODE_RIGHT]) sens = 1;
        else if (state[SDL_SCANCODE_LEFT]) sens = -1;

        // On met à jour l'indice SANS vérifier les bornes ici pour permettre la sortie
        dino->indice_nuage += sens;

        // Cas 1 : On est toujours sur le nuage actuel
        if(dino->indice_nuage >= 0 && dino->indice_nuage < *nb_pts){
            dino->deplacement->v_y += GRAVITE;
            dino->pos.y += (int)dino->deplacement->v_y;
            dino->pos.x = (*nuage)[dino->indice_nuage].x;
            dino->deplacement->indice_reel = (float)dino->indice_nuage;

            if (dino->pos.y >= (*nuage)[dino->indice_nuage].y) {
                dino->pos = (*nuage)[dino->indice_nuage];
                dino->deplacement->sautBooleen = 0;
                dino->deplacement->v_y = 0;
                dino->deplacement->wait = 20; // Délai réduit pour test
            }
        }
        // Cas 2 : ON SORT DU NUAGE -> Transfert
        else {
            int nouvel_id = dino->id_nuage + sens;
            
            if (nouvel_id >= 0 && nouvel_id < nb_nuage) {
                t_coordonnee *nv_nuage = nuage_de_points(nb_pts, nomNuage[nouvel_id]);
                
                if (nv_nuage != NULL) {
                    nuageDetruire(nuage); 
                    *nuage = nv_nuage;    
                    dino->id_nuage = nouvel_id;
                    
                    // On se place sur le bord correspondant du nouveau nuage
                    dino->indice_nuage = (sens == 1) ? 0 : (*nb_pts - 1);
                    dino->pos.x = (*nuage)[dino->indice_nuage].x;
                    dino->deplacement->indice_reel = (float)dino->indice_nuage;
                }
            } else {
                // Si pas de nouveau nuage, on empêche la sortie (blocage au bord)
                if (dino->indice_nuage < 0) dino->indice_nuage = 0;
                if (dino->indice_nuage >= *nb_pts) dino->indice_nuage = *nb_pts - 1;
            }
        }
        remplir_matrice_dino(dino, dino->pos, matrice);
    }
}

void deplacement_dino(t_dino *dino, t_coordonnee **nuage, char *nomNuage[], int nb_nuage, int *nb_pts, int matrice[MAT_H][MAT_L]) {
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    // 1. Toujours appeler saut pour gérer la physique et le changement de nuage
    saut(dino, nuage, nomNuage, nb_nuage, nb_pts, matrice, state);

    // 2. Mouvement horizontal uniquement si on ne saute pas
    if (!dino->deplacement->sautBooleen && !dino->deplacement->hors_nuage) {
        gauche(dino, *nuage, *nb_pts, matrice, state);
        droite(dino, *nuage, *nb_pts, matrice, state);
    }

    if (dino->deplacement->wait > 0) dino->deplacement->wait--;
    if (dino->pv <= 0) dino->etat = 0;
}