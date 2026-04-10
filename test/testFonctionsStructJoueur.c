#include "../lib/chargerMatrice.h"
#include "../lib/fonctionsStructJoueur.h"
#include "../lib/placer_dinos.h"

#include <assert.h>
#include <stdio.h>

/** 
 * @file testFonctionsStructJoueur.c
 * @brief Test des fonctions crées dans le fichier fonctionsStructJoueur.c.
 * @author Hannah Sergent
 * @date Crée le 10/04/2026
 * @version 1.0
 */

/**
 * @brief Cas de tests de la fonction recupererDinoNumero.
 * @param argc Nombre d'arguments de la ligne de commande
 * @param argv Tableau des arguments
 * @return 0 si tout s'est bien passé
 * @version 1.0
 */

int main(int argc, char * argv[]){

    /* Initialisations */
    int i;
    t_joueur equipe1, equipe2;
    t_joueur equipe1Vide, equipe2Vide;
    t_catalogue_zones catalogue;
    t_case (*matriceTerrain)[LARGEUR_TERRAIN] = NULL;
    initialiserMatrice(&matriceTerrain);
    initialiserContenuJoueur(&equipe1);
    initialiserContenuJoueur(&equipe2);
    placer_une_equipe(&equipe1, catalogue.zones_E1, matriceTerrain, D1);
    placer_une_equipe(&equipe2, catalogue.zones_E2, matriceTerrain, D4);

    /* Dinosaure trouvé dans l'équipe 1*/
    assert(recupererDinoNumero(&equipe1, &equipe2, D2) == &(equipe1.tab[1]));

    /* Dinosaure trouvé dans l'équipe 2*/
    assert(recupererDinoNumero(&equipe1, &equipe2, D4) == &(equipe2.tab[0]));

    /* Dinosaure présent dans les deux équipes */
    equipe2.tab[0].d = D1;
    assert(recupererDinoNumero(&equipe1, &equipe2, D1) == &(equipe1.tab[0]));
    equipe2.tab[0].d = D4;

    /* Dinosaure deux fois présent dans le même tableau */
    equipe1.tab[1].d = D3;
    assert(recupererDinoNumero(&equipe1, &equipe2, D3) == &(equipe1.tab[1]));
    equipe1.tab[1].d = D2;

    /* Dinosaure absent des deux équipes */
    equipe2.tab[0].d = D1;
    assert(recupererDinoNumero(&equipe1, &equipe2, D4) == NULL);
    equipe2.tab[0].d = D4;

    /* Numéro valant EAU, AIR, TERRE */
    assert(recupererDinoNumero(&equipe1, &equipe2, EAU) == NULL);
    assert(recupererDinoNumero(&equipe1, &equipe2, AIR) == NULL);
    assert(recupererDinoNumero(&equipe1, &equipe2, TERRE) == NULL);

    /* Numéro strictement supérieur à 7 */
    assert(recupererDinoNumero(&equipe1, &equipe2, 8) == NULL);
  
    /* L'équipe 1 vide */
    equipe1Vide.tab = NULL;
    equipe1Vide.n = 0;
    assert(recupererDinoNumero(&equipe1Vide, &equipe2, D2) == NULL);
    assert(recupererDinoNumero(&equipe1Vide, &equipe2, D6) == &(equipe2.tab[2]));

    /* L'équipe 2 vide */
    equipe2Vide.tab = NULL;
    equipe2Vide.n = 0;
    assert(recupererDinoNumero(&equipe1, &equipe2Vide, D4) == NULL);
    assert(recupererDinoNumero(&equipe1, &equipe2Vide, D2) == &(equipe1.tab[1]));

    /* Les deux équipes vides */
    for (i = 0; i < NOMBRE_DINOS/2; i++){
        free(equipe1.tab[i].deplacement);
        free(equipe2.tab[i].deplacement);
    }
    free(equipe1.tab);
    free(equipe2.tab);
    equipe1.tab = NULL;
    equipe1.n = 0;
    equipe2.tab = NULL;
    equipe2.n = 0;
    assert(recupererDinoNumero(&equipe1, &equipe2, D2) == NULL);

    /* Destructions */
    detruireContenuJoueur(&equipe1);
    detruireContenuJoueur(&equipe2);
    detruireMatrice(&matriceTerrain);

    return 0;

}