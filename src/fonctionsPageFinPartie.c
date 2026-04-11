#include "../lib/fonctionsPageFinPartie.h"
#include "../lib/fonctionsPagesInformations.h"
#include "../lib/fonctionsVerification.h"
#include "../lib/fonctionsMenuPrinc.h"

#include <stdio.h>

/** 
 * @file fonctionsPageFinPartie.c
 * @brief Corps des fonctions liées à la fenêtre de fin de partie.
 * @author Hannah Sergent
 * @date Crée le 11/04/2026
 * @version 1.0
 */

/**
 * @fn void initialiserBoutonsFinPartie(SDL_Rect *boutons);
 * @brief La fonction initialise la liste des boutons de la fenêtre de fin de partie.
 * @author Hannah Sergent
 * @date Crée le 11/04/2026
 * @version 1.0
 * @param boutons un tableau de type SDL_Rect représentant chaque bouton
 */

void initialiserBoutonsFinPartie(SDL_Rect *boutons){
    
    int i;

    for (i = 0; i < 2; i++){
        boutons[i].w = LARGEUR_BOUTON;
        boutons[i].h = HAUTEUR_BOUTON;
        boutons[i].x = (LARGEUR_FEN_MENU - LARGEUR_BOUTON)/2;
        boutons[i].y = 480 + i * (HAUTEUR_BOUTON + ESPACEMENT_BOUTONS);
    }
}


/**
 * @fn int detecterEvenementsFenFinPartie(SDL_Rect *boutons);
 * @brief La fonction détecte si l'utilisateur réalise une action dans la fenêtre de fin de partie (cliquer sur un bouton, sur la croix pour fermer).
 * @author Hannah Sergent
 * @date Crée le 11/04/2026
 * @version 1.0
 * @param boutons un tableau de type SDL_Rect représentant chaque bouton
 * @return un entier entre 0 et 2 indiquant l'action qui vient de se produire 
 */

int detecterEvenementsFenFinPartie(SDL_Rect *boutons){

    SDL_Event evenement;
    int x,y;

    while (SDL_PollEvent(&evenement)){

        if (evenement.type == SDL_QUIT){
            return 0;
        }

        if(evenement.type == SDL_MOUSEBUTTONDOWN) {
            x = evenement.button.x;
            y = evenement.button.y;

            /* Retourner au menu principal quand on appuie sur le bouton retour*/
            if(x >= boutons[0].x && x <= boutons[0].x + boutons[0].w && y >= boutons[0].y && y <= boutons[0].y + boutons[0].h){
                return 2;
            }

            /* Fermer la fenêtre quand on clique sur le bouton quitter */
            if(x >= boutons[1].x && x <= boutons[1].x + boutons[1].w && y >= boutons[1].y && y <= boutons[1].y + boutons[1].h){
                return 0;
            }

        }
    }
    return 1;
}

/**
 * @fn void afficherFenFinPartie(SDL_Renderer *zoneInfos, SDL_Rect *boutonRetour, char *nomFen, t_tour *gestionTours)
 * @brief La fonction affiche une page de fin de partie avec le gagnant.
 * @author Hannah Sergent
 * @date Crée le 11/04/2026
 * @version 1.0
 * @param zoneInfos un pointeur sur la zone d'affichage d'informations
 * @param boutons un tableau de type SDL_Rect représentant chaque bouton
 * @param gestionTours un pointeur sur une structure gérant les tours du jeu
 */

void afficherFenFinPartie(SDL_Renderer *zoneInfos, SDL_Rect *boutons, t_tour *gestionTours){

    SDL_Rect bandeauTitre = {0, 40, LARGEUR_FEN_MENU, 100};
    SDL_Rect bandeauSousTitre = {0, 170, LARGEUR_FEN_MENU, 70};

    /* Variables pour les boutons */

    int i;
    char * texteBoutons[2] = {
        "Retour",
        "Quitter le jeu"
    };

    /* Variables pour le survol des boutons */

    int xSouris;
    int ySouris;
    int surBouton;

    /* Variables pour l'affichage du texte */

    SDL_Rect phrase1 = {0, 170, LARGEUR_FEN_MENU, 300};
    SDL_Rect phrase2 = {0, 220, LARGEUR_FEN_MENU, 300};
    char phraseEquipeGagnante[25];
    char phraseNombreTours[30];
    snprintf(phraseEquipeGagnante, 25, "L'équipe %d a gagné.", gestionTours->equipeCourante);
    snprintf(phraseNombreTours, 30, "La partie a duré %d tours.", gestionTours->numeroTour);

    /* Couleur du fond gris foncé */

    SDL_SetRenderDrawColor(zoneInfos,40,40,40,255);
    SDL_RenderClear(zoneInfos);

    /* Affichage du titre en haut du menu */

    SDL_SetRenderDrawColor(zoneInfos,20,20,20,255);
    SDL_RenderFillRect(zoneInfos, &bandeauTitre);
    afficherTexteCase(zoneInfos, "JURASSICWAR", &bandeauTitre, TAILLE_POLICE_TITRE);

    SDL_RenderFillRect(zoneInfos, &bandeauSousTitre);
    afficherTexteCase(zoneInfos, "Bilan de la partie", &bandeauSousTitre, TAILLE_POLICE_SOUS_TITRE);

    /* Affichage du texte */
    afficherTexteCase(zoneInfos, phraseEquipeGagnante, &phrase1, TAILLE_POLICE_PARAGRAPHE);
    afficherTexteCase(zoneInfos, phraseNombreTours, &phrase2, TAILLE_POLICE_PARAGRAPHE);

    /* Analyser si l'utilisateur survole les boutons */

    SDL_GetMouseState(&xSouris, &ySouris);

    /* Tracer les 2 boutons */

    for (i = 0; i < 2; i++) {

        surBouton = (xSouris >= boutons[i].x) && (xSouris <= boutons[i].x + boutons[i].w) && (ySouris >= boutons[i].y) && (ySouris <= boutons[i].y + boutons[i].h);

        if (surBouton){
            SDL_SetRenderDrawColor(zoneInfos, 255, 120, 150, 255);
        }
        else {
            SDL_SetRenderDrawColor(zoneInfos, 230, 150, 170, 255);
        }

        tracerBouton(zoneInfos, boutons[i], 12);
        afficherTexteCase(zoneInfos, texteBoutons[i], &boutons[i], TAILLE_POLICE_BOUTONS);
    }

    SDL_RenderPresent(zoneInfos);

}

void ouvrirFenFinPartie(t_tour *gestionTours){

    if (initialisationCorrecte()) {

        int enCours = 1;

        /* Les variables nécessaires à la fenêtre d'information */

        SDL_Rect boutons[2];
        initialiserBoutonsFinPartie(boutons);

        SDL_Window *fenInfos;
        SDL_Renderer* zoneInfos;

        if (!creerFenInfos(&fenInfos, &zoneInfos, "JurassicWar - Bilan de la partie")){
            return;
        }

        while(enCours == 1) {
            enCours = detecterEvenementsFenFinPartie(boutons);
            afficherFenFinPartie(zoneInfos, boutons, gestionTours);
        }

        detruireFenInfos(&fenInfos, &zoneInfos);

        if (enCours == 2){
            ouvrirMenuPrinc();
        }

        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
    }
}