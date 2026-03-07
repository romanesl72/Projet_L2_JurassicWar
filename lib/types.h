#ifndef _TYPES_H_
#define _TYPES_H_

/**
 * @file types.h
 * @brief Définition des structures de données pour Jurassic War.
 * @author Solène Orieux Romane Saint-Léger Hannah Sergent
 */

/* Variables globales communes à la matrice et aux fenetres à utiliser*/
#define LARGEUR_TERRAIN 1300
#define HAUTEUR_TERRAIN 700

#define MAT_H 700  
#define MAT_L 1300
#define VIDE 0



typedef enum {FUSIL, REVOLVER} t_pistolet;
typedef enum {DINO1, DINO2, DINO3, DINO4, DINO5, DINO6} t_numDino;

typedef enum {EAU=-1, AIR, TERRE, D1, D2,D3,D4,D5,D6,BOMBE} t_case; //représentation de chaque élément sur la matrice 

typedef struct {
	int x;
	int y;
} t_coordonnee;

/**
 * @struct t_coordonnee_calcul
 * @brief Structure qui contient des coordonnées flottantes pour ne pas perdre de précision dans les calculs
 * @author Hannah Sergent
 * @date Crée le 2/03/2026
 * @version 1.0
 */

typedef struct {
	float x;
	float y;
} t_coordonnee_calcul;

typedef struct {
    t_numDino d; //Numéro de 0 à 5
    t_coordonnee pos;
    t_coordonnee sol;//enregistre coordonnée où le dino doit atterrir quand il saute
    int sautBooleen;
    int indice_nuage;
    float indice_reel; //pour le déplacement
    int id_nuage;
    int largeur, hauteur;
    int etat;
    int pv;
    int tab_res[4];//pour les colisions
    float v_y;//pour les sauts
    int memoire[30][30];
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

/**
 * @struct t_bombe
 * @brief Structure qui contient les coordonnées et le rayon d'une bombe
 * @author Hannah Sergent
 * @date Crée le 17/02/2026
 * @version 2.0
 */

typedef struct {
    t_coordonnee_calcul coor;
    int rayon;
} t_bombe;

/*Pour utiliser les nuages de points :
Soit faire un tableau soit une structure, voici le tableau
t_coordonnee *tous_les_nuages[3];
tous_les_nuages[1] = nuage_de_points(..., "img/test1_c.jpg");
tous_les_nuages[2] = nuage_de_points(..., "img/test2_c.jpg");*/

#endif