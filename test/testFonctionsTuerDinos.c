#include "../lib/chargerMatrice.h"
#include "../lib/tda_nuage.h"
#include "../lib/fonctionsRebonds.h"
#include "../lib/fonctionsVerification.h"
#include "../lib/fonctionsTuerDinos.h"
#include "../lib/gestion_zones.h"
#include "../lib/placer_dinos.h"
#include <time.h>
#include <stdio.h>

#define RAYON 15

#define COOR_X LARGEUR_TERRAIN/3
#define COOR_Y HAUTEUR_TERRAIN/2

#define VITESSE_X 90
#define VITESSE_Y -90

int main(int argc, char * argv[]){

    if (initialisationCorrecte()) {

        Uint32 tempsPrecedent;
        float tempsEcoule;
        const Uint8 *etatClavier;

        int i;
        int enCours = 1;
        int nb_pts;
        int w, h;
        int trouvés_E1 = 0;
        int trouvés_E2 = 0;

        t_coordonnee *nuages_stockes[5];
        t_catalogue_zones catalogue;
        t_joueur equipe1, equipe2;

        t_bombe bombe;

        const float vitesse = 1.0f/120.0f;
        float accumulateur = 0;
        t_vect vectVitesse;

        float gravite = 180;

        int bombeLancee = 0;
        int nombreRebonds = 0;

        SDL_Event evenement;

        SDL_Window *menuPrincipal;
        SDL_Texture *texMap;

        initialiserBombe(&bombe, COOR_X, COOR_Y, RAYON);
        initialiserVitesse(&vectVitesse, VITESSE_X, VITESSE_Y);

        t_case (*matriceTerrain)[LARGEUR_TERRAIN] = NULL;
        initialiserMatrice(&matriceTerrain);

        srand(time(NULL)); /* Initialisation de l'aléatoire */


        creerFenetre(&menuPrincipal, "MenuPrincipal", LARGEUR_TERRAIN, HAUTEUR_TERRAIN);

        SDL_Renderer* zoneAffichage = SDL_CreateRenderer(menuPrincipal, -1, SDL_RENDERER_ACCELERATED);

        chargerImage(zoneAffichage, &texMap, "../img/test1_b.jpg", &w, &h);

        SDL_Rect rect_plein_ecran = {0, 0, LARGEUR_TERRAIN, HAUTEUR_TERRAIN};
        SDL_RenderCopy(zoneAffichage, texMap, NULL, &rect_plein_ecran);
        tracerBombe(zoneAffichage, &bombe);

        tempsPrecedent = SDL_GetTicks();


        /* Récupérer les zones via le nuage de points */
        nuages_stockes[1] = nuage_de_points(&nb_pts, "../img/test1_c.jpg");
        generer_catalogue_depuis_nuage(nuages_stockes[1], nb_pts, &catalogue, &trouvés_E1, &trouvés_E2, 1);

        nuages_stockes[2] = nuage_de_points(&nb_pts, "../img/test2_c.jpg");
        generer_catalogue_depuis_nuage(nuages_stockes[2], nb_pts, &catalogue, &trouvés_E1, &trouvés_E2, 2);

        printf("Total de zones trouvées : E1=%d, E2=%d\n", trouvés_E1, trouvés_E2);


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
        placer_une_equipe(&equipe1, catalogue.zones_E1, matriceTerrain, 0);
        /* Équipe 2 (IDs matrice 6, 7, 8) */
        placer_une_equipe(&equipe2, catalogue.zones_E2, matriceTerrain, 3);

        /* Charger les images (Textures) */

        equipe1.texDinos = malloc(sizeof(SDL_Texture *) * equipe1.n);
        equipe2.texDinos = malloc(sizeof(SDL_Texture *) * equipe2.n);

        chargerImage(zoneAffichage, &(equipe1.texDinos[0]), "../img/dinoTransparent.png", &w, &h);
        chargerImage(zoneAffichage, &(equipe1.texDinos[1]), "../img/dinoTransparent.png", &w, &h);
        chargerImage(zoneAffichage, &(equipe1.texDinos[2]), "../img/dinoTransparent.png", &w, &h);

        chargerImage(zoneAffichage, &(equipe2.texDinos[0]), "../img/dinoTransparent.png", &w, &h);
        chargerImage(zoneAffichage, &(equipe2.texDinos[1]), "../img/dinoTransparent.png", &w, &h);
        chargerImage(zoneAffichage, &(equipe2.texDinos[2]), "../img/dinoTransparent.png", &w, &h);

        /* --- AFFICHAGE DES DINOS --- */

        afficherDinos(zoneAffichage, &equipe1);
        afficherDinos(zoneAffichage, &equipe2);

        SDL_RenderPresent(zoneAffichage);
        
        while(enCours) {

            while (SDL_PollEvent(&evenement)){
                if (evenement.type == SDL_QUIT){
                    enCours = 0;
                }
            }

            etatClavier = SDL_GetKeyboardState(NULL);

            if (etatClavier[SDL_SCANCODE_B]){
                bombeLancee = 1;
                nombreRebonds = 0;

                choixHauteurLancerAvecDinos(zoneAffichage, texMap, &rect_plein_ecran, &etatClavier, &bombe, &vectVitesse, gravite, &equipe1, &equipe2);
            }
            
            miseAjourTemps(&tempsPrecedent, &tempsEcoule);
            accumulateur += tempsEcoule;

            while (accumulateur >= vitesse) {
                if (bombeLancee) {

                    bombe.coor.x += vitesse*vectVitesse.u;
                    bombe.coor.y += vitesse*vectVitesse.v;
                    vectVitesse.v += gravite*vitesse;

                    if (collisionFrontiereBombe(LARGEUR_TERRAIN, HAUTEUR_TERRAIN, &bombe)) {
                        bombeLancee = 0;
                        /* 
                        initialiserBombe(&bombe, COOR_X, COOR_Y, RAYON);
                        initialiserVitesse(&vitesseX, &vitesseY, VITESSE_X, VITESSE_Y);
                        */
                    }
                    if (collisionDinoBombe(matriceTerrain, &bombe)) {
                        bombeLancee = 0;
                        printf("Dino touché \n");
                        
                    }
                    if (collisionTerrainBombe(matriceTerrain, &bombe, &vectVitesse)) {
                        nombreRebonds ++;

                        /* bombe.coor.x += vectVitesse.u *vitesse;
                        bombe.coor.y += vectVitesse.v * vitesse; */
                        if (nombreRebonds > 1){
                            bombeLancee = 0;
                        }
                    }
                    if (collisionEauBombe(matriceTerrain, &bombe)) {
                        bombeLancee = 0;
                        SDL_RenderClear(zoneAffichage);
                        SDL_RenderCopy(zoneAffichage, texMap, NULL, &rect_plein_ecran);

                        /* --- AFFICHAGE DES DINOS --- */

                        afficherDinos(zoneAffichage, &equipe1);
                        afficherDinos(zoneAffichage, &equipe2);


                        SDL_RenderPresent(zoneAffichage);
                    }

                    if (bombeLancee) {

                        SDL_RenderClear(zoneAffichage);
                        SDL_RenderCopy(zoneAffichage, texMap, NULL, &rect_plein_ecran);
                        tracerBombe(zoneAffichage, &bombe);

                        /* --- AFFICHAGE DES DINOS --- */

                        afficherDinos(zoneAffichage, &equipe1);
                        afficherDinos(zoneAffichage, &equipe2);

                        SDL_RenderPresent(zoneAffichage);
                    }
                }
                accumulateur -= vitesse;
            }


        }

        /* --- NETTOYAGE --- */
        free(equipe1.tab);
        free(equipe2.tab);
        for(i=0; i<3; i++) {
            SDL_DestroyTexture(equipe1.texDinos[i]);
        }
        for(i=0; i<3; i++) {
            SDL_DestroyTexture(equipe2.texDinos[i]);
        }
        for(i=1; i<3; i++) {
            free(nuages_stockes[i]);
        }
        SDL_DestroyTexture(texMap);
        
        detruireMatrice(&matriceTerrain);
        SDL_DestroyRenderer(zoneAffichage);
        SDL_DestroyWindow(menuPrincipal);
        IMG_Quit();
        TTF_Quit();
        SDL_Quit();

        return 0;
    }
    return 1;
}