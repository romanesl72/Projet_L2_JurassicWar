#include "../lib/types.h"
#include "../lib/fonctionsVerification.h"

/**
 * @file TestFonctionsVerification.c
 * @brief Test des fonctions crées dans le fichier fonctionsVerification.c
 * @author Hannah Sergent
 * @date Crée le 27/01/2026
 * @version 1.0
 */

#define LARGEUR_FEN_MENU 400
#define HAUTEUR_FEN_MENU 650

int main(int argc, char * argv[]){

    if (initialisationCorrecte()) {

        int enCours = 1;
        SDL_Event evenement;
        SDL_Window *menuPrincipal; 
        creerFenetre(&menuPrincipal, "JurassicWar - Menu Prinicpal", LARGEUR_FEN_MENU, HAUTEUR_FEN_MENU);

        while(enCours) {
            while (SDL_PollEvent(&evenement)){
                if (evenement.type == SDL_QUIT){
                    enCours = 0;
                }
            }
        }

        SDL_DestroyWindow(menuPrincipal);
        IMG_Quit();
        TTF_Quit();
        SDL_Quit();

        return 0;
    }
    return 1;

}