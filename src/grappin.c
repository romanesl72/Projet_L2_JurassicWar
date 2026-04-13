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


int collision_grappin(t_coordonnee pos, int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN]){ 

    if(pos.y >= 0 && pos.y < HAUTEUR_TERRAIN && pos.x >= 0 && pos.x < LARGEUR_TERRAIN) {
        if(matrice[pos.y][pos.x] == TERRE){
            printf("\n--------TERRE-------\n");
            return 1;
        } 
    }
    return 0;
}



int chute(t_dino **dino, int nb_pts, t_coordonnee *nuage, int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], SDL_Renderer* zoneAffichage, 
    TTF_Font *police, SDL_Texture *texMap, SDL_Texture *texObjets[],
    t_joueur *equipe1, t_joueur *equipe2){
    if(horsNuage( *dino, nb_pts, matrice)){
        printf("\nhors nuage\n");
        while (!noyade( *dino, matrice)){
            supprimer_matrice_dino(*dino, matrice);
            (*dino)->deplacement->v_y += GRAVITE;
            (*dino)->pos.y += (int)(*dino)->deplacement->v_y;
            remplir_matrice_dino(*dino, (*dino)->pos, matrice);
            afficher(zoneAffichage, police, texMap, texObjets, equipe1, equipe2);
            SDL_RenderPresent(zoneAffichage);
        }
        supprimer_matrice_dino(*dino, matrice);
        (*dino)->etat=0;
        afficher(zoneAffichage, police, texMap, texObjets, equipe1, equipe2);
        SDL_RenderPresent(zoneAffichage);
        return 0;
    }
    else{
        while ((*dino)->pos.y<nuage[(*dino)->indice_nuage].y){
            supprimer_matrice_dino(*dino, matrice);
            (*dino)->deplacement->v_y += GRAVITE;
            (*dino)->pos.y += (int)(*dino)->deplacement->v_y;
            remplir_matrice_dino(*dino, (*dino)->pos, matrice);
            afficher(zoneAffichage, police, texMap, texObjets, equipe1, equipe2);
            SDL_RenderPresent(zoneAffichage);
        }
        return 1;
    }
}


void balancier(int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], t_dino **dino, SDL_Renderer* zoneAffichage, const Uint8 *state, 
               TTF_Font *police, SDL_Texture *texMap,
               SDL_Texture *texObjets[], t_joueur *equipe1, 
               t_joueur *equipe2, t_coordonnee *pts_rotation,int *nb_pts, t_coordonnee **nuage, 
               int nb_nuage, char *nomNuage[]) {

    if (pts_rotation == NULL || (*dino) == NULL) return;

    t_coordonnee pivot = *pts_rotation;
    
    double dx = (*dino)->pos.x - pivot.x;
    double dy = pivot.y - (*dino)->pos.y; 
    double L = sqrt(dx*dx + dy*dy);//longueur de la corde
     
    double angle = atan2(dy, dx); 
    double vitesse = 0.0;
    double gravite = 0.15;
    int en_mouvement = 1;
    float force_poussee = 0.002f;
    int ecart=(*nuage)[0].x;

    while (en_mouvement) {
        SDL_PumpEvents();
        if (state[SDL_SCANCODE_SPACE])en_mouvement = 0;
        if (state[SDL_SCANCODE_LEFT])vitesse -= force_poussee;
        if (state[SDL_SCANCODE_RIGHT])vitesse += force_poussee;
         
        // L'accélération dépend du sinus de l'angle
        double acceleration = -(gravite / L) * cos(angle); 
        
        vitesse += acceleration;
        angle += vitesse;

        // Amortissement 
        vitesse *= 0.999; 

        
        supprimer_matrice_dino(*dino, matrice);

        // On transforme les polaires en cartésien
        (*dino)->pos.x = (int)(pivot.x + L * cos(angle));
        (*dino)->pos.y = (int)(pivot.y - L * sin(angle));
        (*dino)->indice_nuage = (int)(pivot.x + L * cos(angle))-ecart;
        remplir_matrice_dino(*dino, (*dino)->pos, matrice);

        if(collision_cote(**dino,matrice)){
            vitesse = -vitesse * 0.5;
            angle += vitesse;
            supprimer_matrice_dino(*dino, matrice);
            (*dino)->pos.x = (int)(pivot.x + L * cos(angle));
            (*dino)->pos.y = (int)(pivot.y - L * sin(angle));
            (*dino)->indice_nuage = (int)(pivot.x + L * cos(angle))-ecart;
            remplir_matrice_dino(*dino, (*dino)->pos, matrice);
        }      

        afficher(zoneAffichage, police, texMap, texObjets, equipe1, equipe2);
        
        // Dessin du câble
        SDL_SetRenderDrawColor(zoneAffichage, 0, 0, 0, 255);
        SDL_RenderDrawLine(zoneAffichage, (*dino)->pos.x + 15, (*dino)->pos.y+HAUTEUR_HIP+15, pivot.x+15, pivot.y+HAUTEUR_HIP);
        
        SDL_RenderPresent(zoneAffichage);
        SDL_Delay(10);
    }
    if(horsNuage(*dino,*nb_pts,matrice))replacementNuage(*dino, nb_pts, nuage,nb_nuage, nomNuage,(*dino)->deplacement->sens);
    chute(dino, *nb_pts, *nuage, matrice, zoneAffichage, police,texMap,texObjets,equipe1,equipe2);
    ((*dino)->deplacement->sens) *= -1;
    supprimer_matrice_dino(*dino, matrice);
    (*dino)->pos=(*nuage)[(*dino)->indice_nuage];
    remplir_matrice_dino(*dino, (*dino)->pos, matrice);
    printf("\n---------replacement----------\n");
}

