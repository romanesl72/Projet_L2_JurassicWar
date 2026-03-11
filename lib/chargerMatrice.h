#ifndef _CHARGER_MATRICE_H_
#define _CHARGER_MATRICE_H_

#include "types.h"

/** 
 * @file chargerMatrice.h
 * @brief Fonctions pour charger une matrice depuis un fichier.
 * @author Romane Saint_Léger Hannah Sergent
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

/**
 * @fn int initialiserMatrice(t_case (**matriceTerrain)[LARGEUR_TERRAIN]);
 * @brief la fonction initialise la matrice du terrain
 * @author Hannah Sergent
 * @date Crée le 11/03/2026
 * @version 1.0
 * @param matriceTerrain matrice qui contient les informations sur le terrain
 * @return 1 si tout s'est bien passé et 0 sinon
 */

int initialiserMatrice(t_case (**matriceTerrain)[LARGEUR_TERRAIN]);

/**
 * @fn void detruireMatrice(t_case (**matriceTerrain)[LARGEUR_TERRAIN]);
 * @brief la fonction détruit la matrice du terrain
 * @author Hannah Sergent
 * @date Crée le 11/03/2026
 * @version 1.0
 * @param matriceTerrain La matrice à détruire
 */

void detruireMatrice(t_case (**matriceTerrain)[LARGEUR_TERRAIN]);


#endif