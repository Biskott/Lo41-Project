/**********************************************
* Fonctions de gestion du trajet des trains   *
* Projet LO41 - Printemps 2016                *
* Auteurs :                                   *
* Elise Kocik et Florian Bishop               *
**********************************************/

/**************************************************************************************************
* Une fonction par type et sens de train. 														  *
* Les trains attendent d'avoir l'acces et reservent les prochaines voies à emprunter.			  *
* Le temps passé sur chaque voie est symbolisé par un sleep().									  *
* Avant de modifier les éléments des voies (nombre de trains en attente, occupation, etc..),	  *
* les trains verrouillent le mutex correspondant et le déverrouillent après les opérations.		  *
**************************************************************************************************/
#include "train.h"

/**********************************************
* Fonction pour le trajet des TGV est-ouest   *
**********************************************/
void TGV_EO (Train *t)
{
	printf("\nLe TGV %i à destination de %s a été signalé venant de l'Est.\n", t->id,t->destination);
	pthread_mutex_lock (&tunGar);
	tunnel->TGV++;
	pthread_mutex_unlock (&tunGar);
	sem_wait(tunnel->semTGV);
	pthread_mutex_lock (&tunGar);
	tunnel->occupee++;
	tunnel->TGV--;
	pthread_mutex_unlock (&tunGar);
	printf("Le TGV %i emprunte la voie L.\n",t->id );
	sleep((int)tunnel->longueur/3);
	printf("Le TGV %i emprunte le tunnel.\n",t->id);
	sleep((int)2*tunnel->longueur/3);
	pthread_mutex_lock (&tunGar);
	gTGV->occupee++;
	tunnel->occupee--;
	pthread_mutex_unlock (&tunGar);
	printf("Le TGV %i est sur la voie de garage TGV.\n",t->id );
	pthread_mutex_lock (&voieGL);
	voieD->TGV++;
	pthread_mutex_unlock (&voieGL);
	sem_wait(voieD->semTGV);
	pthread_mutex_lock (&voieGL);
	voieD->reservee++;
	voieD->TGV--;
	aig2->TGV++;
	pthread_mutex_unlock (&voieGL);
	sem_wait(aig2->semTGV);
	pthread_mutex_lock (&voieGL);
	aig2->occupee++;
	aig2->TGV--;
	pthread_mutex_unlock (&voieGL);
	pthread_mutex_lock (&tunGar);
	gTGV->occupee--;
	pthread_mutex_unlock (&tunGar);
	printf("Le TGV %i emprunte l'aiguillage 2.\n",t->id );
	sleep(aig2->longueur);
	pthread_mutex_lock (&voieGL);
	voieD->occupee++;
	voieD->reservee--;
	aig2->occupee--;
	pthread_mutex_unlock (&voieGL);
	printf("Le TGV %i s’arrête voie D.\n",t->id);
	sleep(voieD->longueur);
	pthread_mutex_lock (&voieGL);
	voieD->occupee--;
	pthread_mutex_unlock (&voieGL);
	printf("Le TGV %i continue sa route vers %s \n",t->id, t->destination);
}

/**********************************************
* Fonction pour le trajet des TGV ouest-est   *
**********************************************/
void TGV_OE (Train *t)
{
	printf("\nLe TGV %i à destination de %s a été signalé venant de l'Ouest.\n", t->id,t->destination);
	pthread_mutex_lock (&voieGL);
	voieC->TGV++;
	pthread_mutex_unlock (&voieGL);
	//printf("Voie C %i TGV en attente\n",voieC->TGV );
	sem_wait(voieC->semTGV);
	pthread_mutex_lock (&voieGL);
	voieC->TGV--;
	voieC->occupee++;
	pthread_mutex_unlock (&voieGL);
	printf("Le TGV %i s’arrête voie C.\n",t->id);
	sleep(voieC->longueur);
	pthread_mutex_lock (&voieGL);
	aig2->TGV++;
	pthread_mutex_unlock (&voieGL);
	sem_wait(aig2->semTGV);
	pthread_mutex_lock (&voieGL);
	aig2->occupee++;
	voieC->occupee--;
	aig2->TGV--;
	pthread_mutex_unlock (&voieGL);
	printf("Le TGV %i emprunte l'aiguillage 2.\n",t->id );
	sleep(aig2->longueur);
	pthread_mutex_lock (&voieGL);
	aig2->occupee--;
	pthread_mutex_unlock (&voieGL);
	pthread_mutex_lock (&tunGar);
	gTGV->occupee++;
	printf("Le TGV %i est sur la voie de garage TGV.\n",t->id );
	tunnel->TGV++;
	pthread_mutex_unlock (&tunGar);
	sem_wait(tunnel->semTGV);
	pthread_mutex_lock (&tunGar);
	tunnel->occupee++;
	gTGV->occupee--;
	tunnel->TGV--;
	pthread_mutex_unlock (&tunGar);
	printf("Le TGV %i emprunte le tunnel.\n",t->id );
	sleep((int)2*tunnel->longueur/3);
	printf("Le TGV %i emprunte la voie L.\n",t->id );
	sleep((int)tunnel->longueur/3);
	pthread_mutex_lock (&tunGar);
	tunnel->occupee--;
	pthread_mutex_unlock (&tunGar);
	printf("Le TGV %i continue sa route vers %s \n",t->id, t->destination);
}

