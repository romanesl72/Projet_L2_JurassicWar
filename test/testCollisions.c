#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../lib/types.h"
#include "../lib/collision_decor.h"

// On déclare la matrice de test en global pour qu'elle soit accessible
int matrice_test[MAT_H][MAT_L];

void test_placement_multi_zones();


void test_collision_eau() {
    printf("--- Test Collision Eau ---\n");
    t_dino d = {DINO1, 1, 100, {20, 20}, 2, 2}; 
    int res[4];

    // On vide la matrice et on place de l'eau au SUD
    for(int i=0; i<MAT_H; i++) for(int j=0; j<MAT_L; j++){
        matrice_test[i][j] = VIDE;
    }
    matrice_test[22][21] = EAU; 

    collision_decor(res, d, matrice_test);
    if (res[0] == -1) {
        printf("Succes : Eau detectee au SUD. Le dino va etre supprime.\n");
    } else {
        printf("Echec : L'eau n'a pas ete detectee (res[0] = %d).\n", res[0]);
    }
}

void test_collision_sol() {
    printf("\n--- Test Collision Sol (Verticale) ---\n");
    // Dino posé sur le sol (y=20, hauteur=2, donc pieds à y=22)
    t_dino d = {DINO1, 1, 100, {20, 20}, 2, 2}; 
    int res[4];

    // On place de la TERRE juste sous ses pieds
    matrice_test[22][21] = TERRE; 

    collision_decor(res, d, matrice_test);
    
    // res[0] doit être égal à 1 (collision détectée au SUD)
    if (res[0] == 1) {
        printf("Succes : Sol detecte au SUD (1). Le dino est bien pose.\n");
    } else {
        printf("Echec : Le sol n'a pas ete detecte (res[0] = %d).\n", res[0]);
    }
}

void test_collision_mur_cote() {
    printf("\n--- Test Collision Mur (Horizontale) ---\n");
    // Dino à x=20, largeur=2. Le côté droit est à x=22
    t_dino d = {DINO1, 1, 100, {20, 20}, 2, 2}; 
    int res[4];

    // On place un mur (TERRE) à sa droite (EST)
    // On le met à la hauteur de son corps (y=21)
    matrice_test[21][22] = TERRE; 

    collision_decor(res, d, matrice_test);
    
    // res[2] gère la collision à l'EST (droite)
    if (res[2] == 1) {
        printf("Succes : Mur detecte a l'EST (droite). Le dino est bloque.\n");
    } else {
        printf("Echec : Le mur n'a pas ete detecte (res[2] = %d).\n", res[2]);
    }
}

void test_chute_libre() {
    printf("\n--- Test Chute Libre (Ciel) ---\n");
    t_dino d = {DINO1, 1, 100, {50, 50}, 2, 2}; 
    int res[4];

    // On s'assure que tout est VIDE (0) autour du dino
    for(int i=48; i<55; i++) 
        for(int j=48; j<55; j++) matrice_test[i][j] = 0; 

    collision_decor(res, d, matrice_test);

    if (res[0] == 0 && res[1] == 0 && res[2] == 0 && res[3] == 0) {
        printf("Succes : Le dino est bien dans le vide, il peut tomber.\n");
    } else {
        printf("Echec : Obstacle fantome detecte dans le ciel.\n");
    }
}

int main() {
    srand(time(NULL));
    
    // On réinitialise la matrice avant chaque test ou on la vide ici
    for(int i=0; i<MAT_H; i++) for(int j=0; j<MAT_L; j++){
        matrice_test[i][j] = VIDE;
    }

    test_collision_eau();
    test_collision_sol();
    test_collision_mur_cote();
    test_chute_libre();
    test_placement_multi_zones();

    printf("\n--- Fin des tests ---\n");
    return 0;
}

