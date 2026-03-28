#include "../lib/chargerMatrice.h"
#include "../lib/fonctionsRebonds2.h"
#include "../lib/fonctionsVerification.h"
#include "../lib/types.h"

#include <stdio.h>

/** 
 * @file testFonctionsRebonds.c
 * @brief Test des fonctions crées dans le fichier fonctionsRebonds.c.
 * @author Hannah Sergent
 * @date Crée le 5/02/2026
 */

#define RAYON 15

#define COOR_X LARGEUR_TERRAIN/3
#define COOR_Y 390

#define VITESSE_X 90
#define VITESSE_Y -90

int main(int argc, char * argv[]){

    if (initialisationCorrecte()) {

        Uint32 tempsPrecedent;
        float tempsEcoule;
        const Uint8 *etatClavier;

        t_case (*matriceTerrain)[LARGEUR_TERRAIN] = NULL;
        initialiserMatrice(&matriceTerrain);

        chargerMatriceDepuisFichier("../res/matrice.txt", matriceTerrain);

        t_bombe bombe;

        const float vitesse = 1.0f/250.0f;
        float accumulateur = 0;
        t_vect vectVitesse;

        float gravite = 140;

        int largeurFenetre;
        int hauteurFenetre;

        initialiserBombe(&bombe, COOR_X, COOR_Y, RAYON);
        initialiserVitesse(&vectVitesse, VITESSE_X, VITESSE_Y);

        int enCours = 1;
        int bombeLancee = 0;
        int nombreRebonds = 0;

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
                nombreRebonds = 0;

                choixHauteurLancer(zoneAffichage, texMap, &rect_plein_ecran, &etatClavier, &bombe, &vectVitesse, gravite);
            }
            
            miseAjourTemps(&tempsPrecedent, &tempsEcoule);
            accumulateur += tempsEcoule;

            while (accumulateur >= vitesse) {
                if (bombeLancee) {

                    bombe.coor.x += vitesse*vectVitesse.u;
                    bombe.coor.y += vitesse*vectVitesse.v;
                    vectVitesse.v += gravite*vitesse;

                    if (collisionFrontiereBombe(&bombe)) {
                        bombeLancee = 0;

                    }
                    if (collisionTerrainBombe(matriceTerrain, &bombe, &vectVitesse)) {
                        nombreRebonds ++;

                        if (nombreRebonds > 1){
                            bombeLancee = 0;
                        }
                    }
                    if (collisionEauBombe(matriceTerrain, &bombe)) {
                        bombeLancee = 0;
                        SDL_RenderClear(zoneAffichage);
                        SDL_RenderCopy(zoneAffichage, texMap, NULL, &rect_plein_ecran);
                        SDL_RenderPresent(zoneAffichage);
                    }

                    if (bombeLancee) {
                        SDL_RenderClear(zoneAffichage);
                        SDL_RenderCopy(zoneAffichage, texMap, NULL, &rect_plein_ecran);
                        tracerBombe(zoneAffichage, &bombe);
                        SDL_RenderPresent(zoneAffichage);
                    }
                }
                accumulateur -= vitesse;
            }
        }

        detruireMatrice(&matriceTerrain);
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