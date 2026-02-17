#define STB_IMAGE_IMPLEMENTATION
#include "../lib/stb_image.h"
#include <stdio.h>
#include <stdlib.h>
#include "../lib/types.h"
#include "../lib/regression.h"

//utile pour l'affichage de la fenêtre
#include <SDL2/SDL.h>
#define LARGEUR 1300
#define HAUTEUR 700


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

            nuage[(*nb_points)].x=j;
            nuage[(*nb_points)++].y=(int)(sommeY/compte); //on enregistre les coordonnées de chaque pixel noir puis on incrémente l'indice
            
        } 
        
    }
    stbi_image_free(img);
    return nuage;
}

int tracerCourbe( t_coordonnee *nuage, int nbPoints) {
    // permet de visualiser graphiquement le nuage de point
    
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Tracer une courbe avec SDL2",
                                        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                         LARGEUR, HAUTEUR, SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    int running = 1;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }
        // Fond noir
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        // Dessiner la courbe
        for (int i = 0; i < nbPoints - 1; i++) {
            SDL_RenderDrawPoint(renderer, nuage[i].x, nuage[i].y);
        }
        // Afficher le résultat
        SDL_RenderPresent(renderer);

    }
    return 0;
}



