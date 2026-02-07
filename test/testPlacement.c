#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../lib/types.h"
#include "../lib/collision_decor.h"
#include "../lib/gestion_placement.h"

extern int matrice_test[MAT_H][MAT_L];

void test_placement_multi_zones() {
    printf("\n--- Test Placement Multi-Zones ---\n");
    t_dino d = {DINO1, 1, 100, {0,0}, 2, 2};
    t_zone_depart mes_zones[2] = {
        {{{10, 10}, {15, 10}}, 2, "Zone Depart Gauche"},
        {{{500, 10}, {510, 10}}, 2, "Zone Depart Droite"}
    };

    int z = rand() % 2;
    placer_dino(&d, mes_zones[z], matrice_test);

    printf("Dino place dans '%s' aux coordonnees x=%d, y=%d\n", 
            mes_zones[z].nom_zone, d.pos.x, d.pos.y);
}