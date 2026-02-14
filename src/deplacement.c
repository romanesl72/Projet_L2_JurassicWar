#include <stdio.h>
#include "../lib/types.h"
#include <math.h>


float calculForceAire(float rho,float coef,float surface, t_vect vitesse, t_vect *frottement){
    /*Calcul de la force du frottement de l'air*/
    frottement->u=0.5*rho*coef*surface*(vitesse.u*sqrt(pow(vitesse.u,2)+pow(vitesse.v,2)));
    frottement->v=0.5*rho*coef*surface*(vitesse.v*sqrt(pow(vitesse.u,2)+pow(vitesse.v,2)));
}

void calculAcceleration(t_vect *acceleration,float gravite, t_vect frottement, float masse){
    /*utilisation de la formule de newton: la force divisé par la masse*/
    acceleration->u=(-frottement.u)/masse;
    acceleration->v=(frottement.v/masse)-gravite; //la gravité tire vers le bas
}

void calcuPositionVitess(float coef,t_coordonnee *position, t_vect acceleration,t_vect *vitesse, float temps){
    (vitesse->u)+=acceleration.u*temps;
    (vitesse->v)+=acceleration.v*temps;

    (position->x)+=vitesse->u*temps;
    (position->y)+=vitesse->v*temps;
}

int main(){
    char mat[100][100];
    int i,j;
    t_coordonnee position={0,50};
    float gravite=9.807; //gravité sur terre: 9,807 m/s²
    float masse=0.057;
    float surface=0.0035;//en m²
    float coefficiant=0.55;
    float rho=1.225;//kg par métre cube
    float temps=0.01;
    t_vect vitesse={17.32,10.00};
    t_vect frottement;
    t_vect acceleration;

    for (i = 0; i <100; i++){
        for (j=0;j<100; j++){
            mat[i][j]=' ';
        }    
    }
    
    while ((position.x>=0 && position.x<100)&&(position.y>=0 && position.y<100)){
        calculForceAire(rho,coefficiant,surface, vitesse,&frottement);
        calculAcceleration(&acceleration,gravite, frottement, masse);
        calcuPositionVitess(coefficiant,&position, acceleration,&vitesse, temps);
        mat[position.x][position.y]='*';
    }

    for (i = 0; i <100; i++){
        for (j=0;j<100; j++){
            printf("%c",mat[i][j]);
        }
        printf("\n");    
    }
}

