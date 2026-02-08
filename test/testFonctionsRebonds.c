#include "../lib/types.h"
#include "../lib/fonctionsVerification.h"
#include "../lib/fonctionsRebonds.h"
#include <stdio.h>

#define LARGEUR_FEN_JEU 1050
#define HAUTEUR_FEN_JEU 650

#define LARGEUR_FEN_MENU 400
#define HAUTEUR_FEN_MENU 650

#define RAYON 20

#define COOR_X LARGEUR_FEN_JEU/2
#define COOR_Y HAUTEUR_FEN_JEU/2

// Transformer en fonctions

int main(int argc, char * argv[]){

    if (initialisationCorrecte()) {

        Uint32 tempsPrecedent;
        Uint32 tempsCourant;
        float tempsEcoule;
        const Uint8 *etatClavier;

        const float vitesse = 1.0f/60.0f;
        float accumulateur;
        float vitesseX = 500;
        float vitesseY = -400;
        float gravite = 800;

        t_coordonnee coor;
        coor.x = COOR_X;
        coor.y = COOR_Y;

        int enCours = 1;
        int bombeLancee = 0;

        SDL_Event evenement;
        SDL_Window *menuPrincipal; 
        creerFenetre(&menuPrincipal, "MenuPrincipal", LARGEUR_FEN_JEU, HAUTEUR_FEN_JEU);

        SDL_Renderer* zoneAffichage = SDL_CreateRenderer(menuPrincipal, -1, SDL_RENDERER_ACCELERATED);
        SDL_SetRenderDrawColor(zoneAffichage, 0, 0, 0, 255);
        tracerBombe(zoneAffichage, &coor, RAYON);
        SDL_RenderPresent(zoneAffichage);

        tempsPrecedent = SDL_GetTicks();

        while(enCours) {

            while (SDL_PollEvent(&evenement)){
                if (evenement.type == SDL_QUIT){
                    enCours = 0;
                }
            }

            etatClavier = SDL_GetKeyboardState(NULL);

            if (etatClavier[SDL_SCANCODE_B]){
                bombeLancee = 1;
            }

            tempsCourant = SDL_GetTicks();
            tempsEcoule = (tempsCourant - tempsPrecedent)/1000.0f;
            tempsPrecedent = tempsCourant;

            accumulateur += tempsEcoule;

            while (accumulateur >= vitesse) {
                if (bombeLancee) {

                    vitesseY += gravite*vitesse;
                    coor.x += vitesse*vitesseX;
                    coor.y += vitesse*vitesseY;

                    if (rebondFrontiereBombe(LARGEUR_FEN_JEU, HAUTEUR_FEN_JEU, &coor, RAYON) ) {
                        bombeLancee = 0;
                    }

                    SDL_SetRenderDrawColor(zoneAffichage, 0, 0, 0, 255);
                    SDL_RenderClear(zoneAffichage);
                    tracerBombe(zoneAffichage, &coor, RAYON);
                    SDL_RenderPresent(zoneAffichage);
                }
                accumulateur -= vitesse;
            }
        }

        SDL_DestroyRenderer(zoneAffichage);

        SDL_DestroyWindow(menuPrincipal);
        IMG_Quit();
        TTF_Quit();
        SDL_Quit();

        return 0;
    }
    return 1;

}