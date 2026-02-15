#include "../lib/types.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>



float distance(t_coordonnee p1, t_coordonnee p2) {
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

/**
 * Cette fonction prend le nuage de points (tous les points du sol)
 * et choisit 5 points au hasard à gauche et 5 à droite.
 */
void generer_catalogue_depuis_nuage(t_coordonnee *nuage, int nb_points, t_catalogue_zones *catalogue) {
    int i, r;
    int trouves_E1 = 0;
    int trouves_E2 = 0;
    int trop_proche = 0;
    int securite = 0;

    while ((trouves_E1 < 5 || trouves_E2 < 5) && securite <1000) {
        trop_proche = 0;
        securite++;
        // On choisit un point au hasard dans le nuage
        r = rand() % nb_points;
        t_coordonnee dino = nuage[r];

        // Vérifier si le point est trop proche d'une zone déjà choisie (min 30px pour un dino de 20px)
        for(i=0; i<trouves_E1; i++) {
            if(distance(dino, catalogue->zones_E1[i].bas_gauche) < 30){
                trop_proche = 1;
            }
        }
        for(i=0; i<trouves_E2; i++) {
            if(distance(dino, catalogue->zones_E2[i].bas_gauche) < 30){
                trop_proche = 1;
            }
        }

        if(!trop_proche) {
            // Si le point est à gauche de la map (Equipe 1)
            if ((dino.x < (MAT_L / 3)) && (trouves_E1 < 5)) {
                catalogue->zones_E1[trouves_E1].bas_gauche = dino;
                catalogue->zones_E1[trouves_E1].id_equipe = 1;
                trouves_E1++;
            }
            // Si le point est à droite de la map (Equipe 2)
            else if ((dino.x > (2 * MAT_L / 3)) && (trouves_E2 < 5)) {
                catalogue->zones_E2[trouves_E2].bas_gauche = dino;
                catalogue->zones_E2[trouves_E2].id_equipe = 2;
                trouves_E2++;
            }
        }
    }
    if(securite >= 10000) printf("Attention : Zones de spawn incomplètes !\n");
}