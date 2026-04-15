#include "../lib/fonctionsChangementTour.h"
#include "../lib/fonctionsStructJoueur.h"
#include <stdio.h>

/** 
 * @file fonctionsChangementTour.c
 * @brief Corps des fonctions liées au changement de tour.
 * @author Hannah Sergent
 * @date Crée le 20/03/2026
 * @version 2.3
 */

int finPartie(t_joueur *equipe1, t_joueur *equipe2){
    return ((equipe1->n == 0) || (equipe2->n == 0));
}

int equipeGagnante(t_joueur *equipe1, t_joueur *equipe2){
    if (equipe1->n == 0){
        return 2;
    }
    else {
        return 1;
    }
}


/** 
 * @fn void dinoSuivantEquipe(int equipeCourante, t_case *dinoTour);
 * @brief La fonction sélectionne le dinosaure suivant de la même équipe.
 * @author Hannah Sergent
 * @date Crée le 23/03/2026
 * @version 1.0
 * @param equipeCourante un pointeur sur le numéro de l'équipe qui vient de jouer
 * @param dinoTour un pointeur sur le dinosaure qui vient de jouer
 */

void dinoSuivantEquipe(int equipeCourante, t_case *dinoTour){

    if (equipeCourante == 1){

        if ((*dinoTour) == D3){
            (*dinoTour) = D1;
        }
        else {
            (*dinoTour)++;
        }

    }
    else {

        if ((*dinoTour) == D6){
            (*dinoTour) = D4;
        }
        else {
            (*dinoTour)++;
        }

    }

}

void tourSuivant(t_tour *tour, t_joueur *equipe1, t_joueur *equipe2){

    t_case dinoTemp;
    t_dino *dino = NULL;

    if (!finPartie(equipe1, equipe2)){

        /* Changement de l'équipe courante */

        if (tour->equipeCourante == 1){
            tour->equipeCourante = 2;
        }
        else {
            tour->equipeCourante = 1;
        }

        /* Changement du dinosaure courant */

        dinoTemp = tour->dinoPrecedent;
        tour->dinoPrecedent = tour->dinoCourant;
        
        do {
            dinoSuivantEquipe(tour->equipeCourante, &dinoTemp);
            dino = recupererDinoNumero(equipe1, equipe2, dinoTemp);

        } while (dino == NULL);

        tour->dinoCourant = dinoTemp;

        /* Changement du numéro de tour */

        tour->numeroTour ++;
    }
} 