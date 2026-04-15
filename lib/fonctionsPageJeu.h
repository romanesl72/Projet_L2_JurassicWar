#ifndef _FONCTIONSPAGEJEU_H_
#define _FONCTIONSPAGEJEU_H_

#include "../lib/types.h"
#include <SDL2/SDL_ttf.h>

/** 
 * @file fonctionsPageJeu.h
 * @brief Définitions des fonctions liées à la page du jeu.
 * @author Hannah Sergent Romane Saint-Léger Solène Orieux
 * @date Crée le 29/03/2026
 * @version 1.3
 */

/** 
 * @fn int creerPageJeuBombe(SDL_Window **fenJeu, SDL_Renderer **zoneAffichage, SDL_Texture **texMap);
 * @brief La fonction crée la fenêtre du jeu pour la version de JurassicWar ne contenant que la fonctionnalité bombe.
 * Cette fonction initialise également la zone d'affichage et l'image de la map.
 * @author Hannah Sergent
 * @date Crée le 29/03/2026
 * @version 1.0
 * @param fenJeu un pointeur sur un pointeur de la fenêtre du jeu
 * @param zoneAffichage un pointeur sur un pointeur sur la zone d'affichage
 * @param texMap un pointeur sur un pointeur sur la texture de la map
 * @return 1 si les initialisations se sont correctement déroulées et 0 sinon
 */

int creerPageJeuBombe(SDL_Window **fenJeu, SDL_Renderer **zoneAffichage, SDL_Texture **texMap);

/** 
 * @fn int creerPageJeu(SDL_Window **fenJeu, SDL_Renderer **zoneAffichage, SDL_Texture **texMap, SDL_Texture **texObjets, TTF_Font **policeMenuHIP);
 * @brief La fonction crée la fenêtre du jeu pour la version complète du jeu.
 * Cette fonction initialise également la zone d'affichage et les images de la map et de l'inventaire.
 * @author Hannah Sergent
 * @date Crée le 29/03/2026
 * @version 1.0
 * @param fenJeu un pointeur sur un pointeur de la fenêtre du jeu
 * @param zoneAffichage un pointeur sur un pointeur sur la zone d'affichage
 * @param texMap un pointeur sur un pointeur sur la texture de la map
 * @param texObjets un tableau des textures de l'inventaire
 * @param policeMenuHIP un pointeur sur la police utilisée dans le menu HIP
 * @return 1 si les initialisations se sont correctement déroulées et 0 sinon
 */

int creerPageJeu(SDL_Window **fenJeu, SDL_Renderer **zoneAffichage, SDL_Texture **texMap, SDL_Texture **texObjets, TTF_Font **policeMenuHIP);

/** 
 * @fn void initialiserEquipes(t_joueur *equipe1, t_joueur *equipe2, t_catalogue_zones *catalogue, t_case matriceTerrain[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], SDL_Renderer *zoneAffichage);
 * @brief La fonction initialise les deux équipes, c'est à dire les dinosaures de chaque joueur ainsi que leur placement sur le terrain.
 * @author Hannah Sergent
 * @date Crée le 29/03/2026
 * @version 1.0
 * @param equipe1 un pointeur sur la structure correspondant aux dinosaures du joueur 1
 * @param equipe2 un pointeur sur la structure correspondant aux dinosaures du joueur 2
 * @param catalogue une structure qui contient les zones de spawn
 * @param matriceTerrain la matrice contenant les informations sur le terrain
 * @param zoneAffichage un pointeur sur la zone d'affichage
 */

void initialiserEquipes(t_joueur *equipe1, t_joueur *equipe2, t_catalogue_zones *catalogue, t_case matriceTerrain[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], SDL_Renderer *zoneAffichage);

