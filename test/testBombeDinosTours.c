#include "../lib/chargerMatrice.h"
#include "../lib/fonctionsChangementTour.h"
#include "../lib/fonctionsPlacementBombe.h"
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
 * @file testBombeDinosTours.c
 * @brief Test des fonctions crées dans le fichier fonctionsPlacementBombe.c.
 * @author Hannah Sergent
 * @date Crée le 20/03/2026
 * @version 2.0
 */

/**
 * @brief Les dinosaures peuvent lancer une bombe tour à tour, positionnée à côté d'eux.
 * @param argc nombre d'arguments de la ligne de commande
 * @param argv tableau des arguments
 * @return 0 si tout s'est bien passé et 1 sinon
 * @version 2.0
 */

int main(int argc, char * argv[]){

    if (initialisationCorrecte()) {

        Uint32 tempsPrecedent;
        float tempsEcoule;
        const Uint8 *etatClavier;

        int i;
        int enCours = 1;
        int nb_pts;

        int trouves_E1 = 0;
        int trouves_E2 = 0;

        t_coordonnee *nuages_stockes[5];
        t_catalogue_zones catalogue;

        t_joueur equipe1, equipe2;
        t_case dinoTouche = AIR;

        t_bombe bombe;

        const float vitesse = 1.0f/250.0f;
        float accumulateur = 0;
        t_vect vectVitesse;

        int bombeLancee = 0;
        int nombreRebonds = 0;

        SDL_Event evenement;

        SDL_Window *menuPrincipal;
        SDL_Texture *texMap;

        /* Variable de changement de tour */
        t_tour gestionTours = {1, 1, D1, D6};

        initialiserRayonBombe(&bombe, RAYON);
        initialiserVitesse(&vectVitesse, VITESSE_X, VITESSE_Y);

        t_case (*matriceTerrain)[LARGEUR_TERRAIN] = NULL;
        initialiserMatrice(&matriceTerrain);

        srand(time(NULL)); /* Initialisation de l'aléatoire */


        creerFenetre(&menuPrincipal, "MenuPrincipal", LARGEUR_TERRAIN, HAUTEUR_TERRAIN);

        SDL_Renderer* zoneAffichage = SDL_CreateRenderer(menuPrincipal, -1, SDL_RENDERER_ACCELERATED);

        chargerImageSansTaille(zoneAffichage, &texMap, "../img/test1_b.jpg");

        SDL_Rect rect_plein_ecran = {0, 0, LARGEUR_TERRAIN, HAUTEUR_TERRAIN};
        SDL_RenderCopy(zoneAffichage, texMap, NULL, &rect_plein_ecran);

        tempsPrecedent = SDL_GetTicks();


        /* Récupérer les zones via le nuage de points */
        nuages_stockes[1] = nuage_de_points(&nb_pts, "../img/test1_c.jpg");
        generer_catalogue_depuis_nuage(nuages_stockes[1], nb_pts, &catalogue, &trouves_E1, &trouves_E2, 1);

        nuages_stockes[2] = nuage_de_points(&nb_pts, "../img/test2_c.jpg");
        generer_catalogue_depuis_nuage(nuages_stockes[2], nb_pts, &catalogue, &trouves_E1, &trouves_E2, 2);

        printf("Total de zones trouvées : E1=%d, E2=%d\n", trouves_E1, trouves_E2);


        if (texMap == NULL) {
            printf("ERREUR : Impossible de charger l'image de la map\n");
        } else {
            printf("Texture map chargee avec succes !\n");
        }

        /* Initialiser les joueurs et leurs dinos (3 dinos par équipe) */

        initialiserContenuJoueur(&equipe1);
        initialiserContenuJoueur(&equipe2);

        /* Placer les dinos sur la matrice */
        /* Équipe 1 (IDs matrice 3, 4, 5) */
        placer_une_equipe(&equipe1, catalogue.zones_E1, matriceTerrain, D1);
        /* Équipe 2 (IDs matrice 6, 7, 8) */
        placer_une_equipe(&equipe2, catalogue.zones_E2, matriceTerrain, D4);

        /* Charger les images (Textures) */

        chargerImageSansTaille(zoneAffichage, &(equipe1.texDinos[0]), "../img/dinoTransparent.png");
        chargerImageSansTaille(zoneAffichage, &(equipe1.texDinos[1]), "../img/dinoTransparent.png");
        chargerImageSansTaille(zoneAffichage, &(equipe1.texDinos[2]), "../img/dinoTransparent.png");

        chargerImageSansTaille(zoneAffichage, &(equipe2.texDinos[0]), "../img/dinoTransparent.png");
        chargerImageSansTaille(zoneAffichage, &(equipe2.texDinos[1]), "../img/dinoTransparent.png");
        chargerImageSansTaille(zoneAffichage, &(equipe2.texDinos[2]), "../img/dinoTransparent.png");
        
        chargerImageSansTaille(zoneAffichage, &(equipe1.texDinosInv[0]), "../img/dinoTransparentMiroir.png");
        chargerImageSansTaille(zoneAffichage, &(equipe1.texDinosInv[1]), "../img/dinoTransparentMiroir.png");
        chargerImageSansTaille(zoneAffichage, &(equipe1.texDinosInv[2]), "../img/dinoTransparentMiroir.png");

        chargerImageSansTaille(zoneAffichage, &(equipe2.texDinosInv[0]), "../img/dinoTransparentMiroir.png");
        chargerImageSansTaille(zoneAffichage, &(equipe2.texDinosInv[1]), "../img/dinoTransparentMiroir.png");
        chargerImageSansTaille(zoneAffichage, &(equipe2.texDinosInv[2]), "../img/dinoTransparentMiroir.png");

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

                choixHauteurLancerDinoCourant(zoneAffichage, texMap, &rect_plein_ecran, &etatClavier, &bombe, &vectVitesse, &equipe1, &equipe2, gestionTours.dinoCourant, matriceTerrain);
            }
            
            miseAjourTemps(&tempsPrecedent, &tempsEcoule);
            accumulateur += tempsEcoule;

            while (accumulateur >= vitesse) {
                if (bombeLancee == 1) {

                    bombe.coor.x += vitesse*vectVitesse.u;
                    bombe.coor.y += vitesse*vectVitesse.v;
                    vectVitesse.v += GRAVITE_BOMBE*vitesse;

                    if (collisionFrontiereBombe(&bombe)) {
                        bombeLancee = -1;
                        printf("Collision avec la frontière. \n");

                    }

                    dinoTouche = collisionDinoBombe(matriceTerrain, &bombe);

                    if (((dinoTouche >= D1) && (dinoTouche <= D6)) || collisionEauBombe(matriceTerrain, &bombe)) {
                        bombeLancee = -1;
                        printf("Collision avec eau ou dinosaure. \n");

                        SDL_RenderClear(zoneAffichage);
                        SDL_RenderCopy(zoneAffichage, texMap, NULL, &rect_plein_ecran);

                        if ((dinoTouche >= D1) && (dinoTouche <= D6)){
                            printf("Collision avec un dinosaure. \n");
                            supprimer_matrice_dino(recupererDinoNumero(&equipe1, &equipe2, dinoTouche), matriceTerrain);
                            supprimerDinoJoueur(&equipe1, &equipe2, dinoTouche);
                            dinoTouche = AIR;
                        }

                        /* --- AFFICHAGE DES DINOS --- */

                        afficherDinos(zoneAffichage, &equipe1);
                        afficherDinos(zoneAffichage, &equipe2);


                        SDL_RenderPresent(zoneAffichage);
                        
                    }
                    if (collisionTerrainBombe(matriceTerrain, &bombe, &vectVitesse)) {
                        nombreRebonds ++;
                        printf("Collision avec le terrain. \n");

                        if (nombreRebonds > 1){
                            bombeLancee = -1;
                        }
                    }

                    if (bombeLancee == 1) {

                        SDL_RenderClear(zoneAffichage);
                        SDL_RenderCopy(zoneAffichage, texMap, NULL, &rect_plein_ecran);
                        tracerBombe(zoneAffichage, &bombe);

                        /* --- AFFICHAGE DES DINOS --- */

                        afficherDinos(zoneAffichage, &equipe1);
                        afficherDinos(zoneAffichage, &equipe2);

                        SDL_RenderPresent(zoneAffichage);
                    }
                    
                    if (bombeLancee == -1){
                        tourSuivant(&gestionTours, &equipe1, &equipe2);
                        printf("Passage au dinosaure %d, tour numéro %d, équipe numéro %d \n", gestionTours.dinoCourant, gestionTours.numeroTour, gestionTours.equipeCourante);
                        initialiserVitesse(&vectVitesse, VITESSE_X, VITESSE_Y);
                    }
                }
                accumulateur -= vitesse;
            }


        }

        /* --- NETTOYAGE --- */

        detruireContenuJoueur(&equipe1);
        detruireContenuJoueur(&equipe2);

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