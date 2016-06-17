/**********************************************
* Fonctions relatives au type de donnée :     *
* Voie                                        *
* Projet LO41 - Printemps 2016                *
* Auteurs :                                   *
* Elise Kocik et Florian Bishop               *
**********************************************/
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "voie.h"


/**********************************************
* Création d'une voie                         *
**********************************************/

Voie* createVoie(char* nom, int longueur)
{
    Voie * v =malloc(sizeof(Voie));
    v->nom=nom;
    v->reservee=0;
    v->occupee=0;
    v->longueur=longueur;
    v->TGV=0;
    v->GL=0;
    v->M=0;
    //printf("Creation voie avant sem_nom \n");
    //creation des sem_nom
    char sem_nom1[60] = "\"/a";
    char *m = " \"";
    strcat(sem_nom1,nom);
    strcat(sem_nom1, m);

    //printf("%s \n",sem_nom1);


    //printf("Creation voie pendant sem_nom \n");
    //fflush(stdout);

    char sem_nom2[60] = "\"/b";
    strcat(sem_nom2,nom);
    strcat(sem_nom2, m);

    char sem_nom3[60] = "\"/c";
    strcat(sem_nom3,nom);
    strcat(sem_nom3, m);

    //printf("Creation voie avant sem \n");
    //fflush(stdout);
    //v->semM=sem_open(sem_nom1, O_RDWR | O_CREAT, 0666, 0);
    v->semM = (sem_t * ) malloc(sizeof(sem_t));
    sem_init(v->semM,0,0);
    v->semGL = (sem_t * ) malloc(sizeof(sem_t));
    sem_init(v->semGL,0,0);
    v->semTGV = (sem_t * ) malloc(sizeof(sem_t));
    sem_init(v->semTGV,0,0);
    return v;
}


/**********************************************
* Suppression d'une voie                      *
**********************************************/
void deleteVoie(Voie *v){
    //creation des sem_nom
    char sem_nom1[60] = "\"/a";
    char *m = " \"";
    strcat(sem_nom1,v->nom);
    strcat(sem_nom1, m);

    char sem_nom2[60] = "\"/b";
    strcat(sem_nom2,v->nom);
    strcat(sem_nom2, m);

    char sem_nom3[60] = "\"/c";
    strcat(sem_nom3,v->nom);
    strcat(sem_nom3, m);

    sem_unlink(sem_nom1);
    sem_unlink(sem_nom2);
    sem_unlink(sem_nom3);
    free(v);
}