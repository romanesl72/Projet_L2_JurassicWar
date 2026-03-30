#include "../lib/chargerMatrice.h"
#include "../lib/fonctionsChangementTour.h"
#include "../lib/fonctionsPageJeu.h"
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
 * @file fonctionsPageJeu.c
 * @brief Corps des fonctions liées à la page du jeu.
 * @author Hannah Sergent
 * @date Crée le 29/03/2026
 */

int creerPageJeu(SDL_Window **fenJeu, SDL_Renderer **zoneAffichage, SDL_Texture **texMap){

    creerFenetre(fenJeu, "JurassicWar - Partie en cours", LARGEUR_TERRAIN, HAUTEUR_TERRAIN);

    *zoneAffichage = SDL_CreateRenderer(*fenJeu, -1, SDL_RENDERER_ACCELERATED);

    if(!*zoneAffichage) {

        printf("Erreur lors de l'initialisation de la zone d'affichage de la fenêtre du jeu \n.");
        SDL_DestroyWindow(*fenJeu);
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return 0;

    }

    chargerImageSansTaille(*zoneAffichage, texMap, "../img/test1_b.jpg");
    return 1;
}

void initialiserEquipes(t_joueur *equipe1, t_joueur *equipe2, t_catalogue_zones *catalogue, t_case matriceTerrain[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], SDL_Renderer *zoneAffichage){

    int nb_pts;
    int trouves_E1 = 0;
    int trouves_E2 = 0;
    int i;

    t_coordonnee *nuagesStockes[5];

    srand(time(NULL)); /* Initialisation de l'aléatoire */
    
    /* Récupérer les zones via le nuage de points */
    nuagesStockes[1] = nuage_de_points(&nb_pts, "../img/test1_c.jpg");
    generer_catalogue_depuis_nuage(nuagesStockes[1], nb_pts, catalogue, &trouves_E1, &trouves_E2, 1);

    nuagesStockes[2] = nuage_de_points(&nb_pts, "../img/test2_c.jpg");
    generer_catalogue_depuis_nuage(nuagesStockes[2], nb_pts, catalogue, &trouves_E1, &trouves_E2, 2);

    printf("Total de zones trouvées : E1=%d, E2=%d\n", trouves_E1, trouves_E2);

    /* Initialiser les joueurs et leurs dinosaures (3 dinosaures par équipe) */

    initialiserContenuJoueur(equipe1);
    initialiserContenuJoueur(equipe2);

    /* Placer les dinos sur la matrice */
    /* Équipe 1 (IDs matrice 2, 3, 4) */
    placer_une_equipe(equipe1, catalogue->zones_E1, matriceTerrain, D1);
    /* Équipe 2 (IDs matrice 5, 6, 7) */
    placer_une_equipe(equipe2, catalogue->zones_E2, matriceTerrain, D4);

    /* Charger les images (Textures) */

    chargerImageSansTaille(zoneAffichage, &(equipe1->texDinos[0]), "../img/dinoTransparent.png");
    chargerImageSansTaille(zoneAffichage, &(equipe1->texDinos[1]), "../img/dinoTransparent.png");
    chargerImageSansTaille(zoneAffichage, &(equipe1->texDinos[2]), "../img/dinoTransparent.png");

    chargerImageSansTaille(zoneAffichage, &(equipe2->texDinos[0]), "../img/dinoTransparent.png");
    chargerImageSansTaille(zoneAffichage, &(equipe2->texDinos[1]), "../img/dinoTransparent.png");
    chargerImageSansTaille(zoneAffichage, &(equipe2->texDinos[2]), "../img/dinoTransparent.png");
    
    chargerImageSansTaille(zoneAffichage, &(equipe1->texDinosInv[0]), "../img/dinoTransparentMiroir.png");
    chargerImageSansTaille(zoneAffichage, &(equipe1->texDinosInv[1]), "../img/dinoTransparentMiroir.png");
    chargerImageSansTaille(zoneAffichage, &(equipe1->texDinosInv[2]), "../img/dinoTransparentMiroir.png");

    chargerImageSansTaille(zoneAffichage, &(equipe2->texDinosInv[0]), "../img/dinoTransparentMiroir.png");
    chargerImageSansTaille(zoneAffichage, &(equipe2->texDinosInv[1]), "../img/dinoTransparentMiroir.png");
    chargerImageSansTaille(zoneAffichage, &(equipe2->texDinosInv[2]), "../img/dinoTransparentMiroir.png");

    for(i=1; i<3; i++) {
        nuageDetruire(&(nuagesStockes[i]));
    }
}

