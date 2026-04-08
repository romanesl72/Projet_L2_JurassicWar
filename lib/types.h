#ifndef _TYPES_H_
#define _TYPES_H_

#include <SDL2/SDL.h>

/**
 * @file types.h
 * @brief Définition des structures de données pour JurassicWar.
 * @author Solène Orieux Romane Saint-Léger Hannah Sergent
 * @date Crée le 27/01/2026
 * @version 2.0
 */

/**
 * @def LARGEUR_TERRAIN
 * @brief Largeur du terrain, de la matrice et de la fenêtre.
*/

#define LARGEUR_TERRAIN 1300

/**
 * @def HAUTEUR_TERRAIN
 * @brief Hauteur du terrain, de la matrice et de la fenêtre.
*/

#define HAUTEUR_TERRAIN 700

#define HAUTEUR_HIP 100
#define HAUTEUR_FEN_JEU_HIP (HAUTEUR_HIP + HAUTEUR_TERRAIN)

#define MAT_H 700  
#define MAT_L 1300

#define TIMER 70000

/**
 * @def TAILLE_DINO
 * @brief Taille de l'image dinosaure.
*/

#define TAILLE_DINO 30

/**
 * @def NOMBRE_DINOS
 * @brief Nombre de dinosaures dans le jeu.
*/

#define NOMBRE_DINOS 6

/**
 * @enum t_case
 * @brief Représentation de chaque élément sur la matrice.
 * @author Solène Orieux Romane Saint-Léger Hannah Sergent
 * @date Crée le 27/01/2026
 * @version 1.0
*/

typedef enum {
    EAU=-1, /**< Valeur représentant l'eau */
    AIR,    /**< Valeur représentant l'air */
    TERRE,  /**< Valeur représentant la terre */
    D1,     /**< Dinosaure numéro 1 */
    D2,     /**< Dinosaure numéro 2 */
    D3,     /**< Dinosaure numéro 3 */
    D4,     /**< Dinosaure numéro 4 */
    D5,     /**< Dinosaure numéro 5 */
    D6      /**< Dinosaure numéro 6 */
} t_case; 

/**
 * @enum t_nom_arme
 * @brief Toutes les armes utilisées hormis la bombe.
 * @author Romane Saint-Léger
 * @date Crée le 07/03/2026
 * @version 1.3
*/

typedef enum {ARC, ARBALETE, FUSIL, REVOLVER } t_nom_arme;

/**
 * @enum t_cote
 * @brief Indique la direction dans laquelle pointe les dinosaures ou les armes.
 * @author Hannah Sergent
 * @date Crée le 24/03/2026
 * @version 1.0
*/

typedef enum {
    GAUCHE,     /**< Direction gauche */
    DROITE,     /**< Direction droite */
    SANS_DIR    /**< Aucune direction */
} t_cote;

/**
 * @struct t_coordonnee
 * @brief Structure de coordonnées entières classiques (pixels).
 * @author Solène Orieux Romane Saint-Léger Hannah Sergent
 * @date Crée le 27/01/2026
 * @version 1.0
*/

typedef struct {
	int x;      /**< Position horizontale */
	int y;      /**< Position verticale */
} t_coordonnee;

/**
 * @struct t_coordonnee_calcul
 * @brief Structure qui contient des coordonnées flottantes pour ne pas perdre de précision dans les calculs.
 * @author Hannah Sergent
 * @date Crée le 2/03/2026
 * @version 1.0
 */

typedef struct {
	float x;    /**< Position horizontale flottante */
	float y;    /**< Position verticale flottante */
} t_coordonnee_calcul;

/**
 * @struct t_deplacement
 * @brief Structure regroupant toutes les informations de déplacement d'un dinosaure.
 * @author Solène Orieux
 * @date Crée le 14/03/2026
 * @version 1.0
*/

typedef struct {
    int sautBooleen;            /**< Vaut 1 si le dinosaure est en cours de saut */
    int tomber;                 /**< Vaut 0 si le dinosaure ne tombe pas, 1 si il vient tout juste de tomber et 2 si il tombe */
    int id_nuage_temp;          /**< prochain nuage */
    int indice_nuage_temp;      /**< Position temporaire dans le prochain nuage */
    float indice_reel;          /**< Pour le déplacement */
    int tab_res[4];             /**< pour les colisions */
    float v_y;                  /**< force du saut*/
    int hors_nuage;             /**< Vaut 1 si le dinosaure est en dehors du nuage, 0 sinon*/
    int wait;                   /**< Petite pause pour ne pas sauter deux fois d'un coup*/
    int taille_nuage[5];        /**< donne la taille de chaque nuage */
    int sens;                   /**< donne le sens de déplacement 1 à droite et -1 à gauche */
    t_coordonnee coteProche[5]; /**< donne le premier et le dernier x de chaque nuage */
} t_deplacement;

