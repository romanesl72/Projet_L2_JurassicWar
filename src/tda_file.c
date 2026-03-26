#include <stdlib.h>
#include "../lib/types.h"
#include "../lib/tda_file.h"

// Utilisation de static pour encapsuler les variables dans ce fichier
static t_element_file* tete = NULL;
static t_element_file* queue = NULL;

void initfile(void) {
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