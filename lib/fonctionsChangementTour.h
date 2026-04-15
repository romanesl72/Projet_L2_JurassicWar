#ifndef _FONCTIONSCHANGEMENTTOUR_H_
#define _FONCTIONSCHANGEMENTTOUR_H_

#include "../lib/types.h"

/** 
 * @file fonctionsChangementTour.h
 * @brief Définitions des fonctions liées au changement de tour.
 * @author Hannah Sergent
 * @date Crée le 20/03/2026
 * @version 2.3
 */

/** 
 * @fn int finPartie(t_joueur *equipe1, t_joueur *equipe2);
 * @brief La fonction détermine si la partie est terminée.
 * @author Hannah Sergent
 * @date Crée le 23/03/2026
 * @version 1.1
 * @param equipe1 un pointeur sur la structure correspondant aux dinosaures du joueur 1
 * @param equipe2 un pointeur sur la structure correspondant aux dinosaures du joueur 2
 * @return 1 si la partie est terminée et 0 sinon
 */

int finPartie(t_joueur *equipe1, t_joueur *equipe2);

/** 
 * @fn int equipeGagnante(t_joueur *equipe1, t_joueur *equipe2);
 * @brief La fonction détermine l'équipe gagnante.
 * @author Hannah Sergent
 * @date Crée le 15/04/2026
 * @version 1.0
 * @param equipe1 un pointeur sur la structure correspondant aux dinosaures du joueur 1
 * @param equipe2 un pointeur sur la structure correspondant aux dinosaures du joueur 2
 * @return 1 si l'équipe 1 a gagné et 2 si l'équipe 2 a gagné
 */

int equipeGagnante(t_joueur *equipe1, t_joueur *equipe2);

/** 
 * @fn void tourSuivant(t_tour *tour, t_joueur *equipe1, t_joueur *equipe2);
 * @brief La fonction effectue un changement de tour. Il s'agit de changer de dinosaure, d'équipe et de numéro de tour.
 * @author Hannah Sergent
 * @date Crée le 20/03/2026
 * @version 2.3
 * @param tour un pointeur sur une structure gérant les tours
 * @param equipe1 un pointeur sur la structure correspondant aux dinosaures du joueur 1
 * @param equipe2 un pointeur sur la structure correspondant aux dinosaures du joueur 2
 */

void tourSuivant(t_tour *tour, t_joueur *equipe1, t_joueur *equipe2);

#endif