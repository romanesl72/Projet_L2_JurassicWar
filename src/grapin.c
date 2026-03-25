#define STB_IMAGE_IMPLEMENTATION
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../lib/deplacement.h"
#include "../lib/fonctionsVerification.h"
#include "../lib/regression.h"
#include "../lib/tda_nuage.h"
#include "../lib/chargerMatrice.h"
#include "../lib/placer_dinos.h"
#include "../lib/tda_nuage.h"
#include "../lib/collision_decor.h"


void choixAngleLancer(SDL_Renderer* zoneAffichage, SDL_Texture *texMap, SDL_Rect *rect, const Uint8 **etatClavier, t_bombe *bombe, t_vect *vectVitesse, float gravite){
    
    do {

        SDL_PumpEvents();
        *etatClavier = SDL_GetKeyboardState(NULL);

        if ((*etatClavier)[SDL_SCANCODE_UP]){
            vectVitesse->v -= 0.8;
        }
        if ((*etatClavier)[SDL_SCANCODE_DOWN]){
            vectVitesse->v += 0.8;
        }

        /* Pour tracer la courbe de trajectoire vers la gauche, il faut une vitesse horizontale négative */
        if ((*etatClavier)[SDL_SCANCODE_LEFT]){
            vectVitesse->u = -fabs(vectVitesse->u);
        }

        /* Pour tracer la courbe de trajectoire vers la droite, il faut une vitesse horizontale positive */
        if ((*etatClavier)[SDL_SCANCODE_RIGHT]){
            vectVitesse->u = fabs(vectVitesse->u);
        }

        SDL_RenderClear(zoneAffichage);
        SDL_RenderCopy(zoneAffichage, texMap, NULL, rect);

        tracerBombe(zoneAffichage, bombe);
        tracerTrajectoireLancer(zoneAffichage, &(bombe->coor), vectVitesse, gravite);

        SDL_RenderPresent(zoneAffichage);
        /* SDL_Delay(16);*/
        SDL_Delay(8);

    } while(!(*etatClavier)[SDL_SCANCODE_SPACE]);
}