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

    t_dino *dino=malloc(sizeof(t_dino));
    int nb_pts;
    float a,b,angle;
    float pas;
    t_coordonnee *nuage=NULL; 

    printf("tapez 1 ou 0 pour choisir le nuage");
    scanf("%d",&dino->id_nuage);

    if(dino->id_nuage==0){
        nuage=nuage_de_points(&nb_pts,"../img/test1_c.jpg");
    }
    else{
        nuage=nuage_de_points(&nb_pts,"../img/test2_c.jpg");
    }

    if(nuage==NULL)return 1;

    dino->pos=nuage[150];
    dino->indice_nuage=150;
    dino->indice_reel=(float)dino->indice_nuage;
    remplir_matrice_dino(dino, dino->pos, matrice);


    if (initialisationCorrecte()) {

        enCours = 1;
        SDL_Event evenement;
        SDL_Window *menuPrincipal; 
        SDL_Renderer *rendu;
        
        creerFenetre(&menuPrincipal, "Page du Jeu", LARGEUR_FEN_JEU, HAUTEUR_FEN_JEU);
        //rendu = SDL_CreateRenderer(menuPrincipal, -1, SDL_RENDERER_ACCELERATED);
        rendu = SDL_CreateRenderer(menuPrincipal, -1, SDL_RENDERER_SOFTWARE);

        /* Charger la matrice du décor */
        chargerMatriceDepuisFichier("../res/matrice.txt", matrice);

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
            if (state[SDL_SCANCODE_LEFT]){
                gauche(dino,nuage,nb_pts,matrice);
            }  

            if (state[SDL_SCANCODE_RIGHT]){
                droite(dino,nuage,nb_pts,matrice);
            } 

            SDL_RenderPresent(rendu);
        }

        /* --- NETTOYAGE --- */
        SDL_DestroyTexture(texDino);
        free(nuage);
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