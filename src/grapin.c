#define STB_IMAGE_IMPLEMENTATION
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL_ttf.h>

#include "../lib/deplacement.h"
#include "../lib/fonctionsVerification.h"
#include "../lib/fonctionsAffichage.h"
#include "../lib/chargerMatrice.h"
#include "../lib/placer_dinos.h"
#include "../lib/tda_file.h"
#include "../lib/grapin.h"
#include "../lib/types.h"


int collision_grapin(t_coordonnee pos, int matrice[MAT_H][MAT_L]){ 

    if(pos.y >= 0 && pos.y < MAT_H && pos.x >= 0 && pos.x < MAT_L) {
        if(matrice[pos.y][pos.x] == TERRE) return 1;
    }
    return 0;
}

int chute(t_dino *dino, t_coordonnee *nuage, int nb_pts, int matrice[MAT_H][MAT_L]){
    if(horsNuage(t_dino *dino, t_coordonnee *nuage, int *nb_pts, int matrice[MAT_H][MAT_L])){

    }
}

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
        if (degres > 180) degres = 180;
        if (degres < 0) degres = 0;

        
        afficher(zoneAffichage, police, texMap, texDinos, texObjets, nomsObjets, equipe1, equipe2);
        
        x=(float)dino->pos.x +LONGUEUR*cos(degres*RADIANS);
        y=(float)dino->pos.y -LONGUEUR*sin(degres*RADIANS);
        
        SDL_SetRenderDrawColor(zoneAffichage, 0, 0, 0, 255);
        SDL_RenderDrawLine(zoneAffichage, dino->pos.x, dino->pos.y+HAUTEUR_HIP, (int)x+HAUTEUR_HIP, (int)y);
        SDL_RenderPresent(zoneAffichage);
    }

    return degres*RADIANS;
}

// Utilise t_coordonnee_calcul pour ne pas perdre de précision
int lancer(t_coordonnee_calcul *pos_precise, float angle_rad, int matrice[MAT_H][MAT_L], int *collision_detectee, int distance_parcourue) {
    
    // Calcul précis en flottant
    pos_precise->x += 5.0f * cos(angle_rad);
    pos_precise->y -= 5.0f * sin(angle_rad);

    // Conversion en entier uniquement pour la vérification de collision et le stockage
    t_coordonnee pos_entiere = {(int)pos_precise->x, (int)pos_precise->y};

    if (distance_parcourue > 35) {
        if (collision_grapin(pos_entiere, matrice)) {
            *collision_detectee = 1;
            return 0; 
        }
    }

    ajouter(pos_entiere); 
    return 1; 
}

int rappel(int matrice[MAT_H][MAT_L], t_dino **dino, int *collision, const Uint8 *state, int distance_parcourue, SDL_Renderer* zoneAffichage) {
    int ecart;
    t_coordonnee pos_suivante;

    if (filevide()) return 1; 

    // 1. ARRÊT MANUEL
    // Crucial : il faut vérifier l'état des touches à chaque tour
    if (state[SDL_SCANCODE_SPACE] || state[SDL_SCANCODE_RETURN]) {
        return 1; 
    }

    retirer(&pos_suivante);
    afficherFile(zoneAffichage);

    // 2. COLLISION (On utilise (*dino) pour accéder à la structure)
    if (collision_grapin(pos_suivante, matrice) && distance_parcourue > 35) {
        *collision = 1;
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
 * @fn int grapin(int matrice[MAT_H][MAT_L], SDL_Renderer* zoneAffichage, t_dino **dino, 
 * const Uint8 *state, SDL_Texture *texMap, TTF_Font *police,
 * SDL_Texture *texDinos[], SDL_Texture *texObjets[], char *nomsObjets[],
 * t_joueur equipe1, t_joueur equipe2);
 * @brief Gère l'intégralité de la séquence du grappin : visée, lancer et rappel.
 */
int grapin(int matrice[MAT_H][MAT_L], SDL_Renderer* zoneAffichage, t_dino **dino, 
           const Uint8 *state, SDL_Texture *texMap, TTF_Font *police,
           SDL_Texture *texDinos[], SDL_Texture *texObjets[], char *nomsObjets[],
           t_joueur equipe1, t_joueur equipe2) {
    
    initfile(); // Vide la file pour un nouveau tir
    
    // 1. PHASE DE VISÉE
    // On récupère l'angle en radians. La fonction gère l'affichage du trait vert.
    float angle = choixAngleLancer(*dino, zoneAffichage, state, police, texMap, texDinos, texObjets, nomsObjets, equipe1, equipe2);
    
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
        int col_rappel = 0; // Pour détecter une collision pendant la remontée

        while (!etat_fini) {
            SDL_PumpEvents(); // Pour détecter l'arrêt manuel via state
            
            // On retire temporairement le dino de la matrice pour le mouvement
            supprimer_matrice_dino(*dino, matrice);
            
            /* rappel retourne :
               0 : continue
               1 : fini (fin de file ou arrêt manuel avec Entrée/Espace)
               2 : collision colline (doit tomber) */
            etat_fini = rappel(matrice, dino, &col_rappel, state, dist_rappel, zoneAffichage); 
            
            // On replace le dino dans la matrice à sa nouvelle position
            remplir_matrice_dino(*dino, (*dino)->pos, matrice);
            
            dist_rappel += 5;

            // Mise à jour graphique complète pour voir l'animation
            afficher(zoneAffichage, police, texMap, texDinos, texObjets, nomsObjets, equipe1, equipe2);
            SDL_RenderPresent(zoneAffichage);
            SDL_Delay(16);
            
            // Gestion de la chute si le dino percute une paroi en montant
            if (etat_fini == 2) {
                (*dino)->deplacement->tomber = 1; // Active la gravité
                etat_fini = 1; // Sortie de la boucle de rappel
            }
        }
    }
    
    return 1;
}
 
