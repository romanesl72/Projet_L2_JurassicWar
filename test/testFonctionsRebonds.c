#include "../lib/types.h"
#include "../lib/fonctionsVerification.h"
#include "../lib/fonctionsRebonds.h"
#include <stdio.h>

/** 
 * @file testFonctionsRebonds.c
 * @brief test des fonctions crées dans le fichier fonctionsRebonds.c
 * @author Hannah Sergent
 * @date Crée le 5/02/2026
 */

#define LARGEUR_FEN_JEU 1050
#define HAUTEUR_FEN_JEU 650

#define LARGEUR_FEN_MENU 400
#define HAUTEUR_FEN_MENU 650

#define RAYON 20

#define COOR_X LARGEUR_FEN_JEU/4
#define COOR_Y HAUTEUR_FEN_JEU/2

#define VITESSE_X 200
#define VITESSE_Y -200

// Transformer vitesseX et vitesseY en vecteur

int main(int argc, char * argv[]){

    if (initialisationCorrecte()) {

        Uint32 tempsPrecedent;
        float tempsEcoule;
        const Uint8 *etatClavier;

        t_bombe bombe;

        const float vitesse = 1.0f/60.0f;
        float accumulateur;
        float vitesseX;
        float vitesseY;
        float gravite = 300;

        initialiserBombe(&bombe, COOR_X, COOR_Y, RAYON);
        initialiserVitesse(&vitesseX, &vitesseY, VITESSE_X, VITESSE_Y);

        int enCours = 1;
        int bombeLancee = 0;

        SDL_Event evenement;
        SDL_Window *menuPrincipal; 
        creerFenetre(&menuPrincipal, "MenuPrincipal", LARGEUR_FEN_JEU, HAUTEUR_FEN_JEU);

        SDL_Renderer* zoneAffichage = SDL_CreateRenderer(menuPrincipal, -1, SDL_RENDERER_ACCELERATED);
        SDL_SetRenderDrawColor(zoneAffichage, 0, 0, 0, 255);
        tracerBombe(zoneAffichage, &bombe);
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
                choixHauteurLancer(zoneAffichage, &etatClavier, &bombe, &vitesseX, &vitesseY, gravite);
            }
            
            miseAjourTemps(&tempsPrecedent, &tempsEcoule);
            accumulateur += tempsEcoule;

            while (accumulateur >= vitesse) {
                if (bombeLancee) {

                    vitesseY += gravite*vitesse;
                    bombe.coor.x += vitesse*vitesseX;
                    bombe.coor.y += vitesse*vitesseY;

                    if (rebondFrontiereBombe(LARGEUR_FEN_JEU, HAUTEUR_FEN_JEU, &bombe)) {
                        bombeLancee = 0;
                        /* 
                        initialiserBombe(&bombe, COOR_X, COOR_Y, RAYON);
                        initialiserVitesse(&vitesseX, &vitesseY, VITESSE_X, VITESSE_Y);
                        */
                    }

                    SDL_SetRenderDrawColor(zoneAffichage, 0, 0, 0, 255);
                    SDL_RenderClear(zoneAffichage);
                    tracerBombe(zoneAffichage, &bombe);
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