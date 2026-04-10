#include "../lib/fonctionsPagesInformations.h"

/** 
 * @file testFonctionsPagesInformations.c
 * @brief Test des fonctions crées dans le fichier fonctionsPagesInformations.c
 * @author Hannah Sergent
 * @date Crée le 01/04/2026
 * @version 1.0
 */

/**
 * @brief Ouvrir une page d'information avec la liste des touches.
 * @param argc nombre d'arguments de la ligne de commande
 * @param argv tableau des arguments
 * @return 0 si tout s'est bien passé
 * @version 1.0
 */

int main(int argc, char *argv[]) {
    /* ouvrirFenInfos("Principales Règles du jeu","../res/reglesJeu.txt"); */
    ouvrirFenInfos("Liste des touches","../res/listeTouches.txt");
    return 0;
}