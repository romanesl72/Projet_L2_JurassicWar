#include "../lib/chargerMatrice.h"
#include "../lib/fonctionsMenuHIP.h"
#include "../lib/fonctionsTirs.h"
#include "../lib/fonctionsVerification.h"
#include "../lib/gestion_zones.h"
#include "../lib/placer_dinos.h"
#include "../lib/tda_nuage.h"
#include "../lib/types.h"
#include <time.h>

#define LARGEUR_FEN_JEU 1300
#define HAUTEUR_FEN_JEU 700

#define LARGEUR_FEN_MENU 400
#define HAUTEUR_FEN_MENU 650

int main(int argc, char * argv[]){

    /* ---- Initialisation des variables ---- */
    int i, j, k;
    int enCours;
    int matrice[MAT_H][MAT_L];
    int nb_pts;
    int w, h;
    int trouvés_E1 = 0;
    int trouvés_E2 = 0;
    float graviteMonde = 0.5f;
    int collision = 0;

    t_coordonnee *nuages_stockes[5];
    t_catalogue_zones catalogue;
    t_joueur equipe1, equipe2;
    t_arme arc = {ARC, 20, 1.0f, 5.0f, 15.0f};
    t_tir tirEncours;
    tirEncours.actif = 0;
    TTF_Font *police = NULL;

    initialiserPolice(&police, "../pde/arial.ttf", 16);

    if (initialisationCorrecte()) {
        srand(time(NULL)); /* Initialisation de l'aléatoire */

        enCours = 1;
        SDL_Event evenement;
        SDL_Window *menuPrincipal; 
        SDL_Renderer *rendu;
        
        creerFenetre(&menuPrincipal, "Page du Jeu", LARGEUR_FEN_JEU, HAUTEUR_FEN_JEU);
        //rendu = SDL_CreateRenderer(menuPrincipal, -1, SDL_RENDERER_ACCELERATED);
        rendu = SDL_CreateRenderer(menuPrincipal, -1, SDL_RENDERER_SOFTWARE);

        /* --- PRÉPARATION DU JEU --- */
        printf("Lancement du chargement de la matrice...\n");
        /* Charger la matrice du décor */
        chargerMatriceDepuisFichier("../res/matrice.txt", matrice);
        printf("Chargement du nuage de points...\n");

        /* Récupérer les zones via le nuage de points */
        nuages_stockes[1] = nuage_de_points(&nb_pts, "../img/test1_c.jpg");
        generer_catalogue_depuis_nuage(nuages_stockes[1], nb_pts, &catalogue, &trouvés_E1, &trouvés_E2, 1);

        nuages_stockes[2] = nuage_de_points(&nb_pts, "../img/test2_c.jpg");
        generer_catalogue_depuis_nuage(nuages_stockes[2], nb_pts, &catalogue, &trouvés_E1, &trouvés_E2, 2);

        printf("Total de zones trouvées : E1=%d, E2=%d\n", trouvés_E1, trouvés_E2);        

        /* Initialiser les joueurs et leurs dinos (3 dinos par équipe) */
        equipe1.n = 3;
        equipe1.tab = malloc(sizeof(t_dino) * equipe1.n);
        if (equipe1.tab == NULL) { printf("Erreur malloc equipe1\n"); exit(1); }
        equipe2.n = 3;
        equipe2.tab = malloc(sizeof(t_dino) * equipe2.n);

        /* Placer les dinos sur la matrice */
        /* Équipe 1 (IDs matrice 2, 3, 4) */
        placer_une_equipe(&equipe1, catalogue.zones_E1, matrice, D1);
        /* Équipe 2 (IDs matrice 5, 6, 7) */
        placer_une_equipe(&equipe2, catalogue.zones_E2, matrice, D4);


        /* Charger les images (Textures) */
        printf("Chargement de la texture map...\n");
        SDL_Texture *texMap = NULL, *texDinos[6], *texObjets[7];
        char *nomsObjets[7] = {"../img/img_arc.png", "../img/img_arbalete.png", "../img/img_bombe.png", 
                            "../img/img_fusil.png", "../img/img_revolver.png", "../img/img_potion.png", "../img/img_grappin.png"};

        chargerImage(rendu, &texMap, "../img/test1_b.jpg", &w, &h);
        if (texMap == NULL) {
            printf("ERREUR : Impossible de charger l'image de la map\n");
        } else {
            printf("Texture map chargee avec succes !\n");
        }
        
        equipe1.texDinos = malloc(sizeof(SDL_Texture*) * 6);
        equipe2.texDinos = malloc(sizeof(SDL_Texture*) * 6);
        
        for(j=0; j<6; j++) {
            chargerImage(rendu, &texDinos[j], "../img/dinoTransparent.png", &w, &h);
            // On lie les textures aux structures joueurs
            equipe1.texDinos[j] = texDinos[j];
            equipe2.texDinos[j] = texDinos[j];
        }
        
        
        for(i=0; i<7; i++) chargerImage(rendu, &texObjets[i], nomsObjets[i], &w, &h);

        equipe1.texDinos = malloc(sizeof(SDL_Texture*) * 6);
        equipe2.texDinos = malloc(sizeof(SDL_Texture*) * 6);

        for(k = 0; k < 6; k++) {
            equipe1.texDinos[k] = texDinos[k];
            equipe2.texDinos[k] = texDinos[k];
        }

        tirEncours.pos.x = equipe1.tab[0].pos.x + 15;
        tirEncours.pos.y = equipe1.tab[0].pos.y + 15;
        tirEncours.velo.u = 10.0f; 
        tirEncours.velo.v = -10.0f; 
        tirEncours.arme_source = arc;
        
        while(enCours) {
            while (SDL_PollEvent(&evenement)){
                if (evenement.type == SDL_QUIT){
                    enCours = 0;
                }

                if (evenement.type == SDL_KEYDOWN && evenement.key.keysym.sym == SDLK_SPACE && !tirEncours.actif) {
                    tirEncours.actif = 1;
                    /* Ne sert plus à rien */
                    tirEncours.pos.x = equipe1.tab[0].pos.x + 15;
                    tirEncours.pos.y = equipe1.tab[0].pos.y + 15;
                }
            }

            const Uint8 *clavier = SDL_GetKeyboardState(NULL);

            if (!tirEncours.actif) {
                if (clavier[SDL_SCANCODE_V]) {
                    /* On replace le tir sur le dino avant de viser */
                    tirEncours.pos.x = equipe1.tab[0].pos.x + 15;
                    tirEncours.pos.y = equipe1.tab[0].pos.y + 15;
                    
                    /* Bloque le jeu tant qu'on n'a pas appuyé sur ESPACE */
                    AncienviserArcher(rendu, texMap, &tirEncours, &clavier, graviteMonde, &equipe1, &equipe2);
                }
            }
            else{
                /*On enlève la collision du dino qui tire*/
                collision = mettreAJourVol(&tirEncours, matrice, graviteMonde, equipe1.tab[0].d);
                
                /*Vérification sur les collisions afin d'être sûr que les collisions sont les bonnes*/
                if (collision != 0) {
                    if (collision == -2) printf("Sortie de terrain !\n");
                    else if (collision == TERRE) printf("Touché : TERRE\n");
                    else if (collision == EAU) printf("Touché : EAU\n");
                    else if (collision >= D1) printf("Touché : DINO ID %d\n", collision);
                }
            }

            SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255);
            SDL_RenderClear(rendu);

            /* --- AFFICHAGE DE LA MAP --- */
            SDL_Rect rect_plein_ecran = {0, 0, LARGEUR_FEN_JEU, HAUTEUR_FEN_JEU};
            SDL_RenderCopy(rendu, texMap, NULL, &rect_plein_ecran);
            
            /* --- AFFICHAGE DES DINOS --- */
            /* Équipe 1 */
            for(i = 0; i < equipe1.n; i++) {
                SDL_Rect r = {equipe1.tab[i].pos.x, equipe1.tab[i].pos.y, 30, 30};
                SDL_RenderCopy(rendu, texDinos[equipe1.tab[i].d - D1], NULL, &r);
            }
            /* Équipe 2 */
            for(i = 0; i < equipe2.n; i++) {
                SDL_Rect r = {equipe2.tab[i].pos.x, equipe2.tab[i].pos.y, 30, 30};
                SDL_RenderCopy(rendu, texDinos[equipe2.tab[i].d - D1], NULL, &r);
            }

            if(tirEncours.actif) {
                tracerArme(rendu, &tirEncours);
            }

            SDL_RenderPresent(rendu);
            SDL_Delay(16);
        }

        /* --- NETTOYAGE --- */
        free(equipe1.tab);
        free(equipe2.tab);
        for(i=0; i<6; i++) {
            SDL_DestroyTexture(texDinos[i]);
        }
        for(i=1; i<3; i++) {
            free(nuages_stockes[i]);
        }
        SDL_DestroyTexture(texMap);
        
        SDL_DestroyRenderer(rendu);
        SDL_DestroyWindow(menuPrincipal);
        IMG_Quit();
        TTF_Quit();
        SDL_Quit();

        return 0;
    }
    return 1;
}