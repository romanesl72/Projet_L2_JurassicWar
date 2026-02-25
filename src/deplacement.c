#define STB_IMAGE_IMPLEMENTATION
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../lib/deplacement.h"


#define VITESSE_BASE 0.15



void gauche(t_dino *dino, t_coordonnee *nuage, int nb_pts) {
    float a, b, angle;
    
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
    dino->indice_nuage = (int)dino->indice_reel;
    dino->pos = nuage[dino->indice_nuage];
}

void droite(t_dino *dino, t_coordonnee *nuage, int nb_pts) {
    float a, b, angle;
    
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
    dino->indice_nuage = (int)dino->indice_reel;
    dino->pos = nuage[dino->indice_nuage];
}

