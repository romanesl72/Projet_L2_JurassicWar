#include "../lib/fonctionsPagesInformations.h"
#include "../lib/fonctionsVerification.h"
#include "../lib/fonctionsMenuPrinc.h"
#include <stdio.h>

/** 
 * @file fonctionsPagesInformations.c
 * @brief Corps des fonctions liées aux fenêtres d'informations, c'est à dire la liste des touches et les règles du jeu.
 * @author Hannah Sergent
 * @date Crée le 01/04/2026
 * @version 1.0
 */

/**
 * @fn void initialiserBoutonRetour(SDL_Rect *boutonRetour);
 * @brief La fonction initialise le bouton retour des fenêtres d'information.
 * @author Hannah Sergent
 * @date Crée le 01/04/2026
 * @version 1.0
 * @param boutonRetour un pointeur sur une structure SDL_Rect représentant un bouton
 */

void initialiserBoutonRetour(SDL_Rect *boutonRetour){
    boutonRetour->w = LARGEUR_BOUTON;
    boutonRetour->h = HAUTEUR_BOUTON;
    boutonRetour->x = (LARGEUR_FEN_MENU - LARGEUR_BOUTON)/2;
    boutonRetour->y = 580;
}

int creerFenInfos(SDL_Window **fenInfos, SDL_Renderer **zoneInfos, char *titreFen){

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

/**
 * @fn int detecterEvenementFenInfos(SDL_Rect *boutonRetour);
 * @brief La fonction détecte si l'utilisateur réalise une action dans la fenêtre d'information.
 * @author Hannah Sergent
 * @date Crée le 01/04/2026
 * @version 1.0
 * @param boutonRetour un pointeur sur le bouton permettant de quitter la fenêtre
 * @return un entier entre 0 et 2 indiquant l'action qui vient de se produire 
 */

int detecterEvenementFenInfos(SDL_Rect *boutonRetour){

    SDL_Event evenement;
    int x,y;

    while (SDL_PollEvent(&evenement)){

        if (evenement.type == SDL_QUIT){
            return 0;
        }

        if(evenement.type == SDL_MOUSEBUTTONDOWN) {
            x = evenement.button.x;
            y = evenement.button.y;

            // Fermer la fenêtre quand on clique sur le bouton quitter
            if(x >= boutonRetour->x && x <= boutonRetour->x + boutonRetour->w && y >= boutonRetour->y && y <= boutonRetour->y + boutonRetour->h){
                return 2;
            }
        }
    }
    return 1;
}

/**
 * @fn char* lireInfosFichier(char *nomFichier)
 * @brief La fonction lit les informations à afficher dans la fenêtre d'information.
 * @author Hannah Sergent
 * @date Crée le 01/04/2026
 * @version 1.0
 * @param nomFichier le nom du fichier à lire
 * @return une chaîne de caractère contenant le texte à afficher dans la fenêtre d'information
 */

char* lireInfosFichier(char *nomFichier){

    FILE *fichier = fopen(nomFichier, "r");
    int nbCar;
    int i = 0;
    char carLu;
    char *texteInfos;

    if (fichier == NULL){
        return NULL;
    }

    fseek(fichier, 0, SEEK_END);
    nbCar = ftell(fichier);

    texteInfos = malloc(nbCar * (sizeof(char) + 1));

    if (!texteInfos){
        printf("L'allocation de mémoire pour lire le fichier a échoué. \n");
        fclose(fichier);
        return NULL;
    }

    rewind(fichier);

    while(fscanf(fichier, "%c", &carLu) == 1){
        texteInfos[i++] = carLu;
    }

    texteInfos[i] = '\0';
    fclose(fichier);
    return texteInfos;
}

/**
 * @fn void afficherFenInfos(SDL_Renderer *zoneInfos, SDL_Rect *boutonRetour, char *nomFen, char *nomFichier)
 * @brief La fonction affiche une page d'information sur le jeu.
 * @author Hannah Sergent
 * @date Crée le 01/04/2026
 * @version 1.1
 * @param zoneInfos un pointeur sur la zone d'affichage d'informations
 * @param boutonRetour un pointeur sur le bouton permettant de quitter la fenêtre
 * @param nomFen le nom donné à la fenêtre
 * @param nomFichier le nom du fichier contenant les informations à afficher sur le jeu
 */

void afficherFenInfos(SDL_Renderer *zoneInfos, SDL_Rect *boutonRetour, char *nomFen, char *nomFichier){

    SDL_Rect bandeauTitre = {0, 40, LARGEUR_FEN_MENU, 100};
    SDL_Rect bandeauSousTitre = {0, 170, LARGEUR_FEN_MENU, 70};

    /* Variables pour le survol des boutons */

    int xSouris;
    int ySouris;
    int surBouton;

    /* Variables pour l'affichage du texte */

    SDL_Rect paragraphe = {10, 260, LARGEUR_FEN_MENU, 300};
    char *texteInfos = lireInfosFichier(nomFichier);

    if (texteInfos == NULL){
        printf("Erreur lors de la lecture du fichier. \n");
    }

    /* Couleur du fond gris foncé */

    SDL_SetRenderDrawColor(zoneInfos,40,40,40,255);
    SDL_RenderClear(zoneInfos);

    /* Affichage du titre en haut du menu */

    SDL_SetRenderDrawColor(zoneInfos,20,20,20,255);
    SDL_RenderFillRect(zoneInfos, &bandeauTitre);
    afficherTexteCase(zoneInfos, "JURASSICWAR", &bandeauTitre, TAILLE_POLICE_TITRE);

    SDL_RenderFillRect(zoneInfos, &bandeauSousTitre);
    afficherTexteCase(zoneInfos, nomFen, &bandeauSousTitre, TAILLE_POLICE_SOUS_TITRE);

    /* Affichage du texte */
    afficherTexteCase(zoneInfos, texteInfos, &paragraphe, TAILLE_POLICE_PARAGRAPHE);

    /* Analyser si l'utilisateur survole les boutons */

    SDL_GetMouseState(&xSouris, &ySouris);

    /* Tracer le bouton retour */

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

void ouvrirFenInfos(char *nomFen, char *nomFichier){

    if (initialisationCorrecte()) {

        int enCours = 1;

        /* Les variables nécessaires à la fenêtre d'information */

        SDL_Rect boutonRetour;
        initialiserBoutonRetour(&boutonRetour);

        SDL_Window *fenInfos;
        SDL_Renderer* zoneInfos;

        char *nomJeu = "JurassicWar - ";
        char *intituleFen = malloc(sizeof(char)*(strlen(nomJeu) + strlen(nomFen) + 1));
        strcpy(intituleFen, nomJeu);
        strcat(intituleFen, nomFen);

        if (!creerFenInfos(&fenInfos, &zoneInfos, intituleFen)){
            return;
        }

        while(enCours == 1) {
            enCours = detecterEvenementFenInfos(&boutonRetour);
            afficherFenInfos(zoneInfos, &boutonRetour, nomFen, nomFichier);
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