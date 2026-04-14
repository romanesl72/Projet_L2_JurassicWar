#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../lib/types.h"
#include "../lib/collision_decor.h"
#include "../lib/placer_dinos.h"

/** 
 * @file testPlacement.c
 * @brief Corps d'une fonction de test les placements des dinosaures
 * @author Romane Saint_Léger
 * @date Crée le 07/02/2026
 * @version 1.2
 */

/** 
 * @fn test_placement_multi_zones();
 * @brief Corps d'une fonction de test sur les placements des dinosaures
 * @author Romane Saint_Léger
 * @date Crée le 07/02/2026
 * @version 1.3
 */

void test_placement_multi_zones() {
    printf("\n--- Test Placement Multi-Zones ---\n");
    int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN];
    t_dino dino; 
    dino.d = D1;
    
    t_zone_depart mes_zones[2];
    
    // Zone 1
    mes_zones[0].bas_centre.x = 100;
    mes_zones[0].bas_centre.y = 500;
    mes_zones[0].id_equipe = 1;

    // Zone 2
    mes_zones[1].bas_centre.x = 1000;
    mes_zones[1].bas_centre.y = 450;
    mes_zones[1].id_equipe = 2;

    int z = rand() % 2;
    remplir_matrice_dino(&dino, mes_zones[z].bas_centre, matrice);

    printf("Dino place sur le point (%d, %d). Sa tete est en y=%d\n", 
            mes_zones[z].bas_centre.x, mes_zones[z].bas_centre.y, dino.pos.y);
        
}