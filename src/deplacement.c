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

// --- Dans SAUT ---
void saut(t_dino *dino, t_coordonnee **nuage, char *nomNuage[], int nb_nuage, int *nb_pts, int matrice[MAT_H][MAT_L], const Uint8 *state) {
    int sens;
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
        if (state[SDL_SCANCODE_RIGHT] && dino->indice_nuage < *nb_pts - 1){
            sens=1;
            dino->indice_nuage++;
        }
        if (state[SDL_SCANCODE_LEFT] && dino->indice_nuage > 0){
            sens=-1;
            dino->indice_nuage--;
        }

        if(dino->indice_nuage>=0 && dino->indice_nuage<*nb_pts){
            // Physique du saut
            dino->deplacement->v_y += GRAVITE;
            dino->pos.y += (int)dino->deplacement->v_y;
            dino->pos.x = (*nuage)[dino->indice_nuage].x;
            dino->deplacement->indice_reel = (float)dino->indice_nuage;

            // Atterrissage
            if (dino->pos.y >= (*nuage)[dino->indice_nuage].y) {
                dino->pos = (*nuage)[dino->indice_nuage];
                dino->deplacement->sautBooleen = 0;
                dino->deplacement->v_y = 0;
                dino->deplacement->wait = 250;
            }
        }
        
        else{
            dino->deplacement->v_y += GRAVITE;
            dino->pos.y += (int)dino->deplacement->v_y;
            dino->pos.x+=1;

            if(collision_decor(dino->deplacement->tab_res, *dino, matrice)){
                if((dino->id_nuage<nb_nuage) && (sens==1)){
                    dino->id_nuage+=sens;
                }
                else if((dino->id_nuage>0) && (sens==-1)){
                    dino->id_nuage+=sens;
                }
                t_coordonnee *nv_nuage=NULL;
                nv_nuage=nuage_de_points(nb_pts,nomNuage[dino->id_nuage]);
                if(nuageExiste(nv_nuage)){
                    if(nuageDetruire(nuage)){
                        nuageCopier(nuage,nv_nuage,*nb_pts);
                        nuageDetruire(&nv_nuage);
                    }
                }
                dino->indice_nuage=dino->pos.x-(*nuage)[0].x;
                
            }
        }
        
        remplir_matrice_dino(dino, dino->pos, matrice);
    }
}



void deplacement_dino(t_dino *dino, char *nomNuage[], int nb_nuage, int matrice[MAT_H][MAT_L]){
    // Gérer les entrées clavier pour le mouvement

    int nb_pts;

    t_coordonnee *nuage=NULL;
    nuage=nuage_de_points(&nb_pts,nomNuage[dino->id_nuage]);

    const Uint8 *state = SDL_GetKeyboardState(NULL);

    saut(dino, &nuage, nomNuage, nb_nuage, &nb_pts, matrice,state);

    if ((!dino->deplacement->sautBooleen) && (!dino->deplacement->hors_nuage))
    {
        gauche(dino,nuage,nb_pts,matrice,state);
        droite(dino,nuage,nb_pts,matrice,state);
    }
    
    if (dino->deplacement->wait>0){
        dino->deplacement->wait-=1;
    }
    
    if ((dino->pv<=0) || (nuage==NULL)){
        dino->etat=0;
    }
    nuageDetruire(&nuage);
}