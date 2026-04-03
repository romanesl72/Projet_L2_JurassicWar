#ifndef _FONCTIONSPAGESINFORMATIONS_H_
#define _FONCTIONSPAGESINFORMATIONS_H_

#include "types.h"

/** 
 * @file fonctionsPagesInformations.h
 * @brief Corps des fonctions liées aux fenêtres d'informations, c'est à dire la liste des touches et les règles du jeu.
 * @author Hannah Sergent
 * @date Crée le 01/04/2026
 * @version 1.0
 */

/**
 * @def TAILLE_POLICE_PARAGRAPHE
 * @brief Taille de police choisie pour les paragraphes des fenêtres d'information.
*/

#define TAILLE_POLICE_PARAGRAPHE 20

/**
 * @def TAILLE_POLICE_SOUS_TITRE
 * @brief Taille de police choisie pour les sous-titres des fenêtres d'information.
*/

#define TAILLE_POLICE_SOUS_TITRE 23

void ouvrirFenInfos(char *nomFen, char *nomFichier);

#endif