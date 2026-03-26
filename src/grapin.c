// #define STB_IMAGE_IMPLEMENTATION
// #include <stdio.h>
// #include <stdlib.h>
// #include <math.h>

// #include "../lib/deplacement.h"
// #include "../lib/fonctionsVerification.h"
// #include "../lib/regression.h"
// #include "../lib/tda_nuage.h"
// #include "../lib/chargerMatrice.h"
// #include "../lib/placer_dinos.h"
// #include "../lib/tda_file.h"
// #include "../lib/collision_decor.h"

// int collision_grapin(t_coordonnee pos, int matrice[MAT_H][MAT_L]){
//     if(matrice[pos.x][pos.y]==TERRE) return 1;
//     return 0;
// }

// int choixAngleLancer(t_dino *dino, SDL_Renderer* zoneAffichage, SDL_Texture *texMap, SDL_Rect *rect, const Uint8 **etatClavier){
    
//     // do {

//     //     SDL_PumpEvents();
//     //     *etatClavier = SDL_GetKeyboardState(NULL);

//     //     if ((*etatClavier)[SDL_SCANCODE_UP]){
//     //         vectVitesse->v -= 0.8;
//     //     }
//     //     if ((*etatClavier)[SDL_SCANCODE_DOWN]){
//     //         vectVitesse->v += 0.8;
//     //     }

//     //     /* Pour tracer la courbe de trajectoire vers la gauche, il faut une vitesse horizontale négative */
//     //     if ((*etatClavier)[SDL_SCANCODE_LEFT]){
//     //         vectVitesse->u = -fabs(vectVitesse->u);
//     //     }

//     //     /* Pour tracer la courbe de trajectoire vers la droite, il faut une vitesse horizontale positive */
//     //     if ((*etatClavier)[SDL_SCANCODE_RIGHT]){
//     //         vectVitesse->u = fabs(vectVitesse->u);
//     //     }

//     //     SDL_RenderClear(zoneAffichage);
//     //     SDL_RenderCopy(zoneAffichage, texMap, NULL, rect);

//     //     tracerBombe(zoneAffichage, bombe);
//     //     tracerTrajectoireLancer(zoneAffichage, &(bombe->coor), vectVitesse, gravite);

//     //     SDL_RenderPresent(zoneAffichage);
//     //     /* SDL_Delay(16);*/
//     //     SDL_Delay(8);

//     // } while(!(*etatClavier)[SDL_SCANCODE_SPACE]);
// }

// int lancer(t_coordonnee pos_initial, int angle, int matrice[MAT_H][MAT_L], int *collision_initial, int *collision){
//     ajouter(pos_initial);
//     t_coordonnee nv_pos=malloc(sizeof(t_coordonnee));
//     nv_pos=pos_initial;
//     if(collision_initial){
//         nv_pos.x+=1;
//         nv_pos.y+=angle;
//         *collision_initial=collision_grapin(nv_pos,matrice);
//         ajouter(nv_pos);
//     }
//     else if(!collision){
//         nv_pos.x+=1;
//         nv_pos.y+=angle;
//         *collision=collision_grapin(nv_pos,matrice);
//         ajouter(nv_pos);
//     }
//     free(nv_pos);
//     nv_pos=NULL;
// }

// int rappel(int matrice[MAT_H][MAT_L], t_dino *dino, int *collision_initial, int *collision, int direction){
//     int tab_res[4];
//     t_coordonnee nv_pos=malloc(sizeof(t_coordonnee));
//     if(collision_initial){
//         *collision_initial=collision_decor(tab_res,*dino,matrice);
//         retirer(&nv_pos);
//         dino->pos=nv_pos;
//         dino->indice_nuage+=direction;
//     }
//     else if(!collision){
//         *collision=collision_decor(tab_res,*dino,matrice);
//         retirer(&nv_pos);
//         dino->pos=nv_pos;
//         dino->indice_nuage+=direction;
//     }
// }
