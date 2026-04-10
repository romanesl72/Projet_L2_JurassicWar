#include "../lib/fonctionsMenuPrinc.h"
#include "../lib/fonctionsPageJeu.h"
#include "../lib/fonctionsPagesInformations.h"
#include "../lib/fonctionsVerification.h"

#include <SDL2/SDL_image.h>
#include <stdio.h>

/** 
 * @file testFonctionsMenuPrinc.c
 * @brief Test des fonctions pour l'affichage du menu principal.
 * @author Hannah Sergent
 * @date Crée le 26/03/2026
 * @version 1.2
 */

/**
 * @brief Ouvrir un menu principal qui permet de lancer une partie ou d'accéder à des informations.
 * @param argc nombre d'arguments de la ligne de commande
 * @param argv tableau des arguments
 * @return 0 si tout s'est bien passé et 1 sinon
 * @version 1.2
 */

int main(int argc, char *argv[]) {

    if (initialisationCorrecte()) {

        int enCours = 1;

        /* Les variables nécessaires au menu principal */

        SDL_Rect boutons[4];
        initialiserBoutons(boutons);

        SDL_Window *menuPrincipal;
        SDL_Texture *texImg;
        SDL_Texture *texImgMiroir;
        SDL_Renderer* zoneMenu;

        if (!creerMenuPrincipal(&menuPrincipal, &zoneMenu, &texImg, &texImgMiroir)){
            return 1;
        }

        while(enCours == 1) {
            enCours = detecterEvenementsMenuPrincipal(boutons);
            afficherMenuPrincipal(zoneMenu, boutons, texImg, texImgMiroir);

        }

        detruireMenuPrincipal(&menuPrincipal, &zoneMenu, &texImg, &texImgMiroir);

        /* L'utilisateur a cliqué sur le bouton démarrer la partie */

        if (enCours == 2){
            printf("Partie Lancée ! \n");
            lancerPartieBombe();
        }
        if (enCours == 3){
            ouvrirFenInfos("Principales Règles du jeu","../res/reglesJeu.txt");
        }
        if (enCours == 4){
            ouvrirFenInfos("Liste des touches","../res/listeTouches.txt");
        }

        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return 0;
    }
    return 1;
}