/**
 * @struct t_dino
 * @brief Structure regroupant toutes les informations d'un dinosaure.
 * @author Solène Orieux Romane Saint-Léger Hannah Sergent
 * @date Crée le 27/01/2026
 * @version 3.0
*/

typedef struct {
    t_case d;                   /**< Numéro du dinosaure de 2 à 7 */
    t_coordonnee pos;           /**< Position actuelle */
    int id_nuage;               /**< Numéro du nuage */
    int indice_nuage;           /**< Position dans le nuage */
    int largeur, hauteur;       /**< Dimensions du dinosaure */
    int etat;                   /**< Vivant ou Mort */
    int pv;                     /**< Points de vie restant */
    int memoire[30][30];        /**< Permet de mémoriser Ce qu'il y avait dans la matrice avant le dino */
    t_deplacement *deplacement; /**< Contient toutes les infos utiles au déplacements */
} t_dino;

/**
 * @struct t_joueur
 * @brief Structure représentant un joueur et son équipe de dinosaure.
 * @author Solène Orieux Romane Saint-Léger Hannah Sergent
 * @date Crée le 07/02/2026
 * @version 2.0
*/

typedef struct {
	t_dino *tab;                /**< Tableau de dinosaures */
    SDL_Texture **texDinos;     /**< Tableau contenant les images des dinosaures */
    SDL_Texture **texDinosInv;  /**< Tableau contenant les images des dinosaures dans le sens inverse */
    t_cote *tabCote;            /**< Tableau contenant la direction du dinosaure à l'instant t */
	int n;                      /**< Taille des tableaux*/ 
} t_joueur;

/**
 * @struct t_tour
 * @brief Structure représentant la gestion des tours.
 * @author Hannah Sergent
 * @date Crée le 24/03∕2026
 * @version 1.0
*/

typedef struct {
    int numeroTour;         /**< Numéro du tour en train de se produire */
    int equipeCourante;     /**< Numéro de l'équipe à qui c'est le tour de jouer */
    t_case dinoCourant;     /**< Numéro du dinosaure qui peut d'agir */
    t_case dinoPrecedent;   /**< Numéro du dinosaure qui a fait une action au tour précédent */
} t_tour;

/**
 * @struct t_zone_depart
 * @brief  Zone où un dinosaure peut apparaitre.
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
 * @brief Structures qui contiennent les zones des différentes équipes.
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
 * @brief Une structure représentant un vecteur de R carré.
 * @author Solène Orieux Hannah Sergent
 * @date Crée le 5/02/2026
 * @version 2.3
*/

typedef struct {
	float u;    /**< Première coordonnée du vecteur */
	float v;    /**< Deuxième coordonnée du vecteur */
} t_vect;

/**
 * @struct t_bombe
 * @brief Structure qui contient les coordonnées et le rayon d'une bombe.
 * @author Hannah Sergent
 * @date Crée le 17/02/2026
 * @version 2.0
 */

typedef struct {
    t_coordonnee_calcul coor;   /**< Les coordonnées flottantes de la bombe */
    int rayon;                  /**< Le rayon de la bombe */
} t_bombe;

/**
 * @struct t_arme
 * @brief Caractéristiques de chaque arme.
 * @author Romane Saint-Léger
 * @date Crée le 7/03/2026
 * @version 1.3
*/

typedef struct {
    t_nom_arme nom;             /**< Nom de l'arme utilisée */
    int degats;                 /**< Dégats effectués par l'arme */
    float poids_projectile;     /**< Poids de l'arme, influence sa courbe (gravité) */
    float puissance_propulsion; /**< Vitesse de base */
    float vitesse_max;          /**< Vitesse Maximale */
}t_arme;

/**
 * @struct t_tir
 * @brief Données nécessaires pour calculer un tir.
 * @author Romane Saint-Léger
 * @date Crée le 7/03/2026
 * @version 1.0
*/

typedef struct {
    t_coordonnee_calcul pos;    /**< Position du projectile en cours */
    t_vect velo;                /**< Vecteur correspondant au projectile */
    t_arme arme_source;         /**< Arme utilisé pour le tir */
    int actif;                  /**< Si le tir est en cours ou pas */
}t_tir;

/**
 * @struct t_element_file
 * @brief élement d'une file.
 * @author Solène Orieux
 * @date Crée le 25/03/2026
 * @version 1.0
*/

typedef struct element{
	t_coordonnee *coordonnee; /**< coordonnée (x,y) */
	struct element* suivant;  /**< élément suivant de la file */
} t_element_file;


#endif