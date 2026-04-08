#include "../lib/chargerMatrice.h"
#include "../lib/fonctionsMenuHIP.h"
#include "../lib/fonctionsStructJoueur.h"
#include "../lib/fonctionsTirs.h"
#include "../lib/placer_dinos.h"
#include "../lib/types.h"
#include <time.h>

#define LARGEUR_FEN_JEU 1300
#define HAUTEUR_FEN_JEU 700

int main(int argc, char * argv[]){

    /* ---- Initialisation simplifiée ---- */
    int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN] = {AIR}; // On initialise tout à AIR
    float graviteMonde = 0.5f;
    int enCours = 1;

    const Uint8 *clavier = SDL_GetKeyboardState(NULL);

    // Catalogue des armes
    /*Il suffit de changer les valeurs de poids ou de puissance pour modifier les armes et avoir celles que l'on veut*/
    t_arme catalogue_armes[] = {
        {ARC, 20, 1.0f, 5.0f, 15.0f},
        {ARBALETE, 35, 1.2f, 8.0f, 18.0f},
        {FUSIL, 50, 0.4f, 15.0f, 30.0f},
        {REVOLVER, 30, 0.6f, 13.0f, 25.0f}
    };

    t_tir tirEncours;
    tirEncours.actif = 0;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) return 1;

    SDL_Window *fenetre = SDL_CreateWindow("Test Physique Armes (V, A, R, F)", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, LARGEUR_FEN_JEU, HAUTEUR_FEN_JEU, 0);
    SDL_Renderer *rendu = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_SOFTWARE);


    printf("Commandes : V=Arc, A=Arbalete, R=Revolver, F=Fusil, ESPACE=Viser/Tirer\n");

    while(enCours) {
        SDL_Event evenement;
        while (SDL_PollEvent(&evenement)){
            if (evenement.type == SDL_QUIT) enCours = 0;
        }

        SDL_PumpEvents();
        
        if (!tirEncours.actif){
            int touchePressee = 0;

            /*On vérifie quelle touche est pressée pour choisir l'arme*/
            if (clavier[SDL_SCANCODE_V]) {
                tirEncours.arme_source = catalogue_armes[0];
                printf("Arme : ARC\n");
                touchePressee = 1;
            }
            else if (clavier[SDL_SCANCODE_A]) {
                tirEncours.arme_source = catalogue_armes[1];
                printf("Arme : ARBALETE\n");
                touchePressee = 1;
            }
            else if (clavier[SDL_SCANCODE_F]) {
                tirEncours.arme_source = catalogue_armes[2];
                printf("Arme : FUSIL\n");
                touchePressee = 1;
            }
            else if (clavier[SDL_SCANCODE_R]) {
                tirEncours.arme_source = catalogue_armes[3];
                printf("Arme : REVOLVER\n");
                touchePressee = 1;
            }
            
            if(touchePressee){
                tirEncours.pos.x = 50;
                tirEncours.pos.y = 600;

                viserArcher(rendu, NULL, NULL, NULL, 0, &tirEncours, clavier, graviteMonde, NULL, NULL, 0);
            }
        }

        else{
            mettreAJourVol(&tirEncours, matrice, graviteMonde, -1); // -1 car pas de tireur à ignorer ici
        }

        // --- AFFICHAGE ---
        SDL_SetRenderDrawColor(rendu, 50, 50, 50, 255); // Fond gris
        SDL_RenderClear(rendu);

        
        // Dessin du projectile
        if (tirEncours.actif) {
            tracerArme(rendu, &tirEncours);
        }

        SDL_RenderPresent(rendu);
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(rendu);
    SDL_DestroyWindow(fenetre);
    SDL_Quit();
    return 0;
}