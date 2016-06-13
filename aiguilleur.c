#include "aiguilleur.h"

void * fonc_P0(void *num)
{

	if(aig2->occupee == 0 && aig2->reservee == 0){
		if(aig2->TGV >0){
			sem_prop(aig2->semTGV);
		}
		else if(aig2->GL>0){
			sem_prop(aig2->semGL);
		}
	}

	if(voieC->occupee <2 && voieC->reservee == 0){
		if(voieC->TGV >0){
			sem_prop(voieC->semTGV);
		}
		else if(voieC->GL>0){
			sem_prop(voieC->semGL);
		}
	}

	if(voieD->occupee <2 && voieD->reservee < 2){
		if(voieD->TGV >0){
			sem_prop(voieD->semTGV);
		}
		else if(voieD->GL>0){
			sem_prop(voieD->semGL);
		}
	}
	if(stop)
		pthread_exit(NULL);
}

void * fonc_P1(void *num)
{

	if(aig1->occupee == 0 && aig1->reservee == 0 && aig1->M>0){
		sem_prop(aig1->semM);
	}
	if(voieA->occupee == 0 && voieA->reservee == 0 && voieA->M>0){
		sem_prop(voieA->semM);
	}
	if(voieB->occupee == 0 && voieB->reservee == 0 && voieB->M>0){
		sem_prop(voieB->semM);
	}
	
	if(stop)
		pthread_exit(NULL);
}

void * fonc_P2(void *num)
{
	if(tunnel->occupee ==0 && tunnel->reservee == 0){
		if(tunnel->TGV>0){
			sem_prop(tunnel->semTGV);
		}
		else if(tunnel->GL>0){
			sem_prop(tunnel->semGL);
		}
		else if(tunnel->GL>0){
			sem_prop(tunnel->semGL);
		}
	}
	
	if(stop)
		pthread_exit(NULL);
}