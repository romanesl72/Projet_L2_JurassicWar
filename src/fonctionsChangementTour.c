#include "../lib/fonctionsChangementTour.h"

/** 
 * @file fonctionsChangementTour.c
 * @brief Corps des fonctions liées au changement de tour
 * @author Hannah Sergent
 * @date Crée le 20/03/2026
 */

void tourSuivant(int *numeroTour, int *equipeCourante, t_case *dinoTour){

    if ((*dinoTour) == D6){
        (*dinoTour) = D1;
        (*equipeCourante) = 1;
    }
    else {

        if ((*equipeCourante) == 1){
            (*dinoTour) += NOMBRE_DINOS/2;
            (*equipeCourante) = 2;
        }
        else {
            (*dinoTour) -= NOMBRE_DINOS/3;
            (*equipeCourante) = 1;
        }
    }
    (*numeroTour)++;
}