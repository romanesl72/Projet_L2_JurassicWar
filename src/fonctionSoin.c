 #include "../lib/fonctionSoin.h"

 /** 
 * @file fonctionSoin.c
 * @brief Corps d'une fonction de soin pour les dinosaures.
 * @author Romane Saint_Léger
 * @date Crée le 01/04/2026
 * @version 1.0
 */

void utiliserPotion(t_dino *dino) {
    if (dino == NULL) return;
    
    int chance = rand() % 100;
    int soin;

    if (chance < 50) {
        soin = 5;
    } else if (chance < 80) {
        soin = 10;
    } else {
        soin = 20;
    }

    dino->pv += soin;
    
    if (dino->pv > 100){
        dino->pv = 100;
    }
    
    /*printf("Dino %d a utilise une potion. PV actuels : %d\n", dino->d, dino->pv);*/
}