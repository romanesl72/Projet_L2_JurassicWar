#include <SDL2/SDL_ttf.h>

#include "../lib/types.h"
#include "../lib/fonctionsAffichage.h"
#include "../lib/fonctionsVerification.h"
#include "../lib/fonctionsMenuHIP.h"
#include "../lib/fonctionsStructJoueur.h"
#include "../lib/placer_dinos.h"

void afficher(SDL_Renderer *rendu, TTF_Font *police, SDL_Texture *texMap, SDL_Texture *texObjets[], char *nomsObjets[],
    t_joueur *equipe1, t_joueur *equipe2){

    SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255);
    SDL_RenderClear(rendu);

    /* --- SECTION HAUT : LE HIP --- */
    afficherInventaire(rendu, texObjets, 7);
    
    // CORRECTION : Utilisez '*' pour déréférencer les pointeurs
    afficherMenuPVDinos(rendu, police, *equipe1, *equipe2); 

    /* --- SECTION BAS : LE JEU --- */
    SDL_Rect rectJeu = {0, HAUTEUR_HIP, LARGEUR_FEN, HAUTEUR_JEU};
    SDL_RenderCopy(rendu, texMap, NULL, &rectJeu);

    // CORRECTION : Remplacez 'zoneAffichage' par 'rendu'
    afficherDinosAvecJeu(rendu, equipe1);
    afficherDinosAvecJeu(rendu, equipe2);
}