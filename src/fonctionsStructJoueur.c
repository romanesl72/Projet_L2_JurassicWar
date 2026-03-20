#include "../lib/fonctionsStructJoueur.h"
#include <stdio.h>

/** 
 * @file fonctionsStructJoueur.c
 * @brief Corps des fonctions liées à la structure joueur
 * @author Hannah Sergent
 * @date Crée le 18/03/2026
 */

/** 
 * @fn int rechercherDino(t_joueur * equipe, t_case numero);
 * @brief La fonction recherche si le dinosaure fait partie de l'équipe equipe à partir de son identifiant.
 * @author Hannah Sergent
 * @date Crée le 19/03/2026
 * @param equipe une structure correspondant aux dinosaures de l'équipe equipe
 * @param numero l'identifiant du dinosaure recherché
 * @return l'identifiant du dinosaure s'il a été trouvé et -1 sinon
 */

int rechercherDino(t_joueur * equipe, t_case numero){

    int i;

    for(i = 0; i < equipe->n; i++){
        if (equipe->tab[i].d == numero){
            return i;
        }
    }
    return -1;
}

t_dino * recupererDinoNumero(t_joueur * equipe1, t_joueur * equipe2, t_case numero){
    /* Le numéro du dinosaure est compris entre 2 et 7 */

    int indiceDino = rechercherDino(equipe1, numero);

    if (indiceDino != -1){
        return &(equipe1->tab[indiceDino]);
    }

    indiceDino = rechercherDino(equipe2, numero);

    if (indiceDino != -1){
        return &(equipe2->tab[indiceDino]);
    }

    /* Renvoie un pointeur nul si le dinosaure n'a pas été trouvé */

    else {
        return NULL;
    }
}

void supprimerDinoJoueur(t_joueur * equipe1, t_joueur * equipe2, t_case numero){

    int i;
    int indiceDino;

    /* On vérifie que les équipes de dinosaures ne sont pas vides */

    if ((equipe1->n > 0) && (equipe2->n > 0)){

        /* Recherche du dinosaure dans l'équipe 1*/

        indiceDino = rechercherDino(equipe1, numero);

        if (indiceDino != -1){

            /* Suppression du dinosaure dans l'équipe 1*/

            for(i = indiceDino; i < (equipe1->n - 1); i++){
                equipe1->tab[i] = equipe1->tab[i+1];
                equipe1->texDinos[i] = equipe1->texDinos[i+1];
            }
            equipe1->n --;
        }
        else {

            /* Recherche du dinosaure dans l'équipe 2*/

            indiceDino = rechercherDino(equipe2, numero);

            if (indiceDino != -1){

                /* Suppression du dinosaure dans l'équipe 2*/
                
                for(i = indiceDino; i < (equipe2->n - 1); i++){
                    equipe2->tab[i] = equipe2->tab[i+1];
                    equipe2->texDinos[i] = equipe2->texDinos[i+1];
                }
                equipe2->n --;
            }
        }

    }
}

void initialiserContenuJoueur(t_joueur *joueur){

    joueur->n = NOMBRE_DINOS/2;
    joueur->tab = malloc(sizeof(t_dino) * joueur->n);
    joueur->texDinos = malloc(sizeof(SDL_Texture *) * joueur->n);

}

void detruireContenuJoueur(t_joueur *joueur){

    int i;

    free(joueur->tab);

    for(i=0; i<NOMBRE_DINOS/2; i++) {
        SDL_DestroyTexture(joueur->texDinos[i]);
    }
    free(joueur->texDinos);

}