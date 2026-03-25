// Mise en oeuvre d'une file d'entiers par pointeurs

#include<stdlib.h>
#include "types.h"
#include "tda_file.h"

typedef struct element{
	int nombre; 
	struct element* suivant;
} t_element_file;

t_element_file* tete;
t_element_file* queue;

void initfile(void){
// initialise la file
	tete = NULL;
	queue = NULL;
}

int filevide(void){
// vrai si la file est vide, faux sinon
	return tete == NULL;
}

void ajouter(int v){
// ajoute l'entier v en queue de file
	t_element_file* nouv;

	nouv = malloc(sizeof(t_element_file));
	nouv->nombre = v;
	nouv->suivant = NULL;
	if(filevide())
		tete = nouv;
	else
		queue->suivant = nouv;
	queue = nouv;
}

void retirer(int* v){
// retire l'entier v de la tete de la file
	t_element_file* premier;

	if(!filevide()){
		premier = tete;
		*v = premier->nombre;
		tete = premier->suivant;
		free(premier);
	}
}


