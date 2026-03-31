#include <stdio.h>
#include <stdlib.h>

#include "../lib/fonctionsMenuHIP.h"
#include "../lib/fonctionsVerification.h"

#define HAUTEUR_HIP 100
#define LARGEUR_INVENTAIRE 650
#define HAUTEUR_FEN_TOTALE (HAUTEUR_FEN_JEU + HAUTEUR_HIP)


void afficherTexte(SDL_Renderer *rendu, TTF_Font *police, char *message, int x, int y, SDL_Color couleur) {
    if (!police || !message) return;
    
    SDL_Surface *surface = TTF_RenderText_Blended(police, message, couleur);
    
    if (!surface) return;
    
    SDL_Texture *texture = SDL_CreateTextureFromSurface(rendu, surface);
    
    SDL_Rect dest = {x, y, surface->w, surface->h};
    SDL_RenderCopy(rendu, texture, NULL, &dest);
    
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

// Affiche les 7 cases d'objets à gauche
void afficherInventaire(SDL_Renderer *rendu, SDL_Texture **texObjets, int nbObjets) {
    int i;
    int tailleCase = LARGEUR_INVENTAIRE / nbObjets;
    
    for (i = 0; i < nbObjets; i++) {
        SDL_Rect rCase = {i * tailleCase, 0, tailleCase, HAUTEUR_HIP};
        
        // Fond de la case
        SDL_SetRenderDrawColor(rendu, 40, 40, 40, 255);
        SDL_RenderFillRect(rendu, &rCase);
        

        // Affichage de l'image de l'objet (si elle existe)
        if (texObjets[i] != NULL) {
            SDL_RenderCopy(rendu, texObjets[i], NULL, &rCase);
        }

        // Bordure grise pour séparer les cases
        SDL_SetRenderDrawColor(rendu, 80, 80, 80, 255);
        SDL_RenderDrawRect(rendu, &rCase);
    }
}

void afficherBarrePV(SDL_Renderer *rendu, t_dino dino, int x, int y) {
    int largeurMax = 100; // Largeur de la barre quand le dino a 100 PV
    int hauteurBarre = 15;
    
    /* Calcul de la largeur actuelle (proportionnelle aux PV) */
    int largeurActuelle = (dino.pv * largeurMax) / 100;
    if (largeurActuelle < 0) largeurActuelle = 0;

    /* Choix de la couleur selon la santé */
    if (dino.pv > 50){
        SDL_SetRenderDrawColor(rendu, 0, 255, 0, 255); // Vert
    }
    else if (dino.pv > 20){
        SDL_SetRenderDrawColor(rendu, 255, 165, 0, 255); // Orange
    }
    else{
        SDL_SetRenderDrawColor(rendu, 255, 0, 0, 255); // Rouge
    }

    /* Dessin du remplissage */
    SDL_Rect rPV = {x, y, largeurActuelle, hauteurBarre};
    SDL_RenderFillRect(rendu, &rPV);

    /* Dessin de la bordure (contour blanc/gris) */
    SDL_SetRenderDrawColor(rendu, 200, 200, 200, 255);
    SDL_Rect rBordure = {x, y, largeurMax, hauteurBarre};
    SDL_RenderDrawRect(rendu, &rBordure);
}

void afficherMenuPVDinos(SDL_Renderer *rendu, TTF_Font *police, t_joueur e1, t_joueur e2) {
    int i;
    SDL_Color blanc = {255, 255, 255, 255};
    char buffer[20];
    int xBase = 660; // Juste après l'inventaire (650 + 10 de marge)
    int xPos;

    /* --- Équipe 1 (Ligne du haut dans le HUD) --- */
    for (i = 0; i < e1.n; i++) {
        sprintf(buffer, "Dino %d :", i + 1);
        
        // On affiche le texte (ici je suppose que tu as une fonction utilitaire pour le texte)
        // La position X est décalée pour chaque dino (ex: tous les 200px)
        xPos = xBase + (i * 210);
        afficherTexte(rendu, police, buffer, xPos, 15, blanc);
        
        // On appelle ta fonction de barre de PV juste à côté du texte (+60px)
        afficherBarrePV(rendu, e1.tab[i], xPos + 70, 20);
    }

    /* --- Équipe 2 (Ligne du bas dans le HUD) --- */
    for (i = 0; i < e2.n; i++) {
        sprintf(buffer, "Dino %d :", i + 4); // i+4 pour correspondre aux IDs D4, D5, D6
        
        xPos = xBase + (i * 210);
        afficherTexte(rendu, police, buffer, xPos, 55, blanc);
        
        // Appel de la barre de PV
        afficherBarrePV(rendu, e2.tab[i], xPos + 70, 60);
    }
}

