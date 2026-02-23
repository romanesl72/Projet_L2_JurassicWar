#include "../lib/types.h"
#include "../lib/fonctionsVerification.h"
#include "../lib/fonctionsRebonds.h"
#include "../lib/chargerMatrice.h"
#include <stdio.h>

/** 
 * @file testFonctionsRebonds.c
 * @brief test des fonctions crées dans le fichier fonctionsRebonds.c
 * @author Hannah Sergent
 * @date Crée le 5/02/2026
 */

 /*
 LARGEUR_FEN_JEU 1300
 HAUTEUR_FEN_JEU 700 */

/*
LARGEUR_FEN_JEU 1050
HAUTEUR_FEN_JEU 650 */

#define LARGEUR_FEN_MENU 400
#define HAUTEUR_FEN_MENU 650

#define RAYON 20

#define COOR_X LARGEUR_TERRAIN/4
#define COOR_Y HAUTEUR_TERRAIN/2

#define VITESSE_X 200
#define VITESSE_Y -200

// Transformer vitesseX et vitesseY en vecteur

int main(int argc, char * argv[]){

    if (initialisationCorrecte()) {

        Uint32 tempsPrecedent;
        float tempsEcoule;
        const Uint8 *etatClavier;

        t_case matriceTerrain[HAUTEUR_TERRAIN][LARGEUR_TERRAIN];
        chargerMatriceDepuisFichier("../res/matrice.txt", matriceTerrain);

        t_bombe bombe;

        const float vitesse = 1.0f/60.0f;
        float accumulateur = 0;
        t_vect vectVitesse;

        float gravite = 300;

        int largeurFenetre;
        int hauteurFenetre;

        initialiserBombe(&bombe, COOR_X, COOR_Y, RAYON);
        initialiserVitesse(&vectVitesse, VITESSE_X, VITESSE_Y);

        int enCours = 1;
        int bombeLancee = 0;

        SDL_Event evenement;


        SDL_Window *menuPrincipal; 
        creerFenetre(&menuPrincipal, "MenuPrincipal", LARGEUR_TERRAIN, HAUTEUR_TERRAIN);


        SDL_Renderer* zoneAffichage = SDL_CreateRenderer(menuPrincipal, -1, SDL_RENDERER_ACCELERATED);

        SDL_Texture *texMap;
        chargerImage(zoneAffichage, &texMap, "../img/test1_b.jpg", &largeurFenetre, &hauteurFenetre);

        SDL_Rect rect_plein_ecran = {0, 0, largeurFenetre, hauteurFenetre};
        SDL_RenderCopy(zoneAffichage, texMap, NULL, &rect_plein_ecran);
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

                choixHauteurLancer(zoneAffichage, texMap, &rect_plein_ecran, &etatClavier, &bombe, &vectVitesse, gravite);
            }
            
            miseAjourTemps(&tempsPrecedent, &tempsEcoule);
            accumulateur += tempsEcoule;

            while (accumulateur >= vitesse) {
                if (bombeLancee) {

                    vectVitesse.v += gravite*vitesse;
                    bombe.coor.x += vitesse*vectVitesse.u;
                    bombe.coor.y += vitesse*vectVitesse.v;

                    if (rebondFrontiereBombe(LARGEUR_TERRAIN, HAUTEUR_TERRAIN, &bombe)) {
                        bombeLancee = 0;
                        /* 
                        initialiserBombe(&bombe, COOR_X, COOR_Y, RAYON);
                        initialiserVitesse(&vitesseX, &vitesseY, VITESSE_X, VITESSE_Y);
                        */
                    }

                    if (rebondTerrainBombe(matriceTerrain, &bombe)) {
                        bombeLancee = 0;
                    }


                    SDL_RenderClear(zoneAffichage);
                    SDL_RenderCopy(zoneAffichage, texMap, NULL, &rect_plein_ecran);
                    tracerBombe(zoneAffichage, &bombe);
                    SDL_RenderPresent(zoneAffichage);
                }
                accumulateur -= vitesse;
            }
        }

        SDL_DestroyTexture(texMap);
        SDL_DestroyRenderer(zoneAffichage);

        SDL_DestroyWindow(menuPrincipal);
        IMG_Quit();
        TTF_Quit();
        SDL_Quit();

        return 0;
    }
    return 1;

}