/** void detecterEvenementsPageJeuBombe(
    int *enCours, 
    int *bombeLancee, 
    int *nombreRebonds, 
    SDL_Renderer *zoneAffichage, 
    SDL_Texture *texMap, 
    SDL_Rect *rectFen, 
    t_bombe *bombe, 
    t_vect *vectVitesse, 
    t_joueur *equipe1, 
    t_joueur *equipe2, 
    t_case dinoCourant, 
    t_case matriceTerrain[HAUTEUR_TERRAIN][LARGEUR_TERRAIN]);
 * @brief La fonction détecte si l'utilisateur réalise une action dans la fenêtre du jeu 
 * ne contenant que la fonctionnalité bombe (appuyer sur une touche ou encore cliquer sur la croix pour fermer).
 * @author Hannah Sergent
 * @date Crée le 29/03/2026
 * @version 1.0
 * @param enCours un pointeur qui indique si la fenetre doit rester ouverte
 * @param nombreRebonds un pointeur sur le nombre de rebonds de la bombe
 * @param bombeLancee un pointeur qui indique si la bombe doit être lancée
 * @param zoneAffichage un pointeur sur la zone d'affichage
 * @param texMap un pointeur sur la texture de la map
 * @param rectFen un rectangle de type SDL_Rect contenant les informations sur la fenêtre du jeu
 * @param bombe un pointeur sur une structure de type bombe
 * @param vectVitesse un pointeur sur le vecteur vitesse de la bombe
 * @param equipe1 un pointeur sur la structure correspondant aux dinosaures du joueur 1
 * @param equipe2 un pointeur sur la structure correspondant aux dinosaures du joueur 2
 * @param dinoCourant l'identifiant du dinosaure dont c'est le tour de jouer
 * @param matriceTerrain la matrice contenant les informations sur le terrain
 */

void detecterEvenementsPageJeuBombe(
    int *enCours, 
    int *bombeLancee, 
    int *nombreRebonds, 
    SDL_Renderer *zoneAffichage, 
    SDL_Texture *texMap, 
    SDL_Rect *rectFen, 
    t_bombe *bombe, 
    t_vect *vectVitesse, 
    t_joueur *equipe1, 
    t_joueur *equipe2, 
    t_case dinoCourant, 
    t_case matriceTerrain[HAUTEUR_TERRAIN][LARGEUR_TERRAIN]);

/** 
 * @fn void afficherJeuSansBombe(t_joueur *equipe1, t_joueur *equipe2, SDL_Rect *rectFen, SDL_Renderer *zoneAffichage, SDL_Texture *texMap);
 * @brief La fonction affiche l'image du terrain et les dinosaures.
 * @author Hannah Sergent
 * @date Crée le 29/03/2026
 * @version 1.0
 * @param equipe1 un pointeur sur la structure correspondant aux dinosaures du joueur 1
 * @param equipe2 un pointeur sur la structure correspondant aux dinosaures du joueur 2
 * @param rectFen un rectangle de type SDL_Rect contenant les informations sur la fenêtre du jeu
 * @param zoneAffichage un pointeur sur la zone d'affichage
 * @param texMap un pointeur sur la texture de la map
 */

void afficherJeuSansBombe(t_joueur *equipe1, t_joueur *equipe2, SDL_Rect *rectFen, SDL_Renderer *zoneAffichage, SDL_Texture *texMap);

/** 
 * @fn void afficherJeuAvecBombe(t_joueur *equipe1, t_joueur *equipe2, t_bombe * bombe, SDL_Rect *rectFen, SDL_Renderer *zoneAffichage, SDL_Texture *texMap);
 * @brief La fonction affiche l'image du terrain, les dinosaures et la bombe.
 * @author Hannah Sergent
 * @date Crée le 29/03/2026
 * @version 1.0
 * @param equipe1 un pointeur sur la structure correspondant aux dinosaures du joueur 1
 * @param equipe2 un pointeur sur la structure correspondant aux dinosaures du joueur 2
 * @param bombe un pointeur sur une structure de type bombe
 * @param rectFen un rectangle de type SDL_Rect contenant les informations sur la fenêtre du jeu
 * @param zoneAffichage un pointeur sur la zone d'affichage
 * @param texMap un pointeur sur un pointeur sur la texture de la map
 */

void afficherJeuAvecBombe(t_joueur *equipe1, t_joueur *equipe2, t_bombe * bombe, SDL_Rect *rectFen, SDL_Renderer *zoneAffichage, SDL_Texture *texMap);

/** 
 * @fn void destruireElementsJeuBombe(t_joueur *equipe1, t_joueur *equipe2, t_case matriceTerrain[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], SDL_Texture *texMap, SDL_Renderer *zoneAffichage, SDL_Window *fenJeu);
 * @brief La fonction détruit les différents objets mis en place pour la version du jeu ne contenant que la fonctionnalité bombe.
 * @author Hannah Sergent
 * @date Crée le 29/03/2026
 * @version 1.0
 * @param equipe1 un pointeur sur la structure correspondant aux dinosaures du joueur 1
 * @param equipe2 un pointeur sur la structure correspondant aux dinosaures du joueur 2
 * @param matriceTerrain la matrice contenant les informations sur le terrain
 * @param texMap un pointeur sur la texture de la map
 * @param zoneAffichage un pointeur sur la zone d'affichage
 * @param fenJeu un pointeur sur la fenêtre du jeu
 */

