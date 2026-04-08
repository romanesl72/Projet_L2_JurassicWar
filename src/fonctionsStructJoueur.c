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

t_cote recupererDinoDirection(t_joueur * equipe1, t_joueur * equipe2, t_case numero){
    /* Le numéro du dinosaure est compris entre 2 et 7 */

    int indiceDino = rechercherDino(equipe1, numero);

    if (indiceDino != -1){
        return equipe1->tabCote[indiceDino];
    }

    indiceDino = rechercherDino(equipe2, numero);

    if (indiceDino != -1){
        return equipe2->tabCote[indiceDino];
    }
    return SANS_DIR;
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
                equipe1->texDinosInv[i] = equipe1->texDinosInv[i+1];
                equipe1->tabCote[i] = equipe1->tabCote[i+1];
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
                    equipe2->texDinosInv[i] = equipe2->texDinosInv[i+1];
                    equipe2->tabCote[i] = equipe2->tabCote[i+1];
                }
                equipe2->n --;
            }
        }

    }
}

/** 
 * @fn void echangerImgDino(t_joueur * equipe, int indiceDino);
 * @brief La fonction échange deux images situées dans les deux tableaux d'images de la structure joueur.
 * @author Hannah Sergent
 * @date Crée le 28/03/2026
 * @param equipe un pointeur sur une structure de type joueur
 * @param indiceDino l'indice dans le tableau d'images de l'image à échanger
 */

void echangerImgDino(t_joueur * equipe, int indiceDino){

    SDL_Texture * imgTemp;

    imgTemp = equipe->texDinos[indiceDino];
    equipe->texDinos[indiceDino] = equipe->texDinosInv[indiceDino];
    equipe->texDinosInv[indiceDino] = imgTemp;

}

/** 
 * @fn void echangerCoteDino(t_joueur * equipe, int indiceDino);
 * @brief La fonction échange la direction du dinosaure d'indice indiceDino dans le tableau contenant la direction des dinosaures.
 * @author Hannah Sergent
 * @date Crée le 28/03/2026
 * @param equipe un pointeur sur une structure de type joueur
 * @param indiceDino l'indice dans le tableau de direction de la direction à échanger
 */

void echangerCoteDino(t_joueur * equipe, int indiceDino){

    if (equipe->tabCote[indiceDino] == GAUCHE){
        equipe->tabCote[indiceDino] = DROITE;
    }
    else {
        equipe->tabCote[indiceDino] = GAUCHE;
    }
}

void retournerDino(t_joueur * equipe1, t_joueur * equipe2, t_case numero, t_cote cote, t_cote *ancienCote){

    int indiceDino;

    if (cote != *ancienCote) {
        *ancienCote = cote;

        indiceDino = rechercherDino(equipe1, numero);

        if (indiceDino != -1){
            echangerImgDino(equipe1, indiceDino);
            echangerCoteDino(equipe1, indiceDino);
        }
        else {
            indiceDino = rechercherDino(equipe2, numero);
            echangerImgDino(equipe2, indiceDino);
            echangerCoteDino(equipe2, indiceDino);
        }
    }
}

void initialiserContenuJoueur(t_joueur *joueur){

    int i;

    joueur->n = NOMBRE_DINOS/2;
    joueur->tab = malloc(sizeof(t_dino) * joueur->n);
    joueur->texDinos = malloc(sizeof(SDL_Texture *) * joueur->n);
    joueur->texDinosInv = malloc(sizeof(SDL_Texture *) * joueur->n);
    joueur->tabCote = malloc(sizeof(t_cote) * joueur->n);

    for(i = 0; i < joueur->n; i++) {

        /* Initialisation du côté */
        joueur->tabCote[i] = DROITE;
        
        // ALLOCATION CRUCIALE
        joueur->tab[i].deplacement = malloc(sizeof(t_deplacement));
        
        // Initialisation des valeurs par défaut pour éviter les comportements erratiques
        joueur->tab[i].deplacement->sautBooleen = 0;
        joueur->tab[i].deplacement->tomber = 0;
        joueur->tab[i].deplacement->wait = 0;
        joueur->tab[i].deplacement->indice_reel = 0;
        joueur->tab[i].deplacement->sens = DROITE;
        joueur->tab[i].etat = 1; // Vivant
        joueur->tab[i].pv = 100;
    }

}

void detruireContenuJoueur(t_joueur *joueur) {
    int i;
    for(i = 0; i < joueur->n; i++) {

        free(joueur->tab[i].deplacement); // Libère le malloc du déplacement */
        SDL_DestroyTexture(joueur->texDinos[i]);
        SDL_DestroyTexture(joueur->texDinosInv[i]);
    }
    free(joueur->tab);
    free(joueur->texDinos);
    free(joueur->texDinosInv);
    free(joueur->tabCote);
}