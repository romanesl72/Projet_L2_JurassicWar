#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Lit le fichier texte pour remplir la matrice en mémoire.
 */


// Aux dimensions de ton fichier .txt

void chargerMatriceDepuisFichier(const char* nomFichier, int matrice[800][1500]) {
    int i, j;
    
    FILE* file = fopen(nomFichier, "r");
    if (!file) {
        perror("Erreur ouverture matrice.txt");
        return;
    }
    for (i = 0; i < 800; i++) {
        for (j = 0; j < 1500; j++) {
            if (fscanf(file, "%d", &matrice[i][j]) != 1) break;
        }
    }
    fclose(file);
}