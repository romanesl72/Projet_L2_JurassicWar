#include "../lib/collision_decor.h"

/** 
 * @file collision_decor.c
 * @brief Corps des fonctions de détection de collision du dino avec la matrice.
 * @author Romane Saint_Léger
 * @date Crée le 07/02/2026
 * @version 1.2
 */


int collision_decor(int tab_res[4], t_dino dino, int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN]) {
    int contact = 0;
    int i;

    for(i=0; i<4; i++){
        tab_res[i] = 0;
    }

    int bas = dino.pos.y + TAILLE_DINO;
    int milieu_x = dino.pos.x + (TAILLE_DINO/ 2);

    /* Vérifications limites matrice */
    if (bas >= HAUTEUR_TERRAIN || milieu_x >= LARGEUR_TERRAIN || milieu_x < 0){
        return 0;
    }

    /* Vérification SUD (Priorité à l'Eau) */
    if (matrice[bas][milieu_x] == EAU) {
        tab_res[0] = -1; /* Code spécial pour la mort */
        contact = 1;
    } else if (matrice[bas][milieu_x] == TERRE) {
        tab_res[0] = 1;
        contact = 1;
    }

    /* Vérification des Côtés et Haut (Terre uniquement) */
    if (matrice[dino.pos.y + (TAILLE_DINO/2)][dino.pos.x] == TERRE) { tab_res[1] = 1; contact = 1; } // OUEST
    if (matrice[dino.pos.y + (TAILLE_DINO/2)][dino.pos.x + TAILLE_DINO] == TERRE) { tab_res[2] = 1; contact = 1; } // EST
    if (matrice[dino.pos.y][milieu_x] == TERRE) { tab_res[3] = 1; contact = 1; } // NORD

    return contact;
}


int collision_cote(t_dino dino, int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN]){
    int i;
    for(i=0;i<TAILLE_DINO;i++){
        if(matrice[dino.pos.y+i][dino.pos.x+TAILLE_DINO]==TERRE)return 1;
    }
    return 0;
}
