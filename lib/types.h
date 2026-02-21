#ifndef _TYPES_H_
#define _TYPES_H_


#define MAT_H 700  
#define MAT_L 1300
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
    t_numDino d; //Numéro de 0 à 5
    t_coordonnee pos;
    int indice_nuage;
    int id_nuage;
    int largeur, hauteur;
    int etat;
    int pv;
} t_dino;

typedef struct {
	t_dino * tab;
	int n; // taille du tableau
} t_joueur;


typedef struct {
    t_coordonnee bas_centre; // Le point de contact avec le sol (issu du nuage de Solène)
    int id_equipe;           // 1 ou 2
    int indice_nuage;   // Retrouver le point dans le tableau
    int id_nuage;    // Savoir quel fichier JPG a généré ce point
} t_zone_depart;

typedef struct {
    t_zone_depart zones_E1[10]; // 10 zones pour équipe 1
    t_zone_depart zones_E2[10]; // 10 zones pour équipe 2
} t_catalogue_zones;


typedef struct {
	float u;
	float v;
} t_vect;

typedef struct {
    t_coordonnee coor;
    int rayon;
} t_bombe;


/*Pour utiliser les nuages de points :
Soit faire un tableau soit une structure, voici le tableau
t_coordonnee *tous_les_nuages[3];
tous_les_nuages[1] = nuage_de_points(..., "img/test1_c.jpg");
tous_les_nuages[2] = nuage_de_points(..., "img/test2_c.jpg");*/

#endif