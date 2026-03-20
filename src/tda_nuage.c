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
 * Affectation d'un nuage par copie
 */

/*
 * Affectation d'un nuage par copie
 */

int regroupementNuage(t_coordonnee **nuage_cible, t_coordonnee *nuage_source, int *nb_pts, int nb_pts_source) {
    if (nuage_source == NULL || nb_pts_source <= 0) return 0;

    int d = 0;
    // On calcule l'écart sur l'axe X si le nuage cible n'est pas vide
    if (*nuage_cible != NULL && *nb_pts > 0) {
        d = nuage_source[0].x - (*nuage_cible)[*nb_pts - 1].x;
    }

    // On s'assure que d est positif, sinon on ne rajoute pas de points vides
    int points_ecart = (d > 1) ? (d - 1) : 0; 
    int nouveau_total = (*nb_pts) + points_ecart + nb_pts_source;

    // Déclaration de temp HORS des blocs if/else
    t_coordonnee *temp = realloc(*nuage_cible, sizeof(t_coordonnee) * nouveau_total);
    
    if (temp == NULL) {
        printf("Erreur : Echec de la réallocation mémoire.\n");
        return 0;
    }
    *nuage_cible = temp;

    // 1. Si il y a un trou (d > 0), on peut remplir le vide
    if (points_ecart > 0) {
        for (int i = 0; i < points_ecart; i++) {
            (*nuage_cible)[*nb_pts + i].x = (*nuage_cible)[*nb_pts - 1].x + (i + 1);
            (*nuage_cible)[*nb_pts + i].y = MAT_H;
        }
    }

    // 2. Copier les points de la source à la suite
    for (int i = 0; i < nb_pts_source; i++) {
        // L'index de départ est l'ancien total + l'éventuel écart
        (*nuage_cible)[*nb_pts + points_ecart + i] = nuage_source[i];
    }

    // Mettre à jour le compteur global
    *nb_pts = nouveau_total;

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