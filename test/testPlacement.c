#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../lib/types.h"
#include "../lib/collision_decor.h"
#include "../lib/gestion_placement.h"

extern int matrice_test[MAT_H][MAT_L];

void test_placement_multi_zones() {
    printf("\n--- Test Placement Multi-Zones ---\n");
    t_dino d; 
    d.d = DINO1;
    
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
    remplir_matrice_dino(&d, mes_zones[z].bas_centre, 0, 0, matrice_test);

    printf("Dino place sur le point (%d, %d). Sa tete est en y=%d\n", 
            mes_zones[z].bas_centre.x, mes_zones[z].bas_centre.y, d.pos.y);
        
}