#include "../lib/chargerMatrice.h"
#include "../lib/types.h"
#include "../lib/tda_nuage.h"
#include "../lib/fonctionsVerification.h"
#include "../lib/placer_dinos.h"
#include "../lib/gestion_zones.h"
#include "../lib/fonctionsMenuHIP.h"
#include "../lib/fonctionsStructJoueur.h"

#include <stdio.h>
#include <time.h>
#include <SDL2/SDL_ttf.h>

/** 
 * @file testAffichageMenuHIP.c
 * @brief Corps d'une fonction de test sur l'affichage du menu de l'inventaire et des points de vie restants des dinos.
 * @author Romane Saint_Léger
 * @date Crée le 01/04/2026
 * @version 1.3
 */

/**
 * @brief Test de l'affichage des dinosaures sur le terrain
 * @param argc nombre d'arguments de la ligne de commande
 * @param argv tableau des arguments
 * @return 0 si tout s'est bien passé et 1 sinon
 * @version 2.0
 */

int main(int argc, char * argv[]){

    /* ---- 1. Initialisation ---- */
    if (!initialisationCorrecte()) return 1;
    srand(time(NULL));
    
    SDL_Window *fenetre = NULL;
    SDL_Renderer *rendu = NULL;
    TTF_Font *police = NULL;

    creerFenetre(&fenetre, "Jurassic War - HIP Mode", LARGEUR_TERRAIN, HAUTEUR_FEN_JEU_HIP);
    rendu = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_SOFTWARE);
    initialiserPolice(&police, "../pde/arial.ttf", 16);
    
    /* ---- 2. Chargement de la Map et Placement ---- */
    int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN];
    int nb_pts, w, h;
    int trouves_E1 = 0, trouves_E2 = 0;
    t_coordonnee *nuages_stockes[5];
    t_catalogue_zones catalogue;
    t_joueur equipe1, equipe2;

    chargerMatriceDepuisFichier("../res/matrice.txt", matrice);
    
    // Récupération des zones pour le placement (Placement Réel)
    nuages_stockes[1] = nuage_de_points(&nb_pts, "../img/test1_c.jpg");
    generer_catalogue_depuis_nuage(nuages_stockes[1], nb_pts, &catalogue, &trouves_E1, &trouves_E2, 1);
    nuages_stockes[2] = nuage_de_points(&nb_pts, "../img/test2_c.jpg");
    generer_catalogue_depuis_nuage(nuages_stockes[2], nb_pts, &catalogue, &trouves_E1, &trouves_E2, 2);

    initialiserContenuJoueur(&equipe1);
    initialiserContenuJoueur(&equipe2);

    printf("Ok\n");
    // Placement réel sur la matrice (C'est ce placement qui compte !)
    placer_une_equipe(&equipe1, catalogue.zones_E1, matrice, D1);
    placer_une_equipe(&equipe2, catalogue.zones_E2, matrice, D4);
    
    // Initialisation des PV après le placement
    for(int i=0; i<3; i++) { 
        equipe1.tab[i].pv = 100 - (i*20); 
        equipe2.tab[i].pv = 100; 
    }

    /* ---- 3. Chargement des Textures ---- */
    SDL_Texture *texMap = NULL;
    SDL_Texture *texDinos[6]; // Tableau pour les 6 types de dinos
    SDL_Texture *texObjets[7] = {NULL};

    char *nomsObjets[7] = {
        "../img/img_arc.png", 
        "../img/img_arbalete.png", 
        "../img/img_bombe.png", 
        "../img/img_fusil.png", 
        "../img/img_revolver.png", 
        "../img/img_potion.png", 
        "../img/img_grappin.png"
    };

    for(int i = 0; i < 7; i++) {
        chargerImage(rendu, &texObjets[i], nomsObjets[i], &w, &h);
        if(texObjets[i] == NULL) {
            printf("Attention : Impossible de charger %s\n", nomsObjets[i]);
        }
    }
    chargerImage(rendu, &texMap, "../img/test1_b.jpg", &w, &h);
    for(int k = 0; k < 6; k++) {
        chargerImage(rendu, &texDinos[k], "../img/dinoTransparent.png", &w, &h);
    }

    int enCours = 1;
    SDL_Event e;

    /* ---- 4. Boucle de Rendu ---- */
    while(enCours) {
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT) enCours = 0;
            
            
        }

        SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255);
        SDL_RenderClear(rendu);

        /* --- SECTION HAUT : LE HIP --- */
        afficherInventaire(rendu, texObjets, 7);
        afficherMenuPVDinos(rendu, police, equipe1, equipe2);

        /* --- SECTION BAS : LE JEU --- */
        SDL_Rect rectJeu = {0, HAUTEUR_HIP, LARGEUR_TERRAIN, HAUTEUR_TERRAIN};
        SDL_RenderCopy(rendu, texMap, NULL, &rectJeu);

        // Affichage de l'Équipe 1
        for(int i=0; i<equipe1.n; i++) {
            SDL_Rect r1 = {equipe1.tab[i].pos.x, equipe1.tab[i].pos.y + HAUTEUR_HIP, 30, 30};
            // On utilise l'ID du dino pour choisir la bonne texture
            SDL_RenderCopy(rendu, texDinos[equipe1.tab[i].d - D1], NULL, &r1);
        }

        // Affichage de l'Équipe 2
        for(int i=0; i<equipe2.n; i++) {
            SDL_Rect r2 = {equipe2.tab[i].pos.x, equipe2.tab[i].pos.y + HAUTEUR_HIP, 30, 30};
            SDL_RenderCopy(rendu, texDinos[equipe2.tab[i].d - D1], NULL, &r2);
        }

        SDL_RenderPresent(rendu);
        SDL_Delay(16);
    }

    /* ---- 5. Nettoyage ---- */

    detruireContenuJoueur(&equipe1);
    detruireContenuJoueur(&equipe2);
    
    for(int k=0; k<6; k++) SDL_DestroyTexture(texDinos[k]);
    TTF_CloseFont(police);
    SDL_DestroyTexture(texMap);
    SDL_DestroyRenderer(rendu);
    SDL_DestroyWindow(fenetre);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}