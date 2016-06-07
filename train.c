/**********************************************
* Fonctions relatives au type de donnée :     *
* BaseNIntegerList                            *
* Projet LO44 - Automne 2015				  *
* Auteurs : 								  *
* Elise Kocik et NGOUANA NGOUMKOUA Wilfried	  *
**********************************************/

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
	srand(time(NULL));
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
	printf("Le %s %i a pour destination %s \n",typ,t->id,t->destination);
	return t;
}

Train* randomTrain(int id)
{
	Type type;
	Direction dir;
	srand(time(NULL));
    if((rand()%2)==0){dir=EO;}
    else{dir=OE;}
    switch (rand()%3){
    	case 0:
    			type=TGV;
    			break;
    	case 1:
    			type=GL;
    			break;
    	case 2:
    			type=M;
    			break;
    }

	Train * t =createTrain(id, type, dir);
	return t;
}