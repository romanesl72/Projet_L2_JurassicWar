#include "../lib/fonctionsPagesInformations.h"
#include "../lib/fonctionsVerification.h"
#include "../lib/fonctionsMenuPrinc.h"

/** 
 * @file fonctionsPagesInformations.c
 * @brief Corps des fonctions liées aux fenêtres d'informations, c'est à dire la liste des touches et les règles du jeu.
 * @author Hannah Sergent
 * @date Crée le 01/04/2026
 * @version 1.0
 */

void initialiserBoutonRetour(SDL_Rect *boutonRetour){
    boutonRetour->w = LARGEUR_BOUTON;
    boutonRetour->h = HAUTEUR_BOUTON;
    boutonRetour->x = (LARGEUR_FEN_MENU - LARGEUR_BOUTON)/2;
    boutonRetour->y = 580;
}

int creerFenInfos(SDL_Window **fenInfos, SDL_Renderer **zoneInfos, char * titreFen){

        creerFenetre(fenInfos, titreFen, LARGEUR_FEN_MENU, HAUTEUR_FEN_MENU);

        *zoneInfos = SDL_CreateRenderer(*fenInfos, -1, SDL_RENDERER_ACCELERATED);

        if(!*fenInfos) {

            printf("Erreur lors de l'initialisation de la fenêtre d'information. \n");
            SDL_DestroyWindow(*fenInfos);
            TTF_Quit();
            IMG_Quit();
            SDL_Quit();
            return 0;

        }

        return 1;

}

void detecterEvenementFenInfos(int *enCours){

    SDL_Event evenement;

    while (SDL_PollEvent(&evenement)){

        if (evenement.type == SDL_QUIT){
            *enCours = 0;
        }
    }
}

void afficherFenInfos(SDL_Renderer *zoneInfos, SDL_Rect *boutonRetour){

    SDL_Rect bandeauTitre = {0, 40, LARGEUR_FEN_MENU, 100};

    /* Variables pour le survol des boutons */

    int xSouris;
    int ySouris;
    int surBouton;

    /* Couleur du fond gris foncé */

    SDL_SetRenderDrawColor(zoneInfos,40,40,40,255);
    SDL_RenderClear(zoneInfos);

    /* Affichage du titre en haut du menu */

    SDL_SetRenderDrawColor(zoneInfos,20,20,20,255);
    SDL_RenderFillRect(zoneInfos, &bandeauTitre);
    afficherTexteCase(zoneInfos, "JURASSICWAR", &bandeauTitre, TAILLE_POLICE_TITRE);

    /* Analyser si l'utilisateur survole les boutons */

    SDL_GetMouseState(&xSouris, &ySouris);

    /* Tracer les 4 boutons */

    surBouton = (xSouris >= boutonRetour->x) && (xSouris <= boutonRetour->x + boutonRetour->w) && (ySouris >= boutonRetour->y) && (ySouris <= boutonRetour->y + boutonRetour->h);

    if (surBouton){
        SDL_SetRenderDrawColor(zoneInfos, 255, 120, 150, 255);
    }
    else {
        SDL_SetRenderDrawColor(zoneInfos, 230, 150, 170, 255);
    }

    tracerBouton(zoneInfos, *boutonRetour, 12);
    afficherTexteCase(zoneInfos, "Retour", boutonRetour, TAILLE_POLICE_BOUTONS);

    SDL_RenderPresent(zoneInfos);

}

void detruireFenInfos(SDL_Window **fenInfos, SDL_Renderer **zoneInfos){

    if (*zoneInfos){
        SDL_DestroyRenderer(*zoneInfos);
        *zoneInfos = NULL;
    }

    if (*fenInfos){
        SDL_DestroyWindow(*fenInfos);
        *fenInfos = NULL;
    }
}

void ouvrirFenInfos(){

    if (initialisationCorrecte()) {

        int enCours = 1;

        /* Les variables nécessaires à la fenêtre d'information */

        SDL_Rect boutonRetour;
        initialiserBoutonRetour(&boutonRetour);

        SDL_Window *fenInfos;
        SDL_Renderer* zoneInfos;

        if (!creerFenInfos(&fenInfos, &zoneInfos, "JurassicWar - Principales Règles du jeu")){
            return;
        }

        while(enCours == 1) {
            detecterEvenementFenInfos(&enCours);
            afficherFenInfos(zoneInfos, &boutonRetour);
        }

        detruireFenInfos(&fenInfos, &zoneInfos);

        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
    }
}