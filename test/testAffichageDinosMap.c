#include "../lib/chargerMatrice.h"
#include "../lib/tda_nuage.h"
#include "../lib/fonctionsStructJoueur.h"
#include "../lib/fonctionsVerification.h"
#include "../lib/gestion_zones.h"
#include "../lib/placer_dinos.h"
#include "../lib/types.h"
#include <time.h>
#include <stdio.h>

/** 
 * @file testAffichageDinosMap.c
 * @brief Corps d'une fonction de test sur l'affichage des dinos avec la map
 * @author Romane Saint_Léger
 * @date Crée le 01/04/2026
 * @version 1.5
 */

/**
 * @brief Test de l'affichage des dinosaures sur le terrain
 * @param argc nombre d'arguments de la ligne de commande
 * @param argv tableau des arguments
 * @return 0 si tout s'est bien passé et 1 sinon
 * @version 2.0
 */

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
        
        creerFenetre(&menuPrincipal, "Page du Jeu", LARGEUR_TERRAIN, HAUTEUR_TERRAIN);
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

        /* Initialiser les joueurs et leurs dinosaures (3 dinosaures par équipe) */

        initialiserContenuJoueur(&equipe1);
        initialiserContenuJoueur(&equipe2);

        /* Placer les dinos sur la matrice */
        /* Équipe 1 (IDs matrice 3, 4, 5) */
        placer_une_equipe(&equipe1, catalogue.zones_E1, matrice, 0);
        /* Équipe 2 (IDs matrice 6, 7, 8) */
        placer_une_equipe(&equipe2, catalogue.zones_E2, matrice, 3);

        for(i=0; i<3; i++) {
            chargerImageSansTaille(rendu, &(equipe1.texDinos[i]), "../img/dinoTransparent.png");
            chargerImageSansTaille(rendu, &(equipe2.texDinos[i]), "../img/dinoTransparent.png");
        }
        
        while(enCours) {
            while (SDL_PollEvent(&evenement)){
                if (evenement.type == SDL_QUIT){
                    enCours = 0;
                }
            }

            SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255);
            SDL_RenderClear(rendu);

            /* --- AFFICHAGE DE LA MAP --- */
            SDL_Rect rect_plein_ecran = {0, 0, LARGEUR_TERRAIN, HAUTEUR_TERRAIN};
            SDL_RenderCopy(rendu, texMap, NULL, &rect_plein_ecran);
            
            /* --- AFFICHAGE DES DINOS --- */
            /* Équipe 1 */
            afficherDinos(rendu, &equipe1);
            /* Équipe 2 */
            afficherDinos(rendu, &equipe2);

            SDL_RenderPresent(rendu);
        }

        /* --- NETTOYAGE --- */
        detruireContenuJoueur(&equipe1);
        detruireContenuJoueur(&equipe2);

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