void destruireElementsJeuBombe(t_joueur *equipe1, t_joueur *equipe2, t_case matriceTerrain[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], SDL_Texture *texMap, SDL_Renderer *zoneAffichage, SDL_Window *fenJeu);

/** 
 * @fn void destruireElementsJeu(t_joueur *equipe1, t_joueur *equipe2, t_case matriceTerrain[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], SDL_Texture *texMap, SDL_Texture **texObjets, TTF_Font *policeMenuHIP, SDL_Renderer *zoneAffichage, SDL_Window *fenJeu);
 * @brief La fonction détruit les différents objets mis en place pour le jeu.
 * @author Hannah Sergent
 * @date Crée le 31/03/2026
 * @version 1.3
 * @param equipe1 un pointeur sur la structure correspondant aux dinosaures du joueur 1
 * @param equipe2 un pointeur sur la structure correspondant aux dinosaures du joueur 2
 * @param matriceTerrain la matrice contenant les informations sur le terrain
 * @param texMap un pointeur sur la texture de la map
 * @param texObjets le tableau des textures affichées dans l'inventaire
 * @param policeMenuHIP un pointeur sur la police utilisée dans le menu HIP
 * @param zoneAffichage un pointeur sur la zone d'affichage
 * @param fenJeu un pointeur sur la fenêtre du jeu
 */

void destruireElementsJeu(t_joueur *equipe1, t_joueur *equipe2, t_case matriceTerrain[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], SDL_Texture *texMap, SDL_Texture **texObjets, TTF_Font *policeMenuHIP, SDL_Renderer *zoneAffichage, SDL_Window *fenJeu, t_coordonnee *nuage, t_texte_cache *cache);

/** 
 * @fn void lancerBombeSansHIP(Uint32 *tempsPrecedent, int *bombeLancee, int *nombreRebonds, t_bombe * bombe, t_vect *vectVitesse, t_case matriceTerrain[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], t_joueur *equipe1, t_joueur *equipe2, t_tour *gestionTours, SDL_Rect *rectFen, SDL_Renderer *zoneAffichage, SDL_Texture *texMap);
 * @brief La fonction lance la bombe en appelant toutes les fonctions liées à celle-ci.
 * @author Hannah Sergent
 * @date Crée le 29/03/2026
 * @param tempsPrecedent un pointeur sur le temps précédent
 * @param bombeLancee un pointeur sur une variable indiquant si la bombe est lancée
 * @param nombreRebonds un pointeur sur le nombre de rebonds effectués par la bombe
 * @param bombe un pointeur sur une structure de type bombe
 * @param vectVitesse un pointeur sur le vecteur vitesse de la bombe
 * @param matriceTerrain la matrice contenant les informations sur le terrain
 * @param equipe1 un pointeur sur la structure correspondant aux dinosaures du joueur 1
 * @param equipe2 un pointeur sur la structure correspondant aux dinosaures du joueur 2
 * @param gestionTours un pointeur sur une structure utilisée pour le changement de tour
 * @param rectFen un rectangle de type SDL_Rect contenant les informations sur la fenêtre du jeu
 * @param zoneAffichage un pointeur sur la zone d'affichage
 * @param texMap un pointeur sur la texture de la map
 */

void lancerBombeSansHIP(Uint32 *tempsPrecedent, int *bombeLancee, int *nombreRebonds, t_bombe *bombe, t_vect *vectVitesse, t_case matriceTerrain[HAUTEUR_TERRAIN][LARGEUR_TERRAIN], t_joueur *equipe1, t_joueur *equipe2, t_tour *gestionTours, SDL_Rect *rectFen, SDL_Renderer *zoneAffichage, SDL_Texture *texMap);

/** 
 * @fn void lancerPartieBombe();
 * @brief La fonction lance une partie ne contenant que la fonctionnalité bombe. Elle ouvre une nouvelle fenêtre et appelle successivement toutes les fonctions du jeu liées à la bombe.
 * @author Hannah Sergent
 * @date Crée le 31/03/2026
 * @version 1.0
 */

void lancerPartieBombe();

/** 
 * @fn void lancerPartie();
 * @brief La fonction lance une partie. Elle ouvre une nouvelle fenêtre et appelle successivement toutes les fonctions du jeu.
 * @author Hannah Sergent Romane Saint-Léger Solène Orieux
 * @date Crée le 31/03/2026
 * @version 4.5
 */

void lancerPartie();


#endif