#include "../lib/chargerMatrice.h"
#include "../lib/types.h"
#include "../lib/tda_nuage.h"
#include "../lib/fonctionsVerification.h"
#include "../lib/placer_dinos.h"
#include "../lib/gestion_zones.h"
#include "../lib/fonctionsMenuHIP.h"
#include "../lib/fonctionsTirs.h"
#include "../lib/fonctionsRebonds.h"
#include "../lib/fonctionsPlacementBombe.h"
#include "../lib/fonctionsStructJoueur.h"
#include "../lib/fonctionSoin.h"
#include <time.h>
#include <SDL2/SDL_ttf.h>

#define LARGEUR_FEN 1300
#define HAUTEUR_HIP 100
#define HAUTEUR_JEU 700
#define HAUTEUR_TOTALE (HAUTEUR_HIP + HAUTEUR_JEU)

int main(int argc, char * argv[]){

    int i,j;
    const Uint8 *clavier = NULL;

    /* ---- Initialisation de la fenêtre---- */
    if (!initialisationCorrecte()) return 1;
    srand(time(NULL));

    SDL_Window *fenetre = NULL;
    SDL_Renderer *rendu = NULL;
    TTF_Font *police = NULL;

    creerFenetre(&fenetre, "Test Complet : Armes & Degats", LARGEUR_FEN, HAUTEUR_TOTALE);
    rendu = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_SOFTWARE);
    initialiserPolice(&police, "../pde/arial.ttf", 16);

    /* ---- Initialisation de la Map ---- */
    
    int nb_pts, w, h;
    int trouvés_E1 = 0, trouvés_E2 = 0;
    float graviteMonde = 0.5f;
    int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN];
    t_coordonnee *nuages_stockes[3];
    t_catalogue_zones catalogue;
    

    chargerMatriceDepuisFichier("../res/matrice.txt", matrice);
    nuages_stockes[1] = nuage_de_points(&nb_pts, "../img/test1_c.jpg");
    generer_catalogue_depuis_nuage(nuages_stockes[1], nb_pts, &catalogue, &trouvés_E1, &trouvés_E2, 1);
    nuages_stockes[2] = nuage_de_points(&nb_pts, "../img/test2_c.jpg");
    generer_catalogue_depuis_nuage(nuages_stockes[2], nb_pts, &catalogue, &trouvés_E1, &trouvés_E2, 2);

    /* ---- Initialisation des Joueurs et des Equipes ---- */
    t_joueur equipe1, equipe2;
    equipe1.n = 3; equipe2.n = 3;
    equipe1.tab = malloc(sizeof(t_dino) * equipe1.n);
    equipe2.tab = malloc(sizeof(t_dino) * equipe2.n);

    equipe1.tabCote = malloc(sizeof(t_cote) * equipe1.n);
    equipe2.tabCote = malloc(sizeof(t_cote) * equipe2.n);

    // Initialise les directions par défaut pour éviter des valeurs aléatoires
    for(i = 0; i < 3; i++) {
        equipe1.tabCote[i] = DROITE;
        equipe2.tabCote[i] = GAUCHE;
    }
    
    placer_une_equipe(&equipe1, catalogue.zones_E1, matrice, D1);
    placer_une_equipe(&equipe2, catalogue.zones_E2, matrice, D4);

    for(i=0; i<3; i++) {
        equipe1.tab[i].pv = 100;
        equipe2.tab[i].pv = 100;
    }

    /* ---- Initialisation des Armes ---- */
    t_dino *tireur = NULL;

    t_arme catalogue_armes[4]; // Arc, Arbalete, Bombe Fusil, Revolver
    catalogue_armes[0] = (t_arme){ARC, 20, 1.0f, 5.0f, 15.0f};
    catalogue_armes[1] = (t_arme){ARBALETE, 35, 1.2f, 8.0f, 18.0f};
    catalogue_armes[2] = (t_arme){FUSIL, 45, 0.4f, 15.0f, 30.0f};
    catalogue_armes[3] = (t_arme){REVOLVER, 30, 0.6f, 13.0f, 25.0f};
    
    
    int enCours = 1;

    t_tir tir;              /* Pour flèches/balles */
    tir.actif = 0;


    /* ---- Chargement Textures ---- */
    SDL_Texture *texMap = NULL, *texDinos[6], *texDinosInv[6], *texObjets[7];
    char *nomsObjets[7] = {"../img/img_arc.png", "../img/img_arbalete.png", "../img/img_bombe.png", 
                           "../img/img_fusil.png", "../img/img_revolver.png", "../img/img_potion.png", "../img/img_grappin.png"};

    chargerImage(rendu, &texMap, "../img/test1_b.jpg", &w, &h);

    equipe1.texDinos = malloc(sizeof(SDL_Texture*) * 6);
    equipe1.texDinosInv = malloc(sizeof(SDL_Texture*) * 6);
    equipe2.texDinos = malloc(sizeof(SDL_Texture*) * 6);
    equipe2.texDinosInv = malloc(sizeof(SDL_Texture*) * 6);
    
    for(j=0; j<6; j++) {
        chargerImage(rendu, &texDinos[j], "../img/dinoTransparent.png", &w, &h);
        chargerImage(rendu, &texDinosInv[j], "../img/dinoTransparent.png", &w, &h);
        // On lie les textures aux structures joueurs
        equipe1.texDinos[j] = texDinos[j];
        equipe1.texDinosInv[j] = texDinosInv[j];
        equipe2.texDinos[j] = texDinos[j];
        equipe2.texDinosInv[j] = texDinosInv[j];
    }

    
    for(i=0; i<7; i++) chargerImage(rendu, &texObjets[i], nomsObjets[i], &w, &h);

    /* ---- Initialisation ---- */

    while(enCours) {
        SDL_Event evenement;
        while(SDL_PollEvent(&evenement)) {
            if(evenement.type == SDL_QUIT) enCours = 0;
        }

        clavier = SDL_GetKeyboardState(NULL);
        tireur = recupererDinoNumero(&equipe1, &equipe2, D1);

        SDL_PumpEvents();

        // Tir et Visée
        if (!tir.actif){
            int touchePressee = 0;

            /*On vérifie quelle touche est pressée pour choisir l'arme*/
            if (clavier[SDL_SCANCODE_Q]) {
                tir.arme_source = catalogue_armes[0];
                printf("Arme : ARC\n");
                touchePressee = 1;
            }
            else if (clavier[SDL_SCANCODE_A]) {
                tir.arme_source = catalogue_armes[1];
                printf("Arme : ARBALETE\n");
                touchePressee = 1;
            }
            else if (clavier[SDL_SCANCODE_F]) {
                tir.arme_source = catalogue_armes[2];
                printf("Arme : FUSIL\n");
                touchePressee = 1;
            }
            else if (clavier[SDL_SCANCODE_R]) {
                tir.arme_source = catalogue_armes[3];
                printf("Arme : REVOLVER\n");
                touchePressee = 1;
            }
            else if (clavier[SDL_SCANCODE_B]) {
                printf("Bombe a utilisé\n");
            }
            else if (clavier[SDL_SCANCODE_P]) {
                printf("Soin : POTION\n");
                utiliserPotion(tireur);
            }
            else if (clavier[SDL_SCANCODE_G]) {
                printf("Grappin non implémenté\n");
            }
            
            if (touchePressee && tireur != NULL) {
                /* On replace le tir sur le dino avant de viser */
                tir.pos.x = tireur->pos.x + 15;
                tir.pos.y = tireur->pos.y + 15;
                
                printf("Ok1\n");
                printf("%d\n", tireur->d);
                /* Bloque le jeu tant qu'on n'a pas appuyé sur ESPACE */
                viserArcher(rendu, texMap, texObjets, police, &tir, clavier, graviteMonde, &equipe1, &equipe2, tireur->d);
                printf("Ok2\n");
            }
        
        }

        if (tir.actif) {
            int col = mettreAJourVol(&tir, matrice, graviteMonde, tireur->d);
            if (col >= D1) {
                appliquerDegats(col, tir.arme_source.degats, &equipe1, &equipe2, matrice);
                tir.actif = 0;
            }
            else if (col != 0) tir.actif = 0;
        }

        /* ---- RENDU ---- */
        SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255);
        SDL_RenderClear(rendu);

        // HIP
        afficherInventaire(rendu, texObjets, 7);
        afficherMenuPVDinos(rendu, police, equipe1, equipe2);

        // JEU (Map décalée de 100px)
        SDL_Rect rectJeu = {0, HAUTEUR_HIP, LARGEUR_FEN, HAUTEUR_JEU};
        SDL_RenderCopy(rendu, texMap, NULL, &rectJeu);

        // DINOS (Position Y + 100)
        for(i=0; i<equipe1.n; i++) {
            SDL_Rect r1 = {equipe1.tab[i].pos.x, equipe1.tab[i].pos.y + HAUTEUR_HIP, 30, 30};
            SDL_RenderCopy(rendu, texDinos[equipe1.tab[i].d - D1], NULL, &r1);
        }
        for(i=0; i<equipe2.n; i++) {
            SDL_Rect r2 = {equipe2.tab[i].pos.x, equipe2.tab[i].pos.y + HAUTEUR_HIP, 30, 30};
            SDL_RenderCopy(rendu, texDinos[equipe2.tab[i].d - D1], NULL, &r2);
        }

        if(tir.actif) {
            // On décale aussi l'affichage de la flèche de 100px en Y
            t_tir tirAffichage = tir;
            tirAffichage.pos.y += HAUTEUR_HIP;
            tracerArme(rendu, &tirAffichage);
        }

        SDL_RenderPresent(rendu);
        SDL_Delay(16);
    }

    /* ---- 6. Nettoyage ---- */
    for(i = 0; i < equipe1.n; i++) {
        if(equipe1.tab[i].deplacement) free(equipe1.tab[i].deplacement);
    }
    for(i = 0; i < equipe2.n; i++) {
        if(equipe2.tab[i].deplacement) free(equipe2.tab[i].deplacement);
    }

    free(equipe1.tab);
    free(equipe2.tab);

    TTF_CloseFont(police);

    SDL_DestroyTexture(texMap);
    for(i=0; i<7; i++){
        if(texObjets[i]) SDL_DestroyTexture(texObjets[i]);
    }
    for(i=0; i<6; i++){
        SDL_DestroyTexture(texDinos[i]);
    }
    SDL_DestroyRenderer(rendu);
    SDL_DestroyWindow(fenetre);

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}