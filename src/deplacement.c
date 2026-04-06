#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../lib/deplacement.h"
#include "../lib/fonctionsVerification.h"
#include "../lib/regression.h"
#include "../lib/tda_nuage.h"
#include "../lib/chargerMatrice.h"
#include "../lib/placer_dinos.h"
#include "../lib/collision_decor.h"


/**
 * @brief Vérifie si le dinosaure sort du nuage actuel ou touche l'eau.
 */
int horsNuage(t_dino *dino, int nb_pts, int matrice[MAT_H][MAT_L]) {

    if(dino->indice_nuage < 0 || dino->indice_nuage >=nb_pts){
        dino->deplacement->hors_nuage = 1;
        return 1;
    }
    
    dino->deplacement->hors_nuage = 0;
    return 0; 
}

int noyade(t_dino *dino, int matrice[MAT_H][MAT_L]){
    // Si le pied touche l'eau (EAU = -1 dans votre enum t_case)
    if(dino->pos.y>=(MAT_H-80)) {
        dino->etat = 0; 
        dino->pv = 0;
        dino->deplacement->hors_nuage = 1;
        printf("collision eau\n");
        return 1;
    }
    return 0;
}

/**
 * @brief Gère la transition entre deux nuages et la chute physique.
 */
void tomberNuage(t_dino *dino, t_coordonnee **nuage, char *nomNuage[], int nb_nuage, int *nb_pts, int matrice[MAT_H][MAT_L], int sens) {
    int d1, d2, ecart;
    supprimer_matrice_dino(dino, matrice);

    // Phase 1 : Initialisation de la chute et chargement du nouveau nuage
    if (dino->deplacement->tomber == 1) {
        int nouvel_id = dino->id_nuage + sens;
        
        if (nouvel_id >= 0 && nouvel_id < nb_nuage) {
            t_coordonnee *nv_nuage = nuage_de_points(nb_pts, nomNuage[nouvel_id]);
            
            if(nv_nuage != NULL){
                d1 = dino->pos.x;
                // Détermine le point de bordure le plus proche du nouveau nuage
                d2 = (sens == 1) ? nv_nuage[0].x : nv_nuage[*nb_pts - 1].x;
                ecart = abs(d2 - d1);

                // Transfert de mémoire sécurisé
                nuageDetruire(nuage);
                *nuage = nv_nuage; 
                dino->id_nuage = nouvel_id;
                
                // Positionnement sur le nouveau nuage avec compensation d'écart
                dino->indice_nuage = (sens == 1) ? (0 + ecart) : (*nb_pts - 1 - ecart);
                
                // Sécurité bornes
                if (dino->indice_nuage < 0) dino->indice_nuage = 0;
                if (dino->indice_nuage >= *nb_pts) dino->indice_nuage = *nb_pts - 1;

                dino->pos.x = (*nuage)[dino->indice_nuage].x;
                dino->deplacement->indice_reel = (float)dino->indice_nuage;
                dino->deplacement->tomber = 2; // Passage à la chute physique
            }
        } else {
            dino->deplacement->tomber = 2; // tombe quand même
        }
    }
    // Phase 2 : Chute verticale jusqu'au contact avec le nuage
    else if(dino->deplacement->tomber == 2) {
        if (dino->pos.y < (*nuage)[dino->indice_nuage].y) {
            dino->deplacement->v_y += GRAVITE;
            dino->pos.y += (int)dino->deplacement->v_y;
            noyade(dino,matrice);
        } else {
            // Atterrissage
            if(!noyade(dino,matrice)){
                dino->pos.y = (*nuage)[dino->indice_nuage].y;
                dino->deplacement->v_y = 0;
                dino->deplacement->tomber = 0;
            }
        }
    }
    remplir_matrice_dino(dino, dino->pos, matrice);
    
}

