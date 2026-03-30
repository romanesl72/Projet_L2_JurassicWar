#include "../lib/chargerMatrice.h"
#include "../lib/fonctionsMenuPrinc.h"
#include "../lib/fonctionsVerification.h"

#include <SDL2/SDL_image.h>
#include <stdio.h>

/** 
 * @file testFonctionsMenuPrinc.h
 * @brief Test des fonctions pour l'affichage du menu principal.
 * @author Hannah Sergent
 * @date Crée le 26/03/2026
 */

int main(int argc, char *argv[]) {

    if (initialisationCorrecte()) {

        int enCours = 1;

        SDL_Rect boutons[4];
        initialiserBoutons(boutons);

        SDL_Window *menuPrincipal;
        SDL_Texture *texImg;
        SDL_Texture *texImgMiroir;
        SDL_Renderer* zoneMenu;

        if (!creerMenuPrincipal(&menuPrincipal, &zoneMenu, &texImg, &texImgMiroir)){
            return 1;
        }

        while(enCours) {

            detecterEvenementMenuPrincipal(&enCours, boutons);
            afficherMenuPrincipal(zoneMenu, boutons, texImg, texImgMiroir);

        }

        detruireMenuPrincipal(&menuPrincipal, &zoneMenu, &texImg, &texImgMiroir);

        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return 0;
    }
    return 1;
}