/****************************************************************
* Fonction pour le trajet des trains grandes lignes est-ouest   *
****************************************************************/
void GL_EO (Train *t)
{
	printf("\nLe train %i à destination de %s a été signalé venant de l'Est.\n", t->id,t->destination);
	pthread_mutex_lock (&tunGar);
	tunnel->GL++;
	pthread_mutex_unlock (&tunGar);
	sem_wait(tunnel->semGL);
	pthread_mutex_lock (&tunGar);
	tunnel->occupee++;
	tunnel->GL--;
	pthread_mutex_unlock (&tunGar);
	printf("Le train %i emprunte la voie L.\n",t->id );
	sleep((int)tunnel->longueur/3);
	printf("Le train %i emprunte le tunnel.\n",t->id);
	sleep((int)2*tunnel->longueur/3);
	pthread_mutex_lock (&tunGar);
	gGL->occupee++;
	tunnel->occupee--;
	pthread_mutex_unlock (&tunGar);
	printf("Le train %i est sur la voie de garage GL.\n",t->id );
	pthread_mutex_lock (&voieGL);
	voieD->GL++;
	pthread_mutex_unlock (&voieGL);
	sem_wait(voieD->semGL);
	pthread_mutex_lock (&voieGL);
	voieD->reservee++;
	voieD->GL--;
	aig2->GL++;
	pthread_mutex_unlock (&voieGL);
	sem_wait(aig2->semGL);
	pthread_mutex_lock (&voieGL);
	aig2->occupee++;
	aig2->GL--;
	pthread_mutex_unlock (&voieGL);
	pthread_mutex_lock (&tunGar);
	gGL->occupee--;
	pthread_mutex_unlock (&tunGar);
	printf("Le train %i emprunte l'aiguillage 2.\n",t->id );
	sleep(aig2->longueur);
	pthread_mutex_lock (&voieGL);
	voieD->occupee++;
	voieD->reservee--;
	aig2->occupee--;
	pthread_mutex_unlock (&voieGL);
	printf("Le train %i s’arrête voie D.\n",t->id);
	sleep(voieD->longueur);
	pthread_mutex_lock (&voieGL);
	voieD->occupee--;
	pthread_mutex_unlock (&voieGL);
	printf("Le train %i continue sa route vers %s \n",t->id, t->destination);

}

/****************************************************************
* Fonction pour le trajet des trains grandes lignes ouest-est   *
****************************************************************/
void GL_OE (Train *t)
{
	printf("\nLe train %i à destination de %s a été signalé venant de l'Ouest.\n", t->id,t->destination);
	pthread_mutex_lock (&voieGL);
	voieC->GL++;
	pthread_mutex_unlock (&voieGL);
	sem_wait(voieC->semGL);
	pthread_mutex_lock (&voieGL);
	voieC->GL--;
	voieC->occupee++;
	pthread_mutex_unlock (&voieGL);
	printf("Le train %i s’arrête voie C.\n",t->id);
	sleep(voieC->longueur);
	pthread_mutex_lock (&voieGL);
	aig2->GL++;
	pthread_mutex_unlock (&voieGL);
	sem_wait(aig2->semGL);
	pthread_mutex_lock (&voieGL);
	aig2->occupee++;
	voieC->occupee--;
	aig2->GL--;
	pthread_mutex_unlock (&voieGL);
	printf("Le train %i emprunte l'aiguillage 2.\n",t->id );
	sleep(aig2->longueur);
	pthread_mutex_lock (&voieGL);
	aig2->occupee--;
	pthread_mutex_unlock (&voieGL);
	pthread_mutex_lock (&tunGar);
	gGL->occupee++;
	printf("Le train %i est sur la voie de garage GL.\n",t->id );
	tunnel->GL++;
	pthread_mutex_unlock (&tunGar);
	sem_wait(tunnel->semGL);
	pthread_mutex_lock (&tunGar);
	tunnel->occupee++;
	gGL->occupee--;
	tunnel->GL--;
	pthread_mutex_unlock (&tunGar);
	printf("Le train %i emprunte le tunnel.\n",t->id );
	sleep((int)2*tunnel->longueur/3);
	printf("Le train %i emprunte la voie L.\n",t->id );
	sleep((int)tunnel->longueur/3);
	pthread_mutex_lock (&tunGar);
	tunnel->occupee--;
	pthread_mutex_unlock (&tunGar);
	printf("Le train %i continue sa route vers %s \n",t->id, t->destination);
}

