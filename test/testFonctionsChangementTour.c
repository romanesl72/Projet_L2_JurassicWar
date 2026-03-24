#include "../lib/chargerMatrice.h"
#include "../lib/fonctionsChangementTour.h"
#include "../lib/fonctionsStructJoueur.h"
#include "../lib/placer_dinos.h"

#include <stdio.h>

/** 
 * @file testFonctionsChangementTour.c
 * @brief test des fonctions crées dans le fichier fonctionsChangementTour.c
 * @author Hannah Sergent
 * @date Crée le 20/03/2026
 */

int main(int argc, char * argv[]){

    int i;

    t_tour tour = {1, 1, D1, D6};

    printf("Valeur initiale de numeroTour : %d \n", tour.numeroTour);
    printf("Valeur initiale de equipeCourante : %d \n", tour.equipeCourante);
    printf("Valeur initiale de dinoTour : %d \n\n", tour.dinoCourant);

    t_catalogue_zones catalogue;

    t_joueur equipe1, equipe2;

    t_case (*matriceTerrain)[LARGEUR_TERRAIN] = NULL;
    initialiserMatrice(&matriceTerrain);

    initialiserContenuJoueur(&equipe1);
    initialiserContenuJoueur(&equipe2);

    /* Placer les dinos sur la matrice */
    /* Équipe 1 (IDs matrice 3, 4, 5) */
    placer_une_equipe(&equipe1, catalogue.zones_E1, matriceTerrain, D1);
    /* Équipe 2 (IDs matrice 6, 7, 8) */
    placer_une_equipe(&equipe2, catalogue.zones_E2, matriceTerrain, D4);

    printf("C'est au tour du dino numéroté %d dans la matrice de jouer. Il appartient à l'équipe %d.\n", tour.dinoCourant, tour.equipeCourante);

    for (i = 1; i < 2*NOMBRE_DINOS; i++){
        /* tourSuivant(&numeroTour, &equipeCourante, &dinoTour, &equipe1, &equipe2); */
        tourSuivant(&tour, &equipe1, &equipe2);
        /*
        printf("Passage au tour numéro %d \n", numeroTour);
        printf("C'est au tour du dino numéroté %d dans la matrice de jouer. Il appartient à l'équipe %d.\n", dinoTour, equipeCourante);*/
        printf("Passage au tour numéro %d \n", tour.numeroTour);
        printf("C'est au tour du dino numéroté %d dans la matrice de jouer. Il appartient à l'équipe %d.\n", tour.dinoCourant, tour.equipeCourante);
    }


}