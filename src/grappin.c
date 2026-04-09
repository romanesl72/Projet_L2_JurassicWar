#define STB_IMAGE_IMPLEMENTATION
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL_ttf.h>

#include "../lib/deplacement.h"
#include "../lib/fonctionsVerification.h"
#include "../lib/fonctionsAffichage.h"
#include "../lib/chargerMatrice.h"
#include "../lib/collision_decor.h"
#include "../lib/placer_dinos.h"
#include "../lib/tda_file.h"
#include "../lib/grappin.h"
#include "../lib/types.h"
#include "../lib/fonctionsStructJoueur.h"

/** 
 * @file grappin.h
 * @brief Permet de lancer un grappin pour faciliter les déplacements
 * @author Solène Orieux
 * @date 3/04/2026
 * @version 1.0
 */


/**
 * @fn int collision_grappin(t_coordonnee pos, int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN]);
 * @author Solène Orieux
 * @date 3/04/2026
 * @brief regarde si le grappin accroche
 * @param pos coordonnée du bout du grappin
 * @param matrice représentation du terrain sous forme de matrice
 */

int collision_grappin(t_coordonnee pos, int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN]){ 

    if(pos.y >= 0 && pos.y < HAUTEUR_TERRAIN && pos.x >= 0 && pos.x < LARGEUR_TERRAIN) {
        if(matrice[pos.y][pos.x] == TERRE){
            printf("\n--------TERRE-------\n");
            return 1;
        } 
    }
    return 0;
}

/**
 * @fn int chute(t_dino **dino, int nb_pts, t_coordonnee *nuage, int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], SDL_Renderer* zoneAffichage, 
    TTF_Font *police, SDL_Texture *texMap, SDL_Texture *texDinos[], SDL_Texture *texObjets[], char *nomsObjets[],
    t_joueur *equipe1, t_joueur *equipe2);
 * @author Solène Orieux
 * @date 07/04/2026
 * @brief Le dino chute lorsqu'il percute une colinne
 * @param dino pointeur de pointeur sur un dino
 * @param nb_pts nombre de points dans le nuage
 * @param nuage pointeur sur le nuage de points
 * @param matrice représentation du terrain sous forme de matrice
 * @param zoneAffichage pointeur sur la zone d'affichage
 * @param police un pointeur sur la police du jeu
 * @param texMap pointeur sur l'image de la map
 * @param texDino un tableau de pointeur sur les images représentant le dinosaure
 * @param texObjets un tableau de pointeur sur les images des différants objets
 * @param nomObjets un tableau de pointeur sur les noms des images des différants objets
 * @param equipe1 pointeur sur la structure correspondant aux dinosaures du joueur 1
 * @param equipe2 pointeur sur la structure correspondant aux dinosaures du joueur 2
 */

int chute(t_dino **dino, int nb_pts, t_coordonnee *nuage, int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], SDL_Renderer* zoneAffichage, 
    TTF_Font *police, SDL_Texture *texMap, SDL_Texture *texDinos[], SDL_Texture *texObjets[], char *nomsObjets[],
    t_joueur *equipe1, t_joueur *equipe2){
    if(horsNuage( *dino, nb_pts, matrice)){
        printf("\nhors nuage\n");
        while (!noyade( *dino, matrice)){
            supprimer_matrice_dino(*dino, matrice);
            (*dino)->deplacement->v_y += GRAVITE;
            (*dino)->pos.y += (int)(*dino)->deplacement->v_y;
            remplir_matrice_dino(*dino, (*dino)->pos, matrice);
            afficher(zoneAffichage, police, texMap, texDinos, texObjets, nomsObjets, *equipe1, *equipe2);
            SDL_RenderPresent(zoneAffichage);
        }
        supprimer_matrice_dino(*dino, matrice);
        supprimerDinoJoueur(equipe1, equipe2, (*dino)->d);
        *dino = NULL;
        printf("tout va bien \n");
        afficher(zoneAffichage, police, texMap, texDinos, texObjets, nomsObjets, *equipe1, *equipe2);
        printf("oui \n");
        SDL_RenderPresent(zoneAffichage);
        return 0;
    }
    else{
        while ((*dino)->pos.y<nuage[(*dino)->indice_nuage].y){
            supprimer_matrice_dino(*dino, matrice);
            (*dino)->deplacement->v_y += GRAVITE;
            (*dino)->pos.y += (int)(*dino)->deplacement->v_y;
            remplir_matrice_dino(*dino, (*dino)->pos, matrice);
            afficher(zoneAffichage, police, texMap, texDinos, texObjets, nomsObjets, *equipe1, *equipe2);
            SDL_RenderPresent(zoneAffichage);
        }
        return 1;
    }
}

