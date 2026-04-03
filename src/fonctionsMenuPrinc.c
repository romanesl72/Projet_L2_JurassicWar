#include "../lib/fonctionsMenuPrinc.h"
#include "../lib/fonctionsPageJeu.h"
#include "../lib/fonctionsVerification.h"

#include <math.h>
#include <stdio.h>
#include <string.h>

/** 
 * @file fonctionsMenuPrinc.c
 * @brief Corps des fonctions pour l'affichage du menu principal.
 * @author Hannah Sergent
 * @date Crée le 26/03/2026
 */

void initialiserBoutons(SDL_Rect *boutons){
    
    int i;

    for (i = 0; i < 4; i++){
        boutons[i].w = LARGEUR_BOUTON;
        boutons[i].h = HAUTEUR_BOUTON;
        boutons[i].x = (LARGEUR_FEN_MENU - LARGEUR_BOUTON)/2;
        boutons[i].y = 190 + i * (HAUTEUR_BOUTON + ESPACEMENT_BOUTONS);
    }
}

/**
 * @fn void tracerCoinBouton(SDL_Renderer *zoneMenu, t_coordonnee *coorCoin, int rayon);
 * @brief La fonction trace un cercle de rayon rayon aux coordonnées coorCoin pour que le bouton ait des coins arrondis.
 * @author Hannah Sergent
 * @date Crée le 29/03/2026
 * @param zoneMenu un pointeur sur la zone du menu
 * @param coorCoin les coordonnées du coin du bouton
 * @param x la valeur que l'on veut attribuer à la coordonnée x
 * @param y la valeur que l'on veut attribuer à la coordonnée y
 */

void initialiserCoordonnees(t_coordonnee *coor, int x, int y){

    coor->x = x;
    coor->y = y;

}

/**
 * @fn void tracerCoinBouton(SDL_Renderer *zoneMenu, t_coordonnee *coorCoin, int rayon);
 * @brief La fonction trace un cercle de rayon rayon aux coordonnées coorCoin pour que le bouton ait des coins arrondis.
 * @author Hannah Sergent
 * @date Crée le 29/03/2026
 * @param zoneMenu un pointeur sur la zone du menu
 * @param coorCoin les coordonnées du coin du bouton
 * @param rayon le rayon du cercle à tracer
 */

void tracerCoinBouton(SDL_Renderer *zoneMenu, t_coordonnee *coorCoin, int rayon){

    int largeur;
    int hauteur;

    for(hauteur = -rayon; hauteur <= rayon; hauteur++){
        largeur = roundf(sqrt(rayon*rayon - hauteur*hauteur));
        SDL_RenderDrawLine(zoneMenu, coorCoin->x - largeur, coorCoin->y + hauteur, coorCoin->x + largeur, coorCoin->y + hauteur);
    }
}

void tracerBouton(SDL_Renderer *zoneMenu, SDL_Rect rectBouton, int rayon){

    SDL_Rect rectangleCentral = {rectBouton.x + rayon, rectBouton.y, rectBouton.w - 2*rayon, rectBouton.h};
    SDL_Rect rectangleGauche = {rectBouton.x, rectBouton.y + rayon, rayon, rectBouton.h - 2*rayon};
    SDL_Rect rectangleDroit = {rectBouton.x + rectBouton.w - rayon, rectBouton.y + rayon, rayon, rectBouton.h - 2*rayon};

    t_coordonnee coorCoinHg;
    t_coordonnee coorCoinBg;
    t_coordonnee coorCoinHd;
    t_coordonnee coorCoinBd;

    initialiserCoordonnees(&coorCoinHg, rectBouton.x + rayon, rectBouton.y + rayon);
    initialiserCoordonnees(&coorCoinBg, rectBouton.x + rayon, rectBouton.y + rectBouton.h - rayon - 1);
    initialiserCoordonnees(&coorCoinHd, rectBouton.x + rectBouton.w - rayon - 1, rectBouton.y + rayon);
    initialiserCoordonnees(&coorCoinBd, rectBouton.x + rectBouton.w - rayon - 1, rectBouton.y + rectBouton.h - rayon - 1);

    SDL_RenderFillRect(zoneMenu, &rectangleCentral);
    SDL_RenderFillRect(zoneMenu, &rectangleGauche);
    SDL_RenderFillRect(zoneMenu, &rectangleDroit);

    tracerCoinBouton(zoneMenu, &coorCoinHg, rayon);
    tracerCoinBouton(zoneMenu, &coorCoinBg, rayon);
    tracerCoinBouton(zoneMenu, &coorCoinHd, rayon);
    tracerCoinBouton(zoneMenu, &coorCoinBd, rayon);

}

