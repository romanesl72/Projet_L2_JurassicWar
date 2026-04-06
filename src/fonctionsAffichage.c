#include <SDL2/SDL_ttf.h>

#include "../lib/types.h"
#include "../lib/fonctionsAffichage.h"
#include "../lib/fonctionsVerification.h"
#include "../lib/fonctionsMenuHIP.h"
#include "../lib/fonctionsStructJoueur.h"

void afficher(SDL_Renderer *rendu, TTF_Font *police, SDL_Texture *texMap,
     SDL_Texture *texDinos[], SDL_Texture *texObjets[], char *nomsObjets[],
    t_joueur equipe1, t_joueur equipe2){

    SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255);
    SDL_RenderClear(rendu);

    /* --- SECTION HAUT : LE HIP --- */
    afficherInventaire(rendu, texObjets, 7);
    afficherMenuPVDinos(rendu, police, equipe1, equipe2);

    /* --- SECTION BAS : LE JEU --- */
    SDL_Rect rectJeu = {0, HAUTEUR_HIP, LARGEUR_FEN, HAUTEUR_JEU};
    SDL_RenderCopy(rendu, texMap, NULL, &rectJeu);

    // Affichage de l'Équipe 1
    for(int i=0; i<equipe1.n; i++) {
        SDL_Rect r1 = {equipe1.tab[i].pos.x, equipe1.tab[i].pos.y + HAUTEUR_HIP, 30, 30};
        // On utilise l'ID du dino pour choisir la bonne texture
        SDL_RenderCopy(rendu, texDinos[equipe1.tab[i].d - D1], NULL, &r1);
    }

    // Affichage de l'Équipe 2
    for(int i=0; i<equipe2.n; i++) {
        SDL_Rect r2 = {equipe2.tab[i].pos.x, equipe2.tab[i].pos.y + HAUTEUR_HIP, 30, 30};
        SDL_RenderCopy(rendu, texDinos[equipe2.tab[i].d - D1], NULL, &r2);
    }
}