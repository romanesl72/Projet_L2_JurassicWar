#ifndef _FONCTIONSCHANGEMENTTOUR_H_
#define _FONCTIONSCHANGEMENTTOUR_H_

#include "../lib/types.h"

/** 
 * @file fonctionsChangementTour.h
 * @brief Définitions des fonctions liées au changement de tour
 * @author Hannah Sergent
 * @date Crée le 20/03/2026
 */

/** 
 * @fn void tourSuivant(int *numeroTour, t_case *dinoTour);
 * @brief La fonction effectue un changement de tour. Il s'agit de changer de dinosaure, d'équipe et de numéro de tour.
 * @author Hannah Sergent
 * @date Crée le 20/03/2026
 * @param numeroTour un pointeur sur le numéro du tour
 * @param equipeCourante un pointeur sur le numéro de l'équipe qui vient de jouer
 * @param dinoTour un pointeur sur le dinosaure dont c'est le tour
 */

void tourSuivant(int *numeroTour, int *equipeCourante, t_case *dinoTour);

#endif