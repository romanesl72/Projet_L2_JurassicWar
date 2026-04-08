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
 * @file deplacement.h
 * @brief fonctions permettant au dino de se déplacer
 * @author Solène Orieux
 * @date 25/02/2026
 */


/**
 * @fn int horsNuage(t_dino *dino, int nb_pts, int matrice[MAT_H][MAT_L]);
 * @author Solène Orieux
 * @date 11/03/2026
 * @brief renvoie vraie l'indice du dino n'est plus dans le nuage, faux sinon
 * @param dino pointeur sur dino
 * @param nb_pts nombre de points dans le nuage
 * @param matrice représentation du terrain sous forme de matrice
 */

int horsNuage(t_dino *dino, int nb_pts, int matrice[MAT_H][MAT_L]) {

    if(dino->indice_nuage < 0 || dino->indice_nuage >=nb_pts){
        dino->deplacement->hors_nuage = 1;
        return 1;
    }
    
    dino->deplacement->hors_nuage = 0;
    return 0; 
}

/**
 * @fn int replacementNuage(t_dino *dino, int *nb_pts, t_coordonnee **nuage, int nb_nuage, char *nomNuage[], int sens);
 * @author Solène Orieux
 * @date 06/04/2026
 * @brief permet de retrouver la position du dino sur le nuage de points lorsqu'on change de colline
 * @param dino pointeur sur dino
 * @param nb_pts nombre de points dans le nuage
 * @param nuage pointeur de pointeur sur le nuage de points
 * @param matrice représentation du terrain sous forme de matrice
 * @param nb_nuage nombre de nuage présent dans la map
 * @param nomNuage liste des différents noms d'image permettant de créer le nuage
 * @param sens permet de savoir vers quels nuage on se dirige
 */

int replacementNuage(t_dino *dino, int *nb_pts, t_coordonnee **nuage, int nb_nuage, char *nomNuage[], int sens){
    int d1,d2,ecart;
    int ac_id_nuage, ac_indice;
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
            ac_id_nuage=dino->id_nuage ;
            dino->id_nuage = nouvel_id;
            // Positionnement sur le nouveau nuage avec compensation d'écart
            ac_indice=dino->indice_nuage;
            dino->indice_nuage = (sens == 1) ? (0 + ecart) : (*nb_pts - 1 - ecart);
            printf("id=%d\n,indice=%d\n",dino->id_nuage,dino->indice_nuage);
            // Sécurité bornes
            if (dino->indice_nuage < 0) dino->indice_nuage = 0;
            if (dino->indice_nuage >= *nb_pts) dino->indice_nuage = *nb_pts - 1;

            if((*nuage)[dino->indice_nuage].y<(dino->pos.y-TAILLE_DINO)){
                printf("\ndino=%d\nnuage=%d\n",dino->pos.y,(*nuage)[dino->indice_nuage].y);
                dino->id_nuage=ac_id_nuage;
                dino->indice_nuage=ac_indice;
                nuageDetruire(nuage);
                *nuage = nuage_de_points(nb_pts, nomNuage[dino->id_nuage]);;
                return 0;
            }
            return 1;
        }
    }
    return 0;
}

/**
 * @fn int noyade(t_dino *dino, int matrice[MAT_H][MAT_L]);
 * @author Solène Orieux
 * @date 01/04/2026
 * @brief renvoie vraie si le dino s'est noyé, faux sinon
 * @param dino pointeur sur dino
 * @param matrice représentation du terrain sous forme de matrice
 */

int noyade(t_dino *dino, int matrice[MAT_H][MAT_L]){
    // Si le pied touche l'eau (EAU = -1 dans votre enum t_case)
    
    if(matrice[dino->pos.y+30][dino->pos.x+15]==-1) {
        dino->etat = 0; 
        dino->pv = 0;
        dino->deplacement->hors_nuage = 1;
        printf("collision eau\n");
        return 1;
    }
    return 0;
}

/**
 * @fn void tomberNuage(t_dino *dino, t_coordonnee **nuage, char *nomNuage[], int nb_nuage, int *nb_pts, int matrice[MAT_H][MAT_L], int sens);
 * @author Solène Orieux
 * @date 01/04/2026
 * @brief permet de retrouver la position du dino sur le nuage de points lorsqu'on change de colline
 * @param dino pointeur sur dino
 * @param nuage pointeur de pointeur sur le nuage de points
 * @param nomNuage liste des différents noms d'image permettant de créer le nuage
 * @param nb_nuage nombre de nuage présent dans la map
 * @param nb_pts pointeur sur le nombre de points dans le nuage
 * @param matrice représentation du terrain sous forme de matrice
 * @param sens permet de savoir vers quels nuage on se dirige
 */

