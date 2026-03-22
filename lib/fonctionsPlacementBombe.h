#ifndef _FONCTIONSPLACEMENTBOMBE_H_
#define _FONCTIONSPLACEMENTBOMBE_H_

#include "types.h"

/** 
 * @file fonctionsPlacementBombe.h
 * @brief Définitions des fonctions liées au placement de la bombe à côté des dinosaures
 * @author Hannah Sergent
 * @date Crée le 20/03/2026
 */

/** 
 * @fn void placerBombeEntrePattes(t_dino * dino, t_bombe * bombe, t_cote cote);
 * @brief La fonction place la bombe entre les pattes du dinosaure précisé en paramètre.
 * @author Hannah Sergent
 * @date Crée le 20/03/2026
 * @param dino un pointeur sur un dinosaure
 * @param bombe un pointeur sur une structure de type bombe
 * @param cote 
 */

void placerBombeEntrePattes(t_dino *dino, t_bombe * bombe, t_cote cote);

#endif