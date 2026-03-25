#include "../lib/chargerMatrice.h"
#include "../lib/fonctionsMenuPrinc.h"
#include "../lib/fonctionsVerification.h"

#include <SDL2/SDL_image.h>

int main(int argc, char *argv[]) {

    SDL_Window *menuPrincipal;
    /* SDL_Window *pageJeu; */

    int enCours = 1;
    SDL_Event evenement;

    int xSouris;
    int ySouris;
    int surBouton;


    if (initialisationCorrecte()) {

        creerFenetre(&menuPrincipal, "MenuPrincipal", LARGEUR_FEN_MENU, HAUTEUR_FEN_MENU);

        /* creerFenetre(&pageJeu, "Jeu", LARGEUR_TERRAIN, HAUTEUR_TERRAIN); */

        SDL_Renderer* zoneMenu = SDL_CreateRenderer(menuPrincipal, -1, SDL_RENDERER_ACCELERATED);

        if(!zoneMenu) {
            printf("Erreur de l'initialisation de la zone du menu \n.");
            SDL_DestroyWindow(menuPrincipal);
            IMG_Quit();
            SDL_Quit();
            return 1;
        }

        // Taille et position du bouton

        SDL_Rect bouton = {0, 100, 200, 80};
        bouton.x = (LARGEUR_FEN_MENU - bouton.w)/2;
        SDL_Rect boutonQuitter = {20, 300, 200, 80};
        boutonQuitter.x = (LARGEUR_FEN_MENU - boutonQuitter.w)/2;

        int x,y;

        while(enCours) {

            while (SDL_PollEvent(&evenement)){
                if (evenement.type == SDL_QUIT){
                    enCours = 0;
                }

                if(evenement.type == SDL_MOUSEBUTTONDOWN) {
                    x = evenement.button.x;
                    y = evenement.button.y;

                    if(x >= bouton.x && x <= bouton.x + bouton.w && y >= bouton.y && y <= bouton.y + bouton.h){
                        printf("Bouton cliqué \n");
                    }
                }
            }

            SDL_GetMouseState(&xSouris, &ySouris);
            surBouton = (xSouris >= bouton.x) && (xSouris <= bouton.x + bouton.w) && (ySouris >= bouton.y) && (ySouris <= bouton.y + bouton.h);

            SDL_SetRenderDrawColor(zoneMenu,30,30,30,255);
            SDL_RenderClear(zoneMenu);

            // Couleur du bouton
            if (surBouton){
                SDL_SetRenderDrawColor(zoneMenu,200,80,80,255);
            }
            else {
                SDL_SetRenderDrawColor(zoneMenu,150,50,50,255);
            }

            afficherBouton(zoneMenu, "Lancer le jeu", &bouton);
            afficherBouton(zoneMenu, "Quitter le jeu", &boutonQuitter);

            SDL_RenderPresent(zoneMenu);
        
        }

        SDL_DestroyRenderer(zoneMenu);

        SDL_DestroyWindow(menuPrincipal);

        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return 0;
    }
    return 1;
}