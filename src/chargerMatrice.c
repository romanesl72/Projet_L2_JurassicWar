#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Lit le fichier texte pour remplir la matrice en mémoire.
 */

 #include "../lib/chargerMatrice.h"

// Aux dimensions de ton fichier .txt

void chargerMatriceDepuisFichier(const char* nomFichier, int matrice[MAT_H][MAT_L]) {
    int i, j;
    
    FILE* file = fopen(nomFichier, "r");
    if (!file) {
        perror("Erreur ouverture matrice.txt");
        return;
    }
    for (i = 0; i < MAT_H; i++) {
        for (j = 0; j < MAT_L; j++) {
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

void supprimer_matrice_dino(t_dino *dino, int matrice[MAT_H][MAT_L]) {
    /*permet de remetre à jour les anciennes zones comportant un dino*/
    int i,j,px,py;

    for(i = 0; i < 30; i++) {
        for(j = 0; j < 30; j++) {
            py = dino->pos.y + i;
            px = dino->pos.x + j;
            if (py >= 0 && py < MAT_H && px >= 0 && px < MAT_L) {
                matrice[py][px] = dino->memoire[i][j];
            }
        }
    }
}