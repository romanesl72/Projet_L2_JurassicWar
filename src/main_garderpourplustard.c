/**
 * @file main2.c
 * @brief Point d'entrée principal du jeu avec gestion du temps.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../lib/types.h"
#include "../lib/fonctionsVerification.h"
#include "../lib/collision_decor.h"
#include "../lib/gestion_placement.h"
#include "../lib/chargerMatrice.h"

int main(int argc, char * argv[]) {
    // Initialisation de l'aléatoire
    srand(time(NULL));

    if (!initialisationCorrecte()){
        return 1;
    }

    static int matrice[MAT_H][MAT_L];
    SDL_Window *fenetre = NULL;
    SDL_Renderer *renderer = NULL;

    creerFenetre(&fenetre, "Jurassic War", 1050, 650);
    renderer = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);

    // 1. Initialisation
    chargerMatriceDepuisFichier("../res/matrice.txt", matrice);
    
    // Initialisation des catalogues (Exemple : 5 zones à gauche, 5 à droite)
    t_zone_depart catalogue_equipe1[5] = {
        {{{100, 400}}, 1, "Z1"}, {{{200, 400}}, 1, "Z2"}, {{{300, 400}}, 1, "Z3"}, 
        {{{400, 400}}, 1, "Z4"}, {{{500, 400}}, 1, "Z5"}
    };


    // Initialisation du joueur (équipe de 3 dinos)
    t_dino tab_dinos[3] = {
        {DINO1, 1, 100, {0,0}, 16, 16},
        {DINO2, 1, 100, {0,0}, 16, 16},
        {DINO3, 1, 100, {0,0}, 16, 16}
    };
    t_joueur joueur1 = {tab_dinos, 3};

    // Placement de toute l'équipe d'un coup
    placer_equipe(&joueur1, catalogue_equipe1, matrice);

    int enCours = 1;
    SDL_Event evenement;

    while(enCours) {
        while (SDL_PollEvent(&evenement)) {
            if (evenement.type == SDL_QUIT) enCours = 0;
            
            // Petit test de mouvement pour tester tes collisions
            if (evenement.type == SDL_KEYDOWN) {
                int res[4];
                collision_decor(res, joueur1.tab[0], matrice);
                if (evenement.key.keysym.sym == SDLK_LEFT && res[1] == 0){
                    joueur1.tab[0].pos.x -= 5;
                }
                if (evenement.key.keysym.sym == SDLK_RIGHT && res[2] == 0){
                    joueur1.tab[0].pos.x += 5;
                }
            }
        }

        // 2. DESSIN DU JEU
        SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255); // Ciel
        SDL_RenderClear(renderer);

        // On parcourt la matrice (optimisé : on dessine point par point ou par rectangles)
        for(int y=0; y < 650; y+=2) { // Step de 2 pour la performance
            for(int x=0; x < 1050; x+=2) {
                if(matrice[y][x] == 1) SDL_SetRenderDrawColor(renderer, 100, 50, 0, 255); // Terre
                else if(matrice[y][x] == -1) SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Eau
                else continue;
                SDL_RenderDrawPoint(renderer, x, y);
            }
        }

        // Dessiner le Dino (Carré rouge pour le moment)
        SDL_Rect rDino = {joueur1.tab[0].pos.x, joueur1.tab[0].pos.y, joueur1.tab[0].largeur, joueur1.tab[0].hauteur};
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &rDino);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(fenetre);
    SDL_Quit();
    return 0;
}