void detecterEvenementMenuPrincipal(
    int *enCours, 
    int *bombeLancee, 
    int *nombreRebonds, 
    SDL_Renderer *zoneAffichage, 
    SDL_Texture *texMap, 
    SDL_Rect *rectFen, 
    t_bombe *bombe, 
    t_vect *vectVitesse, 
    t_joueur *equipe1, 
    t_joueur *equipe2, 
    t_case dinoCourant, 
    t_case matriceTerrain[HAUTEUR_TERRAIN][LARGEUR_TERRAIN] ){

    const Uint8 *etatClavier;
    SDL_Event evenement;
    float gravite = 140;

    while (SDL_PollEvent(&evenement)){
        if (evenement.type == SDL_QUIT){
            *enCours = 0;
        }
    }

    etatClavier = SDL_GetKeyboardState(NULL);

    if (etatClavier[SDL_SCANCODE_B]){
        *bombeLancee = 1;
        *nombreRebonds = 0;

        choixHauteurLancerDinoCourant(zoneAffichage, texMap, rectFen, &etatClavier, bombe, vectVitesse, gravite, equipe1, equipe2, dinoCourant, matriceTerrain);
    }
}

void afficherJeuSansBombe(t_joueur *equipe1, t_joueur *equipe2, SDL_Rect *rectFen, SDL_Renderer *zoneAffichage, SDL_Texture *texMap){

    SDL_RenderClear(zoneAffichage);
    SDL_RenderCopy(zoneAffichage, texMap, NULL, rectFen);

    afficherDinos(zoneAffichage, equipe1);
    afficherDinos(zoneAffichage, equipe2);

    SDL_RenderPresent(zoneAffichage);

}

void afficherJeuAvecBombe(t_joueur *equipe1, t_joueur *equipe2, t_bombe * bombe, SDL_Rect *rectFen, SDL_Renderer *zoneAffichage, SDL_Texture *texMap){

    SDL_RenderClear(zoneAffichage);
    SDL_RenderCopy(zoneAffichage, texMap, NULL, rectFen);
    tracerBombe(zoneAffichage, bombe);

    afficherDinos(zoneAffichage, equipe1);
    afficherDinos(zoneAffichage, equipe2);

    SDL_RenderPresent(zoneAffichage);

}

void destruireElementsJeu(t_joueur *equipe1, t_joueur *equipe2, t_case matriceTerrain[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], SDL_Texture *texMap, SDL_Renderer *zoneAffichage, SDL_Window *fenJeu){

    detruireContenuJoueur(equipe1);
    detruireContenuJoueur(equipe2);
 
    detruireMatrice(&matriceTerrain);

    SDL_DestroyTexture(texMap);
    SDL_DestroyRenderer(zoneAffichage);
    SDL_DestroyWindow(fenJeu);
}

void lancerBombe(Uint32 *tempsPrecedent, int * bombeLancee, int *nombreRebonds, t_bombe * bombe, t_vect *vectVitesse, 
    t_case matriceTerrain[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], t_joueur *equipe1, t_joueur *equipe2, t_tour *gestionTours,
    SDL_Rect *rectFen, SDL_Renderer * zoneAffichage, SDL_Texture *texMap
    ){

    const float vitesse = 1.0f/250.0f;
    static float accumulateur = 0;
    float gravite = 140;
    t_case dinoTouche = AIR;
    float tempsEcoule;

    miseAjourTemps(tempsPrecedent, &tempsEcoule);
    accumulateur += tempsEcoule;

    while (accumulateur >= vitesse) {
        if (*bombeLancee == 1) {

            bombe->coor.x += vitesse*vectVitesse->u;
            bombe->coor.y += vitesse*vectVitesse->v;
            vectVitesse->v += gravite*vitesse;

            if (collisionFrontiereBombe(bombe)) {
                *bombeLancee = -1;
                printf("Collision avec la frontière. \n");

            }

            dinoTouche = collisionDinoBombe(matriceTerrain, bombe);

            if (((dinoTouche >= D1) && (dinoTouche <= D6)) || collisionEauBombe(matriceTerrain, bombe)) {
                *bombeLancee = -1;
                printf("Collision avec eau ou dinosaure. \n");

                if ((dinoTouche >= D1) && (dinoTouche <= D6)){
                    printf("Collision avec un dinosaure. \n");
                    supprimer_matrice_dino(recupererDinoNumero(equipe1, equipe2, dinoTouche), matriceTerrain);
                    supprimerDinoJoueur(equipe1, equipe2, dinoTouche);
                    dinoTouche = AIR;
                }

                afficherJeuSansBombe(equipe1, equipe2, rectFen, zoneAffichage, texMap);
                
            }
            if (collisionTerrainBombe(matriceTerrain, bombe, vectVitesse)) {
                (*nombreRebonds) ++;
                printf("Collision avec le terrain. \n");

                if (*nombreRebonds > 1){
                    *bombeLancee = -1;
                }
            }

            if (*bombeLancee == 1) {

                afficherJeuAvecBombe(equipe1, equipe2, bombe, rectFen, zoneAffichage, texMap);
            }
            
            if (*bombeLancee == -1){
                tourSuivant(gestionTours, equipe1, equipe2);
                printf("Passage au dinosaure %d, tour numéro %d, équipe numéro %d \n", gestionTours->dinoCourant, gestionTours->numeroTour, gestionTours->equipeCourante);
                initialiserVitesse(vectVitesse, VITESSE_X, VITESSE_Y);
            }
        }
        accumulateur -= vitesse;
    }
}

