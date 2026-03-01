#define STB_IMAGE_IMPLEMENTATION
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../lib/deplacement.h"

#define VITESSE_BASE 0.15

void supprimer_matrice_dino(t_dino *dino, t_coordonnee p_sol, int matrice[MAT_H][MAT_L]) {
    /*permet de remetre à jour les anciennes zones comportant un dino*/
    int i,j,px,py;

    dino->pos.x = p_sol.x - 15;
    dino->pos.y = p_sol.y - 30; // On remonte pour que les pieds soient au sol

    for(i = 0; i < 30; i++) {
        for(j = 0; j < 30; j++) {
            py = dino->pos.y + i;
            px = dino->pos.x + j;
            if (py >= 0 && py < MAT_H && px >= 0 && px < MAT_L) {
                dino->memoire[i][j]=matrice[py][px];
                matrice[py][px] = dino->memoire[i][j];
            }
        }
    }
}

void gauche(t_dino *dino, t_coordonnee *nuage, int nb_pts, int matrice[MAT_H][MAT_L]) {
    float a, b, angle;
    int colision[4];
    
    // Calculer la pente locale via la régression
    regression(nuage[dino->indice_nuage], nuage, &a, &b, dino->indice_nuage, nb_pts);
    
    // Calculer l'angle en radians
    angle = atanf(a);

    /* Calcul du déplacement horizontal :
       Pour que la vitesse soit constante sur la courbe (vitesse curviligne),
       on divise la vitesse de base par le cosinus de l'angle.
       Si on veut simplement avancer de façon constante en X :
    */
    float pas = VITESSE_BASE * (1.0f - (a * 0.5f)); 

    // Mise à jour de l'indice réel
    dino->indice_reel -= pas;

    // Sécurité : Empêcher de sortir du tableau (bord gauche)
    if (dino->indice_reel < 0) {
        dino->indice_reel = 0;
    }
    if (dino->indice_reel >=nb_pts) {
        dino->indice_reel = nb_pts-1;
    }
    
    // Mise à jour des coordonnées
    supprimer_matrice_dino(dino, dino->pos, matrice);
    dino->indice_nuage = (int)dino->indice_reel;
    dino->pos=nuage[dino->indice_nuage];
    remplir_matrice_dino(dino, dino->pos, matrice);
    
    
}

void droite(t_dino *dino, t_coordonnee *nuage, int nb_pts, int matrice[MAT_H][MAT_L]) {
    float a, b, angle;
    int colision[4];
    
    // Calculer la pente locale
    regression(nuage[dino->indice_nuage], nuage, &a, &b, dino->indice_nuage, nb_pts);
    
    // Calculer l'angle
    angle = atanf(a);

    // Calcul du pas
    float pas = VITESSE_BASE * (1.0f + (a * 0.5f));

    // Mise à jour de l'indice réel
    dino->indice_reel += pas;

    // Sécurité : Empêcher de sortir du tableau (bord droit)
    // On s'arrête à nb_pts - 1 pour éviter un accès mémoire invalide
    if (dino->indice_reel >= nb_pts) {
        dino->indice_reel = (float)(nb_pts - 1);
    }
    
    if (dino->indice_reel >=nb_pts) {
        dino->indice_reel = nb_pts-1;
    }
    
    // Mise à jour des coordonnées
    supprimer_matrice_dino(dino, dino->pos, matrice);
    dino->indice_nuage = (int)dino->indice_reel;
    dino->pos=nuage[dino->indice_nuage];
    remplir_matrice_dino(dino, dino->pos, matrice);

}

