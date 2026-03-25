#include "../lib/fonctionsMenuPrinc.h"
#include "../lib/fonctionsVerification.h"

#include <SDL2/SDL_ttf.h>

void afficherBouton(SDL_Renderer* zoneMenu, char *texteBouton, SDL_Rect *bouton){

    /* Police du bouton */
    TTF_Font *police;
    initialiserPolice(&police, "../pde/arial.ttf", TAILLE_POLICE_MENU);

    /* Couleur du texte du bouton*/
    SDL_Color couleurTexte = {255, 255, 255, 255};

    SDL_Surface * surfaceTexte = TTF_RenderText_Blended(police, texteBouton, couleurTexte);
    SDL_Texture *textureTexte = SDL_CreateTextureFromSurface(zoneMenu, surfaceTexte);
    
    /* Position du texte dans le bouton */
    SDL_Rect rectTexte = {0, 0, surfaceTexte->w, surfaceTexte->h};
    SDL_FreeSurface(surfaceTexte);

    rectTexte.x = bouton->x + (bouton->w - rectTexte.w)/2;
    rectTexte.y = bouton->y + (bouton->h - rectTexte.h)/2; 

    SDL_RenderFillRect(zoneMenu, bouton);

    // Dessiner le texte
    SDL_RenderCopy(zoneMenu, textureTexte, NULL, &rectTexte);

    SDL_DestroyTexture(textureTexte);
    TTF_CloseFont(police);
}