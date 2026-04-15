#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "../lib/chargerMatrice.h"
#include "../lib/fonctionsMenuHIP.h"
#include "../lib/fonctionsTirs.h"
#include "../lib/fonctionsVerification.h"
#include "../lib/placer_dinos.h"
#include "../lib/types.h"


/** 
 * @file test_vol.c
 * @brief Corps des fonctions de test sur les collisions durant le vol
 * @author Romane Saint_Léger
 * @date Crée le 12/04/2026
 * @version 1.2
 */


/**
 * @brief Simulation d'une petite matrice pour le test
 * @author Romane Saint_Léger
 * @date Crée le 12/04/2026
*/
int matriceTest[HAUTEUR_TERRAIN][LARGEUR_TERRAIN] = {0};

 /**
 * @fn void reset_matrice();
 * @brief Un dinosaure peut tirer à l'arc et le terrain est affiché
 * @author Romane Saint_Léger
 * @date Crée le 12/04/2026
 * @version 2.2
 */

void reset_matrice() {
    for(int y=0; y<HAUTEUR_TERRAIN; y++)
        for(int x=0; x<LARGEUR_TERRAIN; x++)
            matriceTest[y][x] = 0;
}

/**
 * @fn remplir_toute_la_matrice(int type_bloc);
 * @brief Test des collisions sur la fonction MettreAJourVol
 * @author Romane Saint_Léger
 * @date Crée le 12/04/2026
 * @param type_bloc entier représentant le type de bloc
 * @version 1.2
 */

void remplir_toute_la_matrice(int type_bloc) {
    for(int y = 0; y < HAUTEUR_TERRAIN; y++) {
        for(int x = 0; x < LARGEUR_TERRAIN; x++) {
            matriceTest[y][x] = type_bloc;
        }
    }
}

/**
 * @fn test_collisions_vol();
 * @brief Test des collisions sur la fonction MettreAJourVol
 * @author Romane Saint_Léger
 * @date Crée le 12/04/2026
 * @version 1.2
 */

void test_collisions_vol() {
    t_tir tir;
    t_arme arc = {ARC, 20, 1.0f, 5.0f, 15.0f}; // exemple
    float g = 0.5f;

    // --- TEST 1 : Vol libre ---
    reset_matrice();
    initialiserTirArcher(&tir, 100, 100, arc);
    tir.actif = 1;
    tir.velo.u = 2.0f; tir.velo.v = 0.0f;
    int res = mettreAJourVol(&tir, matriceTest, g, D1);
    printf("Debug Test 1: Pos(%f, %f), Resultat obtenu: %d, Attendu: %d\n", tir.pos.x, tir.pos.y, res, AIR);
    assert(res == 0);
    assert(tir.actif == 1);
    assert(tir.pos.x == 102.0f); // 100 + u(2)

    // --- TEST 2 : Collision Frontière (Sortie gauche) ---
    initialiserTirArcher(&tir, 1, 100, arc);
    tir.actif = 1;
    tir.velo.u = -5.0f; // Va sortir au prochain update
    res = mettreAJourVol(&tir, matriceTest, g, D1);
    printf("Debug Test 2: Pos(%f, %f), Resultat obtenu: %d, Attendu: %d\n", tir.pos.x, tir.pos.y, res, -2);
    assert(res == -2);
    assert(tir.actif == 0);

    // --- TEST 3 : Collision Terre ---
    remplir_toute_la_matrice(TERRE);
    initialiserTirArcher(&tir, 105, 100, arc);
    tir.actif = 1;
    tir.velo.u = 5.0f; tir.velo.v = 0;
    res = mettreAJourVol(&tir, matriceTest, g, D1);
    printf("Debug Test 3: Pos(%f, %f), Resultat obtenu: %d, Attendu: %d\n", tir.pos.x, tir.pos.y, res, TERRE);
    assert(res == TERRE);
    assert(res == TERRE);
    assert(tir.actif == 0);

    // --- TEST 4 : Collision EAU ---
    remplir_toute_la_matrice(EAU);
    initialiserTirArcher(&tir, 105, 100, arc);
    tir.actif = 1;
    tir.velo.u = 5.0f; tir.velo.v = 0;
    res = mettreAJourVol(&tir, matriceTest, g, D1);
    printf("Debug Test 4: Pos(%f, %f), Resultat obtenu: %d, Attendu: %d\n", tir.pos.x, tir.pos.y, res, EAU);
    assert(res == EAU);
    assert(res == EAU);
    assert(tir.actif == 0);

    // --- TEST 5 : Collision Ennemi ---
    reset_matrice();
    for(int y = 40; y <= 70; y++) {
        for(int x = 40; x <= 70; x++) {
            matriceTest[y][x] = D2;
        }
    }
    initialiserTirArcher(&tir, 45, 50, arc);
    tir.actif = 1;
    tir.velo.u = 5.0f; tir.velo.v = 0;
    res = mettreAJourVol(&tir, matriceTest, g, D1); // D1 tire
    printf("Debug Test 5: Pos(%f, %f), Resultat obtenu: %d, Attendu: %d\n", tir.pos.x, tir.pos.y, res, D2);
    assert(res == D2);
    assert(tir.actif == 0);

    // --- TEST 6 : Auto-Collision (Le projectile traverse le tireur) ---
    reset_matrice();
    for(int y = 40; y <= 70; y++) {
        for(int x = 40; x <= 70; x++) {
            matriceTest[y][x] = D1;
        }
    }
    initialiserTirArcher(&tir, 45, 50, arc);
    tir.actif = 1;
    tir.velo.u = 5.0f; tir.velo.v = 0;
    res = mettreAJourVol(&tir, matriceTest, g, D1); // D1 tire sur lui-même
    printf("Debug Test 6: Pos(%f, %f), Resultat obtenu: %d, Attendu: %d\n", tir.pos.x, tir.pos.y, res, AIR);
    assert(res == 0); // Ne doit pas détecter de collision
    assert(tir.actif == 1);

    printf("Tous les tests de trajectoire et collision sont passés !\n");
}

/**
 * @brief Test des collisions sur la fonction MettreAJourVol
 * @return 0
 * @version 1.0
 */

int main() {
    test_collisions_vol();
    return 0;
}
