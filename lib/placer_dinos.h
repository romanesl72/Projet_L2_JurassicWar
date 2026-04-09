#ifndef _PLACER_DINOS_H_
#define _PLACER_DINOS_H_

#include "types.h"

/** 
 * @file placer_dinos.h
 * @brief Fonctions de placement des dinosaures sur la matrice.
 * @author Romane Saint_Léger Hannah Sergent
 * @date Crée le 15/02/2026
 * @version 1.3
 */

/**
 * @fn void remplir_matrice_dino(t_dino *dino, t_coordonnee p_sol, int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN]);
 * @brief Place un dinosaure aléatoirement dans une zone de spawn valide en le remplissant de son ID.
 * @author Romane Saint-Léger
 * @date Crée le 15/02/2026
 * @version 1.2
 * @param dino Pointeur vers la structure du dino à placer.
 * @param p_sol Coordonnées du point sol o`u les pieds du dinosaure doivent se poser.
 * @param matrice La matrice (terrain) à mettre à jour avec l'ID du dino.
 */

void remplir_matrice_dino(t_dino *dino, t_coordonnee p_sol, int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN]);


/**
 * @fn void placer_une_equipe(t_joueur *joueur, t_zone_depart points_spawn[10], int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], t_case id_depart);
 * @brief Initialise et place tous les dinosaures d'une équipe sur le terrain.
 * @author Romane Saint-Léger
 * @date Crée le 15/02/2026
 * @version 1.2
 * @param joueur Pointeur vers la structure du joueur (l'équipe).
 * @param points_spawn Tableau des points de spawn disponibles.
 * @param matrice Matrice de jeu à modifier
 * @param id_depart Indice de départ pour chaque dinosaure afin de les différencier.
 */


void placer_une_equipe(t_joueur *joueur, t_zone_depart points_spawn[10], int matrice[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], t_case id_depart);

/**
 * @fn void afficherDinos(SDL_Renderer* zoneAffichage, t_joueur * equipe);
 * @brief La fonction affiche à l'écran les dinosaures d'une équipe placés précédemment sur le terrain
 * @author Hannah Sergent
 * @date Crée le 17/03/2026
 * @version 1.3
 * @param zoneAffichage pointeur sur la zone d'affichage
 * @param equipe l'équipe dont on veut afficher les dinosaures
 */

void afficherDinos(SDL_Renderer* zoneAffichage, t_joueur * equipe);

/**
 * @fn void afficherDinosAvecJeu(SDL_Renderer* zoneAffichage, t_joueur * equipe);
 * @brief La fonction affiche à l'écran les dinosaures d'une équipe placés précédemment sur le terrain avec l'inventaire et les points de vie des dinos
 * @author Romane Saint-Léger
 * @date Crée le 01/04/2026
 * @version 1.0
 * @param zoneAffichage pointeur sur la zone d'affichage
 * @param equipe l'équipe dont on veut afficher les dinosaures
 */

void afficherDinosAvecJeu(SDL_Renderer* zoneAffichage, t_joueur * equipe);

#endif