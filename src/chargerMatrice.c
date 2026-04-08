#include <stdio.h>
#include <stdlib.h>

/** 
 * @file chargerMatrice.c
 * @brief Corps des fonctions pour charger une matrice depuis un fichier.
 * @author Romane Saint_Léger Hannah Sergent
 * @date Crée le 07/02/2026
 */

#include "../lib/chargerMatrice.h"

void chargerMatriceDepuisFichier(const char* nomFichier, int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN]) {
    int i, j;
    
    FILE* file = fopen(nomFichier, "r");
    if (!file) {
        perror("Erreur ouverture matrice.txt");
        return;
    }
    for (i = 0; i < HAUTEUR_TERRAIN; i++) {
        for (j = 0; j < LARGEUR_TERRAIN; j++) {
            fscanf(file, "%d", &matrice[i][j]);
        }
    }
    fclose(file);
}


int initialiserMatrice(t_case (**matriceTerrain)[LARGEUR_TERRAIN]){

    *matriceTerrain = malloc(sizeof(t_case) * HAUTEUR_TERRAIN * LARGEUR_TERRAIN);

    if (!*matriceTerrain){
        printf("Erreur d'allocation de la matrice.\n");
        return 0;
    }

    chargerMatriceDepuisFichier("../res/matrice.txt", *matriceTerrain);

    return 1;
}



void detruireMatrice(t_case (**matriceTerrain)[LARGEUR_TERRAIN]){
    free(*matriceTerrain);
    *matriceTerrain = NULL;
}



void supprimer_matrice_dino(t_dino *dino, int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN]) {
    /*permet de remetre à jour les anciennes zones comportant un dino*/
    int i,j,px,py;
    for(i = 0; i < 30; i++) {
        for(j = 0; j < 30; j++) {
            py = dino->pos.y + i;
            px = dino->pos.x + j;
            if (py >= 0 && py < HAUTEUR_TERRAIN && px >= 0 && px < LARGEUR_TERRAIN) {
                matrice[py][px] = dino->memoire[i][j];
            }
        }
    }
}