/**
 * @fn void balancier(int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], t_dino *dino, SDL_Renderer* zoneAffichage, 
               const Uint8 *state, TTF_Font *police, SDL_Texture *texMap, 
               SDL_Texture *texDinos[], SDL_Texture *texObjets[], char *nomsObjets[], 
               t_joueur *equipe1, t_joueur *equipe2, t_coordonnee *pts_rotation);
 * @author Solène Orieux
 * @date 07/04/2026
 * @brief on balance le dino pour qu'il se positionne sur le dessu de la colline
 * @param matrice représentation du terrain sous forme de matrice
 * @param dino pointeur de pointeur sur un dino
 * @param zoneAffichage pointeur sur la zone d'affichage
 * @param state pointeur sur le détecteur de touche du clavier
 * @param police un pointeur sur la police du jeu
 * @param texMap pointeur sur l'image de la map
 * @param texDino un tableau de pointeur sur les images représentant le dinosaure
 * @param texObjets un tableau de pointeur sur les images des différants objets
 * @param nomObjets un tableau de pointeur sur les noms des images des différants objets
 * @param equipe1 pointeur sur la structure correspondant aux dinosaures du joueur 1
 * @param equipe2 pointeur sur la structure correspondant aux dinosaures du joueur 2
 * @param pts_rotation pointeur sur la coordonnée du points de rotation du grappin
 */
void balancier(int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], t_dino *dino, SDL_Renderer* zoneAffichage, const Uint8 *state, 
               TTF_Font *police, SDL_Texture *texMap, SDL_Texture *texDinos[], 
               SDL_Texture *texObjets[], char *nomsObjets[], t_joueur *equipe1, 
               t_joueur *equipe2, t_coordonnee *pts_rotation) {

    // 1. SÉCURITÉ : Si le point de rotation est invalide, on sort pour éviter le Segfault
    if (pts_rotation == NULL || dino == NULL) return;

    // Sauvegarde locale du pivot pour ne plus dépendre du pointeur de la file
    t_coordonnee pivot = *pts_rotation;

    // 2. INITIALISATION DES PARAMÈTRES PHYSIQUES
    // Calcul de la longueur L (distance euclidienne)
    float dx = (float)(dino->pos.x - pivot.x);
    float dy = (float)(dino->pos.y - pivot.y);
    float L = sqrt(dx * dx + dy * dy);

    // Angle initial (en radians)
    float angle = atan2(dx, dy);
    
    float vitesse_angulaire = 0.0f;
    float acceleration_angulaire = 0.0f;
    float gravite = 0.4f;      // Force de la pesanteur
    float amortissement = 0.995f; // Simulation légère du frottement de l'air
    int en_mouvement = 1;

    while (en_mouvement) {
        SDL_PumpEvents();

        // 3. PHYSIQUE DU PENDULE
        // Formule : accélération = -(g/L) * sin(theta)
        acceleration_angulaire = -(gravite / L) * sin(angle);
        vitesse_angulaire += acceleration_angulaire;
        vitesse_angulaire *= amortissement; // On perd un peu d'énergie à chaque frame
        angle += vitesse_angulaire;

        // 4. GESTION DU REBOND ET DE LA PROPULSION (MUR)
        // On vérifie la collision à la position actuelle
        if (collision_grappin(dino->pos, matrice)) {
            // Inversion de la direction + Boost de 20% (Propulsion)
            vitesse_angulaire = -vitesse_angulaire * 1.2f;
            
            // On décale légèrement l'angle pour sortir de la collision et éviter de rester bloqué
            angle += vitesse_angulaire; 
        }

        // 5. SORTIE : Le joueur lâche le grappin avec ESPACE ou ENTREE
        if (state[SDL_SCANCODE_SPACE] || state[SDL_SCANCODE_RETURN]) {
            en_mouvement = 0;
        }

        // 6. MISE À JOUR DES COORDONNÉES (Trigonométrie)
        supprimer_matrice_dino(dino, matrice);
        
        int nouvelle_x = pivot.x + (int)(L * sin(angle));
        int nouvelle_y = pivot.y + (int)(L * cos(angle));

        // SÉCURITÉ BORNES : Empêche de sortir de la matrice (cause de Segfault)
        if (nouvelle_x < 0) nouvelle_x = 0;
        if (nouvelle_x >= LARGEUR_TERRAIN - 30) nouvelle_x = LARGEUR_TERRAIN - 31;
        if (nouvelle_y < 0) nouvelle_y = 0;
        if (nouvelle_y >= HAUTEUR_TERRAIN - 30) nouvelle_y = HAUTEUR_TERRAIN - 31;

        dino->pos.x = nouvelle_x;
        dino->pos.y = nouvelle_y;

        remplir_matrice_dino(dino, dino->pos, matrice);

        // 7. RENDU GRAPHIQUE
        afficher(zoneAffichage, police, texMap, texDinos, texObjets, nomsObjets, *equipe1, *equipe2);
        
        // Dessin du fil du grappin (en blanc)
        SDL_SetRenderDrawColor(zoneAffichage, 255, 255, 255, 255);
        SDL_RenderDrawLine(zoneAffichage, pivot.x + 15, pivot.y + 15, 
                           dino->pos.x + 15, dino->pos.y + 15);
        
        SDL_RenderPresent(zoneAffichage);
        SDL_Delay(16); // ~60 FPS pour une physique fluide
    }
}
               