void tomberNuage(t_dino *dino, t_coordonnee **nuage, char *nomNuage[], int nb_nuage, int *nb_pts, int matrice[MAT_H][MAT_L], int sens) {
    int d1, d2, ecart;
    supprimer_matrice_dino(dino, matrice);

    // Phase 1 : Initialisation de la chute et chargement du nouveau nuage
    if (dino->deplacement->tomber == 1) {
        
        if (replacementNuage(dino, nb_pts, nuage,nb_nuage, nomNuage,sens)) {
            dino->pos.x = (*nuage)[dino->indice_nuage].x;
            dino->deplacement->indice_reel = (float)dino->indice_nuage;
            dino->deplacement->tomber = 2; // Passage à la chute physique
        }
        else {
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

/**
 * @fn void marcher(t_dino *dino, t_coordonnee **nuage, char *nomNuage[], int nb_nuage, int *nb_pts, int matrice[MAT_H][MAT_L], const Uint8 *state, int sens, int booleen);
 * @date 08/04/2026
 * @brief permet au dino de marcher plus ou moins vite en fonction de la pente
 * @param dino pointeur sur dino
 * @param nuage pointeur de pointeur sur le nuage de points
 * @param nomNuage liste des différents noms d'image permettant de créer le nuage
 * @param nb_nuage nombre de nuage présent dans la map
 * @param nb_pts pointeur sur le nombre de points dans le nuage
 * @param matrice représentation du terrain sous forme de matrice
 * @param state pointeur sur l'état du clavier
 * @param sens permet de savoir vers quels nuage on se dirige
 * @param booleen permet de savoir si l'on n'est pas hors nuage
 */
void marcher(t_dino *dino, t_coordonnee **nuage, char *nomNuage[], int nb_nuage, int *nb_pts, int matrice[MAT_H][MAT_L], const Uint8 *state, int sens, int booleen){
    float a, b;
    regression((*nuage)[dino->indice_nuage], *nuage, &a, &b, dino->indice_nuage, *nb_pts);
    
    float pas = VITESSE_BASE * (1.0f + sens*(a * 0.5f));
    dino->deplacement->indice_reel += sens*pas;
    dino->indice_nuage = (int)dino->deplacement->indice_reel;
    noyade(dino,matrice);
    booleen=horsNuage(dino, *nb_pts, matrice);
    if(booleen){
        dino->deplacement->tomber = 1;
        tomberNuage(dino, nuage, nomNuage, nb_nuage, nb_pts, matrice, sens); 
    }
    else {
        supprimer_matrice_dino(dino, matrice);
        dino->pos = (*nuage)[dino->indice_nuage];
        remplir_matrice_dino(dino, dino->pos, matrice);
    }
}

/**
 * @fn void gauche(t_dino *dino, t_coordonnee **nuage, char *nomNuage[], int nb_nuage, int *nb_pts, int matrice[MAT_H][MAT_L],const Uint8 *state);
 * @author Solène Orieux
 * @date 25/02/2026
 * @brief Le dino se dirige à gauche
 * @param dino pointeur sur dino
 * @param nuage pointeur de pointeur sur le nuage de points
 * @param nomNuage liste des différents noms d'image permettant de créer le nuage
 * @param nb_nuage nombre de nuage présent dans la map
 * @param nb_pts pointeur sur le nombre de points dans le nuage
 * @param matrice représentation du terrain sous forme de matrice
 * @param state pointeur sur l'état du clavier
 */

void gauche(t_dino *dino, t_coordonnee **nuage, char *nomNuage[], int nb_nuage, int *nb_pts, int matrice[MAT_H][MAT_L], const Uint8 *state) {
    
    int booleen=horsNuage(dino, *nb_pts, matrice);
    if(dino->etat==0)return;
    if (state[SDL_SCANCODE_LEFT]){
        marcher(dino, nuage, nomNuage, nb_nuage, nb_pts, matrice, state, -1, booleen);
    }
}

/**
 * @fn void droite(t_dino *dino, t_coordonnee **nuage, char *nomNuage[], int nb_nuage, int *nb_pts, int matrice[MAT_H][MAT_L],const Uint8 *state);
 * @author Solène Orieux
 * @date 25/022026
 * @brief Le dino se dirige à droite
 * @param dino pointeur sur dino
 * @param nuage pointeur de pointeur sur le nuage de points
 * @param nomNuage liste des différents noms d'image permettant de créer le nuage
 * @param nb_nuage nombre de nuage présent dans la map
 * @param nb_pts pointeur sur le nombre de points dans le nuage
 * @param matrice représentation du terrain sous forme de matrice
 * @param state pointeur sur l'état du clavier
 */

void droite(t_dino *dino, t_coordonnee **nuage, char *nomNuage[], int nb_nuage, int *nb_pts, int matrice[MAT_H][MAT_L], const Uint8 *state) {
    int booleen=horsNuage(dino, *nb_pts, matrice);
    if(dino->etat==0)return;
    if (state[SDL_SCANCODE_RIGHT]){
        marcher(dino, nuage, nomNuage, nb_nuage, nb_pts, matrice, state, 1, booleen);
    }
}

/**
 * @fn void saut(t_dino *dino, t_coordonnee **nuage, char *nomNuage[], int nb_nuage, int *nb_pts, int matrice[MAT_H][MAT_L], const Uint8 *state);
 * @author Solène Orieux
 * @date 07/03/2026
 * @brief permet au dino de sauter
 * @param dino pointeur sur dino
 * @param nuage pointeur de pointeur sur le nuage de points
 * @param nomNuage liste des différents noms d'image permettant de créer le nuage
 * @param nb_nuage nombre de nuage présent dans la map
 * @param nb_pts pointeur sur le nombre de points dans le nuage
 * @param matrice représentation du terrain sous forme de matrice
 * @param state pointeur sur l'état du clavier
 */

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
        if(!horsNuage(dino,*nb_pts,matrice)){
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
        else if(!collision_decor(dino->deplacement->tab_res,*dino,matrice)){
            dino->deplacement->v_y += GRAVITE;
            dino->pos.y += (int)dino->deplacement->v_y;
            dino->pos.x += sens;
        }
        else{
            if (!noyade(dino,matrice)){
                replacementNuage(dino,nb_pts, nuage, nb_nuage, nomNuage, sens);
                dino->pos.x = (*nuage)[dino->indice_nuage].x;
                dino->deplacement->indice_reel = (float)dino->indice_nuage;
            }
            
        }
        remplir_matrice_dino(dino, dino->pos, matrice);
    }
}
    
/**
 * @fn void deplacement_dino();
 * @author Solène Orieux
 * @date 26/03/2026
 * @brief fonction qui appelle toutes les fonctions de déplacements
 * @param dino pointeur sur dino
 * @param nuage pointeur de pointeur sur le nuage de points
 * @param nomNuage liste des différents noms d'image permettant de créer le nuage
 * @param nb_nuage nombre de nuage présent dans la map
 * @param nb_pts pointeur sur le nombre de points dans le nuage
 * @param matrice représentation du terrain sous forme de matrice
 */

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
    //On vérifie si la position actuelle touche l'eau.
    if (horsNuage(dino, *nb_pts, matrice)) {
        if (dino->etat == 0) { // Si horsNuage a détecté l'eau
            supprimer_matrice_dino(dino, matrice);
        }
    }

    // // 3. LOGIQUE DE MOUVEMENT (Uniquement si vivant)
    if (dino->deplacement->tomber) {
        // Si le dino est en train de tomber (chute libre ou changement de nuage)
        tomberNuage(dino, nuage, nomNuage, nb_nuage, nb_pts, matrice, 0);
    } 
    else {
        //Gestion du saut (prioritaire sur la marche)
        saut(dino, nuage, nomNuage, nb_nuage, nb_pts, matrice, state);

        //Gestion de la marche (uniquement si au sol et pas en train de sauter)
        if (!dino->deplacement->sautBooleen) {
            gauche(dino, nuage, nomNuage, nb_nuage, nb_pts, matrice, state);
            droite(dino, nuage, nomNuage, nb_nuage, nb_pts, matrice, state);
        }
    }
    if (dino->etat == 0) { // Si horsNuage a détecté l'eau
         supprimer_matrice_dino(dino, matrice);
         return; // On arrête tout ici pour éviter que tomberNuage ne le "sauve"
     }

    // // 4. POST-TRAITEMENT
    if (dino->deplacement->wait > 0) {
         dino->deplacement->wait--;
    }

    if(noyade(dino, matrice))printf("dino etat:%d\n",dino->etat);

}
