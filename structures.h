/**********************************************
* Librairie pour la gestion de trains	      *
* Projet LO41 - Printemps 2016				  *
* Auteurs : 								  *
* Florian Bishop et Elise Kocik 			  *
**********************************************/

#include <stdio.h>
#include <stdlib.h>


#ifndef STRUCTURES_H
#define	STRUCTURES_H

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

#endif	/* STRUCTURES_H */
