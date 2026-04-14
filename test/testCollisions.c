#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../lib/types.h"
#include "../lib/collision_decor.h"

/** 
 * @file testCollisions.c
 * @brief Fonctions de tests sur les collisions avec le dinosaure
 * @author Romane Saint_Léger
 * @date Crée le 07/02/2026
 * @version 1.3
 */

 /** 
 * @fn test_placement_multi_zones();
 * @brief Corps d'une fonction de test sur les placements des dinosaures
 * @author Romane Saint_Léger
 * @date Crée le 07/02/2026
 * @version 1.3
 */

void test_placement_multi_zones();

/** 
 * @fn test_collision_eau();
 * @brief Corps d'une fonction de test sur les collisions du dino avec l'eau
 * @author Romane Saint_Léger
 * @date Crée le 07/02/2026
 * @version 1.3
 */

void test_collision_eau() {
    printf("--- Test Collision Eau ---\n");
    int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN];
    t_dino dino;
    dino.d = D1;
    dino.etat = 1;
    dino.pv = 100;
    dino.pos.x = 20;
    dino.pos.y = 20;
    dino.largeur = 2;
    dino.hauteur = 2;
    int res[4];

    // On vide la matrice et on place de l'eau au SUD
    for(int i=0; i<HAUTEUR_TERRAIN; i++) for(int j=0; j<LARGEUR_TERRAIN; j++){
        matrice[i][j] = 0;
    }
    matrice[22][21] = EAU; 

    collision_decor(res, dino, matrice);
    if (res[0] == -1) {
        printf("Succes : Eau detectee au SUD. Le dino va etre supprime.\n");
    } else {
        printf("Echec : L'eau n'a pas ete detectee (res[0] = %d).\n", res[0]);
    }
}

/** 
 * @fn test_collision_sol();
 * @brief Corps d'une fonction de test sur les collisions du dino avec le sol
 * @author Romane Saint_Léger
 * @date Crée le 07/02/2026
 * @version 1.3
 */

void test_collision_sol() {
    printf("\n--- Test Collision Sol (Verticale) ---\n");
    // Dino posé sur le sol (y=20, hauteur=2, donc pieds à y=22)
    int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN];
    t_dino dino;
    dino.d = D1;
    dino.etat = 1;
    dino.pv = 100;
    dino.pos.x = 20;
    dino.pos.y = 20;
    dino.largeur = 2;
    dino.hauteur = 2;
    int res[4];

    // On place de la TERRE juste sous ses pieds
    matrice[22][21] = TERRE; 

    collision_decor(res, dino, matrice);
    
    // res[0] doit être égal à 1 (collision détectée au SUD)
    if (res[0] == 1) {
        printf("Succes : Sol detecte au SUD (1). Le dino est bien pose.\n");
    } else {
        printf("Echec : Le sol n'a pas ete detecte (res[0] = %d).\n", res[0]);
    }
}

/** 
 * @fn test_collision_mur_cote();
 * @brief Corps d'une fonction de test sur les collisions du dino avec un mur
 * @author Romane Saint_Léger
 * @date Crée le 07/02/2026
 * @version 1.3
 */

void test_collision_mur_cote() {
    printf("\n--- Test Collision Mur (Horizontale) ---\n");
    // Dino à x=20, largeur=2. Le côté droit est à x=22
    int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN];
    t_dino dino;
    dino.d = D1;
    dino.etat = 1;
    dino.pv = 100;
    dino.pos.x = 20;
    dino.pos.y = 20;
    dino.largeur = 2;
    dino.hauteur = 2;
    int res[4];

    // On place un mur (TERRE) à sa droite (EST)
    // On le met à la hauteur de son corps (y=21)
    matrice[21][22] = TERRE; 

    collision_decor(res, dino, matrice);
    
    // res[2] gère la collision à l'EST (droite)
    if (res[2] == 1) {
        printf("Succes : Mur detecte a l'EST (droite). Le dino est bloque.\n");
    } else {
        printf("Echec : Le mur n'a pas ete detecte (res[2] = %d).\n", res[2]);
    }
}

/** 
 * @fn test_chute_libre();
 * @brief Corps d'une fonction de test sur les collisions du dino avec l'air
 * @author Romane Saint_Léger
 * @date Crée le 07/02/2026
 * @version 1.3
 */

void test_chute_libre() {
    printf("\n--- Test Chute Libre (Ciel) ---\n");
    int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN];
    t_dino dino;
    dino.d = D1;
    dino.etat = 1;
    dino.pv = 100;
    dino.pos.x = 20;
    dino.pos.y = 20;
    dino.largeur = 2;
    dino.hauteur = 2;
    int res[4];

    // On s'assure que tout est VIDE (0) autour du dino
    for(int i=48; i<55; i++) 
        for(int j=48; j<55; j++) matrice[i][j] = 0; 

    collision_decor(res, dino, matrice);

    if (res[0] == 0 && res[1] == 0 && res[2] == 0 && res[3] == 0) {
        printf("Succes : Le dino est bien dans le vide, il peut tomber.\n");
    } else {
        printf("Echec : Obstacle fantome detecte dans le ciel.\n");
    }
}

/**
 * @brief Tests des fonctions de collisions du dino sur la matrice
 * @author Romane Saint_Léger
 * @return 0
 * @version 1.0
 */

int main(int argc, char * argv[]) {
    int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN];
    srand(time(NULL));
    
    // On réinitialise la matrice avant chaque test ou on la vide ici
    for(int i=0; i<HAUTEUR_TERRAIN; i++) for(int j=0; j<LARGEUR_TERRAIN; j++){
        matrice[i][j] = 0;
    }

    test_collision_eau();
    test_collision_sol();
    test_collision_mur_cote();
    test_chute_libre();
    test_placement_multi_zones();

    printf("\n--- Fin des tests ---\n");
    return 0;
}

