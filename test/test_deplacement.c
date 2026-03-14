#include <stdio.h>
#include <stdlib.h>
#include "../lib/deplacement.h"
//utile pour l'affichage de la fenêtre
#include <SDL2/SDL.h>

#define LARGEUR_FEN_JEU 1300
#define HAUTEUR_FEN_JEU 700

#define LARGEUR_FEN_MENU 400
#define HAUTEUR_FEN_MENU 650


int main(){

    int enCours;
    int matrice[MAT_H][MAT_L];
    int w, h;

    int nb_pts;
    
    t_dino *dino=NULL;

    char *nomNuage[] = {"../img/test1_c.jpg", "../img/test2_c.jpg"};

    t_coordonnee *nuage1=NULL; 
    t_coordonnee *nuage2=NULL;
    t_coordonnee *nuage=NULL;

    if(!init_deplacement(&dino, &nb_pts, matrice, nomNuage, &nuage, 2, &nuage1, &nuage2))return 1;

    
    dino->largeur = 30; // Correspond à la taille de votre rect d'affichage
    dino->hauteur = 30;

    if (initialisationCorrecte()) {

        enCours = 1;
        SDL_Event evenement;
        SDL_Window *menuPrincipal; 
        SDL_Renderer *rendu;
        
        creerFenetre(&menuPrincipal, "Page du Jeu", LARGEUR_FEN_JEU, HAUTEUR_FEN_JEU);
        //rendu = SDL_CreateRenderer(menuPrincipal, -1, SDL_RENDERER_ACCELERATED);
        rendu = SDL_CreateRenderer(menuPrincipal, -1, SDL_RENDERER_SOFTWARE);

        

        printf("Chargement de la texture map...\n");
        SDL_Texture *texMap;
        chargerImage(rendu, &texMap, "../img/test1_b.jpg", &w, &h);
        if (texMap == NULL) {
            printf("ERREUR : Impossible de charger l'image de la map\n");
            return 0;
        } else {
            printf("Texture map chargee avec succes !\n");
        }

        /* Charger les images (Textures) */
        SDL_Texture *texDino;
        chargerImage(rendu, &texDino, "../img/dino_test.png", &w, &h);
        
        while(enCours) {
            while (SDL_PollEvent(&evenement)){
                if (evenement.type == SDL_QUIT){
                    enCours = 0;
                }
            }
            SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255);
            SDL_RenderClear(rendu);

            /* --- AFFICHAGE DE LA MAP --- */
            SDL_Rect rect_plein_ecran = {0, 0, LARGEUR_FEN_JEU, HAUTEUR_FEN_JEU};
            SDL_RenderCopy(rendu, texMap, NULL, &rect_plein_ecran);
            
            /* --- AFFICHAGE DU DINO*/
            SDL_Rect r = {dino->pos.x,dino->pos.y, 30, 30};
            SDL_RenderCopy(rendu, texDino, NULL, &r);
            
            // 2. Gérer les entrées clavier pour le mouvement
            const Uint8 *state = SDL_GetKeyboardState(NULL);

            saut(dino,nuage,nb_pts,matrice,state);

            if ((!dino->deplacement->sautBooleen) && (!dino->deplacement->hors_nuage))
            {
                gauche(dino,nuage,nb_pts,matrice,state);
                droite(dino,nuage,nb_pts,matrice,state);
            }
            
            if (dino->deplacement->wait>0){
                dino->deplacement->wait-=1;
            }
            
            if ((dino->pv<=0) || (nuage==NULL)){
                enCours=0;
            }
            
            SDL_RenderPresent(rendu);
        }

        /* --- NETTOYAGE --- */
        SDL_DestroyTexture(texDino);
        if(nuageExiste(nuage))nuageDetruire(&nuage);
        if(nuageExiste(nuage1))nuageDetruire(&nuage1);
        if(nuageExiste(nuage2))nuageDetruire(&nuage2);

        free(dino->deplacement);
        dino->deplacement=NULL;
        free(dino);
        SDL_DestroyTexture(texMap);
        
        SDL_DestroyRenderer(rendu);
        SDL_DestroyWindow(menuPrincipal);
        IMG_Quit();
        TTF_Quit();
        SDL_Quit();

        return 0;
    }
    return 1;
}
