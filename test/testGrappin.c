#include "../lib/chargerMatrice.h"
#include "../lib/types.h"
#include "../lib/grappin.h"
#include "../lib/tda_file.h"
#include "../lib/tda_nuage.h"
#include "../lib/fonctionsVerification.h"
#include "../lib/placer_dinos.h"
#include "../lib/gestion_zones.h"
#include "../lib/fonctionsMenuHIP.h"
#include "../lib/fonctionsStructJoueur.h"
#include "../lib/fonctionsAffichage.h"
#include "../lib/fonctionsPageJeu.h"

#include <stdio.h>
#include <time.h>
#include <SDL2/SDL_ttf.h>

/** 
 * @file test_deplacement.c
 * @brief Test des fonctions crées dans le fichier grapin.c
 * @author Solène Orieux
 * @date Crée le 03/04/2026
 */

/**
 * @brief Déplacer le dinosaure à l'aide d'un grappin.
 * @return 0 si tout s'est bien passé et 1 sinon
 * @version 1
 */

int main(int argc, char * argv[]){

    /* ---- 1. Initialisation ---- */
    if (!initialisationCorrecte()) return 1;
    srand(time(NULL));

    SDL_Window *fenetre = NULL;
    SDL_Renderer *rendu = NULL;
    TTF_Font *police = NULL;
    const Uint8 *state=NULL;

    creerFenetre(&fenetre, "Jurassic War - HIP Mode", LARGEUR_TERRAIN, HAUTEUR_TERRAIN);
    rendu = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_SOFTWARE);
    initialiserPolice(&police, "../pde/arial.ttf", 16);

    /* ---- 2. Chargement de la Map et Placement ---- */
    int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN];
    int nb_pts, w, h, i;
    int trouves_E1 = 0, trouves_E2 = 0;
    t_coordonnee *nuages_stockes[5];
    t_catalogue_zones catalogue;
    t_tour gestionTours = {1, 1, D1, D6}; // Tour 1, Equipe 1, Dino D1

    char *nomNuage[2] = {"../img/test1_c.jpg", "../img/test2_c.jpg"};
    t_coordonnee *nuage = NULL;
    t_dino *dinoActuel = NULL;

    chargerMatriceDepuisFichier("../res/matrice.txt", matrice);
    
    // Récupération des zones pour le placement (Placement Réel)
    nuages_stockes[0] = nuage_de_points(&nb_pts, nomNuage[0]);
    generer_catalogue_depuis_nuage(nuages_stockes[0], nb_pts, &catalogue, &trouves_E1, &trouves_E2, 1);
    nuageDetruire(&nuages_stockes[0]);

    nuages_stockes[1] = nuage_de_points(&nb_pts, nomNuage[1]);
    generer_catalogue_depuis_nuage(nuages_stockes[1], nb_pts, &catalogue, &trouves_E1, &trouves_E2, 2);
    nuageDetruire(&nuages_stockes[1]);

    t_joueur equipe1, equipe2;

    /* ---- 4. Initialisation des Equipes ---- */
    initialiserEquipes(&equipe1, &equipe2, &catalogue, matrice, rendu);

    afficherContenuJoueur(equipe1, "equipe1");
    afficherContenuJoueur(equipe2, "equipe2");

    
    // Initialisation des PV après le placement
    for(int i=0; i<3; i++) { 
        equipe1.tab[i].pv = 100 - (i*20); 
        equipe2.tab[i].pv = 100; 
    }
    /* ---- 3. Chargement des Textures ---- */
    SDL_Texture *texMap = NULL;
    SDL_Texture *texDinos[6]={NULL}; // Tableau pour les 6 types de dinos
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

    dinoActuel = recupererDinoNumero(&equipe1, &equipe2, gestionTours.dinoCourant);
    for(i=0;i<30;i++){
        for (int j=0; j<30; j++)
        {
            printf("%d",dinoActuel->memoire[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    afficher_matrice_dino(dinoActuel, matrice);
    supprimer_matrice_dino(dinoActuel, matrice);
    dinoActuel->id_nuage=0;
    dinoActuel->indice_nuage=390;
    nuage= nuage_de_points(&nb_pts, nomNuage[dinoActuel->id_nuage]);
    dinoActuel->pos=nuage[dinoActuel->indice_nuage];
    
    remplir_matrice_dino(dinoActuel, dinoActuel->pos, matrice);

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

        // PROTECTION CRITIQUE
        if(dinoActuel != NULL) {
            state = SDL_GetKeyboardState(NULL);
            // On affiche l'état actuel des équipes
            afficher(rendu, police, texMap, texObjets, &equipe1, &equipe2);
            // On ne lance le grappin que si le dinosaure existe toujours
            if (state[SDL_SCANCODE_G]) {
                grappin(matrice, rendu, &dinoActuel, state, texMap, police, texObjets, &equipe1, &equipe2 , &nb_pts, &nuage, 2, nomNuage);
            }

            SDL_RenderPresent(rendu);
            SDL_Delay(16);
        } else {
            // Le dinosaure est mort, on peut soit quitter, soit changer de tour
            printf("Plus de dinosaure actif. Fin du test.\n");
            enCours = 0; 
        }
    }

    /* ---- 5. Nettoyage ---- */
    detruireFile();
    nuageDetruire(&nuage);
    nuage=NULL;
    detruireContenuJoueur(&equipe1);
    detruireContenuJoueur(&equipe2);
    
    for(int k = 0; k < 6; k++) {
        if(texDinos[k] != NULL) {
            SDL_DestroyTexture(texDinos[k]);
            texDinos[k] = NULL;
        }
    }

    for(int i = 0; i < 7; i++) {
        if(texObjets[i] != NULL) {
            SDL_DestroyTexture(texObjets[i]);
            texObjets[i] = NULL;
        }
    }
    
    if(texMap != NULL) SDL_DestroyTexture(texMap);
    if(police != NULL) TTF_CloseFont(police);
    
    // Détruire le moteur de rendu AVANT la fenêtre
    if(rendu != NULL) SDL_DestroyRenderer(rendu);
    if(fenetre != NULL) SDL_DestroyWindow(fenetre);

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}