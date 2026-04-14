#include "../lib/chargerMatrice.h"
#include "../lib/deplacement.h"
#include "../lib/fonctionsChangementTour.h"
#include "../lib/fonctionsMenuHIP.h"
#include "../lib/fonctionsPageFinPartie.h"
#include "../lib/fonctionsPageJeu.h"
#include "../lib/fonctionsRebonds.h"
#include "../lib/fonctionSoin.h"
#include "../lib/fonctionsStructJoueur.h"
#include "../lib/fonctionsTirs.h"
#include "../lib/fonctionsTuerDinos.h"
#include "../lib/fonctionsVerification.h"
#include "../lib/gestion_zones.h"
#include "../lib/placer_dinos.h"
#include "../lib/regression.h"
#include "../lib/tda_nuage.h"
#include "../lib/grappin.h"

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
    nuagesStockes[0] = nuage_de_points(&nb_pts, "../img/test1_c.jpg");
    generer_catalogue_depuis_nuage(nuagesStockes[0], nb_pts, catalogue, &trouves_E1, &trouves_E2, 0);

    nuagesStockes[1] = nuage_de_points(&nb_pts, "../img/test2_c.jpg");
    generer_catalogue_depuis_nuage(nuagesStockes[1], nb_pts, catalogue, &trouves_E1, &trouves_E2, 1);
    
    for(i=0; i<2; i++) {
        nuageDetruire(&(nuagesStockes[i]));
    }

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

    for (i = 0; i < NOMBRE_DINOS/2; i++){
        chargerImageSansTaille(zoneAffichage, &(equipe1->texDinos[i]), "../img/dinoTransparent.png");
        chargerImageSansTaille(zoneAffichage, &(equipe2->texDinos[i]), "../img/dinoTransparent.png");
        chargerImageSansTaille(zoneAffichage, &(equipe1->texDinosInv[i]), "../img/dinoTransparentMiroir.png");
        chargerImageSansTaille(zoneAffichage, &(equipe2->texDinosInv[i]), "../img/dinoTransparentMiroir.png");
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
    t_case matriceTerrain[HAUTEUR_TERRAIN][LARGEUR_TERRAIN]){

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

/** 
 * @brief La fonction détecte si l'utilisateur réalise une action dans la fenêtre du jeu (appuyer sur une touche ou encore cliquer sur la croix pour fermer).
 * @author Hannah Sergent
 * @date Crée le 5/04/2026
 * @version 1.3
 * @param enCours un pointeur qui indique si la fenetre doit rester ouverte
 * @param nombreRebonds un pointeur sur le nombre de rebonds de la bombe
 * @param bombeLancee un pointeur qui indique si la bombe doit être lancée
 * @param zoneAffichage un pointeur sur la zone d'affichage
 * @param texMap un pointeur sur la texture de la map
 * @param texObjets le tableau des textures affichées dans l'inventaire
 * @param policeMenuHIP un pointeur sur la police utilisée dans le menu HIP
 * @param rectFen un rectangle de type SDL_Rect contenant les informations sur la fenêtre du jeu
 * @param bombe un pointeur sur une structure de type bombe
 * @param vectVitesse un pointeur sur le vecteur vitesse de la bombe
 * @param tir un pointeur sur une structure de type tir
 * @param equipe1 un pointeur sur la structure correspondant aux dinosaures du joueur 1
 * @param equipe2 un pointeur sur la structure correspondant aux dinosaures du joueur 2
 * @param dinoCourant l'identifiant du dinosaure dont c'est le tour de jouer
 * @param matriceTerrain la matrice contenant les informations sur le terrain
 * @param cache un pointeur sur une structure contenant le texte à afficher pour le menu HIP
 * @param catalogue_armes un tableau d'armes
 */

int detecterEvenementsPageJeu(
    int *enCours,  
    int *nombreRebonds,
    int *bombeLancee, 
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
    t_arme catalogue_armes[4],
    char *nomNuage[],
    t_coordonnee **nuage,
    int *nb_pts){

    const Uint8 *etatClavier;
    SDL_Event evenement;
    
    t_dino *tireur = recupererDinoNumero(equipe1, equipe2, dinoCourant);


    while (SDL_PollEvent(&evenement)){
        if (evenement.type == SDL_QUIT){
            *enCours = 0;
        }
    }

    etatClavier = SDL_GetKeyboardState(NULL);

    /* La Bombe */
    if (etatClavier[SDL_SCANCODE_B]){
        *nombreRebonds = 0;
        *bombeLancee = 2;

        choixHauteurLancerDinoCourantHIP(zoneAffichage, texMap, texObjets, policeMenuHIP, rectFen, &etatClavier, bombe, vectVitesse, equipe1, equipe2, dinoCourant, matriceTerrain, cache);
        return 2;
    }

    /* Les Tirs */
    if (!tir->actif){

        if (etatClavier[SDL_SCANCODE_Q]) {
            tir->arme_source = catalogue_armes[0];
            tir->actif = 1;
        }
        else if (etatClavier[SDL_SCANCODE_A]) {
            tir->arme_source = catalogue_armes[1];
            tir->actif = 1;
        }
        else if (etatClavier[SDL_SCANCODE_F]) {
            tir->arme_source = catalogue_armes[2];
            tir->actif = 1;
        }
        else if (etatClavier[SDL_SCANCODE_R]) {
            tir->arme_source = catalogue_armes[3];
            tir->actif = 1;
        }
        else if (etatClavier[SDL_SCANCODE_P]) {
            utiliserPotion(tireur);
            return 3;
        }
        if (etatClavier[SDL_SCANCODE_G]) {
            grappin(matriceTerrain, zoneAffichage, &tireur, etatClavier, texMap, policeMenuHIP, texObjets, equipe1, equipe2 , nb_pts, nuage, 2, nomNuage);
            return 4;
        }

        if (tir->actif){
            /* On replace le tir sur le dino avant de viser */
            tir->pos.x = tireur->pos.x + 15;
            tir->pos.y = tireur->pos.y + 15;
            
            /* Bloque le jeu tant qu'on n'a pas appuyé sur ESPACE */
            viserArcher(zoneAffichage, texMap, texObjets, policeMenuHIP, tir, etatClavier, GRAVITE, equipe1, equipe2, dinoCourant);
        }
    }
    return tir->actif;
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

/** 
 * @fn void afficherJeuSansArmes(t_joueur *equipe1, t_joueur *equipe2, SDL_Rect *rectFen, SDL_Renderer *zoneAffichage, SDL_Texture *texMap, SDL_Texture **texObjets, TTF_Font *policeMenuHIP, t_texte_cache *cache);
 * @brief La fonction affiche l'image du terrain, l'inventaire et les dinosaures.
 * @author Hannah Sergent
 * @date Crée le 5/04/2026
 * @version 1.0
 * @param equipe1 un pointeur sur la structure correspondant aux dinosaures du joueur 1
 * @param equipe2 un pointeur sur la structure correspondant aux dinosaures du joueur 2
 * @param rectFen un rectangle de type SDL_Rect contenant les informations sur la fenêtre du jeu
 * @param zoneAffichage un pointeur sur la zone d'affichage
 * @param texMap un pointeur sur la texture de la map
 * @param texObjets le tableau des textures affichées dans l'inventaire
 * @param policeMenuHIP un pointeur sur la police utilisée dans le menu HIP
 * @param cache un pointeur sur une structure contenant le texte à afficher pour le menu HIP
 */

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

/** 
 * @fn void afficherJeuAvecArmes(t_joueur *equipe1, t_joueur *equipe2, t_bombe *bombe, SDL_Rect *rectFen, SDL_Renderer *zoneAffichage, SDL_Texture *texMap, SDL_Texture **texObjets, TTF_Font *policeMenuHIP, t_texte_cache *cache);
 * @brief La fonction affiche l'image du terrain, l'inventaire, les dinosaures et la bombe.
 * @author Hannah Sergent
 * @date Crée le 5/04/2026
 * @version 1.0
 * @param equipe1 un pointeur sur la structure correspondant aux dinosaures du joueur 1
 * @param equipe2 un pointeur sur la structure correspondant aux dinosaures du joueur 2
 * @param bombe un pointeur sur une structure de type bombe
 * @param rectFen un rectangle de type SDL_Rect contenant les informations sur la fenêtre du jeu
 * @param zoneAffichage un pointeur sur la zone d'affichage
 * @param texMap un pointeur sur la texture de la map
 * @param texObjets le tableau des textures affichées dans l'inventaire
 * @param policeMenuHIP un pointeur sur la police utilisée dans le menu HIP
 * @param cache un pointeur sur une structure contenant le texte à afficher pour le menu HIP
 */

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

/** 
 * @fn void afficherJeuAvecArmesTir(t_joueur *equipe1, t_joueur *equipe2, SDL_Rect *rectFen, SDL_Renderer *zoneAffichage, SDL_Texture *texMap, SDL_Texture **texObjets, TTF_Font *policeMenuHIP, t_texte_cache *cache, t_tir *tir);
 * @brief La fonction affiche l'image du terrain, l'inventaire, les dinosaures et une arme de tir.
 * @author Hannah Sergent
 * @date Crée le 5/04/2026
 * @version 1.0
 * @param equipe1 un pointeur sur la structure correspondant aux dinosaures du joueur 1
 * @param equipe2 un pointeur sur la structure correspondant aux dinosaures du joueur 2
 * @param rectFen un rectangle de type SDL_Rect contenant les informations sur la fenêtre du jeu
 * @param zoneAffichage un pointeur sur la zone d'affichage
 * @param texMap un pointeur sur la texture de la map
 * @param texObjets le tableau des textures affichées dans l'inventaire
 * @param policeMenuHIP un pointeur sur la police utilisée dans le menu HIP
 * @param cache un pointeur sur une structure contenant le texte à afficher pour le menu HIP
 * @param tir un pointeur sur une structure de type tir
 */

void afficherJeuAvecArmesTir(t_joueur *equipe1, t_joueur *equipe2, SDL_Rect *rectFen, SDL_Renderer *zoneAffichage, SDL_Texture *texMap, SDL_Texture **texObjets, TTF_Font *policeMenuHIP, t_texte_cache *cache, t_tir *tir){

    SDL_RenderClear(zoneAffichage);
    SDL_RenderCopy(zoneAffichage, texMap, NULL, rectFen);

    t_tir tirAffichage = *tir;
    tirAffichage.pos.y += HAUTEUR_HIP;
    tracerArme(zoneAffichage, &tirAffichage);

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

/** 
 * @fn void destruireElementsJeu(t_joueur *equipe1, t_joueur *equipe2, t_case matriceTerrain[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], SDL_Texture *texMap, SDL_Texture **texObjets, TTF_Font *policeMenuHIP, SDL_Renderer *zoneAffichage, SDL_Window *fenJeu, t_coordonnee *nuage, t_texte_cache *cache);
 * @brief La fonction détruit les différents objets mis en place pour le jeu.
 * @author Hannah Sergent
 * @date Crée le 29/03/2026
 * @version 1.0
 * @param equipe1 un pointeur sur la structure correspondant aux dinosaures du joueur 1
 * @param equipe2 un pointeur sur la structure correspondant aux dinosaures du joueur 2
 * @param matriceTerrain la matrice contenant les informations sur le terrain
 * @param texMap un pointeur sur la texture de la map
 * @param texObjets le tableau des textures affichées dans l'inventaire
 * @param policeMenuHIP un pointeur sur la police utilisée dans le menu HIP
 * @param zoneAffichage un pointeur sur la zone d'affichage
 * @param fenJeu un pointeur sur la fenêtre du jeu
 * @param nuage un pointeur sur les coordonnées d'un nuage
 * @param cache un pointeur sur une structure contenant le texte à afficher pour le menu HIP
 */

void destruireElementsJeu(t_joueur *equipe1, t_joueur *equipe2, t_case matriceTerrain[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], SDL_Texture *texMap, SDL_Texture **texObjets, TTF_Font *policeMenuHIP, SDL_Renderer *zoneAffichage, SDL_Window *fenJeu, t_coordonnee *nuage, t_texte_cache *cache){
    int i;

    nuageDetruire(&nuage);
    detruireContenuJoueur(equipe1);
    detruireContenuJoueur(equipe2);
 
    detruireMatrice(&matriceTerrain);

    TTF_CloseFont(policeMenuHIP);

    for(i=0; i<7; i++){
        if(texObjets[i]) {
            SDL_DestroyTexture(texObjets[i]);
        }
    }

    for (i = 0; i < 6; i++) {
        SDL_DestroyTexture(cache[i].tex);
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
            vectVitesse->v += GRAVITE_BOMBE*vitesse;

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

/** 
 * @fn void lancerBombe(int * bombeLancee, int *nombreRebonds, t_bombe * bombe, t_vect *vectVitesse, 
    t_case matriceTerrain[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], t_joueur *equipe1, t_joueur *equipe2, t_tour *gestionTours,
    SDL_Rect *rectFen, SDL_Renderer * zoneAffichage, SDL_Texture *texMap, SDL_Texture **texObjets, TTF_Font *policeMenuHIP, t_texte_cache *cache
    )
 * @brief La fonction lance la bombe en appelant toutes les fonctions liées à celle-ci avec un affichage intégrant le menu HIP.
 * @author Hannah Sergent
 * @date Crée le 29/03/2026
 * @param bombeLancee un pointeur sur une variable indiquant si la bombe est lancée
 * @param nombreRebonds un pointeur sur le nombre de rebonds effectués par la bombe
 * @param bombe un pointeur sur une structure de type bombe
 * @param vectVitesse un pointeur sur le vecteur vitesse de la bombe
 * @param matriceTerrain la matrice contenant les informations sur le terrain
 * @param equipe1 un pointeur sur la structure correspondant aux dinosaures du joueur 1
 * @param equipe2 un pointeur sur la structure correspondant aux dinosaures du joueur 2
 * @param gestionTours un pointeur sur une structure utilisée pour le changement de tour
 * @param rectFen un rectangle de type SDL_Rect contenant les informations sur la fenêtre du jeu
 * @param zoneAffichage un pointeur sur la zone d'affichage
 * @param texMap un pointeur sur la texture de la map
 * @param texObjets le tableau des textures affichées dans l'inventaire
 * @param policeMenuHIP un pointeur sur la police utilisée dans le menu HIP
 * @param cache un pointeur sur une structure contenant le texte à afficher pour le menu HIP
 */

void lancerBombe(int * bombeLancee, int *nombreRebonds, t_bombe * bombe, t_vect *vectVitesse, 
    t_case matriceTerrain[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], t_joueur *equipe1, t_joueur *equipe2, t_tour *gestionTours,
    SDL_Rect *rectFen, SDL_Renderer * zoneAffichage, SDL_Texture *texMap, SDL_Texture **texObjets, TTF_Font *policeMenuHIP, t_texte_cache *cache
    ){

    const float vitesse = 1.0f/120.0f;
    t_case dinoTouche = AIR;

    while ((*bombeLancee == 2)) {

        bombe->coor.x += vitesse*vectVitesse->u;
        bombe->coor.y += vitesse*vectVitesse->v;
        vectVitesse->v += GRAVITE_BOMBE*vitesse;

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

        if (*bombeLancee == 2) {

            afficherJeuAvecArmes(equipe1, equipe2, bombe, rectFen, zoneAffichage, texMap, texObjets, policeMenuHIP, cache);
        }
        
        if (*bombeLancee == -1){
            tourSuivant(gestionTours, equipe1, equipe2);
            printf("Passage au dinosaure %d, tour numéro %d, équipe numéro %d \n", gestionTours->dinoCourant, gestionTours->numeroTour, gestionTours->equipeCourante);
            initialiserVitesse(vectVitesse, VITESSE_X_MAIN, VITESSE_Y_MAIN);
        }
        SDL_Delay(4);
    }
}

/** 
 * @fn void effectuerDeplacement(t_joueur *equipe1, t_joueur *equipe2, t_tour *gestionTours, 
                          t_case matriceTerrain[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], 
                          SDL_Rect *rectFen, SDL_Renderer * zoneAffichage, 
                          SDL_Texture *texMap, SDL_Texture **texObjets, 
                          TTF_Font *policeMenuHIP, t_texte_cache *cache, 
                          t_dino **dinoActuel, int *timer, 
                          char **nomNuage, int *nb_pts, t_coordonnee **nuage);
 * @brief La fonction gère les éplacements des dinosaures dans le programme principal.
 * @author Hannah Sergent Solène Orieux
 * @date Crée le 5/04/2026
 * @param equipe1 un pointeur sur la structure correspondant aux dinosaures du joueur 1
 * @param equipe2 un pointeur sur la structure correspondant aux dinosaures du joueur 2
 * @param gestionTours un pointeur sur une structure utilisée pour le changement de tour
 * @param matriceTerrain la matrice contenant les informations sur le terrain
 * @param rectFen un rectangle de type SDL_Rect contenant les informations sur la fenêtre du jeu
 * @param zoneAffichage un pointeur sur la zone d'affichage
 * @param texMap un pointeur sur la texture de la map
 * @param texObjets le tableau des textures affichées dans l'inventaire
 * @param policeMenuHIP un pointeur sur la police utilisée dans le menu HIP
 * @param cache un pointeur sur une structure contenant le texte à afficher pour le menu HIP
 * @param dinoActuel un pointeur sur le dinosaure courant
 * @param timer un pointeur sur le temps pour réaliser les actions
 * @param nomNuage un tableau contenant les noms des nuages
 * @param nb_pts un pointeur sur le nombre de points du nuage
 * @param nuage un pointeur sur un pointeur sur les coordonnées du nuage
 */

void effectuerDeplacement(t_joueur *equipe1, t_joueur *equipe2, t_tour *gestionTours, 
                          t_case matriceTerrain[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], 
                          SDL_Rect *rectFen, SDL_Renderer * zoneAffichage, 
                          SDL_Texture *texMap, SDL_Texture **texObjets, 
                          TTF_Font *policeMenuHIP, t_texte_cache *cache, 
                          t_dino **dinoActuel, int *timer, 
                          char **nomNuage, int *nb_pts, t_coordonnee **nuage) {



    //Si le dino est là mais que le nuage a été oublié
    if (*nuage == NULL && (*dinoActuel) != NULL) {
         *nuage = nuage_de_points(nb_pts, nomNuage[(*dinoActuel)->id_nuage]);
    }

    // On vérifie si dinoActuel est NULL ou si son état est passé à 0 (mort)
    if (*timer <= 0 || (*dinoActuel) == NULL || (*dinoActuel)->etat == 0) {
        
        // Si le dino est mort, on le retire proprement de la matrice et de l'équipe
        if ((*dinoActuel) != NULL && (*dinoActuel)->etat == 0) {
            printf("Le dinosaure %d est mort (noyade). Suppression...\n", (*dinoActuel)->d);
            supprimer_matrice_dino((*dinoActuel), matriceTerrain);
            supprimerDinoJoueur(equipe1, equipe2, (*dinoActuel)->d);
        }
        tourSuivant(gestionTours, equipe1, equipe2);
        (*dinoActuel) = recupererDinoNumero(equipe1, equipe2, gestionTours->dinoCourant);
        nuageDetruire(nuage); 
        if ((*dinoActuel) != NULL) {
            (*nuage) = nuage_de_points(nb_pts, nomNuage[(*dinoActuel)->id_nuage]);
            (*timer) = TIMER;
            (*dinoActuel)->deplacement->indice_reel = (float)(*dinoActuel)->indice_nuage;
        }
    }

    if ((*dinoActuel) != NULL && *nuage != NULL && (*dinoActuel)->etat != 0) {
        deplacement_dino((*dinoActuel), nuage, nomNuage, 2, nb_pts, matriceTerrain, equipe1, equipe2);
        
        // Vérification immédiate après le mouvement pour éviter un frame d'attente
        if ((*dinoActuel)->etat == 0) {
            *timer = 0; // Force le changement de tour au prochain appel
        }
    }

    if (*timer > 0) (*timer)--;

    afficherJeuSansArmes(equipe1, equipe2, rectFen, zoneAffichage, texMap, texObjets, policeMenuHIP, cache);
    SDL_Delay(10);
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
        float graviteArmes = 0.5f;
        t_tir tir = {0};           /* Pour flèches/balles */

        // Variables pour la bombe 
        t_bombe bombe;
        t_vect vectVitesse;
        int action = 0;
        int nombreRebonds = 0;
        int bombeLancee = 0;

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
        initialiserVitesse(&vectVitesse, VITESSE_X_MAIN, VITESSE_Y_MAIN);
        initialiserMatrice(&matriceTerrain);
        initialiserEquipes(&equipe1, &equipe2, &catalogue, matriceTerrain, zoneAffichage);

        afficherContenuJoueur(equipe1, "equipe1");
        afficherContenuJoueur(equipe2, "equipe2");

        // Variables pour les déplacements
        t_dino *dinoActuel = NULL;
        int timer = TIMER;
        char *nomNuage[2] = {"../img/test1_c.jpg", "../img/test2_c.jpg"};
        int nb_pts;
        t_coordonnee *nuage = NULL;

        SDL_SetRenderDrawColor(zoneAffichage, 40, 40, 40, 255);
        afficherJeuSansArmes(&equipe1, &equipe2, &rectFen, zoneAffichage, texMap, texObjets, policeMenuHIP, cache);

        dinoActuel = recupererDinoNumero(&equipe1, &equipe2, gestionTours.dinoCourant);
        if (dinoActuel != NULL) {
            // On charge le nuage correspondant au premier dino
            nuage = nuage_de_points(&nb_pts, nomNuage[dinoActuel->id_nuage]);
            // On synchronise sa position
            dinoActuel->deplacement->indice_reel = (float)dinoActuel->indice_nuage;
            dinoActuel->deplacement->sens = recupererDinoDirection(&equipe1, &equipe2, dinoActuel->d);
        }
                
        while(enCours && (!finPartie(&equipe1,&equipe2))) {

            action = detecterEvenementsPageJeu(&enCours, &nombreRebonds, &bombeLancee, zoneAffichage, texMap, texObjets, policeMenuHIP, &rectFen, &bombe, 
                &vectVitesse, &tir, &equipe1, &equipe2, gestionTours.dinoCourant, matriceTerrain, cache, catalogue_armes, nomNuage, &nuage, &nb_pts);

            // Les Armes
            if (tir.actif) {
                tireurActuel = recupererDinoNumero(&equipe1, &equipe2, gestionTours.dinoCourant);
                
                // On fait avancer la flèche
                col = mettreAJourVol(&tir, matriceTerrain, graviteArmes, tireurActuel->d);

                afficherJeuAvecArmesTir(&equipe1, &equipe2, &rectFen, zoneAffichage, texMap, texObjets, policeMenuHIP, cache, &tir);
                SDL_Delay(16);

                // Collision ?
                if (col != 0) {
                    if (col >= D1) {
                        appliquerDegats(col, tir.arme_source.degats, &equipe1, &equipe2, matriceTerrain);
                    }
                    
                    // On arrête le tir et on change de tour
                    tir.actif = 0;
                    tourSuivant(&gestionTours, &equipe1, &equipe2);
                    /*printf("  Dino n°%d\n", dinoActuel->d);*/
                    dinoActuel = recupererDinoNumero(&equipe1, &equipe2, gestionTours.dinoCourant);
                    /*printf("  Dino n°%d\n", dinoActuel->d);*/
                    nuageDetruire(&nuage); 
                    if (dinoActuel != NULL) {
                        nuage = nuage_de_points(&nb_pts, nomNuage[dinoActuel->id_nuage]);
                        timer = TIMER;
                        dinoActuel->deplacement->indice_reel = (float)dinoActuel->indice_nuage;
                        dinoActuel->deplacement->sens = recupererDinoDirection(&equipe1, &equipe2, dinoActuel->d);
                    }
                }
            }
            
            // La Bombe
            if (action == 2) {
                lancerBombe(&bombeLancee, &nombreRebonds, &bombe, &vectVitesse, matriceTerrain, &equipe1, &equipe2, &gestionTours, &rectFen, zoneAffichage, texMap, texObjets, policeMenuHIP, cache);
                dinoActuel = recupererDinoNumero(&equipe1, &equipe2, gestionTours.dinoCourant);
                nuageDetruire(&nuage); 
                if (dinoActuel != NULL) {
                    nuage = nuage_de_points(&nb_pts, nomNuage[dinoActuel->id_nuage]);
                    timer = TIMER;
                    dinoActuel->deplacement->indice_reel = (float)dinoActuel->indice_nuage;
                    dinoActuel->deplacement->sens = recupererDinoDirection(&equipe1, &equipe2, dinoActuel->d);
                }
            }
            else if (action == 3) {
                // On rafraîchit l'affichage pour voir les nouveaux PV
                afficherJeuSansArmes(&equipe1, &equipe2, &rectFen, zoneAffichage, texMap, texObjets, policeMenuHIP, cache);
                SDL_Delay(200);
                tourSuivant(&gestionTours, &equipe1, &equipe2);
                dinoActuel = recupererDinoNumero(&equipe1, &equipe2, gestionTours.dinoCourant);
                nuageDetruire(&nuage); 
                if (dinoActuel != NULL) {
                    nuage = nuage_de_points(&nb_pts, nomNuage[dinoActuel->id_nuage]);
                    timer = TIMER;
                    dinoActuel->deplacement->indice_reel = (float)dinoActuel->indice_nuage;
                    dinoActuel->deplacement->sens = recupererDinoDirection(&equipe1, &equipe2, dinoActuel->d);
                }
            
            }
            else if (action == 4) {
                printf("\n------------------action4---------\n");
                tourSuivant(&gestionTours, &equipe1, &equipe2);
                dinoActuel = recupererDinoNumero(&equipe1, &equipe2, gestionTours.dinoCourant);
                nuageDetruire(&nuage); 
                if (dinoActuel != NULL) {
                    nuage = nuage_de_points(&nb_pts, nomNuage[dinoActuel->id_nuage]);
                    timer = TIMER;
                    dinoActuel->deplacement->indice_reel = (float)dinoActuel->indice_nuage;
                    dinoActuel->deplacement->sens = recupererDinoDirection(&equipe1, &equipe2, dinoActuel->d);
                }
            }
            else if (action == 1) {
                afficherJeuSansArmes(&equipe1, &equipe2, &rectFen, zoneAffichage, texMap, texObjets, policeMenuHIP, cache);
            }
            else {
                effectuerDeplacement(&equipe1, &equipe2, &gestionTours, matriceTerrain, &rectFen, zoneAffichage, texMap, texObjets, policeMenuHIP, cache, &dinoActuel, &timer, nomNuage, &nb_pts, &nuage);
            }
        }

        destruireElementsJeu(&equipe1, &equipe2, matriceTerrain, texMap, texObjets, policeMenuHIP, zoneAffichage, fenJeu, nuage, cache);

        if (finPartie(&equipe1, &equipe2)){
            ouvrirFenFinPartie(&gestionTours);
        }

        IMG_Quit();
        TTF_Quit();
        SDL_Quit();
    }
}