/**
 * @fn float choixAngleLancer(t_dino *dino, SDL_Renderer* zoneAffichage,  const Uint8 *state, TTF_Font *police, SDL_Texture *texMap,
     SDL_Texture *texDinos[], SDL_Texture *texObjets[], char *nomsObjets[],
     t_joueur equipe1, t_joueur equipe2);
 * @author Solène Orieux
 * @date 3/04/2026
 * @brief on choisit l'angle du lancers du grappin
 * @param dino pointeur de pointeur sur un dino
 * @param zoneAffichage pointeur sur la zone d'affichage
 * @param state pointeur sur le détecteur de touche du clavier
 * @param police un pointeur sur la police du jeu
 * @param texMap pointeur sur l'image de la map
 * @param texDino un tableau de pointeur sur les images représentant le dinosaure
 * @param texObjets un tableau de pointeur sur les images des différants objets
 * @param nomObjets un tableau de pointeur sur les noms des images des différants objets
 * @param equipe1 structure correspondant aux dinosaures du joueur 1
 * @param equipe2 structure correspondant aux dinosaures du joueur 2
 */
float choixAngleLancer(t_dino *dino, SDL_Renderer* zoneAffichage,  const Uint8 *state, TTF_Font *police, SDL_Texture *texMap,
     SDL_Texture *texDinos[], SDL_Texture *texObjets[], char *nomsObjets[],
     t_joueur equipe1, t_joueur equipe2){

    float degres=-1;
    float x=(double)dino->pos.x, y=(double)dino->pos.y;
    int valider = 0;

    while (!valider) {
        SDL_PumpEvents(); // Actualise l'état du clavier
        
        if (state[SDL_SCANCODE_LEFT]) degres += 0.5f;
        if (state[SDL_SCANCODE_RIGHT]) degres -= 0.5f;
        if (state[SDL_SCANCODE_SPACE]) valider = 1;

        // Limite entre 0 et 180°
        if (degres > 360) degres = 0;
        if (degres < 0) degres = 360;

        if (degres>=90 && degres<=270)
        {
            dino->deplacement->sens=-1;
        }else dino->deplacement->sens=1;
        
        
        afficher(zoneAffichage, police, texMap, texDinos, texObjets, nomsObjets, equipe1, equipe2);
        
        x=(float)dino->pos.x +LONGUEUR*cos(degres*RADIANS);
        y=(float)dino->pos.y -LONGUEUR*sin(degres*RADIANS);
        
        SDL_SetRenderDrawColor(zoneAffichage, 0, 0, 0, 255);
        SDL_RenderDrawLine(zoneAffichage, dino->pos.x+15, dino->pos.y+HAUTEUR_HIP+15, (int)x+15, (int)y+HAUTEUR_HIP+15);
        SDL_RenderPresent(zoneAffichage);
    }

    return degres*RADIANS;
}


