#include "../lib/placer_dinos.h"
#include <stdlib.h>
#include <stdio.h>


/** 
 * @file placer_dinos.c
 * @brief Corps des fonctions de placement des dinosaures sur la matrice.
 * @author Romane Saint_Léger
 * @date Crée le 15/02/2026
 * @version 1.3
 */


void remplir_matrice_dino(t_dino *dino, t_coordonnee p_sol, int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN]) {
    int i,j,px,py;

    dino->pos.x = p_sol.x;
    dino->pos.y = p_sol.y; /* On remonte pour que les pieds soient au sol */

    for(i = 0; i < 30; i++) {
        for(j = 0; j < 30; j++) {
            py = dino->pos.y + i;
            px = dino->pos.x + j;
            if (py >= 0 && py < HAUTEUR_TERRAIN && px >= 0 && px < LARGEUR_TERRAIN) {
                dino->memoire[i][j]=matrice[py][px];
                matrice[py][px] = dino->d;
            }
        }
    }
}


void placer_une_equipe(t_joueur *joueur, t_zone_depart points_spawn[10], int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], t_case id_depart) {
    int i;
    for(i = 0; i < joueur->n; i++) {
        /* On attribue un type de dino différent pour tester les IDs (2, 3, 4...) */
        joueur->tab[i].d = id_depart + i; 
        
        joueur->tab[i].id_nuage = points_spawn[i].id_nuage;
        joueur->tab[i].indice_nuage = points_spawn[i].indice_nuage;
        joueur->tab[i].deplacement->indice_reel = (float)points_spawn[i].indice_nuage;

        /* On place le dino sur l'un des 6 points du catalogue */
        remplir_matrice_dino(&(joueur->tab[i]), points_spawn[i].bas_centre, matrice);
    }
}


void afficherDinos(SDL_Renderer* zoneAffichage, t_joueur * equipe){

    int i;
    SDL_Rect rectEquipe;
    rectEquipe.w = TAILLE_DINO;
    rectEquipe.h = TAILLE_DINO;

    for(i = 0; i < equipe->n; i++) {
        rectEquipe.x = equipe->tab[i].pos.x;
        rectEquipe.y = equipe->tab[i].pos.y;
        SDL_RenderCopy(zoneAffichage, equipe->texDinos[i], NULL, &rectEquipe);
    }
}


void afficherDinosAvecJeu(SDL_Renderer* zoneAffichage, t_joueur * equipe){
    if (equipe == NULL || equipe->tab == NULL) return;

    int i;
    SDL_Rect rectEquipe;
    rectEquipe.w = TAILLE_DINO;
    rectEquipe.h = TAILLE_DINO;

    for(i = 0; i < equipe->n; i++) {

        if (equipe->texDinos != NULL && equipe->texDinos[i] != NULL) {
            
            rectEquipe.x = equipe->tab[i].pos.x;
            rectEquipe.y = equipe->tab[i].pos.y + 100; /* Décalage pour le menu HIP */
            
            SDL_RenderCopy(zoneAffichage, equipe->texDinos[i], NULL, &rectEquipe);
        }
    }
}