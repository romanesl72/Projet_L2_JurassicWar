#define STB_IMAGE_IMPLEMENTATION
#include "../lib/stb_image.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../lib/types.h"
#include "../lib/tda_nuage.h"

/*
 * création du nuage 
 */

t_coordonnee *nuage_de_points(int *nb_points,char nomFichier[]) {
    int largeur, hauteur, canaux, r, g, b, sommeY,compte, index, i, j;
    *nb_points=0; //indice du premier élement de nuage

    //Charge l'image (force 3 canaux : RGB)
    unsigned char *img = stbi_load(nomFichier, &largeur, &hauteur, &canaux, 3);
    
    if (img == NULL) {
        printf("Erreur : Impossible de charger l'image. Verifiez le chemin.\n");
        return NULL;
    }
    
    t_coordonnee *nuage=malloc(sizeof(t_coordonnee)*largeur);
    if (nuage == NULL) {
        stbi_image_free(img);
        return NULL;
    }
    
    // Parcourir les colonnes (j) puis les lignes (i)
    for (j = 0; j < largeur; j++){
        sommeY = 0;
        compte = 0;

        for (i = 0; i < hauteur; i++) {
            index = (i * largeur + j) * 3;
            r = img[index];
            g = img[index + 1];
            b = img[index + 2];

            //moyenne des point sur la hauteur pour affiner le résultat
            if (r < 25 && g < 25 && b < 25) {
                sommeY += i;
                compte++;
            }
        }
        if (compte>0){
            // Logique de conversion (avec une petite tolerance) pour reperer la courbe noir

            nuage[(*nb_points)].x=j-15;
            nuage[(*nb_points)++].y=(int)(sommeY/compte)-30; //on enregistre les coordonnées de chaque pixel noir puis on incrémente l'indice
            
        } 
        
    }
    stbi_image_free(img);
    return nuage;
}

/*
 * Test d'existance 
 */

int nuageExiste( t_coordonnee * const nuage ){
    if( nuage == NULL ) return(0);
    return(1) ; 
}

/*
 * fonction de destruction 
 */

int nuageDetruire( t_coordonnee ** nuage) {
    /* Liberation attributs */
    /* Liberation memoire de l'objet */
    free((*nuage)) ;
    /* Pour eviter les pointeurs fous */
    (*nuage) = NULL ;
    return 1;
}

/*
* Affichage du nuage
*/

void afficherNuage(t_coordonnee *nuage, int nb_pts) {
    if (nuage == NULL || nb_pts == 0) {
        printf("Le nuage est vide ou n'existe pas.\n");
        return;
    }

    printf("--- Affichage du Nuage de Points (%d points) ---\n", nb_pts);
    for (int i = 0; i < nb_pts; i++) {
        printf("Point %d : [x = %d, y = %d]\n", i, nuage[i].x, nuage[i].y);
    }
    printf("-----------------------------------------------\n");
}