#include <stdlib.h>
#include "../lib/types.h"
#include "../lib/fonctionsVerification.h"
#include "../lib/tda_file.h"

// Utilisation de static pour encapsuler les variables dans ce fichier
t_element_file* tete = NULL;
t_element_file* queue = NULL;

void initfile(void) {
    detruireFile();
    tete = NULL;
    queue = NULL;
}

int filevide(void) {
    return tete == NULL;
}

void ajouter(t_coordonnee v) {
    t_element_file* nouv = malloc(sizeof(t_element_file));
    if (nouv == NULL) return; // Sécurité allocation

    // On alloue et on COPIE la valeur pour être autonome
    nouv->coordonnee = malloc(sizeof(t_coordonnee));
    *(nouv->coordonnee) = v; 
    nouv->suivant = NULL;

    if (filevide()) {
        tete = nouv;
    } else {
        queue->suivant = nouv;
    }
    queue = nouv;
}

void retirer(t_coordonnee *v) {
    if (!filevide()) {
        t_element_file* a_supprimer = tete;
        
        // Copie la donnée vers la sortie
        *v = *(a_supprimer->coordonnee);
        
        tete = tete->suivant;
        if (tete == NULL) {
            queue = NULL;
        }

        free(a_supprimer->coordonnee);
        free(a_supprimer);
    }
}

t_coordonnee *lire(){
    if(!filevide())return tete->coordonnee;
    return NULL;
}

void detruireFile() {
    t_element_file* courant = tete;
    t_element_file* a_supprimer;

    while (courant != NULL) {
        a_supprimer = courant;
        courant = courant->suivant;

        if (a_supprimer->coordonnee != NULL) {
            free(a_supprimer->coordonnee);
        }
        free(a_supprimer);
    }

    tete = NULL;
    queue = NULL;
}

int afficherFile(SDL_Renderer *rendu){
    if(filevide())return 1;
    t_element_file *elem_courant=tete;
    
    while (elem_courant!=NULL){
        SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255);
        // Ajout de HAUTEUR_HIP pour l'affichage écran par rapport à la matrice
        SDL_RenderDrawLine(rendu, (int)queue->coordonnee->x, (int)queue->coordonnee->y+HAUTEUR_HIP, elem_courant->coordonnee->x,  elem_courant->coordonnee->y+HAUTEUR_HIP);
        SDL_RenderPresent(rendu);
        SDL_Delay(2);
        elem_courant=elem_courant->suivant;
    }
    return 0;
}

t_coordonnee *lireTete(){
    if(!filevide())return tete->coordonnee;
}