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
#include "../lib/chargerMatrice.h"
#include "../lib/fonctionsStructJoueur.h"
#include <time.h>
#include <SDL2/SDL_ttf.h>

#define LARGEUR_FEN 1300
#define HAUTEUR_HIP 100
#define HAUTEUR_JEU 700
#define HAUTEUR_TOTALE (HAUTEUR_HIP + HAUTEUR_JEU)

int main(int argc, char * argv[]){

    int i,j;

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
    int matrice[MAT_H][MAT_L];
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

    placer_une_equipe(&equipe1, catalogue.zones_E1, matrice, D1);
    placer_une_equipe(&equipe2, catalogue.zones_E2, matrice, D4);

    for(i=0; i<3; i++) {
        equipe1.tab[i].pv = 100;
        equipe2.tab[i].pv = 100;
    }

    /* ---- Initialisation des Armes ---- */
    t_dino *tireur = NULL;

    t_arme catalogue_armes[5]; // Arc, Arbalete, Bombe Fusil, Revolver
    catalogue_armes[0] = (t_arme){ARC, 20, 1.0f, 5.0f, 15.0f};
    catalogue_armes[1] = (t_arme){ARBALETE, 35, 1.2f, 8.0f, 18.0f};
    // Index 2 est réservé à la BOMBE (pas de t_arme nécessaire)
    catalogue_armes[3] = (t_arme){FUSIL, 45, 0.4f, 15.0f, 30.0f};
    catalogue_armes[4] = (t_arme){REVOLVER, 30, 0.6f, 13.0f, 25.0f};

    int enCours = 1;
    int armeSelectionnee = 0;

    t_tir tir;              /* Pour flèches/balles */
    tir.actif = 0;

    t_bombe bombe;          /* Pour la bombe */
    t_vect vectVitesse;
    const float vitesse = 1.0f/250.0f;
    float accumulateur = 0;
    int bombeLancee = 0;
    int nombreRebonds = 0;
    

    /* ---- Chargement Textures ---- */
    SDL_Texture *texMap = NULL, *texDinos[6], *texObjets[7];
    char *nomsObjets[7] = {"../img/img_arc.png", "../img/img_arbalete.png", "../img/img_bombe.png", 
                           "../img/img_fusil.png", "../img/img_revolver.png", "../img/img_potion.png", "../img/img_grappin.png"};

    chargerImage(rendu, &texMap, "../img/test1_b.jpg", &w, &h);
    for(j=0; j<6; j++) chargerImage(rendu, &texDinos[j], "../img/dinoTransparent.png", &w, &h);
    for(i=0; i<7; i++) chargerImage(rendu, &texObjets[i], nomsObjets[i], &w, &h);

    /* ---- Initialisation ---- */
    

    while(enCours) {
        SDL_Event e;
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT) enCours = 0;

            // Changement d'arme graphique (touches 1 à 7)
            if(e.type == SDL_KEYDOWN && e.key.keysym.sym >= SDLK_1 && e.key.keysym.sym <= SDLK_7) {
                armeSelectionnee = e.key.keysym.sym - SDLK_1;
                printf("Arme selectionnee : %d\n", armeSelectionnee);
            }
        }

        const Uint8 *clavier = SDL_GetKeyboardState(NULL);

        tireur = recupererDinoNumero(&equipe1, &equipe2, numDinoCourant);

        // Tir et Visée
        if (!tir.actif && !bombeEnVol && clavier[SDL_SCANCODE_SPACE]) {
            
            switch(armeSelectionnee) {
                case 0: // ARC
                case 1: // ARBALÈTE
                case 3: // FUSIL
                case 4: // REVOLVER
                    tir.actif = 1;
                    tir.arme = catalogue_armes[armeSelectionnee];
                    tir.pos.x = tireur->pos.x + 15;
                    tir.pos.y = tireur->pos.y + 15;
                    viserArcher(rendu, texMap, &tir, &clavier, graviteMonde, &equipe1, &equipe2);
                    break;

                case 2: // LA BOMBE
                    initialiserBombe(&bombeActuelle, tireur->pos.x, tireur->pos.y, 10);
                    initialiserVitesse(&vectVitesse, 150.0f, -150.0f);
                    nbRebonds = 0;
                    
                    SDL_Rect rectMapSeule = {0, 0, LARGEUR_FEN, HAUTEUR_JEU}; 
                    choixHauteurLancerDinoCourant(rendu, texMap, &rectMapSeule, &clavier, &bombeActuelle, &vectVitesse, &equipe1, &equipe2, numDinoCourant, matrice);
                    bombeEnVol = 1;
                    break;

                case 5: // LA POTION
                    utiliserPotion(tireur);
                    break;

                case 6: // LE GRAPPIN
                    printf("Grappin non implémenté\n");
                    break;
            }
        }

        if (bombeEnVol) {
            Uint32 tempsCourant = SDL_GetTicks();
            static Uint32 tempsPrecedent = 0;
            float tempsEcoule = (tempsCourant - tempsPrecedent) / 1000.0f;
            tempsPrecedent = tempsCourant;
            
            accumulateurBombe += tempsEcoule;

            while (accumulateurBombe >= dt_bombe) {
                bombeActuelle.coor.x += dt_bombe * vectVitesse.u;
                bombeActuelle.coor.y += dt_bombe * vectVitesse.v;
                vectVitesse.v += GRAVITE * dt_bombe;

                if (collisionFrontiereBombe(&bombeActuelle)) bombeEnVol = 0;
                
                if (collisionTerrainBombe(matrice, &bombeActuelle, &vectVitesse)) {
                    nbRebonds++;
                    if (nbRebonds > 2) bombeEnVol = 0; // Explosion après 2 rebonds
                }
                
                if (collisionEauBombe(matrice, &bombeActuelle)) bombeEnVol = 0;
                
                accumulateurBombe -= dt_bombe;
            }
        }

        if (tir.actif) {
            int col = mettreAJourVol(&tir, matrice, graviteMonde, tireur->d);
            if (col >= D1) {
                appliquerDegats(col, tir.arme.degats, &equipe1, &equipe2);
                tir.actif = 0;
            }
            else if (col != 0) tir.actif = 0;
        }

        /* ---- RENDU ---- */
        SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255);
        SDL_RenderClear(rendu);

        // HIP
        afficherInventaire(rendu, texObjets, 7, armeSelectionnee);
        afficherMenuPVDinos(rendu, police, equipe1, equipe2);

        // JEU (Map décalée de 100px)
        SDL_Rect rectJeu = {0, HAUTEUR_HIP, LARGEUR_FEN, HAUTEUR_JEU};
        SDL_RenderCopy(rendu, texMap, NULL, &rectJeu);

        // DINOS (Position Y + 100)
        for(i=0; i<3; i++) {
            SDL_Rect r1 = {equipe1.tab[i].pos.x, equipe1.tab[i].pos.y + HAUTEUR_HIP, 30, 30};
            SDL_RenderCopy(rendu, texDinos[equipe1.tab[i].d - D1], NULL, &r1);
            SDL_Rect r2 = {equipe2.tab[i].pos.x, equipe2.tab[i].pos.y + HAUTEUR_HIP, 30, 30};
            SDL_RenderCopy(rendu, texDinos[equipe2.tab[i].d - D1], NULL, &r2);
        }

        if(tir.actif) {
            // On décale aussi l'affichage de la flèche de 100px en Y
            t_tir tirAffichage = tir;
            tirAffichage.pos.y += HAUTEUR_HIP;
            tracerFleche(rendu, &tirAffichage);
        }

        SDL_RenderPresent(rendu);
        SDL_Delay(16);
    }

    /* ---- 6. Nettoyage ---- */
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