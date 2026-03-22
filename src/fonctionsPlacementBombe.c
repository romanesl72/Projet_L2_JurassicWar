#include "../lib/fonctionsPlacementBombe.h"

/** 
 * @file fonctionsPlacementBombe.c
 * @brief Corps des fonctions liées au placement de la bombe à côté des dinosaures
 * @author Hannah Sergent
 * @date Crée le 20/03/2026
 */

void placerBombeEntrePattes(t_dino *dino, t_bombe * bombe, t_cote cote){

    t_coordonnee coorDino;
    coorDino.x = dino->pos.x;
    coorDino.y = dino->pos.y;

    bombe->coor.y = coorDino.y + TAILLE_DINO/2;

    if (cote == GAUCHE){
        bombe->coor.x = coorDino.x - bombe->rayon;
    }
    else {
        bombe->coor.x = coorDino.x + TAILLE_DINO + bombe->rayon;
    }

}