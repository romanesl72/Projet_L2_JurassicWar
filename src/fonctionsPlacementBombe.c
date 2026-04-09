#include "../lib/fonctionsPlacementBombe.h"
#include <math.h>
#include <stdio.h>

/** 
 * @file fonctionsPlacementBombe.c
 * @brief Corps des fonctions liées au placement de la bombe à côté des dinosaures.
 * @author Hannah Sergent
 * @date Crée le 20/03/2026
 * @version 1.2
 */

/**
 * @fn int enterreeBombe(t_bombe * bombe, t_case matriceTerrain[HAUTEUR_TERRAIN][LARGEUR_TERRAIN]);
 * @brief La fonction vérifie si la bombe est enterrée dans le terrain aux coordonnées qu'elle possède actuellement.
 * @author Hannah Sergent
 * @date Crée le 27/03/2026
 * @version 1.2
 * @param bombe un pointeur sur une structure de type bombe 
 * @param matriceTerrain une matrice contenant les informations sur le terrain
 */

int enterreeBombe(t_bombe * bombe, t_case matriceTerrain[HAUTEUR_TERRAIN][LARGEUR_TERRAIN]){

    int largeur;
    int hauteur;
    int enterreTot = 1;
    int enterrePartiel = 0;

    t_coordonnee posBombe;

    posBombe.x = roundf(bombe->coor.x);
    posBombe.y = roundf(bombe->coor.y);

    for(largeur = -bombe->rayon; largeur <= bombe->rayon; largeur++){

        for(hauteur = -bombe->rayon; hauteur <= bombe->rayon; hauteur++){

            if (largeur*largeur + hauteur*hauteur <= bombe->rayon*bombe->rayon) {

                if (matriceTerrain[posBombe.y + largeur][posBombe.x + hauteur] == TERRE){
                    enterrePartiel = 1;
                }
                else {
                    enterreTot = 0;
                }
            }
        }
    }

    /* La bombe est enterrée totalement. */

    if (enterreTot){
        return 1;
    }

    /* La bombe est enterrée partiellement. */

    if (enterrePartiel){
        return 2;
    }

    /* La bombe n'est pas enterrée. */

    return 0;
}

void placerBombeEntrePattes(t_dino *dino, t_bombe * bombe, t_cote *cote, t_case matriceTerrain[HAUTEUR_TERRAIN][LARGEUR_TERRAIN]){

    int cotesEnterres[2] = {0, 0};

    t_coordonnee coorDino;
    coorDino.x = dino->pos.x;
    coorDino.y = dino->pos.y;

    bombe->coor.y = coorDino.y + TAILLE_DINO/2;

    bombe->coor.x = coorDino.x + TAILLE_DINO + bombe->rayon + EXPLOSION_NON_CONTROLEE;
    cotesEnterres[DROITE] = enterreeBombe(bombe, matriceTerrain);
    printf("Enterree à droite : %d \n", cotesEnterres[DROITE]);

    /* La gauche est le côté par défaut. */

    bombe->coor.x = coorDino.x - bombe->rayon - EXPLOSION_NON_CONTROLEE;
    cotesEnterres[GAUCHE] = enterreeBombe(bombe, matriceTerrain);
    printf("Enterree à gauche : %d \n", cotesEnterres[GAUCHE]);

    /* On veut lancer la bombe vers la gauche et il y a assez de place à gauche. */

    if ((*cote == GAUCHE) && (cotesEnterres[GAUCHE] == 0)){
        bombe->coor.x = coorDino.x - bombe->rayon - EXPLOSION_NON_CONTROLEE;
        return;
    }

    /* On veut lancer la bombe vers la droite et il y a assez de place à droite. */

    if ((*cote == DROITE) && (cotesEnterres[DROITE] == 0)){
        bombe->coor.x = coorDino.x + TAILLE_DINO + bombe->rayon + EXPLOSION_NON_CONTROLEE;
        return;
    }

    /* On veut lancer la bombe vers la gauche mais il n'y a assez de place qu'à droite. */

    if (cotesEnterres[DROITE] == 0){
        bombe->coor.x = coorDino.x + TAILLE_DINO + bombe->rayon + EXPLOSION_NON_CONTROLEE;
        *cote = DROITE;
        return;
    }
    *cote = GAUCHE;
}