void gauche(t_dino *dino, t_coordonnee **nuage, char *nomNuage[], int nb_nuage, int *nb_pts, int matrice[MAT_H][MAT_L], const Uint8 *state) {
    float a, b;
    int booleen=horsNuage(dino, *nuage, nb_pts, matrice);
    if(dino->etat==0)return;
    if (state[SDL_SCANCODE_LEFT]){
        regression((*nuage)[dino->indice_nuage], *nuage, &a, &b, dino->indice_nuage, *nb_pts);
        
        float pas = VITESSE_BASE * (1.0f - (a * 0.5f));
        dino->deplacement->indice_reel -= pas;
        dino->indice_nuage = (int)dino->deplacement->indice_reel;
        noyade(dino,matrice);
        booleen=horsNuage(dino, *nuage, nb_pts, matrice);
        if(booleen){
        dino->deplacement->tomber = 1;
        tomberNuage(dino, nuage, nomNuage, nb_nuage, nb_pts, matrice, -1); 
        }
        else {
            supprimer_matrice_dino(dino, matrice);
            dino->pos = (*nuage)[dino->indice_nuage];
            remplir_matrice_dino(dino, dino->pos, matrice);
        }
    }
}

void droite(t_dino *dino, t_coordonnee **nuage, char *nomNuage[], int nb_nuage, int *nb_pts, int matrice[MAT_H][MAT_L], const Uint8 *state) {
    float a, b;
    int booleen=horsNuage(dino, *nuage, nb_pts, matrice);
    if(dino->etat==0)return;
    if (state[SDL_SCANCODE_RIGHT]){
        regression((*nuage)[dino->indice_nuage], *nuage, &a, &b, dino->indice_nuage, *nb_pts);
        
        float pas = VITESSE_BASE * (1.0f + (a * 0.5f));
        dino->deplacement->indice_reel += pas;
        dino->indice_nuage = (int)dino->deplacement->indice_reel;
        noyade(dino,matrice);
        if(booleen){
        dino->deplacement->tomber = 1;
        tomberNuage(dino, nuage, nomNuage, nb_nuage, nb_pts, matrice, -1); 
        }
        else {
            supprimer_matrice_dino(dino, matrice);
            dino->pos = (*nuage)[dino->indice_nuage];
            remplir_matrice_dino(dino, dino->pos, matrice);
        }
        
    }
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
            if(!noyade(dino,matrice)){
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
                    noyade(dino,matrice);
                }
            }
            else{
                if(!noyade(dino,matrice))tomberNuage(dino, nuage, nomNuage, nb_nuage, nb_pts, matrice, 1); 
            }
        }
        remplir_matrice_dino(dino, dino->pos, matrice);
    }
}
    

void deplacement_dino(t_dino *dino, t_coordonnee **nuage, char *nomNuage[], int nb_nuage, int *nb_pts, int matrice[MAT_H][MAT_L]) {
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    
    // 1. VÉRIFICATION DE L'ÉTAT (SÉCURITÉ)
    // Si le dino est déjà mort ou n'a plus de PV, on nettoie la matrice et on sort.
    if (dino->etat == 0 || dino->pv <= 0) {
        dino->etat = 0;
        supprimer_matrice_dino(dino, matrice);
        return;
    }

    // 2. DÉTECTION DE COLLISION IMMÉDIATE
    // On vérifie si la position actuelle touche l'eau.
    if (horsNuage(dino, *nuage, nb_pts, matrice)) {
        if (dino->etat == 0) { // Si horsNuage a détecté l'eau
            supprimer_matrice_dino(dino, matrice);
        }
    }

    // 3. LOGIQUE DE MOUVEMENT (Uniquement si vivant)
    if (dino->deplacement->tomber) {
        // Si le dino est en train de tomber (chute libre ou changement de nuage)
        tomberNuage(dino, nuage, nomNuage, nb_nuage, nb_pts, matrice, 0);
    } 
    else {
        //Gestion du saut (prioritaire sur la marche)
        saut(dino, nuage, nomNuage, nb_nuage, nb_pts, matrice, state);

        // Gestion de la marche (uniquement si au sol et pas en train de sauter)
        if (!dino->deplacement->sautBooleen) {
            gauche(dino, nuage, nomNuage, nb_nuage, nb_pts, matrice, state);
            droite(dino, nuage, nomNuage, nb_nuage, nb_pts, matrice, state);
        }
    }
    if (dino->etat == 0) { // Si horsNuage a détecté l'eau
        supprimer_matrice_dino(dino, matrice);
        return; // On arrête tout ici pour éviter que tomberNuage ne le "sauve"
    }

    // 4. POST-TRAITEMENT
    if (dino->deplacement->wait > 0) {
        dino->deplacement->wait--;
    }

    if(noyade(dino, matrice))printf("dino etat:%d\n",dino->etat);

}
