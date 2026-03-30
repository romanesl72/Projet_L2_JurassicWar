#include "../lib/chargerMatrice.h"
#include "../lib/fonctionsChangementTour.h"
#include "../lib/fonctionsPageJeu.h"
#include "../lib/fonctionsPlacementBombe.h"
#include "../lib/fonctionsRebonds.h"
#include "../lib/fonctionsStructJoueur.h"
#include "../lib/fonctionsTuerDinos.h"
#include "../lib/fonctionsVerification.h"
#include "../lib/placer_dinos.h"
#include "../lib/tda_nuage.h"

#include <stdio.h>

/** 
 * @file testBombeDinosToursV2.c
 * @brief Test des fonctions crées dans le fichier fonctionsPageJeu.c et fonctionsMenuPrincipal.c.
 * @author Hannah Sergent
 * @date Crée le 29/03/2026
 */

int main(int argc, char * argv[]){

    if (initialisationCorrecte()) {

        int enCours = 1;

        t_joueur equipe1, equipe2;

        t_bombe bombe;

        t_vect vectVitesse;

        int bombeLancee = 0;
        int nombreRebonds = 0;

        // Variable de changement de tour
        t_tour gestionTours = {1, 1, D1, D6};

        SDL_Window *menuPrincipal;
        SDL_Renderer* zoneAffichage;
        SDL_Texture *texMap;
        SDL_Rect rectFen = {0, 0, LARGEUR_TERRAIN, HAUTEUR_TERRAIN};

        t_catalogue_zones catalogue;

        t_case (*matriceTerrain)[LARGEUR_TERRAIN] = NULL;

        if (!creerPageJeu(&menuPrincipal, &zoneAffichage, &texMap)){
            return 1;
        }

        initialiserRayonBombe(&bombe, RAYON);
        initialiserVitesse(&vectVitesse, VITESSE_X, VITESSE_Y);
        initialiserMatrice(&matriceTerrain);
        initialiserEquipes(&equipe1, &equipe2, &catalogue, matriceTerrain, zoneAffichage);

        afficherJeuSansBombe(&equipe1, &equipe2, &rectFen, zoneAffichage, texMap);

        Uint32 tempsPrecedent = SDL_GetTicks();
        
        while(enCours) {

            detecterEvenementMenuPrincipal(&enCours, &bombeLancee, &nombreRebonds, zoneAffichage, texMap, &rectFen, &bombe, &vectVitesse, &equipe1, &equipe2, gestionTours.dinoCourant, matriceTerrain);
            lancerBombe(&tempsPrecedent, &bombeLancee, &nombreRebonds, &bombe, &vectVitesse, matriceTerrain, &equipe1, &equipe2, &gestionTours, &rectFen, zoneAffichage, texMap);

        }

        // --- NETTOYAGE --- 

        destruireElementsJeu(&equipe1, &equipe2, matriceTerrain, texMap, zoneAffichage, menuPrincipal);
        IMG_Quit();
        TTF_Quit();
        SDL_Quit();

        return 0;
    }
    return 1;
}