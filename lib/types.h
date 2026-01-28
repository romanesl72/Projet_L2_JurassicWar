#ifndef _TYPES_H_
#define _TYPES_H_

typedef enum {FUSIL, REVOLVER} t_pistolet;
typedef enum {DINO1, DINO2, DINO3, DINO4, DINO5, DINO6} t_numDino;

typedef struct {
	t_numDino d;
	int etat;
	int pv;
} t_dino;

typedef struct {
	t_dino * tab;
	int n; // taille du tableau
} t_joueur;

typedef struct {
	int x;
	int y;
} t_coordonnee;

#endif