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

int init_deplacement(t_dino **dino, int *nb_pts, char *nomNuage[], int matrice[MAT_H][MAT_L], t_coordonnee **nuage_principal, int nb_nuage, ...) {
    *dino = malloc(sizeof(t_dino));
    if (*dino == NULL) return 0;

    (*dino)->deplacement = malloc(sizeof(t_deplacement));
    if ((*dino)->deplacement == NULL) {
        free(*dino);
        return 0;
    }

    // Initialisation impérative du nuage de destination à NULL pour realloc
    *nuage_principal = NULL; 
    int nb_pts_retenu = 0;
    int nb_pts_image_actuelle = 0;

    (*dino)->indice_nuage = 1000;

    va_list args;
    va_start(args, nb_nuage);

    for (int i = 0; i < nb_nuage; i++) {
        t_coordonnee **ptr_sur_nuage = va_arg(args, t_coordonnee **);
        
        // Charger l'image i
        *ptr_sur_nuage = nuage_de_points(&nb_pts_image_actuelle, nomNuage[i]);
        
        if (!nuageExiste(*ptr_sur_nuage)) {
            va_end(args);
            return 0;
        }


        // Fusionner dans le nuage principal
        // IMPORTANT : Bien passer &nb_pts_retenu pour mettre à jour le total
        regroupementNuage(nuage_principal, *ptr_sur_nuage, &nb_pts_retenu, nb_pts_image_actuelle);
    }
    
    va_end(args);

    // Mise à jour du compteur final de points pour l'appelant
    *nb_pts = nb_pts_retenu;

    /* --- Reste de l'initialisation --- */
    chargerMatriceDepuisFichier("../res/matrice.txt", matrice);
    
    // On définit la position de départ (ici sur le premier nuage chargé)
    // Attention : vérifiez que (*dino)->indice_nuage < nb_pts_retenu
    (*dino)->pos = (*nuage_principal)[(*dino)->indice_nuage];
    
    (*dino)->deplacement->indice_reel = (float)(*dino)->indice_nuage;
    (*dino)->deplacement->wait = 0;
    (*dino)->pv = 100;
    (*dino)->deplacement->hors_nuage = 0;

    remplir_matrice_dino(*dino, (*dino)->pos, matrice);

    return 1;
}

void supprimer_matrice_dino(t_dino *dino, int matrice[MAT_H][MAT_L]) {
    /*permet de remetre à jour les anciennes zones comportant un dino*/
    int i,j,px,py;

    for(i = 0; i < 30; i++) {
        for(j = 0; j < 30; j++) {
            py = dino->pos.y + i;
            px = dino->pos.x + j;
            if (py >= 0 && py < MAT_H && px >= 0 && px < MAT_L) {
                matrice[py][px] = dino->memoire[i][j];
            }
        }
    }
}


int horsNuage(t_dino *dino, t_coordonnee *nuage, int *nb_pts, int matrice[MAT_H][MAT_L], int mvt) {
    int i;
    for(i=0; i<4; i++) {
        dino->deplacement->tab_res[i] = 1;
    }
    
    int booleen = collision_decor(dino->deplacement->tab_res, *dino, matrice);
    
    if((dino->deplacement->tab_res[0] == EAU)) {
        supprimer_matrice_dino(dino, matrice);
        dino->pv = 0;
        dino->deplacement->hors_nuage = 1;
        return 1;
    }
    if((dino->pos.y!=nuage[dino->indice_nuage].y) && (!booleen)){
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

// --- Dans SAUT ---
void saut(t_dino *dino, t_coordonnee *nuage, int nb_pts, int matrice[MAT_H][MAT_L], const Uint8 *state) {
    // Déclenchement : On vérifie juste qu'on ne saute pas déjà et que le wait est fini
    if (dino->deplacement->wait == 0 && !dino->deplacement->sautBooleen) {
        if (state[SDL_SCANCODE_UP]) {
            dino->deplacement->v_y = FORCE_SAUT;
            dino->deplacement->sautBooleen = 1;
        }
    }

    if (dino->deplacement->sautBooleen) {
        supprimer_matrice_dino(dino, matrice);
        
        // Gestion des déplacements aériens
        if (state[SDL_SCANCODE_RIGHT] && dino->indice_nuage < nb_pts - 1) 
            dino->indice_nuage++;
        if (state[SDL_SCANCODE_LEFT] && dino->indice_nuage > 0) 
            dino->indice_nuage--;

        // Physique du saut
        dino->deplacement->v_y += GRAVITE;
        dino->pos.y += (int)dino->deplacement->v_y;
        dino->pos.x = nuage[dino->indice_nuage].x;
        dino->deplacement->indice_reel = (float)dino->indice_nuage;

        // Atterrissage
        if (dino->pos.y >= nuage[dino->indice_nuage].y) {
            dino->pos = nuage[dino->indice_nuage];
            dino->deplacement->sautBooleen = 0;
            dino->deplacement->v_y = 0;
            dino->deplacement->wait = 250;
        }
        
        remplir_matrice_dino(dino, dino->pos, matrice);
    }
}



