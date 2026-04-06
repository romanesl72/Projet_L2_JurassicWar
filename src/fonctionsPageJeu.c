#include "../lib/chargerMatrice.h"
#include "../lib/fonctionsChangementTour.h"
#include "../lib/fonctionsMenuHIP.h"
#include "../lib/fonctionSoin.h"
#include "../lib/fonctionsPageJeu.h"
#include "../lib/fonctionsRebonds.h"
#include "../lib/fonctionsStructJoueur.h"
#include "../lib/fonctionsTirs.h"
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
 * @version 1.3
 */

int creerPageJeuBombe(SDL_Window **fenJeu, SDL_Renderer **zoneAffichage, SDL_Texture **texMap){

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

/* création de la page de jeu avec les armes,  J'ai ajouté initialisation de la police du menuHIP
et la liste des images d'armes */

int creerPageJeu(SDL_Window **fenJeu, SDL_Renderer **zoneAffichage, SDL_Texture **texMap, SDL_Texture **texObjets, TTF_Font **policeMenuHIP){

    int i;

    char *nomsObjets[7] = {
        "../img/img_arc.png", 
        "../img/img_arbalete.png", 
        "../img/img_bombe.png", 
        "../img/img_fusil.png", 
        "../img/img_revolver.png", 
        "../img/img_potion.png", 
        "../img/img_grappin.png"};

    creerFenetre(fenJeu, "JurassicWar - Partie en cours", LARGEUR_TERRAIN, HAUTEUR_FEN_JEU_HIP);
    initialiserPolice(policeMenuHIP, "../pde/arial.ttf", 16);

    *zoneAffichage = SDL_CreateRenderer(*fenJeu, -1, SDL_RENDERER_ACCELERATED);

    if(!*zoneAffichage) {

        printf("Erreur lors de l'initialisation de la zone d'affichage de la fenêtre du jeu \n.");
        SDL_DestroyWindow(*fenJeu);
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return 0;

    }

    for(i=0; i<7; i++) {
        chargerImageSansTaille(*zoneAffichage, &texObjets[i], nomsObjets[i]);
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

void detecterEvenementsPageJeuBombe(
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

    while (SDL_PollEvent(&evenement)){
        if (evenement.type == SDL_QUIT){
            *enCours = 0;
        }
    }

    etatClavier = SDL_GetKeyboardState(NULL);

    if (etatClavier[SDL_SCANCODE_B]){
        *bombeLancee = 1;
        *nombreRebonds = 0;

        choixHauteurLancerDinoCourant(zoneAffichage, texMap, rectFen, &etatClavier, bombe, vectVitesse, equipe1, equipe2, dinoCourant, matriceTerrain);
    }
}

/* Ajouter les touches pour les armes dans les évènements */
void detecterEvenementsPageJeu(
    int *enCours, 
    int *bombeLancee, 
    int *nombreRebonds, 
    SDL_Renderer *zoneAffichage, 
    SDL_Texture *texMap, 
    SDL_Texture **texObjets,
    TTF_Font *policeMenuHIP,
    SDL_Rect *rectFen, 
    t_bombe *bombe, 
    t_vect *vectVitesse, 
    t_tir *tir, 
    t_joueur *equipe1, 
    t_joueur *equipe2, 
    t_case dinoCourant, 
    t_case matriceTerrain[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], 
    t_texte_cache *cache,
    t_arme catalogue[4] ){

    const Uint8 *etatClavier;
    SDL_Event evenement;

    t_dino *dinoActuel = recupererDinoNumero(equipe1, equipe2, dinoCourant);
    int armePrise = -1;
    //Ajout de cette vérification ? if (dinoActuel != NULL)


    while (SDL_PollEvent(&evenement)){
        if (evenement.type == SDL_QUIT){
            *enCours = 0;
        }
    }

    etatClavier = SDL_GetKeyboardState(NULL);

    /* La Bombe */
    if (etatClavier[SDL_SCANCODE_B]){
        *bombeLancee = 1;
        *nombreRebonds = 0;

        choixHauteurLancerDinoCourantHIP(zoneAffichage, texMap, texObjets, policeMenuHIP, rectFen, &etatClavier, bombe, vectVitesse, equipe1, equipe2, dinoCourant, matriceTerrain, cache);
    }

    /* Les Armes de tirs */
    else if (etatClavier[SDL_SCANCODE_Q]) armePrise = 0; 
    else if (etatClavier[SDL_SCANCODE_A]) armePrise = 1;
    else if (etatClavier[SDL_SCANCODE_F]) armePrise = 2;
    else if (etatClavier[SDL_SCANCODE_R]) armePrise = 3;

    if (armePrise != -1 && !(tir->actif)) {
        
        tir->pos.x = dinoActuel->pos.x + 15; 
        tir->pos.y = dinoActuel->pos.y + 15;
        tir->arme_source = catalogue[armePrise];
        
        viserArcher(zoneAffichage, texMap, texObjets, policeMenuHIP, armePrise, tir, etatClavier, GRAVITE, equipe1, equipe2);
    }

    /* La Potion */
    if (etatClavier[SDL_SCANCODE_P]) {
        utiliserPotion(dinoActuel);
    }

}

void afficherJeuSansBombe(t_joueur *equipe1, t_joueur *equipe2, SDL_Rect *rectFen, SDL_Renderer *zoneAffichage, SDL_Texture *texMap){

    SDL_RenderClear(zoneAffichage);
    SDL_RenderCopy(zoneAffichage, texMap, NULL, rectFen);

    afficherDinos(zoneAffichage, equipe1);
    afficherDinos(zoneAffichage, equipe2);

    SDL_RenderPresent(zoneAffichage);

}

void afficherJeuAvecBombe(t_joueur *equipe1, t_joueur *equipe2, t_bombe *bombe, SDL_Rect *rectFen, SDL_Renderer *zoneAffichage, SDL_Texture *texMap){

    SDL_RenderClear(zoneAffichage);
    SDL_RenderCopy(zoneAffichage, texMap, NULL, rectFen);
    tracerBombe(zoneAffichage, bombe);

    afficherDinos(zoneAffichage, equipe1);
    afficherDinos(zoneAffichage, equipe2);

    SDL_RenderPresent(zoneAffichage);

}

/* créer des fonctions d'affichage avec toutes les armes : bombe et tirs + menuHIP */
void afficherJeuSansArmes(t_joueur *equipe1, t_joueur *equipe2, SDL_Rect *rectFen, SDL_Renderer *zoneAffichage, SDL_Texture *texMap, SDL_Texture **texObjets, TTF_Font *policeMenuHIP, t_texte_cache *cache){

    SDL_RenderClear(zoneAffichage);

    SDL_RenderCopy(zoneAffichage, texMap, NULL, rectFen);

    afficherDinosAvecJeu(zoneAffichage, equipe1);
    afficherDinosAvecJeu(zoneAffichage, equipe2);

    /* Affichage de l'inventaire */
    afficherInventaire(zoneAffichage, texObjets, 7);
    afficherMenuPVDinosOp(zoneAffichage, policeMenuHIP, *equipe1, *equipe2, cache);

    SDL_RenderPresent(zoneAffichage);

}

void afficherJeuAvecArmes(t_joueur *equipe1, t_joueur *equipe2, t_bombe *bombe, SDL_Rect *rectFen, SDL_Renderer *zoneAffichage, SDL_Texture *texMap, SDL_Texture **texObjets, TTF_Font *policeMenuHIP, t_texte_cache *cache){

    SDL_RenderClear(zoneAffichage);
    SDL_RenderCopy(zoneAffichage, texMap, NULL, rectFen);

    tracerBombeHIP(zoneAffichage, bombe);

    afficherDinosAvecJeu(zoneAffichage, equipe1);
    afficherDinosAvecJeu(zoneAffichage, equipe2);

    /* Affichage de l'inventaire */
    afficherInventaire(zoneAffichage, texObjets, 7);
    afficherMenuPVDinosOp(zoneAffichage, policeMenuHIP, *equipe1, *equipe2, cache);

    SDL_RenderPresent(zoneAffichage);

}

void destruireElementsJeuBombe(t_joueur *equipe1, t_joueur *equipe2, t_case matriceTerrain[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], SDL_Texture *texMap, SDL_Renderer *zoneAffichage, SDL_Window *fenJeu){

    detruireContenuJoueur(equipe1);
    detruireContenuJoueur(equipe2);
 
    detruireMatrice(&matriceTerrain);

    SDL_DestroyTexture(texMap);
    SDL_DestroyRenderer(zoneAffichage);
    SDL_DestroyWindow(fenJeu);
}

/* Détruire les éléments que tu initialises pour tes armes */
void destruireElementsJeu(t_joueur *equipe1, t_joueur *equipe2, t_case matriceTerrain[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], SDL_Texture *texMap, SDL_Texture **texObjets, TTF_Font *policeMenuHIP, SDL_Renderer *zoneAffichage, SDL_Window *fenJeu){
    int i;

    detruireContenuJoueur(equipe1);
    detruireContenuJoueur(equipe2);
 
    detruireMatrice(&matriceTerrain);

    TTF_CloseFont(policeMenuHIP);

    for(i=0; i<7; i++){
        if(texObjets[i]) {
            SDL_DestroyTexture(texObjets[i]);
        }
    }

    SDL_DestroyTexture(texMap);
    SDL_DestroyRenderer(zoneAffichage);
    SDL_DestroyWindow(fenJeu);
}

void lancerBombeSansHIP(Uint32 *tempsPrecedent, int * bombeLancee, int *nombreRebonds, t_bombe * bombe, t_vect *vectVitesse, 
    t_case matriceTerrain[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], t_joueur *equipe1, t_joueur *equipe2, t_tour *gestionTours,
    SDL_Rect *rectFen, SDL_Renderer * zoneAffichage, SDL_Texture *texMap
    ){

    const float vitesse = 1.0f/250.0f;
    static float accumulateur = 0;
    t_case dinoTouche = AIR;
    float tempsEcoule;

    miseAjourTemps(tempsPrecedent, &tempsEcoule);
    accumulateur += tempsEcoule;

    while (accumulateur >= vitesse) {
        if (*bombeLancee == 1) {

            bombe->coor.x += vitesse*vectVitesse->u;
            bombe->coor.y += vitesse*vectVitesse->v;
            vectVitesse->v += GRAVITE*vitesse;

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

/* Fonction pour le lancer de la bombe adaptée au menu des armes */
void lancerBombe(Uint32 *tempsPrecedent, int * bombeLancee, int *nombreRebonds, t_bombe * bombe, t_vect *vectVitesse, 
    t_case matriceTerrain[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], t_joueur *equipe1, t_joueur *equipe2, t_tour *gestionTours,
    SDL_Rect *rectFen, SDL_Renderer * zoneAffichage, SDL_Texture *texMap, SDL_Texture **texObjets, TTF_Font *policeMenuHIP, t_texte_cache *cache
    ){

    const float vitesse = 1.0f/250.0f;
    static float accumulateur = 0;
    t_case dinoTouche = AIR;
    float tempsEcoule;

    miseAjourTemps(tempsPrecedent, &tempsEcoule);
    accumulateur += tempsEcoule;

    while (accumulateur >= vitesse) {
        if (*bombeLancee == 1) {

            bombe->coor.x += vitesse*vectVitesse->u;
            bombe->coor.y += vitesse*vectVitesse->v;
            vectVitesse->v += GRAVITE*vitesse;

            if (collisionFrontiereBombe(bombe)) {
                *bombeLancee = -1;
                afficherJeuSansArmes(equipe1, equipe2, rectFen, zoneAffichage, texMap, texObjets, policeMenuHIP, cache);
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

                afficherJeuSansArmes(equipe1, equipe2, rectFen, zoneAffichage, texMap, texObjets, policeMenuHIP, cache);
                
            }
            if (collisionTerrainBombe(matriceTerrain, bombe, vectVitesse)) {
                (*nombreRebonds) ++;
                printf("Collision avec le terrain. \n");

                if (*nombreRebonds > 1){
                    *bombeLancee = -1;
                    afficherJeuSansArmes(equipe1, equipe2, rectFen, zoneAffichage, texMap, texObjets, policeMenuHIP, cache);
                }
            }

            if (*bombeLancee == 1) {

                afficherJeuAvecArmes(equipe1, equipe2, bombe, rectFen, zoneAffichage, texMap, texObjets, policeMenuHIP, cache);
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

void lancerPartieBombe(){
    if (initialisationCorrecte()) {

        int enCours = 1;

        t_joueur equipe1, equipe2;

        t_bombe bombe;

        t_vect vectVitesse;

        int bombeLancee = 0;
        int nombreRebonds = 0;

        // Variable de changement de tour
        t_tour gestionTours = {1, 1, D1, D6};

        SDL_Window *menuPrincipal;
        SDL_Renderer* zoneAffichage;
        SDL_Texture *texMap;
        SDL_Rect rectFen = {0, 0, LARGEUR_TERRAIN, HAUTEUR_TERRAIN};

        t_catalogue_zones catalogue;

        t_case (*matriceTerrain)[LARGEUR_TERRAIN] = NULL;

        if (!creerPageJeuBombe(&menuPrincipal, &zoneAffichage, &texMap)){
            return;
        }

        initialiserRayonBombe(&bombe, RAYON);
        initialiserVitesse(&vectVitesse, VITESSE_X, VITESSE_Y);
        initialiserMatrice(&matriceTerrain);
        initialiserEquipes(&equipe1, &equipe2, &catalogue, matriceTerrain, zoneAffichage);

        afficherJeuSansBombe(&equipe1, &equipe2, &rectFen, zoneAffichage, texMap);

        Uint32 tempsPrecedent = SDL_GetTicks();
        
        while(enCours) {

            detecterEvenementsPageJeuBombe(&enCours, &bombeLancee, &nombreRebonds, zoneAffichage, texMap, &rectFen, &bombe, &vectVitesse, &equipe1, &equipe2, gestionTours.dinoCourant, matriceTerrain);
            lancerBombeSansHIP(&tempsPrecedent, &bombeLancee, &nombreRebonds, &bombe, &vectVitesse, matriceTerrain, &equipe1, &equipe2, &gestionTours, &rectFen, zoneAffichage, texMap);

        }

        // --- NETTOYAGE --- 

        destruireElementsJeuBombe(&equipe1, &equipe2, matriceTerrain, texMap, zoneAffichage, menuPrincipal);
        IMG_Quit();
        TTF_Quit();
        SDL_Quit();
    }
}

/* Une partie avec les bombes et les armes !!! */
void lancerPartie(){
    if (initialisationCorrecte()) {

        int enCours = 1;
        int col;

        t_joueur equipe1, equipe2;
        t_dino *tireurActuel;

        // Variables pour les tirs
        t_arme catalogue_armes[4]; // Arc, Arbalete, Bombe Fusil, Revolver
        catalogue_armes[0] = (t_arme){ARC, 20, 1.0f, 5.0f, 15.0f};
        catalogue_armes[1] = (t_arme){ARBALETE, 35, 1.2f, 8.0f, 18.0f};
        catalogue_armes[2] = (t_arme){FUSIL, 45, 0.4f, 15.0f, 30.0f};
        catalogue_armes[3] = (t_arme){REVOLVER, 30, 0.6f, 13.0f, 25.0f};
        t_tir tir;              /* Pour flèches/balles */
        tir.actif = 0;

        // Variables pour la bombe 
        t_bombe bombe;
        t_vect vectVitesse;
        int bombeLancee = 0;
        int nombreRebonds = 0;

        // Variable de changement de tour
        t_tour gestionTours = {1, 1, D1, D6};

        // Variables pour la fenetre et les menus
        SDL_Window *fenJeu;
        SDL_Renderer *zoneAffichage;
        SDL_Texture *texMap;
        SDL_Texture *texObjets[7];
        TTF_Font *policeMenuHIP = NULL;
        SDL_Rect rectFen = {0, HAUTEUR_HIP, LARGEUR_TERRAIN, HAUTEUR_TERRAIN};

        t_catalogue_zones catalogue;

        t_case (*matriceTerrain)[LARGEUR_TERRAIN] = NULL;

        if (!creerPageJeu(&fenJeu, &zoneAffichage, &texMap, texObjets, &policeMenuHIP)){
            return;
        }

        /* Initialiser images du menu */
        t_texte_cache cache[6];
        chargerTexteDinos(zoneAffichage, policeMenuHIP, cache);

        initialiserRayonBombe(&bombe, RAYON);
        initialiserVitesse(&vectVitesse, VITESSE_X, VITESSE_Y);
        initialiserMatrice(&matriceTerrain);
        initialiserEquipes(&equipe1, &equipe2, &catalogue, matriceTerrain, zoneAffichage);

        SDL_SetRenderDrawColor(zoneAffichage, 40, 40, 40, 255);
        afficherJeuSansArmes(&equipe1, &equipe2, &rectFen, zoneAffichage, texMap, texObjets, policeMenuHIP, cache);

        Uint32 tempsPrecedent = SDL_GetTicks();
        
        while(enCours) {

            detecterEvenementsPageJeu(&enCours, &bombeLancee, &nombreRebonds, zoneAffichage, texMap, texObjets, policeMenuHIP, &rectFen, &bombe, &vectVitesse, &tir, &equipe1, &equipe2, gestionTours.dinoCourant, matriceTerrain, cache, catalogue_armes);
            //detecterEvenementsPageJeu(&enCours, &bombeLancee, &nombreRebonds, zoneAffichage, texMap, texObjets, policeMenuHIP, &rectFen, &bombe, &vectVitesse, &equipe1, &equipe2, gestionTours.dinoCourant, matriceTerrain, cache);
            
            /* Ici je ne comprends pas, dans ta fonction detecterEvenemntsPageJeu tu n'as pas déjà lancé ta bombe ?*/
            lancerBombe(&tempsPrecedent, &bombeLancee, &nombreRebonds, &bombe, &vectVitesse, matriceTerrain, &equipe1, &equipe2, &gestionTours, &rectFen, zoneAffichage, texMap, texObjets, policeMenuHIP, cache);

            if (tir.actif) {
                // On récupère le tireur pour l'ID (éviter qu'il se tire dessus)
                tireurActuel = recupererDinoNumero(&equipe1, &equipe2, gestionTours.dinoCourant);
                
                col = mettreAJourVol(&tir, matriceTerrain, GRAVITE, tireurActuel->d);
                
                if (col >= D1) { // Touche un dino
                    appliquerDegats(col, tir.arme_source.degats, &equipe1, &equipe2, matriceTerrain);
                    tir.actif = 0;
                    tourSuivant(&gestionTours, &equipe1, &equipe2); // On change de tour après l'impact
                }
                else if (col != 0) { // Touche sol ou eau
                    tir.actif = 0;
                    tourSuivant(&gestionTours, &equipe1, &equipe2);
                }
            }

            if (tir.actif) {
                afficherJeuSansArmes(&equipe1, &equipe2, &rectFen, zoneAffichage, texMap, texObjets, policeMenuHIP, cache);
                
                t_tir tirAffichage = tir;
                tirAffichage.pos.y += 100;
                tracerArme(zoneAffichage, &tirAffichage);
                
                SDL_RenderPresent(zoneAffichage);
            }
        }

        // --- NETTOYAGE --- 

        for (int i = 0; i < 6; i++) {
            SDL_DestroyTexture(cache[i].tex);
        }
        destruireElementsJeu(&equipe1, &equipe2, matriceTerrain, texMap, texObjets, policeMenuHIP, zoneAffichage, fenJeu);
        IMG_Quit();
        TTF_Quit();
        SDL_Quit();
    }
}

