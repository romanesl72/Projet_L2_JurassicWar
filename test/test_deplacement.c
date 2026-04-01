#include "../lib/chargerMatrice.h"
#include "../lib/fonctionsChangementTour.h"
#include "../lib/fonctionsStructJoueur.h"
#include "../lib/fonctionsVerification.h"
#include "../lib/gestion_zones.h"
#include "../lib/placer_dinos.h"
#include "../lib/deplacement.h"
#include "../lib/tda_nuage.h"
#include "../lib/types.h"
#include <time.h>
#include <stdio.h>

#define LARGEUR_FEN_JEU 1300
#define HAUTEUR_FEN_JEU 700

int main(int argc, char * argv[]) {
    /* ---- 1. Déclarations et Initialisations ---- */
    int i, nb_pts, w, h;
    int enCours = 0;
    int matrice[MAT_H][MAT_L];
    int trouves_E1 = 0, trouves_E2 = 0;
    int timer = TIMER; // Initialisé avec la macro de types.h
    int nb_nuage = 2; 
    int cgt = 0; // Indicateur de changement forcé (mort)

    t_coordonnee *nuages_stockes[5];
    t_catalogue_zones catalogue;
    t_joueur equipe1, equipe2;
    t_tour gestionTours = {1, 1, D1, D6}; // Tour 1, Equipe 1, Dino D1
    
    char *nomNuage[2] = {"../img/test1_c.jpg", "../img/test2_c.jpg"};
    t_coordonnee *nuage = NULL;
    t_dino *dinoActuel = NULL;

    SDL_Window *menuPrincipal = NULL;
    SDL_Renderer *rendu = NULL;
    SDL_Texture *texMap = NULL;
    SDL_Event evenement;
    SDL_Rect rect_plein_ecran = {0, 0, LARGEUR_FEN_JEU, HAUTEUR_FEN_JEU};

    /* ---- 2. Initialisation SDL et Ressources ---- */
    if (initialisationCorrecte()) {
        srand(time(NULL));
        enCours = 1;

        creerFenetre(&menuPrincipal, "Jurassic War - Test Déplacement", LARGEUR_FEN_JEU, HAUTEUR_FEN_JEU);
        rendu = SDL_CreateRenderer(menuPrincipal, -1, SDL_RENDERER_ACCELERATED);

        chargerMatriceDepuisFichier("../res/matrice.txt", matrice);
        chargerImage(rendu, &texMap, "../img/test1_b.jpg", &w, &h);

        /* ---- 3. Préparation du terrain (Zones de spawn) ---- */
        nuages_stockes[0] = nuage_de_points(&nb_pts, nomNuage[0]);
        generer_catalogue_depuis_nuage(nuages_stockes[0], nb_pts, &catalogue, &trouves_E1, &trouves_E2, 1);
        nuageDetruire(&nuages_stockes[0]);

        nuages_stockes[1] = nuage_de_points(&nb_pts, nomNuage[1]);
        generer_catalogue_depuis_nuage(nuages_stockes[1], nb_pts, &catalogue, &trouves_E1, &trouves_E2, 2);
        nuageDetruire(&nuages_stockes[1]);

        /* ---- 4. Initialisation des Equipes ---- */
        initialiserContenuJoueur(&equipe1);
        initialiserContenuJoueur(&equipe2);

        for(i = 0; i < equipe1.n; i++) {
            chargerImage(rendu, &equipe1.texDinos[i], "../img/dino_test.png", &w, &h);
            chargerImage(rendu, &equipe2.texDinos[i], "../img/dino_test.png", &w, &h);
        }

        if (trouves_E1 >= 3 && trouves_E2 >= 3) {
            placer_une_equipe(&equipe1, catalogue.zones_E1, matrice, D1);
            placer_une_equipe(&equipe2, catalogue.zones_E2, matrice, D4);
            for(i = 0; i < 3; i++) {
                equipe1.tab[i].id_nuage = 0;
                equipe2.tab[i].id_nuage = 1;
            }
        }
    }

    /* ---- 5. Boucle de Jeu Principale ---- */
    while (enCours) {
        while (SDL_PollEvent(&evenement)) {
            if (evenement.type == SDL_QUIT) enCours = 0;
        }

        // A. GESTION AUTOMATIQUE DU TOUR
        // Si le temps est fini OU si le dinosaure actuel est inexistant/mort
        if (timer <= 0 || dinoActuel == NULL) {
            
            // Si le dino précédent est mort, on le retire avant de passer au suivant
            if (dinoActuel != NULL && dinoActuel->etat == 0) {
                supprimerDinoJoueur(&equipe1, &equipe2, dinoActuel->d);
                dinoActuel = NULL;
            }

            // Calcul du tour suivant
            if(!cgt) {
                tourSuivant(&gestionTours, &equipe1, &equipe2);
            } else {
                cgt = 0; // On reset l'indicateur de mort
            }
            
            // Récupération du nouveau dinosaure actif
            dinoActuel = recupererDinoNumero(&equipe1, &equipe2, gestionTours.dinoCourant);
            
            if (dinoActuel != NULL) {
                nuageDetruire(&nuage);
                nuage = nuage_de_points(&nb_pts, nomNuage[dinoActuel->id_nuage]);
                
                // Synchronisation position réelle pour la fluidité
                dinoActuel->deplacement->indice_reel = (float)dinoActuel->indice_nuage;
                timer = TIMER; // Relance du temps de jeu
            }
        } else {
            timer--; // Le temps s'écoule
        }

        // B. LOGIQUE DE DÉPLACEMENT ET NOYADE
        if (dinoActuel != NULL && nuage != NULL && dinoActuel->etat != 0) {
            deplacement_dino(dinoActuel, &nuage, nomNuage, nb_nuage, &nb_pts, matrice);
            
            // Si le dinosaure vient de se noyer (état passé à 0 dans deplacement.c)
            if(dinoActuel->etat == 0) {
                supprimer_matrice_dino(dinoActuel, matrice); // Effacement immédiat
                timer = 0;  // Force le changement de tour au prochain cycle
                cgt = 1;    // Indique qu'on change suite à une mort
            }
        }

        // C. RENDU GRAPHIQUE
        SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255);
        SDL_RenderClear(rendu);
        SDL_RenderCopy(rendu, texMap, NULL, &rect_plein_ecran);

        // Affichage des dinosaures vivants
        for(i = 0; i < equipe1.n; i++) {
            SDL_Rect r = {equipe1.tab[i].pos.x, equipe1.tab[i].pos.y, 30, 30};
            SDL_RenderCopy(rendu, equipe1.texDinos[i], NULL, &r);
        }
        for(i = 0; i < equipe2.n; i++) {
            SDL_Rect r = {equipe2.tab[i].pos.x, equipe2.tab[i].pos.y, 30, 30};
            SDL_RenderCopy(rendu, equipe2.texDinos[i], NULL, &r);
        }

        SDL_RenderPresent(rendu);
        SDL_Delay(2); // Petit délai pour stabiliser la vitesse du timer
    }

    /* ---- 6. Nettoyage ---- */
    nuageDetruire(&nuage);
    detruireContenuJoueur(&equipe1);
    detruireContenuJoueur(&equipe2);
    SDL_DestroyTexture(texMap);
    SDL_DestroyRenderer(rendu);
    SDL_DestroyWindow(menuPrincipal);
    SDL_Quit();

    return 0;
}