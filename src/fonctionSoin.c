 #include "../lib/fonctionSoin.h"


void utiliserPotion(t_dino *dino) {
    if (dino == NULL) return;
    
    int soin = 20; // Valeur du soin
    dino->pv += soin;
    
    if (dino->pv > 100){
        dino->pv = 100; // Cap à 100%
    }
    
    /*printf("Dino %d a utilise une potion. PV actuels : %d\n", dino->d, dino->pv);*/
}