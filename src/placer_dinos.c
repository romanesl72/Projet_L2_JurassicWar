/**
 * @file placer_dino.c
 * @brief Placement des dinosaures sur la matrice.
 */

#include "../lib/placer_dinos.h"
#include <stdlib.h>

/**
 * @brief Place un dinosaure aléatoirement dans une zone de spawn valide.
 * @param dino Pointeur vers le dino à placer.
 * @param zones Structure contenant les coordonnées des zones possibles.
 * @param matrice La matrice à mettre à jour avec l'ID du dino.
 */


void remplir_matrice_dino(t_dino *dino, t_coordonnee p_sol, int matrice[MAT_H][MAT_L]) {
    int i,j,px,py;
    // On calcule l'ID réel pour la matrice (3, 4, 5...)
    // Si dino->d vaut DINO1 (0), alors l'ID est 3.
    int id_final = dino->d + 3; 

    dino->pos.x = p_sol.x - 9;
    dino->pos.y = p_sol.y - 19; // On remonte pour que les pieds soient au sol

    for(i = 0; i < 20; i++) {
        for(j = 0; j < 20; j++) {
            py = dino->pos.y + i;
            px = dino->pos.x + j;
            if (py >= 0 && py < MAT_H && px >= 0 && px < MAT_L) {
                matrice[py][px] = id_final;
            }
        }
    }
}

void placer_une_equipe(t_joueur *joueur, t_zone_depart points_spawn[10], int matrice[MAT_H][MAT_L], int id_depart) {
    int i;
    for(i = 0; i < joueur->n; i++) {
        // On attribue un type de dino différent pour tester les IDs (0, 1, 2...)
        joueur->tab[i].d = (t_numDino)(id_depart + i); 
        
        // On place le dino sur l'un des 5 points du catalogue
        remplir_matrice_dino(&(joueur->tab[i]), points_spawn[i].bas_centre, matrice);
    }
}