/****************************************************************
* Fonction pour le trajet des trains de marchandises est-ouest  *
****************************************************************/
void M_EO (Train *t)
{
	printf("\nLe train de marchandises %i à destination de %s a été signalé venant de l'Est.\n", t->id,t->destination);
	pthread_mutex_lock (&tunGar);
	tunnel->M++;
	pthread_mutex_unlock (&tunGar);
	sem_wait(tunnel->semM);
	pthread_mutex_lock (&tunGar);
	tunnel->occupee++;
	tunnel->M--;
	pthread_mutex_unlock (&tunGar);
	printf("Le train de marchandises %i emprunte la voie L.\n",t->id );
	sleep((int)tunnel->longueur/3);
	printf("Le train de marchandises %i emprunte le tunnel.\n",t->id);
	sleep((int)2*tunnel->longueur/3);
	pthread_mutex_lock (&tunGar);
	gM1->occupee++;
	tunnel->occupee--;
	pthread_mutex_unlock (&tunGar);
	printf("Le train de marchandises %i est sur la voie de garage M2.\n",t->id );
	pthread_mutex_lock (&marchandises);
	voieB->M++;
	pthread_mutex_unlock (&marchandises);
	sem_wait(voieB->semM);
	pthread_mutex_lock (&marchandises);
	voieB->reservee++;
	voieB->M--;
	aig1->M++;
	pthread_mutex_unlock (&marchandises);
	sem_wait(aig1->semM);
	pthread_mutex_lock (&marchandises);
	aig1->occupee++;
	aig1->M--;
	pthread_mutex_unlock (&marchandises);
	pthread_mutex_lock (&tunGar);
	gM1->occupee--;
	pthread_mutex_unlock (&tunGar);
	printf("Le train de marchandises %i emprunte l'aiguillage 1.\n",t->id );
	sleep(aig1->longueur);
	pthread_mutex_lock (&marchandises);
	voieB->occupee++;
	voieB->reservee--;
	aig1->occupee--;
	pthread_mutex_unlock (&marchandises);
	printf("Le train de marchandises %i emprunte la voie B.\n",t->id);
	sleep(voieB->longueur);
	pthread_mutex_lock (&marchandises);
	voieB->occupee--;
	pthread_mutex_unlock (&marchandises);
	printf("Le train de marchandises %i continue sa route vers %s \n",t->id, t->destination);
}	

/****************************************************************
* Fonction pour le trajet des trains de marchandises ouest-est  *
****************************************************************/
void M_OE (Train *t)
{
	printf("\nLe train de marchandises %i à destination de %s a été signalé venant de l'Ouest.\n", t->id,t->destination);
	pthread_mutex_lock (&marchandises);
	aig1->M++;
	pthread_mutex_unlock (&marchandises);
	sem_wait(aig1->semM);
	pthread_mutex_lock (&marchandises);
	aig1->reservee++;
	aig1->M--;
	voieA->M++;
	pthread_mutex_unlock (&marchandises);
	sem_wait(voieA->semM);
	pthread_mutex_lock (&marchandises);
	voieA->occupee++;
	voieA->M--;
	pthread_mutex_unlock (&marchandises);
	printf("Le train de marchandises %i emprunte la voie A.\n",t->id);
	sleep(voieA->longueur);
	printf("Le train de marchandises %i emprunte l'aiguillage 1.\n",t->id );
	pthread_mutex_lock (&marchandises);
	aig1->occupee++;
	voieA->occupee--;
	aig1->reservee--;
	pthread_mutex_unlock (&marchandises);
	sleep(aig1->longueur);
	pthread_mutex_lock (&tunGar);
	gM2->occupee++;
	pthread_mutex_unlock (&tunGar);
	pthread_mutex_lock (&marchandises);
	aig1->occupee--;
	pthread_mutex_unlock (&marchandises);
	printf("Le train de marchandises %i est sur la voie de garage M2.\n",t->id );
	pthread_mutex_lock (&tunGar);
	tunnel->M++;
	pthread_mutex_unlock (&tunGar);
	sem_wait(tunnel->semM);
	pthread_mutex_lock (&tunGar);
	tunnel->occupee++;
	gM2->occupee--;
	tunnel->M--;
	pthread_mutex_unlock (&tunGar);
	printf("Le train de marchandises %i emprunte le tunnel.\n",t->id );
	sleep((int)2*tunnel->longueur/3);
	printf("Le train de marchandises %i emprunte la voie L.\n",t->id );
	sleep((int)tunnel->longueur/3);
	pthread_mutex_lock (&tunGar);
	tunnel->occupee--;
	pthread_mutex_unlock (&tunGar);
	printf("Le train de marchandises %i continue sa route vers %s \n",t->id, t->destination);
}