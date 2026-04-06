#include "../lib/chargerMatrice.h"
#include "../lib/fonctionsRebonds.h"
#include "../lib/fonctionsVerification.h"

#include <stdio.h>

/** 
 * @file testFonctionsRebonds.c
 * @brief Test des fonctions crées dans le fichier fonctionsRebonds.c.
 * @author Hannah Sergent
 * @date Crée le 5/02/2026
 * @version 2.5
 */

#define COOR_X LARGEUR_TERRAIN/3
#define COOR_Y 390

int main(int argc, char * argv[]){

    if (initialisationCorrecte()) {

        int enCours = 1;

        /* Variables pour la gestion des actions réalisées par l'utilisateur */

        SDL_Event evenement;
        const Uint8 *etatClavier;

        /* Initialisation de la matrice */

        t_case (*matriceTerrain)[LARGEUR_TERRAIN] = NULL;
        initialiserMatrice(&matriceTerrain);

        /* Initialisations liées à la bombe */

        t_bombe bombe;
        t_vect vectVitesse;
        const float vitesse = 1.0f/250.0f;
        float accumulateur = 0;
        int bombeLancee = 0;
        int nombreRebonds = 0;

        initialiserBombe(&bombe, COOR_X, COOR_Y, RAYON);
        initialiserVitesse(&vectVitesse, VITESSE_X, VITESSE_Y);

        /* Initialisation de la fenêtre */

        SDL_Window *fenJeu;
        SDL_Texture *texMap;
        SDL_Rect rect_plein_ecran = {0, 0, LARGEUR_TERRAIN, HAUTEUR_TERRAIN};

        creerFenetre(&fenJeu, "JurassicWar - Partie en cours", LARGEUR_TERRAIN, HAUTEUR_TERRAIN);
        SDL_Renderer* zoneAffichage = SDL_CreateRenderer(fenJeu, -1, SDL_RENDERER_ACCELERATED);
        chargerImageSansTaille(zoneAffichage, &texMap, "../img/test1_b.jpg");

        /* Affichage initial */

        SDL_RenderCopy(zoneAffichage, texMap, NULL, &rect_plein_ecran);
        tracerBombe(zoneAffichage, &bombe);
        SDL_RenderPresent(zoneAffichage);

        /* Variables pour la gestion du temps */

        float tempsEcoule;
        Uint32 tempsPrecedent = SDL_GetTicks();

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

                choixHauteurLancer(zoneAffichage, texMap, &rect_plein_ecran, &etatClavier, &bombe, &vectVitesse);
            }
            
            miseAjourTemps(&tempsPrecedent, &tempsEcoule);
            accumulateur += tempsEcoule;

            while (accumulateur >= vitesse) {
                if (bombeLancee) {

                    bombe.coor.x += vitesse*vectVitesse.u;
                    bombe.coor.y += vitesse*vectVitesse.v;
                    vectVitesse.v += GRAVITE_BOMBE*vitesse;

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

        /* Destruction */

        detruireMatrice(&matriceTerrain);

        SDL_DestroyTexture(texMap);
        SDL_DestroyRenderer(zoneAffichage);
        SDL_DestroyWindow(fenJeu);

        IMG_Quit();
        TTF_Quit();
        SDL_Quit();

        return 0;
    }
    return 1;

}