/**********************************************
* Fonctions relatives au type de donnée :     *
* BaseNIntegerList                            *
* Projet LO44 - Automne 2015				  *
* Auteurs : 								  *
* Elise Kocik et NGOUANA NGOUMKOUA Wilfried	  *
**********************************************/
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "train.h"


/**********************************************
* Création d'un train                         *
**********************************************/

Train* createTrain(int id, Type type, Direction dir)
{
	Train * t =malloc(sizeof(Train));
	t->id=id;
	t->type=type;
	t->direction=dir;
	t->destination=tab_Dest[(rand()%10)];
	char* typ;
	switch(t->type){
		case TGV:
				typ="TGV";
				break;
		case GL:
				typ="train GL";
				break;
		case M:
				typ="train M";
				break;
		default:
				typ="train fantome";
				break;

	}
	char* direc;
	switch(t->direction){
		case EO:
				direc="EO";
				break;
		default:
				direc="OE";
				break;

	}
	printf("Le %s %i  %s a pour destination %s \n",typ,t->id,direc,t->destination);
	return t;
}

/**********************************************
* Création d'un train aléatoire               *
**********************************************/
Train* randomTrain(int id)
{
	Type type;
	Direction dir;
    int k=rand()%6;
    switch (k){
    	case 0:
    			type=TGV;
    			dir=OE;
    			break;
    	case 1:
    			type=GL;
    			dir=OE;
    			break;
    	case 2:
    			type=M;
    			dir=OE;
    			break;
    	case 3:
    			type=TGV;
    			dir=EO;
    			break;
    	case 4:
    			type=GL;
    			dir=EO;
    			break;
    	case 5:
    			type=M;
    			dir=EO;
    			break;
    }

	Train * t =createTrain(id, type, dir);
	return t;
}

/**********************************************
* Suppression d'un train                      *
**********************************************/
void deleteTrain(Train *t){
	free(t);
}


