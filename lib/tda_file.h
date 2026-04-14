#ifndef _TDA_FILE_H_
#define _TDA_FILE_H_

#include "types.h"

// J'ai repris les fonctions du module d'algo2, merci Madame Py.

/** 
 * @file tda_file.h
 * @brief fonction permettant la création d'une file
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
 * @fn int filevide(void);
 * @author Solène Orieux
 * @date 25/03/2025
 * @brief vérifie si la file est vide
 */

int filevide(void);
/**
 * @fn void ajouter(t_coordonnee v);
 * @author Solène Orieux
 * @date 25/03/2025
 * @brief ajout dans la file
 * @param v valeur à ajouter
 */

void ajouter(t_coordonnee v);

/**
 * @fn void retirer(t_coordonnee *v);
 * @author Solène Orieux
 * @date 25/03/2025
 * @brief ajout dans la file
 * @param v poiteur sur la valeur à supprimer
 */

void retirer(t_coordonnee *v);

/**
 * @fn void detruireFile();
 * @author Solène Orieux
 * @date 05/04/2025
 * @brief destruction globale de la file
 */
void detruireFile();


/**
 * @fn int afficherFile(SDL_Renderer *rendu);
 * @author Solène Orieux
 * @date 05/04/2025
 * @brief affiche l'entiéreté de la file
 * @param rendu pointeur sur la fenêtre de jeu
 */
int afficherFile(SDL_Renderer *rendu);

/**
 * @fn t_coordonnee *lireQueue();
 * @author Solène Orieux
 * @date 07/04/2025
 * @brief renvoie un pointeur sur la tête de file
 */

t_coordonnee *lireQueue();

#endif