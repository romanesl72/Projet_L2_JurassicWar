#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../lib/deplacement.h"
#include "../lib/fonctionsVerification.h"
#include "../lib/fonctionsStructJoueur.h"
#include "../lib/regression.h"
#include "../lib/tda_nuage.h"
#include "../lib/chargerMatrice.h"
#include "../lib/placer_dinos.h"
#include "../lib/collision_decor.h"

// --- FONCTIONS UTILITAIRES ---

int horsNuage(t_dino *dino, int nb_pts) {
    if(dino->indice_nuage < 0 || dino->indice_nuage >= nb_pts){
        dino->deplacement->hors_nuage = 1;
        return 1;
    }
    dino->deplacement->hors_nuage = 0;
    return 0; 
}

int noyade(t_dino *dino, int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN]){
    if(matrice[dino->pos.y+30][dino->pos.x+15] == -1) {
        dino->etat = 0; 
        dino->pv = 0;
        dino->deplacement->hors_nuage = 1;
        return 1;
    }
    return 0;
}


int replacementNuage(t_dino *dino, int *nb_pts, t_coordonnee **nuage, int nb_nuage, char *nomNuage[], int sens){

    int d1,d2,ecart;
    int ac_id_nuage, ac_indice;
    int nouvel_id = dino->id_nuage + sens;
    if(!horsNuage(dino, *nb_pts))return 1;
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
            ac_id_nuage=dino->id_nuage ;
            dino->id_nuage = nouvel_id;
            // Positionnement sur le nouveau nuage avec compensation d'écart
            ac_indice=dino->indice_nuage;

            dino->indice_nuage = (sens == 1) ? (0 + ecart) : (*nb_pts - 1 - ecart);
            printf("id=%d\n,indice=%d\n",dino->id_nuage,dino->indice_nuage);
            if (dino->indice_nuage < 0) dino->indice_nuage = 0;
            if (dino->indice_nuage >= *nb_pts) dino->indice_nuage = *nb_pts - 1;
            if(((*nuage)[dino->indice_nuage].y<(dino->pos.y-TAILLE_DINO)) || ((*nuage)[0].x>dino->pos.x) || ((*nuage)[(*nb_pts)-1].x<dino->pos.x)){
                printf("\ndino=%d\nnuage=%d\n",dino->pos.y,(*nuage)[dino->indice_nuage].y);
                dino->id_nuage=ac_id_nuage;
                dino->indice_nuage=ac_indice;
                nuageDetruire(nuage);
                *nuage = nuage_de_points(nb_pts, nomNuage[dino->id_nuage]);
                printf("\n-------------pas de nuage--------------\n");
                return 0;
            }
            return 1;
        }
    }
    return 0;
}

void tomberNuage(t_dino *dino, t_coordonnee **nuage, char *nomNuage[], int nb_nuage, int *nb_pts, int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], int sens) {
    supprimer_matrice_dino(dino, matrice);
    if (dino->deplacement->tomber == 1) {
        if (replacementNuage(dino, nb_pts, nuage, nb_nuage, nomNuage, sens)) {
            dino->pos.x = (*nuage)[dino->indice_nuage].x;
            dino->deplacement->indice_reel = (float)dino->indice_nuage;
            dino->deplacement->tomber = 2;
        } else {
            dino->deplacement->tomber = 2;
        }
    }
    else if(dino->deplacement->tomber == 2) {
        if (dino->pos.y < (*nuage)[dino->indice_nuage].y) {
            dino->deplacement->v_y += GRAVITE;
            dino->pos.y += (int)dino->deplacement->v_y;
            noyade(dino, matrice);
        } else {
            if(!noyade(dino, matrice)){
                dino->pos.y = (*nuage)[dino->indice_nuage].y;
                dino->deplacement->v_y = 0;
                dino->deplacement->tomber = 0;
            }
        }
    }
    remplir_matrice_dino(dino, dino->pos, matrice);
}

void marcher(t_dino *dino, t_coordonnee **nuage, char *nomNuage[], int nb_nuage, int *nb_pts, int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], const Uint8 *state, int sens, int booleen){
    float a, b;
    regression((*nuage)[dino->indice_nuage], *nuage, &a, &b, dino->indice_nuage, *nb_pts);
    float pas = VITESSE_BASE * (1.0f + sens*(a * 0.5f));
    dino->deplacement->indice_reel += sens*pas;
    dino->indice_nuage = (int)dino->deplacement->indice_reel;
    if(horsNuage(dino, *nb_pts)){
        supprimer_matrice_dino(dino, matrice);
        dino->pos.x+=sens*10;//pour s'assurer que si il marche dans l'eau il meurt
        dino->pos.y+=10;
        remplir_matrice_dino(dino, dino->pos, matrice);
        if(!noyade(dino, matrice)){
            dino->deplacement->tomber=1;
            tomberNuage( dino, nuage, nomNuage, nb_nuage, nb_pts, matrice, sens);
        }
    } else {
        supprimer_matrice_dino(dino, matrice);
        dino->pos = (*nuage)[dino->indice_nuage];
        remplir_matrice_dino(dino, dino->pos, matrice);
    }
}
// --- LOGIQUE DE DIRECTION ---

