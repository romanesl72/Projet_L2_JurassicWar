#include "../lib/chargerMatrice.h"
#include "../lib/types.h"
#include "../lib/tda_nuage.h"
#include "../lib/fonctionsChangementTour.h"
#include "../lib/deplacement.h"
#include "../lib/fonctionsVerification.h"
#include "../lib/placer_dinos.h"
#include "../lib/gestion_zones.h"
#include "../lib/fonctionsMenuHIP.h"
#include "../lib/fonctionsPageJeu.h"
#include "../lib/fonctionsStructJoueur.h"
#include "../lib/fonctionsAffichage.h"
#include <time.h>

#include <SDL2/SDL_ttf.h>



int main(int argc, char * argv[]){

    /* ---- 1. Initialisation ---- */
    if (!initialisationCorrecte()) return 1;
    srand(time(NULL));

    SDL_Window *fenetre = NULL;
    SDL_Renderer *rendu = NULL;
    TTF_Font *police = NULL;
    t_joueur equipe1, equipe2;
    int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN];
    int nb_pts;
    t_catalogue_zones catalogue;
    t_tour gestionTours = {1, 1, D1, D6}; // Tour 1, Equipe 1, Dino D1
    int timer=TIMER;
    int cgt=0;
    int nb_nuage=2;
    char *nomNuage[2] = {"../img/test1_c.jpg", "../img/test2_c.jpg"};
    t_texte_cache cache[6];
    t_coordonnee *nuage = NULL;
    t_dino *dinoActuel = NULL;
    SDL_Texture *texMap = NULL;
    SDL_Texture *texObjets[7] = {NULL};

    creerPageJeu(&fenetre, &rendu, &texMap, texObjets, &police);
    chargerTexteDinos(rendu, police, cache);
    chargerMatriceDepuisFichier("../res/matrice.txt", matrice);
    
    initialiserEquipes(&equipe1, &equipe2, &catalogue, matrice, rendu);

    dinoActuel = recupererDinoNumero(&equipe1, &equipe2, gestionTours.dinoCourant);
    nuage= nuage_de_points(&nb_pts, nomNuage[dinoActuel->id_nuage]);
    dinoActuel->pos=nuage[dinoActuel->indice_nuage];
    
    remplir_matrice_dino(dinoActuel, dinoActuel->pos, matrice);

    int enCours = 1;
    SDL_Event e;

    /* ---- 4. Boucle de Rendu ---- */
    while(enCours) {
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT) enCours = 0;
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
        } 
        else {
            timer--; // Le temps s'écoule
        }

        // B. LOGIQUE DE DÉPLACEMENT ET NOYADE
        if (dinoActuel != NULL && nuage != NULL && dinoActuel->etat != 0) {
            deplacement_dino(dinoActuel, &nuage, nomNuage, nb_nuage, &nb_pts, matrice,&equipe1, &equipe2);
            
            // Si le dinosaure vient de se noyer (état passé à 0 dans deplacement.c)
            if(dinoActuel->etat == 0) {
                supprimer_matrice_dino(dinoActuel, matrice); // Effacement immédiat
                timer = 0;  // Force le changement de tour au prochain cycle
                cgt = 1;    // Indique qu'on change suite à une mort
            }
        }
            // On affiche l'état actuel des équipes
        afficher(rendu, police, texMap, texObjets, &equipe1, &equipe2);
        SDL_RenderPresent(rendu);
        SDL_Delay(10);
        
    }

    /* ---- 5. Nettoyage ---- */
    destruireElementsJeu(&equipe1, &equipe2, matrice, texMap, texObjets, police, rendu, fenetre, nuage, cache);

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}