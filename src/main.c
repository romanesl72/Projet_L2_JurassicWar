#include "../lib/types.h"
#include "../lib/fonctionsVerification.h"

#define LARGEUR_FEN_JEU 1050
#define HAUTEUR_FEN_JEU 650

#define LARGEUR_FEN_MENU 400
#define HAUTEUR_FEN_MENU 650

int main(int argc, char * argv[]){

    if (initialisationCorrecte()) {

        int enCours = 1;
        SDL_Event evenement;
        SDL_Window *menuPrincipal; 
        creerFenetre(&menuPrincipal, "MenuPrincipal", LARGEUR_FEN_MENU, HAUTEUR_FEN_MENU);

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