#define STB_IMAGE_IMPLEMENTATION
#include "../lib/stb_image.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

            nuage[(*nb_points)].x=j-15;
            nuage[(*nb_points)++].y=(int)(sommeY/compte)-30; //on enregistre les coordonnées de chaque pixel noir puis on incrémente l'indice
            
        } 
        
    }
    stbi_image_free(img);
    return nuage;
}

void moyenne(t_coordonnee *T, int n, float *x, float *y){
    (*x)=0.0, (*y)=0.0;
    int i;
    for (i=0; i<n; i++){
        *x+=T[i].x;
        *y+=T[i].y;
    }
    (*x)/=n;
    (*y)/=n;
}

void calculPente(t_coordonnee *T, int n, float *a, float x, float y){
    *a=0;
    int i;
    int d=0;//dénominateur
    for(i=0;i<n;i++){
        (*a)+=(T[i].x-x)*(T[i].y-y);
        d+=pow(T[i].x-x,2);
    }
    (*a)/=d;
}

void regression(t_coordonnee dino, t_coordonnee * nuage, float *a, float *b, int indice, int nb_point){
    t_coordonnee tab[10];
    int i,n=10;
    float m_x,m_y;
    int depart=indice-5;

    if(depart<0)depart=0;
    if((depart+n)>nb_point)depart=nb_point-n;
    
    for ( i=0; i<n ; i++){
        tab[i] = nuage[depart + i];
    }

    moyenne(tab,n,&m_x,&m_y);
    calculPente(tab, n, a, m_x, m_y);
    *b=m_y-((*a)*m_x);
}

int tracerCourbe( t_coordonnee *nuage, int nbPoints) {
     float a,b;
     int i=0,j=0;
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

        for (i = 0; i < nbPoints - 1; i++) {
            SDL_RenderDrawPoint(renderer, nuage[i].x, nuage[i].y);
        }


        regression(nuage[j], nuage, &a, &b, j, nbPoints);
        ++j;
        // Calcul des extrémités
        int x_debut = nuage[0].x;
        int y_debut = (int)(a * x_debut + b);
        
        int x_fin = nuage[nbPoints - 1].x;
        int y_fin = (int)(a * x_fin + b);

        // Dessiner la droite
        SDL_RenderDrawLine(renderer, x_debut, y_debut, x_fin, y_fin);       
        // Afficher le résultat
        SDL_RenderPresent(renderer);
        
    }
    return 0;
}