/**
 * @fn int lancer(t_coordonnee_calcul *pos_precise, float angle, int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], int *collision, int distance_parcourue);
 * @author Solène Orieux
 * @date 3/04/2026
 * @brief on lance le grappin
 * @param pos_precise pointeur sur la dernière position ajouté dans la file
 * @param angle angle choisi pour lancer le grappin
 * @param matrice représentation du terrain sous forme de matrice
 * @param collision pointeur sur une variable booléenne qui permet de savoir si on à touché une nouvelle colline
 * @param distance_parcourue On s'assure que le grappin ne va pas détecter une colision avec l'emplacement initial
 */
int lancer(t_coordonnee_calcul *pos_precise, float angle_rad, int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], int *collision_detectee, int distance_parcourue) {
    
    // Calcul précis en flottant
    pos_precise->x += 5.0f * cos(angle_rad);
    pos_precise->y -= 5.0f * sin(angle_rad);
    
    // Conversion en entier uniquement pour la vérification de collision et le stockage
    t_coordonnee pos_entiere = {(int)pos_precise->x, (int)pos_precise->y};

    if((pos_entiere.x<0)||(pos_entiere.x>=LARGEUR_FEN)||(pos_entiere.y<HAUTEUR_HIP)){
        detruireFile();
        return 0;
    }
    if (distance_parcourue > 35) {
        if (collision_grappin(pos_entiere, matrice)) {
            *collision_detectee = 1;
            return 0; 
        }
    }

    ajouter(pos_entiere); 
    return 1; 
}

/**
 * @fn int rappel(int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], t_dino **dino, const Uint8 *state, int distance_parcourue, 
     SDL_Renderer* zoneAffichage, int *nb_pts, t_coordonnee **nuage, int nb_nuage, char *nomNuage[]);
 * @author Solène Orieux
 * @date 3/04/2026
 * @brief on monte le dino en rappel
 * @param matrice représentation du terrain sous forme de matrice
 * @param dino pointeur de pointeur sur un dino
 * @param state pointeur sur le détecteur de touche du clavier
 * @param distance_parcourue On s'assure que le grappin ne va pas détecter une colision avec l'emplacement initial
 * @param zoneAffichage pointeur sur la zone d'affichage
 * @param nb_pts pointeur sur le nombre de points dans le nuage
 * @param nuage pointeur de pointeur sur le nuage de points
 * @param nb_nuage nombre de nuage présent dans la map
 * @param nomNuage liste des différents noms d'image permettant de créer le nuage
 */
int rappel(int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], t_dino **dino, const Uint8 *state, int distance_parcourue, 
     SDL_Renderer* zoneAffichage, int *nb_pts, t_coordonnee **nuage, int nb_nuage, char *nomNuage[]) {
    int ecart;
    t_coordonnee pos_suivante;
    printf("\n----------rappel---------------\ndistance=%d\n",distance_parcourue);
    if (filevide() && (distance_parcourue < 35)){
        printf("\nfilevide\n");
        return 1;
    }  

    // 1. ARRÊT MANUEL
    // Crucial : il faut vérifier l'état des touches à chaque tour
    if (state[SDL_SCANCODE_SPACE] || state[SDL_SCANCODE_RETURN]) {
        return 1; 
    }

    retirer(&pos_suivante);
    afficherFile(zoneAffichage);
    

    // 2. COLLISION (On utilise (*dino) pour accéder à la structure)
    if (filevide()  && (distance_parcourue > 35)) {
        printf("\ncollision\n");
        if(replacementNuage(*dino, nb_pts, nuage,nb_nuage, nomNuage,(*dino)->deplacement->sens)){
            ((*dino)->deplacement->sens) *= -1;
            (*dino)->pos=(*nuage)[(*dino)->indice_nuage];
            printf("\n---------replacement----------\n");
            return 1;
        }
        return 2; 
    }

    // 3. MOUVEMENT (Utilise (*dino) partout)
    
    ecart = pos_suivante.x - (*dino)->pos.x;
    supprimer_matrice_dino(*dino, matrice);
    (*dino)->pos = pos_suivante;
    remplir_matrice_dino(*dino, (*dino)->pos, matrice);
    (*dino)->indice_nuage += ecart;
    printf("indice nuage=%d\n",(*dino)->indice_nuage);

    return 0; 
}


