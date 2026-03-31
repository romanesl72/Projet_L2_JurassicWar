#include "../lib/chargerMatrice.h"
#include "../lib/fonctionsMenuPrinc.h"
#include "../lib/fonctionsPageJeu.h"
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

            detecterEvenementMenuPrincipal(&enCours, boutons);
            afficherMenuPrincipal(zoneMenu, boutons, texImg, texImgMiroir);

        }

        detruireMenuPrincipal(&menuPrincipal, &zoneMenu, &texImg, &texImgMiroir);

        /* L'utilisateur a cliqué sur le bouton démarrer la partie */

        if (enCours == 2){
            printf("Partie Lancée ! \n");
            lancerPartie();
        }

        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return 0;
    }
    return 1;
}