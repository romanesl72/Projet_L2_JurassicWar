#define STB_IMAGE_IMPLEMENTATION
#include "../lib/stb_image.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    int largeur, hauteur, canaux;

    //Charge l'image (force 3 canaux : RGB)
    unsigned char *img = stbi_load("../img/test1_a.jpg", &largeur, &hauteur, &canaux, 3);
    
    if (img == NULL) {
        printf("Erreur : Impossible de charger l'image. Verifiez le chemin.\n");
        return 1;
    }

    FILE *sortie = fopen("../res/matrice.txt", "w");
    if (!sortie) {
        stbi_image_free(img);
        return 1;
    }

    // Parcourir les lignes (i) puis les colonnes (j)
    for (int i = 0; i < hauteur; i++) {
        for (int j = 0; j < largeur; j++) {
            int index = (i * largeur + j) * 3;
            int r = img[index];
            int g = img[index + 1];
            int b = img[index + 2];

            // Logique de conversion (avec une petite tolerance)
            // Marron
            if (r > 80 && g < 60 && b < 30) {
                fprintf(sortie, "%3d", 1); 
            } 
            // Bleu 
            else if (b > 200 && r < 60) {
                fprintf(sortie, "%3d", -1); 
            } 
            // Blanc / Reste
            else {
                fprintf(sortie, "%3d", 0); 
            }
        }
        // IMPORTANT : Saut de ligne APRES avoir fini une ligne de pixels
        fprintf(sortie, "\n");
    }

    // Nettoyage
    fclose(sortie);
    stbi_image_free(img);
    printf("Succes ! Matrice %dx%d generee dans '../res/matrice.txt'.\n", largeur, hauteur);

    return 0;
}