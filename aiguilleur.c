/**********************************************
* Fonctions des aiguilleurs qui décident 	  *
* du passage des trains						  *
* Projet LO41 - Printemps 2016                *
* Auteurs :                                   *
* Elise Kocik et Florian Bishop               *
**********************************************/

#include "aiguilleur.h"

void * fonc_P0(void *num)
{
	while (*stop==0){
		pthread_mutex_lock (&voieGL);
		if(aig2->occupee == 0 && aig2->reservee == 0){
			if(aig2->TGV >0){
				sem_post(aig2->semTGV);
			}
			else if(aig2->GL>0){
				sem_post(aig2->semGL);
			}
		}

		if(voieC->occupee <2 && voieC->reservee == 0){
			if(voieC->TGV >0){
				sem_post(voieC->semTGV);
			}
			else if(voieC->GL>0){
				sem_post(voieC->semGL);
			}
		}

		if(voieD->occupee <2 && voieD->reservee < 2){
			if(voieD->TGV >0){
				sem_post(voieD->semTGV);
			}
			else if(voieD->GL>0){
				sem_post(voieD->semGL);
			}
		}
		pthread_mutex_unlock (&voieGL);
		//sleep(1);
		//printf("Stop : %i\n", stop);
	}
	pthread_exit(NULL);
}

void * fonc_P1(void *num)
{
	while(*stop==0){
		pthread_mutex_lock (&marchandises);
		if(aig1->occupee == 0 && aig1->reservee == 0 && aig1->M>0){
			sem_post(aig1->semM);
		}
		if(voieA->occupee == 0 && voieA->reservee == 0 && voieA->M>0){
			sem_post(voieA->semM);
		}
		if(voieB->occupee == 0 && voieB->reservee == 0 && voieB->M>0){
			sem_post(voieB->semM);
		}
		pthread_mutex_unlock (&marchandises);
	}
	pthread_exit(NULL);
}

void * fonc_P2(void *num)
{
	while(*stop==0){
		pthread_mutex_lock (&tunGar);
		if(tunnel->occupee ==0 && tunnel->reservee == 0){
			if(tunnel->TGV>0){
				sem_post(tunnel->semTGV);
			}
			else if(tunnel->GL>0){
				sem_post(tunnel->semGL);
			}
			else if(tunnel->M>0){
				sem_post(tunnel->semM);
			}
		}
		pthread_mutex_unlock (&tunGar);
	}
	pthread_exit(NULL);
}