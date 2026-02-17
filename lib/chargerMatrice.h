#ifndef _CHARGER_MATRICE_H_
#define _CHARGER_MATRICE_H_

#include "types.h"

/** 
 * @file chargerMatrice.h
 * @brief Fonctions pour charger une matrice depuis un fichier.
 * @author Romane Saint_Léger
 * @date Crée le 07/02/2026
 */

/**
 * @fn void chargerMatriceDepuisFichier(const char* nomFichier, int matrice[MAT_H][MAT_L]);
 * @brief Charge une matrice depuis un fichier.
 * @author Romane Saint-Léger
 * @date Crée le 07/02/2026
 * @param nomFichier Le nom du fichier à lire.
 * @param matrice La matrice à remplir avec les données du fichier.
 */

void chargerMatriceDepuisFichier(const char* nomFichier, int matrice[MAT_H][MAT_L]);


#endif