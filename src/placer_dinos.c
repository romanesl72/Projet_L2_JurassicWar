/**
 * @file placer_dino.c
 * @brief Placement des dinosaures sur la matrice.
 */

#include "../lib/gestion_placement.h"
#include <stdlib.h>

/**
 * @brief Place un dinosaure aléatoirement dans une zone de spawn valide.
 * @param dino Pointeur vers le dino à placer.
 * @param zones Structure contenant les coordonnées des zones possibles.
 * @param matrice La matrice à mettre à jour avec l'ID du dino.
 */
void placer_dino(t_dino *dino, t_zone_depart zone, int matrice[MAT_H][MAT_L]) {
    int i,j;
    
    // Sécurité : vérifier si la zone a des points
    if (zone.nb_points <= 0){
        return;
    }

    int r = rand() % zone.nb_points;
    
    dino->pos.x = zone.points[r].x;
    dino->pos.y = zone.points[r].y;

    int val_dino = dino->d + 3; 
    
    for(i = 0; i < dino->hauteur; i++) {
        for(j = 0; j < dino->largeur; j++) {
            // Vérification des limites de la matrice
            int py = dino->pos.y + i;
            int px = dino->pos.x + j;
            
            if (py >= 0 && py < MAT_H && px >= 0 && px < MAT_L) {
                matrice[py][px] = val_dino;
            }
        }
    }
}

void placer_equipe(t_joueur *joueur, t_zone_depart catalogue[5], int matrice[MAT_H][MAT_L]) {
    int indices_utilises[5] = {0}; // Pour éviter de placer deux dinos dans la même zone
    int dinos_places = 0;

    while (dinos_places < joueur->n) { // joueur->n vaut 3 selon ton projet
        int r = rand() % 5; // On choisit une zone parmi les 5 du catalogue
        
        if (indices_utilises[r] == 0) {
            // On appelle ta fonction initiale
            placer_dino(&(joueur->tab[dinos_places]), catalogue[r], matrice);
            
            indices_utilises[r] = 1;
            dinos_places++;
        }
    }
}