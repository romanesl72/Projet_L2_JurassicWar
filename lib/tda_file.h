
// J'ai repris les fonctions du module d'algo2, merci Madame Py.

#ifndef _TDA_FILE_H_
#define _TDA_FILE_H_

#include "types.h"

/** 
 * @file tda_file.h
 * @brief 
 * @author Solène Orieux
 * @date 25/03/2025
 */



/**
 * @fn void initfile(void);
 * @author Solène Orieux
 * @date 25/03/2025
 * @brief initialisation de la file
 */

void initfile(void);

/**
 * @fn void ajouter(int v);
 * @author Solène Orieux
 * @date 25/03/2025
 * @brief ajout dans la file
 * @param v valeur à ajouter
 */


void ajouter(t_coordonnee v);

/**
 * @fn void retirer(int* v);
 * @author Solène Orieux
 * @date 25/03/2025
 * @brief ajout dans la file
 * @param v poiteur sur la valeur à supprimer
 */

void retirer(t_coordonnee *v);

void detruireFile();

/**
 * @fn int filevide(void);
 * @author Solène Orieux
 * @date 25/03/2025
 * @brief vérifie si la file est vide
 */

int filevide(void);

int afficherFile(SDL_Renderer *rendu);

t_coordonnee *lireTete();

#endif