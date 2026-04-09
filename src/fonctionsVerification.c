#include "../lib/fonctionsVerification.h"
#include <stdio.h>

/**
 * @file fonctionsVerification.c
 * @brief Corps des fonctions pour initialiser différents objets SDL.
 * @author Hannah Sergent
 * @date Crée le 27/01/2026
 * @version 1.3
 */

int initialisationCorrecte() {

    /* Initialisation de SDL */

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Erreur lors de l'initialisation de SDL : %s \n", SDL_GetError());
        return 0;
    }

    /* Initialisation de SDL_image */

    if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) && (IMG_INIT_PNG | IMG_INIT_JPG)){
        printf("Erreur lors de l'initialisation de SDL_image : %s \n", IMG_GetError());
        return 0;
    }

    /* Initialisation de SDL_ttf */

    if (TTF_Init() != 0) {
        printf("Erreur lors de l'initialisation de SDL_ttf : %s \n", TTF_GetError());
        return 0;
    }

    return 1;

}

void chargerImage(SDL_Renderer *zoneAffichage, SDL_Texture **img, char *nomFichier, int *imgLargeur, int *imgHauteur) {
    
    *img = IMG_LoadTexture(zoneAffichage, nomFichier);

    if(!*img) {
        printf("Erreur lors du chargement de l'image : %s \n", IMG_GetError());
    }
	
	/* Récupérer la taille de l'image */
    SDL_QueryTexture(*img, NULL, NULL, imgLargeur, imgHauteur);

}

void chargerImageSansTaille(SDL_Renderer *zoneAffichage, SDL_Texture **img, char *nomFichier) {
    
    *img = IMG_LoadTexture(zoneAffichage, nomFichier);

    if(!*img) {
        printf("Erreur lors du chargement de l'image : %s \n", IMG_GetError());
    }
    
}

void creerFenetre(SDL_Window **fenetre, char* nomFenetre, int fenLargeur, int fenHauteur) {

        *fenetre = SDL_CreateWindow(nomFenetre, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, fenLargeur, fenHauteur, 0);

        if (!*fenetre) {
            printf("Erreur lors de la création de la fenêtre : %s \n", SDL_GetError());
        }
}

void initialiserPolice(TTF_Font **police, char *nomFichier, int taillePolice) {
    
    *police = TTF_OpenFont(nomFichier, taillePolice);

    if(!*police) {
        printf("Erreur lors du chargement de la police : %s \n", TTF_GetError());
    }

}