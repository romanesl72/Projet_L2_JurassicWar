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

int main(int argc, char * argv[]) {
    /* ---- Déclarations des variables (Portée : toute la fonction main) ---- */
    int i, enCours = 0;
    int matrice[MAT_H][MAT_L];
    int nb_pts, w, h;
    int trouves_E1 = 0, trouves_E2 = 0;
    int timer = 1000;
    t_case dinoTouche = D1;

    char *nomNuage[5];
    t_coordonnee *nuages_stockes[5];
    t_catalogue_zones catalogue;
    t_joueur equipe1, equipe2;
    t_tour gestionTours = {0, 1, D1, D1}; // Initialisation basique
    
    SDL_Event evenement;
    SDL_Window *menuPrincipal = NULL;
    SDL_Renderer *rendu = NULL;
    SDL_Texture *texMap = NULL;
    SDL_Rect rect_plein_ecran = {0, 0, LARGEUR_TERRAIN, HAUTEUR_TERRAIN};

    nomNuage[0] = "../img/test1_c.jpg";
    nomNuage[1] = "../img/test2_c.jpg";
    int nb_nuage = 2;

    /* ---- Initialisation ---- */
    if (initialisationCorrecte()) {
        srand(time(NULL));
        enCours = 1;

        creerFenetre(&menuPrincipal, "Jurassic War - Test Déplacement", LARGEUR_TERRAIN, HAUTEUR_TERRAIN);
        rendu = SDL_CreateRenderer(menuPrincipal, -1, SDL_RENDERER_ACCELERATED);

        chargerMatriceDepuisFichier("../res/matrice.txt", matrice);

        // Extraction des points pour les zones de départ
        nuages_stockes[0] = nuage_de_points(&nb_pts, nomNuage[0]);
        generer_catalogue_depuis_nuage(nuages_stockes[0], nb_pts, &catalogue, &trouves_E1, &trouves_E2, 1);
        nuageDetruire(&(nuages_stockes[0]));

        nuages_stockes[1] = nuage_de_points(&nb_pts, nomNuage[1]);
        generer_catalogue_depuis_nuage(nuages_stockes[1], nb_pts, &catalogue, &trouves_E1, &trouves_E2, 2);
        nuageDetruire(&(nuages_stockes[1]));

        chargerImage(rendu, &texMap, "../img/test1_b.jpg", &w, &h);

        initialiserContenuJoueur(&equipe1); // Alloue tab ET texDinos
        initialiserContenuJoueur(&equipe2);

        // CHARGER LES TEXTURES DANS LA STRUCTURE
        for(i = 0; i < 3; i++) {
            chargerImage(rendu, &equipe1.texDinos[i], "../img/dino_test.png", &w, &h);
            chargerImage(rendu, &equipe2.texDinos[i], "../img/dino_test.png", &w, &h);
        }

        // Vérification de la réussite du catalogue
        if (trouves_E1 < 3 || trouves_E2 < 3) {
            printf("ERREUR CRITIQUE : Impossible de trouver assez de zones de spawn (%d/3 E1, %d/3 E2).\n", trouves_E1, trouves_E2);
            printf("Vérifiez que vos images .jpg ont assez de zones noires aux extrémités.\n");
            enCours = 0; // Empêche de lancer la boucle
        } else {
            // Placement sécurisé uniquement si les zones existent
            placer_une_equipe(&equipe1, catalogue.zones_E1, matrice, D1);
            placer_une_equipe(&equipe2, catalogue.zones_E2, matrice, D4);
        }
    }

    /* ---- Boucle Principale ---- */
    while (enCours) {
        while (SDL_PollEvent(&evenement)) {
            if (evenement.type == SDL_QUIT) enCours = 0;
        }

        const Uint8 *state = SDL_GetKeyboardState(NULL);

        SDL_RenderClear(rendu);
        SDL_RenderCopy(rendu, texMap, NULL, &rect_plein_ecran);

        // Gestion du déplacement du dino actif
        t_dino *dinoActuel = recupererDinoNumero(&equipe1, &equipe2, dinoTouche);
        if (dinoActuel != NULL) {
            deplacement_dino(dinoActuel, nomNuage, nb_nuage, matrice);
            if(dinoActuel->etat==0){
                supprimerDinoJoueur(&equipe1,&equipe2, dinoTouche);
            }
        }

        afficherDinos(rendu, &equipe1);
        afficherDinos(rendu, &equipe2);

        SDL_RenderPresent(rendu);

        if (timer == 0) {
            tourSuivant(&gestionTours, &equipe1, &equipe2);
            timer = 1000;
        } else timer--;
        
        SDL_Delay(16); // ~60 FPS
    }

    /* ---- Nettoyage ---- */
    detruireContenuJoueur(&equipe1);
    detruireContenuJoueur(&equipe2);
    SDL_DestroyTexture(texMap);
    SDL_DestroyRenderer(rendu);
    SDL_DestroyWindow(menuPrincipal);
    SDL_Quit();

    return 0;
}