#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../lib/types.h"
#include "../lib/regression.h"

//utile pour l'affichage de la fenêtre
#include <SDL2/SDL.h>
#define LARGEUR 1300
#define HAUTEUR 700

/**
 * @file regression.h
 * @brief fonctions permettant de calculer la pente d'un points donné
 * @author Solène Orieux
 * @date 24/03/2026
 */

/**
 * @fn void moyenne(t_coordonnee *T, int n, float *x, float *y);
 * @author Solène Orieux
 * @date 24/03/2026
 * @brief Calcule la moyenne des coordonnées X et Y d'un échantillon de points.
 * @param T Tableau de coordonnées (échantillon).
 * @param n Nombre de points dans l'échantillon.
 * @param x Pointeur pour stocker la moyenne des abscisses (X) calculée.
 * @param y Pointeur pour stocker la moyenne des ordonnées (Y) calculée.
 */
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

/**
 * @fn void calculPente(t_coordonnee *T, int n, float *a, float x, float y);
 * @author Solène Orieux
 * @date 24/03/2026
 * @brief Calcule le coefficient directeur par la méthode des moindres carrées* 
 * @param T Tableau de coordonnées (échantillon).
 * @param n Nombre de points dans l'échantillon.
 * @param a Pointeur pour stocker le coefficient directeur résultant.
 * @param x Moyenne des abscisses (X) de l'échantillon.
 * @param y Moyenne des ordonnées (Y) de l'échantillon.
 */

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

/**
 * @fn void regression(t_coordonnee dino, t_coordonnee * nuage, float *a, float *b, int indice, int nb_point);
 * @author Solène Orieux
 * @date 24/03/2026
 * @brief calcul la régression d'un échantillon de 10 points
 * @param dino structure du dinosaure
 * @param nuage pointeur sur le nuage de points
 * @param a coefficient directeur
 * @param b ordonnée à l'origine
 * @param indice indice du point dont on veut calculer la pente
 * @param nb_points nombre de points sur le nuage
 */

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

/**
 * @fn int tracerCourbe( t_coordonnee *nuage, int nbPoints);
 * @author Solène Orieux
 * @date 24/03/2026
 * @brief permet d'afficher la pente
 * @param nuage pointeur sur le nuage de points
 * @param nbPoints nombre de points sur le nuage
 */

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



