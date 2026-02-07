/**
 * @file collision_decor.c
 * @brief Gestion des collisions sur la matrice.
 */

#include "../lib/collision_decor.h"

/**
 * @brief Vérifie les collisions autour du dinosaure.
 * SUD : 1 (Terre), -1 (Eau). OUEST/EST/NORD : 1 (Terre).
 * @param tab_collision Tableau de 4 entiers (0:SUD, 1:OUEST, 2:EST, 3:NORD).
 * @param dino Structure contenant les données du dinosaure (pos, taille).
 * @param matrice La matrice du terrain chargée en mémoire.
 * @return int Retourne 1 si une collision avec la terre est détectée, 0 sinon.
 */
int collision_decor(int tab_res[4], t_dino dino, int matrice[MAT_H][MAT_L]) {
    int contact = 0;
    int i;

    for(i=0; i<4; i++){
        tab_res[i] = 0;
    }

    int bas = dino.pos.y + dino.hauteur;
    int milieu_x = dino.pos.x + (dino.largeur / 2);

    // Sécurité limites matrice
    if (bas >= MAT_H || milieu_x >= MAT_L || milieu_x < 0){
        return 0;
    }

    // Vérification SUD (Priorité à l'Eau)
    if (matrice[bas][milieu_x] == EAU) {
        tab_res[0] = -1; // Code spécial pour la mort
        contact = 1;
    } else if (matrice[bas][milieu_x] == TERRE) {
        tab_res[0] = 1;
        contact = 1;
    }

    // Vérification Côtés et Haut (Terre uniquement)
    if (matrice[dino.pos.y + (dino.hauteur/2)][dino.pos.x] == TERRE) { tab_res[1] = 1; contact = 1; } // OUEST
    if (matrice[dino.pos.y + (dino.hauteur/2)][dino.pos.x + dino.largeur] == TERRE) { tab_res[2] = 1; contact = 1; } // EST
    if (matrice[dino.pos.y][milieu_x] == TERRE) { tab_res[3] = 1; contact = 1; } // NORD

    return contact;
}
