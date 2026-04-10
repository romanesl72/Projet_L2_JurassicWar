#ifndef _FONCTIONSCHANGEMENTTOUR_H_
#define _FONCTIONSCHANGEMENTTOUR_H_

#include "../lib/types.h"

/** 
 * @file fonctionsChangementTour.h
 * @brief Définitions des fonctions liées au changement de tour.
 * @author Hannah Sergent
 * @date Crée le 20/03/2026
 * @version 1.0
 */

/** 
 * @fn void tourSuivant(t_tour *tour, t_joueur *equipe1, t_joueur *equipe2);
 * @brief La fonction effectue un changement de tour. Il s'agit de changer de dinosaure, d'équipe et de numéro de tour.
 * @author Hannah Sergent
 * @date Crée le 20/03/2026
 * @version 1.5
 * @param tour un pointeur sur une structure gérant les tours
 * @param equipe1 un pointeur sur la structure correspondant aux dinosaures du joueur 1
 * @param equipe2 un pointeur sur la structure correspondant aux dinosaures du joueur 2
 */

void tourSuivant(t_tour *tour, t_joueur *equipe1, t_joueur *equipe2);

#endif