#ifndef _TYPES_H_
#define _TYPES_H_


#define MAT_H 800  
#define MAT_L 1500
#define VIDE 0


/**
 * @file types.h
 * @brief Définition des structures de données pour Jurassic War.
 */

typedef enum {FUSIL, REVOLVER} t_pistolet;
typedef enum {DINO1, DINO2, DINO3, DINO4, DINO5, DINO6} t_numDino;

typedef enum {EAU=-1, AIR, TERRE, D1, D2,D3,D4,D5,D6,BOMBE} t_case; //représentation de chaque élément sur la matrice 

typedef struct {
	int x;
	int y;
} t_coordonnee;

typedef struct {
    t_numDino d;
    int etat;
    int pv;
    t_coordonnee pos;
    int largeur, hauteur;
} t_dino;

typedef struct {
	t_dino * tab;
	int n; // taille du tableau
} t_joueur;


typedef struct {
	float u;
	float v;
} t_vect;

typedef struct {
    t_coordonnee coor;
    int rayon;
} t_bombe;

#endif