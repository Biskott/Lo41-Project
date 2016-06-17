/**********************************************
* Fonctions de gestion du trajet des trains   *
* Projet LO41 - Printemps 2016                *
* Auteurs :                                   *
* Elise Kocik et Florian Bishop               *
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

void GL_OE (Train *t)
{
	printf("\nLe train %i à destination de %s a été signalé venant de l'Ouest.\n", t->id,t->destination);
	voieC->GL++;
	sem_wait(voieC->semGL);
	voieC->GL--;
	voieC->occupee++;
	printf("Le train %i s’arrête voie C.\n",t->id);
	sleep(voieC->longueur);
	aig2->GL++;
	sem_wait(aig2->semGL);
	aig2->occupee++;
	voieC->occupee--;
	aig2->GL--;
	printf("Le train %i emprunte l'aiguillage 2.\n",t->id );
	sleep(aig2->longueur);
	aig2->occupee--;
	gGL->occupee++;
	printf("Le train %i est sur la voie de garage GL.\n",t->id );
	tunnel->GL++;
	sem_wait(tunnel->semGL);
	tunnel->occupee++;
	gGL->occupee--;
	tunnel->GL--;
	printf("Le train %i emprunte le tunnel.\n",t->id );
	sleep((int)2*tunnel->longueur/3);
	printf("Le train %i emprunte la voie L.\n",t->id );
	sleep((int)tunnel->longueur/3);
	tunnel->occupee--;
	printf("Le train %i continue sa route vers %s \n",t->id, t->destination);
}

void M_EO (Train *t)
{
	printf("\nLe train de marchandises %i à destination de %s a été signalé venant de l'Est.\n", t->id,t->destination);
	tunnel->M++;
	sem_wait(tunnel->semM);
	tunnel->occupee++;
	tunnel->M--;
	printf("Le train de marchandises %i emprunte le tunnel.\n",t->id );
	sleep((int)tunnel->longueur/3);
	printf("Le train de marchandises %i emprunte le tunnel.\n",t->id);
	sleep((int)2*tunnel->longueur/3);
	gM1->occupee++;
	tunnel->occupee--;
	printf("Le train de marchandises %i est sur la voie de garage M2.\n",t->id );
	voieB->M++;
	sem_wait(voieB->semM);
	voieB->reservee++;
	voieB->M--;
	aig1->M++;
	sem_wait(aig1->semM);
	aig1->occupee++;
	gM1->occupee--;
	aig1->M--;
	printf("Le train de marchandises %i emprunte l'aiguillage 1.\n",t->id );
	sleep(aig1->longueur);
	voieB->occupee++;
	voieB->reservee--;
	aig1->occupee--;
	printf("Le train de marchandises %i emprunte la voie B.\n",t->id);
	sleep(voieB->longueur);
	voieB->occupee--;
	printf("Le train de marchandises %i continue sa route vers %s \n",t->id, t->destination);
}	

void M_OE (Train *t)
{
	printf("\nLe train de marchandises %i à destination de %s a été signalé venant de l'Ouest.\n", t->id,t->destination);
	aig1->M++;
	sem_wait(aig1->semM);
	aig1->reservee++;
	aig1->M--;
	voieA->M++;
	sem_wait(voieA->semM);
	voieA->occupee++;
	voieA->M--;
	printf("Le train de marchandises %i emprunte la voie A.\n",t->id);
	sleep(voieA->longueur);
	printf("Le train de marchandises %i emprunte l'aiguillage 1.\n",t->id );
	aig1->occupee++;
	voieA->occupee--;
	aig1->reservee--;
	sleep(aig1->longueur);
	gM2->occupee++;
	aig1->occupee--;
	printf("Le train de marchandises %i est sur la voie de garage M2.\n",t->id );
	tunnel->M++;
	sem_wait(tunnel->semM);
	tunnel->occupee++;
	gM2->occupee--;
	tunnel->M--;
	printf("Le train de marchandises %i emprunte le tunnel.\n",t->id );
	sleep((int)2*tunnel->longueur/3);
	printf("Le train de marchandises %i emprunte la voie L.\n",t->id );
	sleep((int)tunnel->longueur/3);
	tunnel->occupee--;
	printf("Le train de marchandises %i continue sa route vers %s \n",t->id, t->destination);
}