float choixAngleLancer(t_dino *dino, SDL_Renderer* zoneAffichage,  const Uint8 *state, TTF_Font *police, SDL_Texture *texMap, SDL_Texture *texObjets[],
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
        
        
        afficher(zoneAffichage, police, texMap, texObjets, &equipe1, &equipe2);
        x=(float)dino->pos.x +LONGUEUR*cos(degres*RADIANS);
        y=(float)dino->pos.y -LONGUEUR*sin(degres*RADIANS);
        
        SDL_SetRenderDrawColor(zoneAffichage, 0, 0, 0, 255);
        SDL_RenderDrawLine(zoneAffichage, dino->pos.x+15, dino->pos.y+HAUTEUR_HIP+15, (int)x+15, (int)y+HAUTEUR_HIP+15);
        SDL_RenderPresent(zoneAffichage);
    }

    return degres*RADIANS;
}

int lancer(t_coordonnee_calcul *pos_precise, float angle_rad, int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], int *collision_detectee, int distance_parcourue) {
    
    // Calcul précis en flottant
    pos_precise->x += 5.0f * cos(angle_rad);
    pos_precise->y -= 5.0f * sin(angle_rad);
    
    // Conversion en entier uniquement pour la vérification de collision et le stockage
    t_coordonnee pos_entiere = {(int)pos_precise->x, (int)pos_precise->y};
    printf("case:%d\n",matrice[pos_entiere.y][pos_entiere.x]);
    if((pos_entiere.x<0)||(pos_entiere.x>=LARGEUR_TERRAIN)||(pos_entiere.y<0)){
        detruireFile();
        return 0;
    }
    if (distance_parcourue > 35) {
        if (collision_grappin(pos_entiere, matrice)) {
            printf("-----------------colision-----------");
            *collision_detectee = 1;
            return 0; 
        }
    }

    ajouter(pos_entiere);
    return 1; 
}