void afficherTexteCase(SDL_Renderer* zoneMenu, char *texte, SDL_Rect *rectCase, int tailleTexte){

    /* Police choisie pour le texte */
    
    TTF_Font *police;
    initialiserPolice(&police, "../pde/arial.ttf", tailleTexte);

    /* Le texte est écrit en blanc */ 

    SDL_Color couleurTexte = {255, 255, 255, 255};

    SDL_Surface *surfaceTexte = TTF_RenderUTF8_Blended_Wrapped(police, texte, couleurTexte, LARGEUR_FEN_MENU);
    SDL_Texture *textureTexte = SDL_CreateTextureFromSurface(zoneMenu, surfaceTexte);
    
    /* Position du texte centrée dans la case */

    SDL_Rect rectTexte = {0, 0, surfaceTexte->w, surfaceTexte->h};
    rectTexte.x = rectCase->x + (rectCase->w - rectTexte.w)/2;
    rectTexte.y = rectCase->y + (rectCase->h - rectTexte.h)/2; 

    /* Ecrire le texte sur le menu */

    SDL_RenderCopy(zoneMenu, textureTexte, NULL, &rectTexte);

    /* Destruction */

    SDL_FreeSurface(surfaceTexte);
    SDL_DestroyTexture(textureTexte);
    TTF_CloseFont(police);
}

void afficherMenuPrincipal(SDL_Renderer *zoneMenu, SDL_Rect *boutons, SDL_Texture *texImg, SDL_Texture *texImgMiroir){

    SDL_Rect bandeauTitre = {0, 40, LARGEUR_FEN_MENU, 100};

    /* Variables pour les boutons */

    int i;
    char * texteBoutons[4] = {
        "Démarrer une partie",
        "Règles du jeu",
        "Liste des touches",
        "Quitter le jeu"
    };

    /* Variables pour le survol des boutons */

    int xSouris;
    int ySouris;
    int surBouton;

    /* Position des images */

    SDL_Rect rectImg = {LARGEUR_FEN_MENU/2 - 100, 600, 70, 70};
    SDL_Rect rectImgMiroir = {LARGEUR_FEN_MENU/2 + 30, 600, 70, 70};

    /* Couleur du fond gris foncé */

    SDL_SetRenderDrawColor(zoneMenu,40,40,40,255);
    SDL_RenderClear(zoneMenu);

    /* Affichage du titre en haut du menu*/

    SDL_SetRenderDrawColor(zoneMenu,20,20,20,255);
    SDL_RenderFillRect(zoneMenu, &bandeauTitre);
    afficherTexteCase(zoneMenu, "JURASSICWAR", &bandeauTitre, TAILLE_POLICE_TITRE);

    /* Analyser si l'utilisateur survole les boutons */

    SDL_GetMouseState(&xSouris, &ySouris);

    /* Tracer les 4 boutons */

    for (i = 0; i < 4; i++) {

        surBouton = (xSouris >= boutons[i].x) && (xSouris <= boutons[i].x + boutons[i].w) && (ySouris >= boutons[i].y) && (ySouris <= boutons[i].y + boutons[i].h);

        if (surBouton){
            SDL_SetRenderDrawColor(zoneMenu, 255, 120, 150, 255);
        }
        else {
            SDL_SetRenderDrawColor(zoneMenu, 230, 150, 170, 255);
        }

        tracerBouton(zoneMenu, boutons[i], 12);
        afficherTexteCase(zoneMenu, texteBoutons[i], &boutons[i], TAILLE_POLICE_BOUTONS);
    }

    /* Afficher les images */

    SDL_RenderCopy(zoneMenu, texImg, NULL, &rectImg);
    SDL_RenderCopy(zoneMenu, texImgMiroir, NULL, &rectImgMiroir);

    SDL_RenderPresent(zoneMenu);

}

