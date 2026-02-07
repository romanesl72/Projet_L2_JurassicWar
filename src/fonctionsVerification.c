#include <stdio.h>

#include "../lib/fonctionsVerification.h"

/* Fonction initialisationCorrecte
 * Rôle : initialiser SDL2, SDL2_image et SDL_ttf
 * Paramètres : aucun
 * Valeur de retour : 1 si tout c'est bien passé et 0 sinon 
*/
/*
int initialisationCorrecte() {

    // Initialisation de SDL

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Erreur lors de l'initialisation de SDL : %s \n", SDL_GetError());
        return 0;
    }

    // Initialisation de SDL_image

    if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) && (IMG_INIT_PNG | IMG_INIT_JPG)){
        printf("Erreur lors de l'initialisation de SDL_image : %s \n", IMG_GetError());
        return 0;
    }

    // Initialisation de SDL_ttf

    if (TTF_Init() != 0) {
        printf("Erreur lors de l'initialisation de SDL_ttf : %s \n", TTF_GetError());
        return 0;
    }

    return 1;

}*/

/* Fonction chargerImage
 * Rôle : charge une image comme une texture
 * Paramètres : un pointeur sur la zone d'affichage, un pointeur sur un pointeur de l'image, le nom du fichier de l'image
 * et deux pointeurs sur la longueur et la hauteur de l'image
 * Valeur de retour : aucune, mais imgLargeur contient la largeur de l'image et imgHauteur sa hauteur
*/
/*
void chargerImage(SDL_Renderer *zoneAffichage, SDL_Texture **img, char *nomFichier, int *imgLargeur, int *imgHauteur) {
    
    *img = IMG_LoadTexture(zoneAffichage, nomFichier);

    if(!*img) {
        printf("Erreur lors du chargement de l'image : %s \n", IMG_GetError());
    }
	
	// Récupérer la taille de l'image
    SDL_QueryTexture(*img, NULL, NULL, imgLargeur, imgHauteur);

}*/

/* Fonction creerFenetre
 * Rôle : créer une fenêtre centrée sur l'écran
 * Paramètres : un pointeur sur un pointeur de la fenêtre, le nom de la fenêtre, sa longueur et sa hauteur
 * Valeur de retour : aucune
*/
/*
void creerFenetre(SDL_Window **fenetre, char* nomFenetre, int fenLargeur, int fenHauteur) {

        *fenetre = SDL_CreateWindow(nomFenetre, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, fenLargeur, fenHauteur, 0);

        if (!*fenetre) {
            printf("Erreur lors de la création de la fenêtre : %s \n", SDL_GetError());
        }
}*/

/* Fonction initialiserPolice
 * Rôle : charge une police
 * Paramètres : un pointeur sur un pointeur de la police, le nom du fichier contenant la police et la taille de la police
 * Valeur de retour : aucune
*/
/*
void initialiserPolice(TTF_Font **police, char *nomFichier, int taillePolice) {
    
    *police = TTF_OpenFont(nomFichier, taillePolice);

    if(!*police) {
        printf("Erreur lors du chargement de la police : %s \n", TTF_GetError());
    }

}*/