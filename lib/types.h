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
#define TAILLE_DINO 30

/**
 * @enum t_numDino
 * @brief Enumération des différents dinosaures disponibles
*/

typedef enum {DINO1, DINO2, DINO3, DINO4, DINO5, DINO6} t_numDino;

/**
 * @enum t_case
 * @brief Représentation de chaque élément sur la matrice 
*/

typedef enum {EAU=-1, AIR, TERRE, D1, D2,D3,D4,D5,D6,BOMBE} t_case; 

typedef enum {ARC, ARBALETE } t_arme_archer;
typedef enum {FUSIL, REVOLVER } t_arme_feu;
typedef enum {ARME_FEU, ARME_ARCHER} t_type_arme;


/**
 * @struct t_coordonnee
 * @brief Structure de coordonnées entières classiques (pixels)
 * @author Solène Orieux Romane Saint-Léger Hannah Sergent
 * @date Crée le 27/01/2026
 * @version 1.0
*/

typedef struct {
	int x; /**< Position Horizontale */
	int y; /**< Position Verticale */
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

/**
 * @struct t_deplacement
 * @brief Structure regroupant toutes les informations de déplacement d'un dinosaure
 * @author Solène Orieux
 * @date Crée le 14/03/2026
 * @version 1.0
*/

typedef struct {
    int sautBooleen;        /**< Vaut 1 si le dinosaure est en cours de saut */
    int indice_nuage_temp;  /**< Position temporaire dans le prochain nuage */
    float indice_reel;      /**< Pour le déplacement */
    int tab_res[4];         /**< pour les colisions */
    float v_y;              /**< pour les sauts */
    int hors_nuage;         /**<  */
    int wait;               /**< Petite pause pour ne pas sauter deux fois d'un coup*/
    t_coordonnee coteProche[5];      /**< donne le premier et le dernier x de chaque nuage */
} t_deplacement;

/**
 * @struct t_dino
 * @brief Structure regroupant toutes les informations d'un dinosaure
 * @author Solène Orieux Romane Saint-Léger Hannah Sergent
 * @date Crée le 27/01/2026
 * @version 3.0
*/

typedef struct {
    t_numDino d;            /**< Numéro du dinosaure de 0 à 5 */
    t_coordonnee pos;       /**< Position actuelle */
    int id_nuage;           /**< Numéro du nuage */
    int indice_nuage;       /**< Position dans le nuage */
    int largeur, hauteur;   /**< Dimensions du dinosaure */
    int etat;               /**< Vivant ou Mort */
    int pv;                 /**< Points de vie restant */
    int memoire[30][30];    /**< Permet de mémoriser Ce qu'il y avait dans la matrice avant le dino */
    t_deplacement *deplacement;
} t_dino;

/**
 * @struct t_joueur
 * @brief Structure représentant un joueur et son équipe de dinosaure
 * @author Solène Orieux Romane Saint-Léger Hannah Sergent
 * @date Crée le 07/02/2026
 * @version 1.0
*/

typedef struct {
	t_dino * tab;   /**< Tableau de dinosaure */
	int n;          /**< Taille du tableau*/ 
} t_joueur;


/**
 * @struct t_zone_depart
 * @brief  Zone où un dinosaure peut apparaitre
 * @author Romane Saint-Léger
 * @date Crée le 17/02/2026
 * @version 1.2
*/

typedef struct {
    t_coordonnee bas_centre;    /**< Le point de contact avec le sol (issu du nuage de Solène)*/
    int id_equipe;              /**< ID de l'équipe propriétaire (1 ou 2) */
    int indice_nuage;           /**< Retrouver le point dans le tableau */
    int id_nuage;               /**< Savoir quel fichier JPG a généré ce point (numéro du nuage)*/
} t_zone_depart;


/**
 * @struct t_catalogue_zones
 * @brief Structures qui contient les zones des différentes équipes
 * @author Romane Saint-Léger
 * @date Crée le 17/02/2026
 * @version 1.0
*/

typedef struct {
    t_zone_depart zones_E1[10]; /**< 10 zones pour l'équipe 1 */
    t_zone_depart zones_E2[10]; /**< 10 zones pour l'équipe 2 */
} t_catalogue_zones;


/**
 * @struct t_vect
 * @brief 
 * @author Solène Orieux Hannah Sergent
 * @date Crée le 5/02/2026
 * @version 2.3
*/

typedef struct {
	float u;    /**< */
	float v;    /**< */
} t_vect;

/**
 * @struct t_bombe
 * @brief Structure qui contient les coordonnées et le rayon d'une bombe
 * @author Hannah Sergent
 * @date Crée le 17/02/2026
 * @version 2.0
 */

typedef struct {
    t_coordonnee_calcul coor;   /**< */
    int rayon;                  /**< */
} t_bombe;

typedef struct {
    t_type_arme type_general;
    union {
        t_arme_archer archer;
        t_arme_feu feu;
    }sous_type;
    int degats;
    float poids_projectile;
}t_arme;

typedef struct {
    t_coordonnee_calcul pos;
    t_vect velo;
    int actif;
    t_arme arme_source;
}t_tir;



#endif