void detecterEvenementsMenuPrincipal(int *enCours, SDL_Rect *boutons){

    SDL_Event evenement;
    int x,y;
    int i;

    while (SDL_PollEvent(&evenement)){

        if (evenement.type == SDL_QUIT){
            *enCours = 0;
        }

        if(evenement.type == SDL_MOUSEBUTTONDOWN) {
            x = evenement.button.x;
            y = evenement.button.y;

            for (i = 1; i < 3; i++){

                if(x >= boutons[i].x && x <= boutons[i].x + boutons[i].w && y >= boutons[i].y && y <= boutons[i].y + boutons[i].h){
                    printf("Bouton %d cliqué  \n", i);
                }
            }

            // Lancer une partie quand on appuie sur le bouton démarrer
            if(x >= boutons[0].x && x <= boutons[0].x + boutons[0].w && y >= boutons[0].y && y <= boutons[0].y + boutons[0].h){
                *enCours = 2;
            }

            // Fermer la fenêtre quand on clique sur le bouton quitter
            if(x >= boutons[3].x && x <= boutons[3].x + boutons[3].w && y >= boutons[3].y && y <= boutons[3].y + boutons[3].h){
                *enCours = 0;
            }

        }
    }
}

int creerMenuPrincipal(SDL_Window **menuPrincipal, SDL_Renderer **zoneMenu, SDL_Texture **texImg, SDL_Texture **texImgMiroir){

        creerFenetre(menuPrincipal, "JurassicWar - Menu principal", LARGEUR_FEN_MENU, HAUTEUR_FEN_MENU);

        *zoneMenu = SDL_CreateRenderer(*menuPrincipal, -1, SDL_RENDERER_ACCELERATED);

        if(!*zoneMenu) {

            printf("Erreur lors de l'initialisation de la zone du menu \n.");
            SDL_DestroyWindow(*menuPrincipal);
            TTF_Quit();
            IMG_Quit();
            SDL_Quit();
            return 0;

        }

        chargerImageSansTaille(*zoneMenu, texImg, "../img/dinoMenu.png");
        chargerImageSansTaille(*zoneMenu, texImgMiroir, "../img/dinoMenuMiroir.png");

        return 1;

}

void detruireMenuPrincipal(SDL_Window **menuPrincipal, SDL_Renderer **zoneMenu, SDL_Texture **texImg, SDL_Texture **texImgMiroir){

    if (*texImg){
        SDL_DestroyTexture(*texImg);
        *texImg = NULL;
    }

    if (*texImgMiroir){
        SDL_DestroyTexture(*texImgMiroir);
        *texImgMiroir = NULL;
    }

    if (*zoneMenu){
        SDL_DestroyRenderer(*zoneMenu);
        *zoneMenu = NULL;
    }

    if (*menuPrincipal){
        SDL_DestroyWindow(*menuPrincipal);
        *menuPrincipal = NULL;
    }
}

void ouvrirMenuPrincBombe(){

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
            return;
        }

        while(enCours == 1) {

            detecterEvenementsMenuPrincipal(&enCours, boutons);
            afficherMenuPrincipal(zoneMenu, boutons, texImg, texImgMiroir);

        }

        detruireMenuPrincipal(&menuPrincipal, &zoneMenu, &texImg, &texImgMiroir);

        /* L'utilisateur a cliqué sur le bouton démarrer la partie */

        if (enCours == 2){
            printf("Partie Lancée ! \n");
            lancerPartieBombe();
        }

        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
    }
}

void ouvrirMenuPrinc(){

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
            return;
        }

        while(enCours == 1) {

            detecterEvenementsMenuPrincipal(&enCours, boutons);
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
    }
}

