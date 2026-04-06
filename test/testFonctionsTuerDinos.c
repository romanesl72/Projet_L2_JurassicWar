#include "../lib/chargerMatrice.h"
#include "../lib/fonctionsRebonds.h"
#include "../lib/fonctionsStructJoueur.h"
#include "../lib/fonctionsTuerDinos.h"
#include "../lib/fonctionsVerification.h"
#include "../lib/gestion_zones.h"
#include "../lib/placer_dinos.h"
#include "../lib/tda_nuage.h"

#include <time.h>
#include <stdio.h>

/** 
 * @file testFonctionsTuerDinos.c
 * @brief Test des fonctions crées dans le fichier fonctionsTuerDinos.c.
 * @author Hannah Sergent
 * @date Crée le 11/03/2026
 * @version 4.3
 */

#define COOR_X LARGEUR_TERRAIN/3
#define COOR_Y HAUTEUR_TERRAIN/2

int main(int argc, char * argv[]){

    if (initialisationCorrecte()) {

        int enCours = 1;

        /* Variables pour la gestion des actions réalisées par l'utilisateur */

        const Uint8 *etatClavier;
        SDL_Event evenement;

        /* Initialisation de la matrice */

        t_case (*matriceTerrain)[LARGEUR_TERRAIN] = NULL;
        initialiserMatrice(&matriceTerrain);

        /* Initialisations liées à la bombe */

        t_bombe bombe;
        t_vect vectVitesse;
        const float vitesse = 1.0f/250.0f;
        float accumulateur = 0;
        t_case dinoTouche;
        int bombeLancee = 0;
        int nombreRebonds = 0;

        initialiserBombe(&bombe, COOR_X, COOR_Y, RAYON);
        initialiserVitesse(&vectVitesse, VITESSE_X, VITESSE_Y);

        /* Initialisation des équipes */

        int i;
        int nb_pts;
        int trouves_E1 = 0;
        int trouves_E2 = 0;
        t_coordonnee *nuages_stockes[5];
        t_catalogue_zones catalogue;
        t_joueur equipe1, equipe2;

        srand(time(NULL)); /* Initialisation de l'aléatoire */

        /* Récupérer les zones via le nuage de points */
        nuages_stockes[1] = nuage_de_points(&nb_pts, "../img/test1_c.jpg");
        generer_catalogue_depuis_nuage(nuages_stockes[1], nb_pts, &catalogue, &trouves_E1, &trouves_E2, 1);

        nuages_stockes[2] = nuage_de_points(&nb_pts, "../img/test2_c.jpg");
        generer_catalogue_depuis_nuage(nuages_stockes[2], nb_pts, &catalogue, &trouves_E1, &trouves_E2, 2);

        printf("Total de zones trouvées : E1=%d, E2=%d\n", trouves_E1, trouves_E2);

        /* Initialiser les joueurs et leurs dinosaures (3 dinosaures par équipe) */

        initialiserContenuJoueur(&equipe1);
        initialiserContenuJoueur(&equipe2);

        /* Placer les dinosaures sur la matrice */
        /* Équipe 1 (IDs matrice 2, 3, 4) */
        placer_une_equipe(&equipe1, catalogue.zones_E1, matriceTerrain, D1);
        /* Équipe 2 (IDs matrice 5, 6, 7) */
        placer_une_equipe(&equipe2, catalogue.zones_E2, matriceTerrain, D4);

        /* Initialisation de la fenêtre */

        SDL_Window *menuPrincipal;
        SDL_Texture *texMap;
        SDL_Rect rect_plein_ecran = {0, 0, LARGEUR_TERRAIN, HAUTEUR_TERRAIN};

        creerFenetre(&menuPrincipal, "MenuPrincipal", LARGEUR_TERRAIN, HAUTEUR_TERRAIN);
        SDL_Renderer* zoneAffichage = SDL_CreateRenderer(menuPrincipal, -1, SDL_RENDERER_ACCELERATED);
        chargerImageSansTaille(zoneAffichage, &texMap, "../img/test1_b.jpg");

        /* Charger les images (Textures) */

        chargerImageSansTaille(zoneAffichage, &(equipe1.texDinos[0]), "../img/dinoTransparent.png");
        chargerImageSansTaille(zoneAffichage, &(equipe1.texDinos[1]), "../img/dinoTransparent.png");
        chargerImageSansTaille(zoneAffichage, &(equipe1.texDinos[2]), "../img/dinoTransparent.png");

        chargerImageSansTaille(zoneAffichage, &(equipe2.texDinos[0]), "../img/dinoTransparent.png");
        chargerImageSansTaille(zoneAffichage, &(equipe2.texDinos[1]), "../img/dinoTransparent.png");
        chargerImageSansTaille(zoneAffichage, &(equipe2.texDinos[2]), "../img/dinoTransparent.png");

        /* Affichage initial */

        SDL_RenderCopy(zoneAffichage, texMap, NULL, &rect_plein_ecran);
        tracerBombe(zoneAffichage, &bombe);
        afficherDinos(zoneAffichage, &equipe1);
        afficherDinos(zoneAffichage, &equipe2);
        SDL_RenderPresent(zoneAffichage);

        /* Variables pour la gestion du temps */
        
        float tempsEcoule;
        Uint32 tempsPrecedent = SDL_GetTicks();
        
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

                choixHauteurLancerAvecDinos(zoneAffichage, texMap, &rect_plein_ecran, &etatClavier, &bombe, &vectVitesse, &equipe1, &equipe2);
            }
            
            miseAjourTemps(&tempsPrecedent, &tempsEcoule);
            accumulateur += tempsEcoule;

            while (accumulateur >= vitesse) {
                if (bombeLancee) {

                    bombe.coor.x += vitesse*vectVitesse.u;
                    bombe.coor.y += vitesse*vectVitesse.v;
                    vectVitesse.v += GRAVITE_BOMBE*vitesse;

                    if (collisionFrontiereBombe(&bombe)) {
                        bombeLancee = 0;

                    }

                    dinoTouche = collisionDinoBombe(matriceTerrain, &bombe);

                    if (dinoTouche || collisionEauBombe(matriceTerrain, &bombe)) {

                        bombeLancee = 0;

                        if (dinoTouche){
                            supprimerDinoJoueur(&equipe1, &equipe2, dinoTouche);
                        }

                        SDL_RenderClear(zoneAffichage);
                        SDL_RenderCopy(zoneAffichage, texMap, NULL, &rect_plein_ecran);
                        afficherDinos(zoneAffichage, &equipe1);
                        afficherDinos(zoneAffichage, &equipe2);
                        SDL_RenderPresent(zoneAffichage);
                        
                    }
                    if (collisionTerrainBombe(matriceTerrain, &bombe, &vectVitesse)) {
                        nombreRebonds ++;

                        if (nombreRebonds > 1){
                            bombeLancee = 0;
                        }
                    }

                    if (bombeLancee) {

                        SDL_RenderClear(zoneAffichage);
                        SDL_RenderCopy(zoneAffichage, texMap, NULL, &rect_plein_ecran);
                        tracerBombe(zoneAffichage, &bombe);
                        afficherDinos(zoneAffichage, &equipe1);
                        afficherDinos(zoneAffichage, &equipe2);
                        SDL_RenderPresent(zoneAffichage);
                    }
                }
                accumulateur -= vitesse;
            }


        }

        /* Destruction */

        detruireContenuJoueur(&equipe1);
        detruireContenuJoueur(&equipe2);
        detruireMatrice(&matriceTerrain);

        for(i=1; i<3; i++) {
            nuageDetruire(&(nuages_stockes[i]));
        }

        SDL_DestroyTexture(texMap);
        SDL_DestroyRenderer(zoneAffichage);
        SDL_DestroyWindow(menuPrincipal);

        IMG_Quit();
        TTF_Quit();
        SDL_Quit();

        return 0;
    }
    return 1;
}