/**
 * @fn int grappin(int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], SDL_Renderer* zoneAffichage, t_dino **dino, 
           const Uint8 *state, SDL_Texture *texMap, TTF_Font *police,
           SDL_Texture *texDinos[], SDL_Texture *texObjets[], char *nomsObjets[],
           t_joueur *equipe1, t_joueur *equipe2,int *nb_pts, t_coordonnee **nuage, 
           int nb_nuage, char *nomNuage[]);
 * @author Solène Orieux
 * @date 3/04/2026
 * @brief on utilise le grappin
 * @param matrice représentation du terrain sous forme de matrice
 * @param zoneAffichage pointeur sur la zone d'affichage
 * @param dino pointeur de pointeur sur un dino
 * @param state pointeur sur le détecteur de touche du clavier
 * @param texMap pointeur sur l'image de la map
 * @param police un pointeur sur la police du jeu
 * @param texDino un tableau de pointeur sur les images représentant le dinosaure
 * @param texObjets un tableau de pointeur sur les images des différants objets
 * @param nomObjets un tableau de pointeur sur les noms des images des différants objets
 * @param equipe1 structure correspondant aux dinosaures du joueur 1
 * @param equipe2 structure correspondant aux dinosaures du joueur 2
 */
int grappin(int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], SDL_Renderer* zoneAffichage, t_dino **dino, 
           const Uint8 *state, SDL_Texture *texMap, TTF_Font *police,
           SDL_Texture *texDinos[], SDL_Texture *texObjets[], char *nomsObjets[],
           t_joueur *equipe1, t_joueur *equipe2,int *nb_pts, t_coordonnee **nuage, 
           int nb_nuage, char *nomNuage[]){
    
    initfile(); // Vide la file pour un nouveau tir
    
    // 1. PHASE DE VISÉE
    // On récupère l'angle en radians. La fonction gère l'affichage du trait vert.
    float angle = choixAngleLancer(*dino, zoneAffichage, state, police, texMap, texDinos, texObjets, nomsObjets, *equipe1, *equipe2);
    
    int collision_detectee = 0;
    int etat_fini = 0;
    int distance_lancer = 0;

    // Utilisation de coordonnées flottantes pour éviter la dérive de trajectoire
    t_coordonnee_calcul pos_f;
    pos_f.x = (float)(*dino)->pos.x + 15.0f; // Point de départ centré (30/2)
    pos_f.y = (float)(*dino)->pos.y + 15.0f; 

    // 2. PHASE DE LANCER (Extension du fil)
    // On avance tant qu'il n'y a pas de collision (après le décollage de 35px)
    while (lancer(&pos_f, angle, matrice, &collision_detectee, distance_lancer)) {
        distance_lancer += 5; // Vitesse de progression du grappin
        afficherFile(zoneAffichage);
    }
    
    // 3. PHASE DE RAPPEL (Le dinosaure remonte le fil)
    // On n'entre ici que si le grappin a accroché la TERRE
    if (collision_detectee) {
        int dist_rappel = 0;

        while (!etat_fini) {
            SDL_PumpEvents(); // Pour détecter l'arrêt manuel via state
            
            // On retire temporairement le dino de la matrice pour le mouvement
            supprimer_matrice_dino(*dino, matrice);
            
            /* rappel retourne :
               0 : continue
               1 : fini (fin de file ou arrêt manuel avec Entrée/Espace)
               2 : collision colline (doit tomber) */
            etat_fini = rappel(matrice, dino, state, dist_rappel, zoneAffichage, nb_pts, nuage, nb_nuage, nomNuage);
            
            // On replace le dino dans la matrice à sa nouvelle position
            remplir_matrice_dino(*dino, (*dino)->pos, matrice);
            
            dist_rappel += 5;

            // Mise à jour graphique complète pour voir l'animation
            afficher(zoneAffichage, police, texMap, texDinos, texObjets, nomsObjets, *equipe1, *equipe2);
            SDL_RenderPresent(zoneAffichage);
            SDL_Delay(16);
            
            // Gestion de la chute si le dino percute une paroi en montant
            printf("etat=%d",etat_fini);
            if (etat_fini == 2) {
                printf("test\n");
                chute(dino, *nb_pts, *nuage, matrice,zoneAffichage, police, texMap,texDinos, texObjets,nomsObjets,
                    equipe1, equipe2);
                etat_fini = 1; // Sortie de la boucle de rappel
            }
            else if(etat_fini==1){
                t_coordonnee *pts_rotation=lireTete();
                balancier(matrice,*dino,zoneAffichage,state,police,texMap,texDinos,texObjets,nomsObjets,equipe1,equipe2,pts_rotation);
            }
        }
    }
    
    return 1;
}
 
