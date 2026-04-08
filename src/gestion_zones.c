#include "../lib/types.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>



float distance(t_coordonnee p1, t_coordonnee p2) {
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

/**
 * Cette fonction prend le nuage de points (tous les points du sol)
 * et choisit 10 points au hasard à gauche et 10 à droite.
 */
void generer_catalogue_depuis_nuage(t_coordonnee *nuage, int nb_points, t_catalogue_zones *catalogue, int *nb_E1, int *nb_E2, int id_n) {
    int i, r;
    int trop_proche = 0;
    int securite = 0;
    int points_ajoutes_ce_tour = 0;

    // La boucle continue tant qu'on n'a pas 10 de chaque côté
    while (points_ajoutes_ce_tour < 10 && securite < 5000) {
        trop_proche = 0;
        securite++;
        
        r = rand() % nb_points;
        t_coordonnee dino = nuage[r];

        // Vérifier la distance par rapport à CEUX DÉJÀ EXISTANTS
        for(i=0; i < *nb_E1; i++) {
            if(distance(dino, catalogue->zones_E1[i].bas_centre) < 30){
                trop_proche = 1;
            }
        }
        for(i=0; i < *nb_E2; i++) {
            if(distance(dino, catalogue->zones_E2[i].bas_centre) < 30){
                trop_proche = 1;
            }
        }

        if(!trop_proche) {
            // Zone Gauche : on n'ajoute que si on en a moins de 10 ET que le point est à gauche
            if ((dino.x < (LARGEUR_TERRAIN / 3)) && (*nb_E1 < 10)) {
                catalogue->zones_E1[*nb_E1].bas_centre = dino;
                catalogue->zones_E1[*nb_E1].id_equipe = 1;
                catalogue->zones_E1[*nb_E1].indice_nuage = r;
                catalogue->zones_E1[*nb_E1].id_nuage = id_n;
                (*nb_E1)++; // On incrémente le compteur réel du main
                points_ajoutes_ce_tour++;
            }
            // Zone Droite
            else if ((dino.x > (2 * LARGEUR_TERRAIN / 3)) && (*nb_E2 < 10)) {
                catalogue->zones_E2[*nb_E2].bas_centre = dino;
                catalogue->zones_E2[*nb_E2].id_equipe = 2;
                catalogue->zones_E2[*nb_E2].indice_nuage = r;
                catalogue->zones_E2[*nb_E2].id_nuage = id_n;
                (*nb_E2)++;
                points_ajoutes_ce_tour++;
            }
        }
    }
    if(securite >= 5000) printf("Attention : Zones de spawn incomplètes !\n");
}