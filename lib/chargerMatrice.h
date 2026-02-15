/**
 * @file chargerMatrice.h
 * @brief Fonctions pour charger une matrice depuis un fichier.
 */

#ifndef _CHARGER_MATRICE_H_
#define _CHARGER_MATRICE_H_


#include "types.h"


/**
 * @brief Charge une matrice depuis un fichier.
 * @param nomFichier Le nom du fichier à lire.
 * @param matrice La matrice à remplir avec les données du fichier.
 * @return int Retourne 1 si le chargement a réussi, 0 sinon.
 */
void chargerMatriceDepuisFichier(const char* nomFichier, int matrice[MAT_H][MAT_L]);



#endif