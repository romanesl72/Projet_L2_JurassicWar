#define STB_IMAGE_IMPLEMENTATION
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../lib/deplacement.h"
#include <SDL2/SDL.h>

void supprimer_matrice_dino(t_dino *dino, int matrice[MAT_H][MAT_L]) {
    /*permet de remetre à jour les anciennes zones comportant un dino*/
    int i,j,px,py;

    for(i = 0; i < 30; i++) {
        for(j = 0; j < 30; j++) {
            py = dino->pos.y + i;
            px = dino->pos.x + j;
            if (py >= 0 && py < MAT_H && px >= 0 && px < MAT_L) {
                matrice[py][px] = dino->memoire[i][j];
                dino->memoire[i][j]=matrice[py][px];
            }
        }
    }
}

int chercherNouveauIndiceNuage(t_dino *dino, t_coordonnee *nuage, int *nb_pts, int matrice[MAT_H][MAT_L]){
    if(dino->id_nuage==0){
        dino->id_nuage=1;
        nuage=nuage_de_points(nb_pts,"../img/test2_c.jpg");
    }
    else{
        dino->id_nuage=0;
        nuage=nuage_de_points(nb_pts,"../img/test1_c.jpg");
    }
    dino->id_nuage=dino->pos.x-nuage[0].x;
    if(nuage[dino->id_nuage].x==dino->pos.x){
        dino->pos=nuage[dino->id_nuage];
        return 1;
    }
    return 0;
}

int horsNuage(t_dino *dino, t_coordonnee *nuage, int nb_pts, int matrice[MAT_H][MAT_L],int mvt){
    int tab_res[4]={1,1,1,1};
    int booleen=collision_decor(tab_res,*dino,matrice);
    if(tab_res[0]==EAU){
        supprimer_matrice_dino(dino,matrice);
        dino->pv=0;
        return 1;
    }
    else if((!booleen) && (dino->indice_nuage<0 || dino->indice_nuage>=nb_pts)){
        if(nuage!=NULL){
            free(nuage);
            nuage=NULL;
        }
        supprimer_matrice_dino(dino,matrice);
        dino->pos.x+=mvt;
        dino->v_y += GRAVITE;
        dino->pos.y += (int)dino->v_y;
        remplir_matrice_dino(dino,dino->pos,matrice);
        return 1;
    }
    else if(booleen && (dino->indice_nuage<0 || dino->indice_nuage>=nb_pts)){
        if(nuage!=NULL){
            free(nuage);
            nuage=NULL;
        }
        supprimer_matrice_dino(dino,matrice);
        if(chercherNouveauIndiceNuage(dino, nuage, &nb_pts, matrice)){
            remplir_matrice_dino(dino,dino->pos,matrice);
        }
    }
    return 0; 
}

void gauche(t_dino *dino, t_coordonnee *nuage, int nb_pts, int matrice[MAT_H][MAT_L],const Uint8 *state) {

    /* Le code utilise une fonction regression pour obtenir la pente locale (a) 
    de la courbe sur laquelle se déplace le dino.
    Si a > 0 : La courbe "descend" (vers la gauche).
    Si a < 0 : La courbe "monte" (vers la gauche).
    Si a = 0 : Le terrain est plat. */

    float a, b, angle;
    int mvt =0;
    int colision[4];
    if (state[SDL_SCANCODE_LEFT]){
        // Calculer la pente locale via la régression
        regression(nuage[dino->indice_nuage], nuage, &a, &b, dino->indice_nuage, nb_pts);
        
        float pas = VITESSE_BASE * (1.0f - (a * 0.5f));
        
        // Mise à jour de l'indice réel
        dino->indice_reel -= pas;
        
        // Mise à jour des coordonnées
        supprimer_matrice_dino(dino, matrice);
        dino->indice_nuage = (int)dino->indice_reel;
        if(!horsNuage(dino, nuage, nb_pts, matrice,mvt)){
            dino->pos=nuage[dino->indice_nuage];
            remplir_matrice_dino(dino, dino->pos, matrice);
        }
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
    int colision[4];
    if (state[SDL_SCANCODE_RIGHT]){    
        // Calculer la pente locale
        regression(nuage[dino->indice_nuage], nuage, &a, &b, dino->indice_nuage, nb_pts);
        
        // Calcul du pas
        float pas = VITESSE_BASE * (1.0f + (a * 0.5f));


        // Mise à jour de l'indice réel
        dino->indice_reel += pas;

        // Mise à jour des coordonnées
        supprimer_matrice_dino(dino, matrice);
        dino->indice_nuage = (int)dino->indice_reel;
        if(!horsNuage(dino, nuage, nb_pts, matrice,mvt)){
            dino->pos=nuage[dino->indice_nuage];
            remplir_matrice_dino(dino, dino->pos, matrice);
        }
    }
}

void saut(t_dino *dino, t_coordonnee *nuage, int nb_pts, int matrice[MAT_H][MAT_L],const Uint8 *state) {
    int tab_res[4];
    int mvt;
    if(dino->wait==0){
        if (state[SDL_SCANCODE_UP] && (dino->pos.x == nuage[dino->indice_nuage].x) && (dino->pos.y == nuage[dino->indice_nuage].y)){
            dino->v_y=FORCE_SAUT;
            dino->sautBooleen=1;
        }
        // Appliquer la vélocité
        if(dino->sautBooleen){

            if (state[SDL_SCANCODE_RIGHT]){
                dino->indice_nuage +=1;
                mvt=1;
                if(!horsNuage(dino, nuage, nb_pts, matrice,mvt)){
                    dino->pos.x=nuage[dino->indice_nuage].x;
                    dino->indice_reel = (float)dino->indice_nuage;
                }
                else{
                    dino->pos.x+=1;
                }
            }

            if (state[SDL_SCANCODE_LEFT]){
                dino->indice_nuage -=1;
                mvt=-1;
                if(!horsNuage(dino, nuage, nb_pts, matrice,mvt)){
                    dino->pos.x=nuage[dino->indice_nuage].x;
                    dino->indice_reel = (float)dino->indice_nuage;
                }
                else{
                    dino->pos.x-=1;
                }
            }

            supprimer_matrice_dino(dino, matrice);
            dino->v_y += GRAVITE;
            dino->pos.y += (int)dino->v_y;

            // Test de collision avec le sol
            if (dino->pos.y >= nuage[dino->indice_nuage].y) {
                dino->pos = nuage[dino->indice_nuage];
                dino->sautBooleen = 0;
                dino->v_y = 0;
                dino->wait=250; //petite pause pour ne pas sauter deux fois d'un coup
            }
            // Réécrire dans la matrice à la nouvelle position
            remplir_matrice_dino(dino, dino->pos, matrice);

            SDL_Delay(16);
        }
    }
    
}



