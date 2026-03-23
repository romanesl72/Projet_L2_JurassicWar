#include "../lib/fonctionsChangementTour.h"
#include "../lib/fonctionsStructJoueur.h"
#include <stdio.h>

/** 
 * @file fonctionsChangementTour.c
 * @brief Corps des fonctions liées au changement de tour
 * @author Hannah Sergent
 * @date Crée le 20/03/2026
 */

/** 
 * @fn int finPartie(t_joueur *equipe1, t_joueur *equipe2);
 * @brief La fonction détermine si la partie est terminée.
 * @author Hannah Sergent
 * @date Crée le 23/03/2026
 * @param equipe1 un pointeur sur la structure correspondant aux dinosaures du joueur 1
 * @param equipe2 un pointeur sur la structure correspondant aux dinosaures du joueur 2
 * @return 1 si la partie est terminée et 0 sinon
 */

int finPartie(t_joueur *equipe1, t_joueur *equipe2){
    return ((equipe1->n == 0) || (equipe2->n == 0));
}

/** 
 * @fn void dinoSuivantAdversaire(int *equipeCourante, t_case *dinoTour);
 * @brief La fonction sélectionne le dinosaure suivant de l'équipe adverse.
 * @author Hannah Sergent
 * @date Crée le 23/03/2026
 * @param equipeCourante un pointeur sur le numéro de l'équipe qui vient de jouer
 * @param dinoTour un pointeur sur le dinosaure qui vient de jouer
 */

void dinoSuivantAdversaire(int *equipeCourante, t_case *dinoTour){

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
            (*dinoTour) -= NOMBRE_DINOS/2 - 1;
            (*equipeCourante) = 1;
        }
    }

}

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

void tourSuivant(int *numeroTour, int *equipeCourante, t_case *dinoTour, t_joueur *equipe1, t_joueur *equipe2){

    t_dino *dino;

    if (!finPartie(equipe1, equipe2)){

        dinoSuivantAdversaire(equipeCourante, dinoTour);

        do {
            dino = recupererDinoNumero(equipe1, equipe2, (*dinoTour));
            if (dino == NULL){
                dinoSuivantEquipe((*equipeCourante), dinoTour);
            }
        } while(dino == NULL);

        (*numeroTour)++;
    }
    else {
        (*numeroTour) = -1;
    }
}

/** 
 * @fn void dinoSuivantEquipe(int equipeCourante, t_case *dinoTour);
 * @brief La fonction sélectionne le dinosaure suivant de la même équipe.
 * @author Hannah Sergent
 * @date Crée le 23/03/2026
 * @param equipeCourante un pointeur sur le numéro de l'équipe qui vient de jouer
 * @param dinoTour un pointeur sur le dinosaure qui vient de jouer
 */
