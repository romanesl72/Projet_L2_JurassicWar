#include "../lib/chargerMatrice.h"
#include "../lib/tda_nuage.h"
#include "../lib/fonctionsVerification.h"
#include "../lib/gestion_zones.h"
#include "../lib/placer_dinos.h"
#include "../lib/types.h"
#include <time.h>
#include <stdio.h>

#define LARGEUR_FEN_JEU 1300
#define HAUTEUR_FEN_JEU 700

#define LARGEUR_FEN_MENU 400
#define HAUTEUR_FEN_MENU 650

int main(int argc, char * argv[]){

    /* ---- Initialisation des variables ---- */
    int i;
    int enCours;
    int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN];
    int nb_pts;
    int w, h;
    int trouves_E1 = 0;
    int trouves_E2 = 0;

    t_coordonnee *nuages_stockes[5];
    t_catalogue_zones catalogue;
    t_joueur equipe1, equipe2;


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
        generer_catalogue_depuis_nuage(nuages_stockes[1], nb_pts, &catalogue, &trouves_E1, &trouves_E2, 1);

        nuages_stockes[2] = nuage_de_points(&nb_pts, "../img/test2_c.jpg");
        generer_catalogue_depuis_nuage(nuages_stockes[2], nb_pts, &catalogue, &trouves_E1, &trouves_E2, 2);

        printf("Total de zones trouvées : E1=%d, E2=%d\n", trouves_E1, trouves_E2);

        printf("Chargement de la texture map...\n");
        SDL_Texture *texMap;
        chargerImage(rendu, &texMap, "../img/test1_b.jpg", &w, &h);
        if (texMap == NULL) {
            printf("ERREUR : Impossible de charger l'image de la map\n");
        } else {
            printf("Texture map chargee avec succes !\n");
        }

        /* Initialiser les joueurs et leurs dinos (3 dinos par équipe) */
        equipe1.n = 3;
        equipe1.tab = malloc(sizeof(t_dino) * equipe1.n);
        equipe2.n = 3;
        equipe2.tab = malloc(sizeof(t_dino) * equipe2.n);

        /* Placer les dinos sur la matrice */
        /* Équipe 1 (IDs matrice 3, 4, 5) */
        placer_une_equipe(&equipe1, catalogue.zones_E1, matrice, 0);
        /* Équipe 2 (IDs matrice 6, 7, 8) */
        placer_une_equipe(&equipe2, catalogue.zones_E2, matrice, 3);

        /* Charger les images (Textures) */
        SDL_Texture *texDinos[6];
        chargerImage(rendu, &texDinos[0], "../img/dino_test.png", &w, &h);
        chargerImage(rendu, &texDinos[1], "../img/dino_test.png", &w, &h);
        chargerImage(rendu, &texDinos[2], "../img/dino_test.png", &w, &h);
        chargerImage(rendu, &texDinos[3], "../img/dino_test.png", &w, &h);
        chargerImage(rendu, &texDinos[4], "../img/dino_test.png", &w, &h);
        chargerImage(rendu, &texDinos[5], "../img/dino_test.png", &w, &h);

        
        
        while(enCours) {
            while (SDL_PollEvent(&evenement)){
                if (evenement.type == SDL_QUIT){
                    enCours = 0;
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
                SDL_RenderCopy(rendu, texDinos[equipe1.tab[i].d], NULL, &r);
            }
            /* Équipe 2 */
            for(i = 0; i < equipe2.n; i++) {
                SDL_Rect r = {equipe2.tab[i].pos.x, equipe2.tab[i].pos.y, 30, 30};
                SDL_RenderCopy(rendu, texDinos[equipe2.tab[i].d], NULL, &r);
            }

            SDL_RenderPresent(rendu);
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