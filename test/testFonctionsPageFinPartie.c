#include "../lib/fonctionsPageFinPartie.h"

/** 
 * @file testFonctionsPageFinPartie.c
 * @brief Test des fonctions crées dans le fichier fonctionsPageFinPartie.c
 * @author Hannah Sergent
 * @date Crée le 11/04/2026
 * @version 1.0
 */

/**
 * @brief Ouvrir une fenêtre de fin de partie.
 * @param argc nombre d'arguments de la ligne de commande
 * @param argv tableau des arguments
 * @return 0 si tout s'est bien passé
 * @version 1.0
 */

int main(int argc, char *argv[]) {

    /* Variable de changement de tour */
    t_tour gestionTours = {10, 1, D1, D6};

    ouvrirFenFinPartie(&gestionTours);
    
    return 0;
}