int rappel(int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], t_dino **dino, const Uint8 *state, int distance_parcourue, 
     SDL_Renderer* zoneAffichage, int *nb_pts, t_coordonnee **nuage, int nb_nuage, char *nomNuage[]) {
    int ecart;
    t_coordonnee pos_suivante;
    printf("\n----------rappel---------------\ndistance=%d\n",distance_parcourue);
    if (filevide() && (distance_parcourue < 35)){
        printf("\nfilevide\n");
        return 1;
    }  

    if (state[SDL_SCANCODE_RETURN]) {
        return 3; 
    }

    retirer(&pos_suivante);
    afficherFile(zoneAffichage);
    SDL_RenderPresent(zoneAffichage);
    SDL_Delay(16);
    
    if (filevide()  && (distance_parcourue > 35)) {
        printf("\ncollision\n");
        if(replacementNuage(*dino, nb_pts, nuage,nb_nuage, nomNuage,(*dino)->deplacement->sens)){
            ((*dino)->deplacement->sens) *= -1;
            supprimer_matrice_dino(*dino, matrice);
            (*dino)->pos=(*nuage)[(*dino)->indice_nuage];
            remplir_matrice_dino(*dino, (*dino)->pos, matrice);
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
    if(collision_decor((*dino)->deplacement->tab_res,**dino,matrice)){
        
        supprimer_matrice_dino(*dino, matrice);
        (*dino)->pos=(*nuage)[(*dino)->indice_nuage];
        remplir_matrice_dino(*dino, (*dino)->pos, matrice);
        return 1;
    }
    (*dino)->indice_nuage += ecart;
    printf("indice nuage=%d\n",(*dino)->indice_nuage);

    return 0; 
}



int grappin(int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], SDL_Renderer* zoneAffichage, t_dino **dino, 
           const Uint8 *state, SDL_Texture *texMap, TTF_Font *police, SDL_Texture *texObjets[],
           t_joueur *equipe1, t_joueur *equipe2,int *nb_pts, t_coordonnee **nuage, 
           int nb_nuage, char *nomNuage[]){
    
    initfile(); // Vide la file pour un nouveau tir
    
    float angle = choixAngleLancer(*dino, zoneAffichage, state, police, texMap, texObjets, *equipe1, *equipe2);
    
    int collision_detectee = 0;
    int etat_fini = 0;
    int distance_lancer = 0;

    // Utilisation de coordonnées flottantes pour éviter la dérive de trajectoire
    t_coordonnee_calcul pos_f;
    pos_f.x = (float)(*dino)->pos.x + 15.0f; // Point de départ centré (30/2)
    pos_f.y = (float)(*dino)->pos.y + 15.0f; 

    // On avance tant qu'il n'y a pas de collision
    while (lancer(&pos_f, angle, matrice, &collision_detectee, distance_lancer)) {
        distance_lancer += 5; // Vitesse de progression du grappin
        afficherFile(zoneAffichage);    
        SDL_RenderPresent(zoneAffichage); 
        SDL_Delay(10);
    }
    
    // On n'entre ici que si le grappin a accroché la TERRE
    if (collision_detectee) {
        int dist_rappel = 0;

        while (!etat_fini) {
            SDL_PumpEvents(); // Pour détecter l'arrêt manuel via state
            
            // On retire temporairement le dino de la matrice pour le mouvement
            
            supprimer_matrice_dino(*dino, matrice);

            /* rappel retourne :
               0 : continue
               1 : fini
               2 : collision colline (doit tomber) 
               3 : balancier (entrer)
            */

            etat_fini = rappel(matrice, dino, state, dist_rappel, zoneAffichage, nb_pts, nuage, nb_nuage, nomNuage);
            
            // On replace le dino dans la matrice à sa nouvelle position
            remplir_matrice_dino(*dino, (*dino)->pos, matrice);
            
            dist_rappel += 5;

            // Mise à jour graphique complète pour voir l'animation
            afficher(zoneAffichage, police, texMap, texObjets, equipe1, equipe2);
            SDL_RenderPresent(zoneAffichage);
            SDL_Delay(16);
            
            // Gestion de la chute si le dino percute une paroi en montant
            printf("etat=%d",etat_fini);
            if (etat_fini == 2) {
                chute(dino, *nb_pts, *nuage, matrice,zoneAffichage, police, texMap, texObjets,
                    equipe1, equipe2);
                etat_fini = 1; // Sortie de la boucle de rappel
                if((*dino)->etat==0){
                    supprimerDinoJoueur(equipe1, equipe2, (*dino)->d);
                    *dino = NULL;
                    return 0;
                }
            }
            else if(etat_fini == 3) {
                t_coordonnee *res = lireQueue();
                if (res != NULL) {
                    t_coordonnee pivot_fixe = *res; // COPIE DES VALEURS
                    detruireFile(); // On peut maintenant vider la file sans risque
                    
                    balancier(matrice, dino, zoneAffichage, state, police, texMap,
                        texObjets, equipe1, equipe2, &pivot_fixe,
                        nb_pts,nuage,nb_nuage,nomNuage);
                    if((*dino)->etat==0){
                        supprimerDinoJoueur(equipe1, equipe2, (*dino)->d);
                        *dino = NULL;
                        return 0;
                    }
                }
            }
        }
    }
    
    return 1;
}
 