void gauche(t_dino *dino, t_coordonnee **nuage, char *nomNuage[], int nb_nuage, int *nb_pts, int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], const Uint8 *state) {
    if (state[SDL_SCANCODE_LEFT]){
        dino->deplacement->sens = GAUCHE; 
        marcher(dino, nuage, nomNuage, nb_nuage, nb_pts, matrice, state, -1, 0);
    }
}

void droite(t_dino *dino, t_coordonnee **nuage, char *nomNuage[], int nb_nuage, int *nb_pts, int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], const Uint8 *state) {
    if (state[SDL_SCANCODE_RIGHT]){
        dino->deplacement->sens = DROITE;
        marcher(dino, nuage, nomNuage, nb_nuage, nb_pts, matrice, state, 1, 0);
    }
}

void saut(t_dino *dino, t_coordonnee **nuage, char *nomNuage[], int nb_nuage, int *nb_pts, int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], const Uint8 *state) {
    int sens = 0; 
    if (dino->deplacement->wait == 0 && !dino->deplacement->sautBooleen) {
        if (state[SDL_SCANCODE_UP]) {
            dino->deplacement->v_y = FORCE_SAUT;
            dino->deplacement->sautBooleen = 1;
        }
    }
    if (dino->deplacement->sautBooleen) {
        supprimer_matrice_dino(dino, matrice);
        if (state[SDL_SCANCODE_RIGHT]) sens = 1, dino->deplacement->sens = DROITE;
        else if (state[SDL_SCANCODE_LEFT]) sens = -1, dino->deplacement->sens = GAUCHE;
        dino->indice_nuage += sens;
        if(!horsNuage(dino, *nb_pts)){
           
            dino->deplacement->v_y += GRAVITE;
            dino->pos.y += (int)dino->deplacement->v_y;
            dino->pos.x = (*nuage)[dino->indice_nuage].x;
            dino->deplacement->indice_reel = (float)dino->indice_nuage;
            if (dino->pos.y >= (*nuage)[dino->indice_nuage].y) {
                dino->pos = (*nuage)[dino->indice_nuage];
                dino->deplacement->sautBooleen = 0;
                dino->deplacement->v_y = 0;
                dino->deplacement->wait = 20;
            }
            remplir_matrice_dino(dino, dino->pos, matrice);
            
        } 
        else {
            if(!replacementNuage(dino, nb_pts, nuage, nb_nuage, nomNuage, sens)){
                if(!noyade(dino, matrice)){
                    dino->deplacement->v_y += GRAVITE;
                    dino->pos.y += (int)dino->deplacement->v_y;
                    dino->pos.x += sens;
                    dino->deplacement->indice_reel = (float)dino->indice_nuage;
                    remplir_matrice_dino(dino, dino->pos, matrice);
                }
                else if(dino->deplacement->tomber==0){
                    dino->deplacement->tomber=1;
                    tomberNuage( dino, nuage, nomNuage, nb_nuage, nb_pts, matrice, sens);
                }
                else{
                    tomberNuage( dino, nuage, nomNuage, nb_nuage, nb_pts, matrice, sens);
                }
                
            }
        }
    }
}

void deplacement_dino(t_dino *dino, t_coordonnee **nuage, char *nomNuage[], int nb_nuage, int *nb_pts, int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], t_joueur * equipe1, t_joueur * equipe2) {
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    
    // 1. On garde précieusement le sens AVANT que les fonctions ne le modifient
    t_cote sensAuDepart = dino->deplacement->sens;

    if (dino->etat == 0 || dino->pv <= 0) return;

    // 2. Calcul des mouvements (Saut, Gauche, Droite)
    if (dino->deplacement->tomber) {
        tomberNuage(dino, nuage, nomNuage, nb_nuage, nb_pts, matrice, 0);
    } else {
        saut(dino, nuage, nomNuage, nb_nuage, nb_pts, matrice, state);
        if (!dino->deplacement->sautBooleen) {
            gauche(dino, nuage, nomNuage, nb_nuage, nb_pts, matrice, state);
            droite(dino, nuage, nomNuage, nb_nuage, nb_pts, matrice, state);
        }
    }

    // 3. LA CORRECTION : 
    // On compare le sens d'origine avec le sens après mouvement.
    // Si c'est différent, on demande le retournement.
    if (sensAuDepart != dino->deplacement->sens) {
        // On envoie :
        // - dino->deplacement->sens (le nouveau sens vers lequel on veut aller)
        // - &sensAuDepart (l'adresse de la variable contenant l'ancienne direction)
        retournerDino(equipe1, equipe2, dino->d, dino->deplacement->sens, &sensAuDepart);
    }

    if (dino->deplacement->wait > 0) dino->deplacement->wait--;
}