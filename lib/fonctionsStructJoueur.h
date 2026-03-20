#ifndef _FONCTIONSSTRUCTJOUEUR_H_
#define _FONCTIONSSTRUCTJOUEUR_H_

#include "../lib/types.h"

/** 
 * @file fonctionsStructJoueur.h
 * @brief Définitions de fonctions liées à la structure joueur
 * @author Hannah Sergent
 * @date Crée le 18/03/2026
 */

/** 
 * @fn t_dino * recupererDinoNumero(t_joueur * equipe1, t_joueur * equipe2, t_case numero);
 * @brief La fonction récupère l'adresse d'une structure dinosaure à partir de son identifiant.
 * @author Hannah Sergent
 * @date Crée le 19/03/2026
 * @param equipe1 un pointeur sur la structure correspondant aux dinosaures du joueur 1
 * @param equipe2 un pointeur sur la structure correspondant aux dinosaures du joueur 2
 * @param numero l'identifiant du dinosaure recherché
 * @return l'adresse de la structure dinosaure correspondant au numéro d'identifiant ou un pointeur nul si le dinosaure n'existe dans aucune équipe.
 */

t_dino * recupererDinoNumero(t_joueur * equipe1, t_joueur * equipe2, t_case numero);

/** 
 * @fn void supprimerDinoJoueur(t_joueur * equipe1, t_joueur * equipe2, t_case numero);
 * @brief La fonction supprime un dinosaure de l'équipe auquel il appartient.
 * @author Hannah Sergent
 * @date Crée le 19/03/2026
 * @param equipe1 un pointeur sur la structure correspondant aux dinosaures du joueur 1
 * @param equipe2 un pointeur sur la structure correspondant aux dinosaures du joueur 2
 * @param numero l'identifiant du dinosaure à supprimer
 */

void supprimerDinoJoueur(t_joueur * equipe1, t_joueur * equipe2, t_case numero);

/** 
 * @fn void initialiserContenuJoueur(t_joueur *joueur);
 * @brief La fonction initialise le contenu d'un joueur.
 * @author Hannah Sergent
 * @date Crée le 19/03/2026
 * @param joueur un pointeur sur la structure dont on veut initialiser le contenu 
 */

void initialiserContenuJoueur(t_joueur *joueur);

/** 
 * @fn void detruireContenuJoueur(t_joueur *joueur);
 * @brief La fonction détruit le contenu d'une structure joueur.
 * @author Hannah Sergent
 * @date Crée le 19/03/2026
 * @param joueur un pointeur sur la structure dont on veut détruire le contenu 
 */

void detruireContenuJoueur(t_joueur *joueur);

#endif