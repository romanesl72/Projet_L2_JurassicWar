#include "../lib/chargerMatrice.h"
#include "../lib/fonctionsChangementTour.h"
#include "../lib/fonctionsStructJoueur.h"
#include "../lib/fonctionsVerification.h"
#include "../lib/gestion_zones.h"
#include "../lib/placer_dinos.h"
#include "../lib/deplacement.h"
#include "../lib/tda_nuage.h"
#include <time.h>
#include <stdio.h>

#define LARGEUR_FEN_JEU 1300
#define HAUTEUR_FEN_JEU 700

int main(int argc, char * argv[]) {
    /* ---- 1. Déclarations et Initialisations de base ---- */
    int i, nb_pts, w, h;
    int enCours = 0;
    int matrice[MAT_H][MAT_L];
    int trouves_E1 = 0, trouves_E2 = 0;
    int timer =0;
    int nb_nuage = 2; 

    t_coordonnee *nuages_stockes[5];
    t_catalogue_zones catalogue;
    t_joueur equipe1, equipe2;
    t_tour gestionTours = {1, 1, D1, D6};
    
    char *nomNuage[2] = {"../img/test1_c.jpg", "../img/test2_c.jpg"};
    t_coordonnee *nuage = NULL;
    t_dino *dinoActuel = NULL;

    SDL_Window *menuPrincipal = NULL;
    SDL_Renderer *rendu = NULL;
    SDL_Texture *texMap = NULL;
    SDL_Event evenement;
    SDL_Rect rect_plein_ecran = {0, 0, LARGEUR_FEN_JEU, HAUTEUR_FEN_JEU};

    /* ---- 2. Initialisation SDL et Chargement des ressources ---- */
    if (initialisationCorrecte()) {
        srand(time(NULL));
        enCours = 1;

        creerFenetre(&menuPrincipal, "Jurassic War - Test Déplacement", LARGEUR_FEN_JEU, HAUTEUR_FEN_JEU);
        rendu = SDL_CreateRenderer(menuPrincipal, -1, SDL_RENDERER_SOFTWARE);

        // Chargement du décor
        chargerMatriceDepuisFichier("../res/matrice.txt", matrice);
        chargerImage(rendu, &texMap, "../img/test1_b.jpg", &w, &h);

        /* ---- 3. Génération du catalogue de zones ---- */
        // Nuage 1 pour l'équipe 1
        nuages_stockes[0] = nuage_de_points(&nb_pts, nomNuage[0]);
        generer_catalogue_depuis_nuage(nuages_stockes[0], nb_pts, &catalogue, &trouves_E1, &trouves_E2, 1);
        nuageDetruire(&nuages_stockes[0]);

        // Nuage 2 pour l'équipe 2
        nuages_stockes[1] = nuage_de_points(&nb_pts, nomNuage[1]);
        generer_catalogue_depuis_nuage(nuages_stockes[1], nb_pts, &catalogue, &trouves_E1, &trouves_E2, 2);
        nuageDetruire(&nuages_stockes[1]);

        printf("Zones trouvées : E1=%d, E2=%d\n", trouves_E1, trouves_E2);

        /* ---- 4. Initialisation des Joueurs et Textures ---- */
        initialiserContenuJoueur(&equipe1);
        initialiserContenuJoueur(&equipe2);

        for(i = 0; i < equipe1.n; i++) {
            chargerImage(rendu, &equipe1.texDinos[i], "../img/dino_test.png", &w, &h);
            chargerImage(rendu, &equipe2.texDinos[i], "../img/dino_test.png", &w, &h);
        }

        /* ---- 5. Placement et Correction des IDs Nuages ---- */
        if (trouves_E1 >= 3 && trouves_E2 >= 3) {
            placer_une_equipe(&equipe1, catalogue.zones_E1, matrice, D1);
            placer_une_equipe(&equipe2, catalogue.zones_E2, matrice, D4);
            
            // Correction importante : id_nuage doit être 0 ou 1 pour correspondre à nomNuage
            for(i = 0; i < 3; i++) {
                equipe1.tab[i].id_nuage = 0;
                equipe2.tab[i].id_nuage = 1;
            }
        } else {
            printf("ERREUR : Pas assez de zones de spawn !\n");
            enCours = 0;
        }
    }

    /* ---- 6. Boucle de Jeu Principale ---- */
    while (enCours) {
        while (SDL_PollEvent(&evenement)) {
            if (evenement.type == SDL_QUIT) enCours = 0;
        }

        /* --- Gestion du Tour et Chargement du Nuage Actif --- */
        if (timer <= 0) {
            tourSuivant(&gestionTours, &equipe1, &equipe2);
            dinoActuel = recupererDinoNumero(&equipe1, &equipe2, gestionTours.dinoCourant);
            
            if (dinoActuel != NULL) {
                nuageDetruire(&nuage);
                // On utilise l'ID du nuage stocké dans le dinosaure
                nuage = nuage_de_points(&nb_pts, nomNuage[dinoActuel->id_nuage]);
                dinoActuel->pos=nuage[dinoActuel->indice_nuage];
                
                if (nuage == NULL) {
                    printf("Erreur chargement nuage pour dino %d\n", dinoActuel->d);
                    enCours = 0;
                }
                printf("C'est au tour du dinosaure %d\n", dinoActuel->d);
            }
            timer = 10000; // Délai avant le prochain changement de tour automatique
        } else timer--;

        /* --- Mise à jour du Déplacement --- */
        if (dinoActuel != NULL && nuage != NULL) {
            deplacement_dino(dinoActuel, &nuage, nomNuage, nb_nuage, &nb_pts, matrice);
        }

        /* --- Rendu Graphique --- */
        SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255);
        SDL_RenderClear(rendu);
        SDL_RenderCopy(rendu, texMap, NULL, &rect_plein_ecran);

        // Affichage Équipe 1
        for(i = 0; i < equipe1.n; i++) {
            SDL_Rect r = {equipe1.tab[i].pos.x, equipe1.tab[i].pos.y, 30, 30};
            SDL_RenderCopy(rendu, equipe1.texDinos[i], NULL, &r);
        }
        // Affichage Équipe 2
        for(i = 0; i < equipe2.n; i++) {
            SDL_Rect r = {equipe2.tab[i].pos.x, equipe2.tab[i].pos.y, 30, 30};
            SDL_RenderCopy(rendu, equipe2.texDinos[i], NULL, &r);
        }

        SDL_RenderPresent(rendu);
    }

    /* ---- 7. Nettoyage final ---- */
    nuageDetruire(&nuage);
    detruireContenuJoueur(&equipe1);
    detruireContenuJoueur(&equipe2);
    SDL_DestroyTexture(texMap);
    SDL_DestroyRenderer(rendu);
    SDL_DestroyWindow(menuPrincipal);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();

    return 0;
}