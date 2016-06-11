/**********************************************
* Librairie pour la gestion de trains	      *
* Projet LO41 - Printemps 2016				  *
* Auteurs : 								  *
* Florian Bishop et Elise Kocik 			  *
**********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#ifndef TRAIN_H
#define	TRAIN_H

/**********************************************
* Définition des destinations         		  *
**********************************************/

char* tab_Dest[]={
	"Chez P.Descamps",
	"Paris",
	"Mamen",
	"Le Crew",
	"Dijon",
	"Palaiseau",
	"Lyon",
	"Bordeaux",
	"Strasbourg",
	"Toulouse"
};


/**********************************************
* Définition du type Train         			  *
**********************************************/

typedef enum {
    EO,
    OE
} Direction;

typedef enum {
    TGV,
    GL,
    M
} Type;

typedef struct {
    Type type;
    Direction direction;
    int id;
    char* destination;
} Train;

/**********************************************
* Fonctions sur les Trains         			  *
**********************************************/

/** Crée un nouveau train avec l'id et le type spécifié
* La destination est aléatoire*/
Train* createTrain(int id, Type type, Direction dir);

/**Crée un train aléatoire**/
Train* randomTrain(int id);

/** Suppression du train*/
void deleteTrain(Train *t);

#endif	/* STRUCTURES_H */
