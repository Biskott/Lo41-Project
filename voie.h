/**********************************************
* Librairie pour la gestion des voies	      *
* Projet LO41 - Printemps 2016				  *
* Auteurs : 								  *
* Florian Bishop et Elise Kocik 			  *
**********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

/**#define TRUE 1
#define FALSE 0
typedef int BOOL;*/

#ifndef VOIE_H
#define	VOIE_H

/**********************************************
* Définition du type Voie         			  *
**********************************************/

typedef struct {
	sem_t * semM;
	sem_t * semGL;
	sem_t * semTGV;
	int reservee;
    int occupee;
    char * nom;
    int TGV; //TGV en attente
    int GL; //GL en attente
    int M; //M en attente
} Voie;

/**********************************************
* Fonctions sur les Trains         			  *
**********************************************/

/** Crée une nouvelle voie*/
Voie* createVoie(char * nom);

/** Suppression de la voie*/
void deleteVoie(Voie *v);

#endif	/* VOIE_H */
