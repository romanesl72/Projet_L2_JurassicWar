#include "../lib/types.h"
#include "../lib/fonctionsVerification.h"

/**
 * @file TestFonctionsVerification.c
 * @brief Test des fonctions crées dans le fichier fonctionsVerification.c
 * @author Hannah Sergent
 * @date Crée le 27/01/2026
 * @version 1.0
 */

/**
 * @def LARGEUR_FEN_VERIF
 * @brief Largeur de la fenêtre crée pour vérifier le fichier fonctionsVerification.c.
*/

#define LARGEUR_FEN_VERIF 400

/**
 * @def HAUTEUR_FEN_VERIF
 * @brief Largeur de la fenêtre crée pour vérifier le fichier fonctionsVerification.c.
*/

#define HAUTEUR_FEN_VERIF 650

/**
 * @brief Création d'une fenêtre avec les fonctions du fichier fonctionsVerification.c.
 * @param argc nombre d'arguments de la ligne de commande
 * @param argv tableau des arguments
 * @return 0 si tout s'est bien passé et 1 sinon
 * @version 1.0
 */

int main(int argc, char * argv[]){

    if (initialisationCorrecte()) {

        int enCours = 1;
        SDL_Event evenement;
        SDL_Window *menuPrincipal; 
        creerFenetre(&menuPrincipal, "JurassicWar - Menu Prinicpal", LARGEUR_FEN_VERIF, HAUTEUR_FEN_VERIF);

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