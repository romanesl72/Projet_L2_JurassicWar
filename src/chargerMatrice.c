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