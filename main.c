#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/sem.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "train.c"
#include "voie.c"

int *stop=0;
Voie *voieA, *voieB, *voieC, *voieD, *aig1, *aig2, *gTGV, *gM1, *gM2, *gGL,*tunnel;
#include "aiguilleur.c"

#define NB_TRAINS 20



void greve()
{
	sleep(4);
	printf("\nSuite à une grève du personnel, aucun train ne circulera aujourd'hui.\n");
	printf("\nVeuillez nous excuser pour la gène occasionnée.\n\n");
	sleep (7);
	printf("\nLa SNCF ne contrôle pas ce programme : reprise normale du trafic.\n\n");
	sleep(4);
	system("clear");
	printf("\n");
}

void initReseau()
{
	//printf("voieA");
	//fflush(stdout);
	voieA =createVoie("voieA");
	voieB=createVoie("voieB");
	voieC=createVoie("voieC");
	voieD=createVoie("voieD");
	aig1=createVoie("aig1");
	aig2=createVoie("aig2");
	gTGV=createVoie("gTGV");
	gM1=createVoie("gM1");
	gM2=createVoie("gM2");
	gGL=createVoie("gGL");
	tunnel=createVoie("tunnel");
}
void deleteReseau()
{
	deleteVoie(voieA);
	deleteVoie(voieB);
	deleteVoie(voieC);
	deleteVoie(voieD);
	deleteVoie(aig1);
	deleteVoie(aig2);
	deleteVoie(gTGV);
	deleteVoie(gM1);
	deleteVoie(gM2);
	deleteVoie(gGL);
	deleteVoie(tunnel);
}

void TGV_EO (Train *t)
{
	printf("\nLe TGV %i à destination de %s a été signalé venant de l'Est.\n", t->id,t->destination);
	tunnel->TGV++;
	sem_wait(tunnel->semTGV);
	tunnel->occupee++;
	tunnel->TGV--;
	printf("Le TGV %i emprunte le tunnel.\n",t->id );
	sleep(1);
	gTGV->occupee++;
	tunnel->occupee--;
	printf("Le TGV %i est sur la voie de garage TGV.\n",t->id );
	voieD->TGV++;
	sem_wait(voieD->semTGV);
	voieD->reservee++;
	voieD->TGV--;
	aig2->TGV++;
	sem_wait(aig2->semTGV);
	aig2->occupee++;
	aig2->TGV--;
	printf("Le TGV %i emprunte l'aiguillage 2.\n",t->id );
	sleep(1);
	voieD->occupee++;
	voieD->reservee--;
	aig2->occupee--;
	printf("Le TGV %i s'arrete voie D.\n",t->id);
	sleep(2);
	voieD->occupee--;
	printf("Le TGV %i continue sa route vers %s \n",t->id, t->destination);
}

void TGV_OE (Train *t)
{
	printf("\nLe TGV %i à destination de %s a été signalé venant de l'Ouest.\n", t->id,t->destination);
	voieC->TGV++;
	//printf("Voie C %i TGV en attente\n",voieC->TGV );
	sem_wait(voieC->semTGV);
	voieC->TGV--;
	voieC->occupee++;
	printf("Le TGV %i s'arrete voie C.\n",t->id);
	sleep(2);
	aig2->TGV++;
	sem_wait(aig2->semTGV);
	aig2->occupee++;
	voieC->occupee--;
	aig2->TGV--;
	printf("Le TGV %i emprunte l'aiguillage 2.\n",t->id );
	sleep(1);
	aig2->occupee--;
	gTGV->occupee++;
	printf("Le TGV %i est sur la voie de garage TGV.\n",t->id );
	tunnel->TGV++;
	sem_wait(tunnel->semTGV);
	tunnel->occupee++;
	gTGV->occupee--;
	tunnel->TGV--;
	printf("Le TGV %i emprunte le tunnel.\n",t->id );
	sleep(1);
	tunnel->occupee--;
	printf("Le TGV %i continue sa route vers %s \n",t->id, t->destination);
}

void GL_EO (Train *t)
{
	printf("GL_EO\n");

}

void GL_OE (Train *t)
{
	printf("\nLe train %i à destination de %s a été signalé venant de l'Ouest.\n", t->id,t->destination);
	voieC->GL++;
	sem_wait(voieC->semGL);
	voieC->GL--;
	voieC->occupee++;
	printf("Le train %i s'arrete voie C.\n",t->id);
	sleep(2);
	aig2->GL++;
	sem_wait(aig2->semGL);
	aig2->occupee++;
	voieC->occupee--;
	aig2->GL--;
	printf("Le train %i emprunte l'aiguillage 2.\n",t->id );
	sleep(1);
	aig2->occupee--;
	gGL->occupee++;
	printf("Le train %i est sur la voie de garage TGV.\n",t->id );
	tunnel->GL++;
	sem_wait(tunnel->semGL);
	tunnel->occupee++;
	gGL->occupee--;
	tunnel->GL--;
	printf("Le train %i emprunte le tunnel.\n",t->id );
	sleep(1);
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
	sleep(1);
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
	aig1->M--;
	printf("Le train de marchandises %i emprunte l'aiguillage 1.\n",t->id );
	sleep(1);
	voieB->occupee++;
	voieB->reservee--;
	aig1->occupee--;
	printf("Le train de marchandises %i emprunte la voie B.\n",t->id);
	sleep(1);
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
	sleep(1);
	printf("Le train de marchandises %i emprunte l'aiguillage 1.\n",t->id );
	aig1->occupee++;
	voieA->occupee--;
	aig1->reservee--;
	sleep(1);
	gM2->occupee++;
	aig1->occupee--;
	printf("Le train de marchandises %i est sur la voie de garage M2.\n",t->id );

	tunnel->M++;
	sem_wait(tunnel->semM);
	tunnel->occupee++;
	gM2->occupee--;
	tunnel->M--;
	printf("Le train de marchandises %i emprunte le tunnel.\n",t->id );
	sleep(1);
	tunnel->occupee--;
	printf("Le train de marchandises %i continue sa route vers %s \n",t->id, t->destination);
}

void * fonc_Train(void *num)
{
	//printf("num thread %i \n",(int)num);
    //printf("de TID : %ld \n", (long) pthread_self());
	Train * t=randomTrain((int)num);
	switch(t->type){
		case TGV:
					if (t->direction==EO){TGV_EO(t);}
					else{TGV_OE(t);}
					break;
		case GL:
					if (t->direction==EO){GL_EO(t);}
					else{GL_OE(t);}
					break;
		case M:
					if (t->direction==EO){M_EO(t);}
					else{M_OE(t);}
					break;
		default:
					printf("Default case");
					break;
	}
	deleteTrain(t);
	pthread_exit(NULL);
}

int main(int argc, char* argv[])
{
	//La SNCF est en greve
	//greve();
	initReseau();
	srand(time(NULL));
	// nombre de trains déf en paramètre ou via la constante
	int NbTrains = (argc > 1 ? atoi(argv[1]) : NB_TRAINS); 
	
	
	//printf("nbtrains : %i \n",NbTrains);
	int NumTrain =0;
	int depTrain=5;
	pthread_t tid[NbTrains];
	pthread_t aiguil[3];
	//getchar();
	int rc,k;
	//Génération de 2 premiers trains
	if(NbTrains>=depTrain){
		for (int tr=0; tr<depTrain;tr++){
			if(rc=pthread_create(&(tid[NumTrain]), NULL, fonc_Train, (void*)NumTrain)!=0){
		        	printf("Erreur dans la creation du thread %i",NumTrain);
					return EXIT_FAILURE;
		    }
		    else{
		    		NumTrain++;
		    }
		}
	}
	//Generation des aiguilleurs

	if(rc=pthread_create(&(aiguil[0]), NULL, fonc_P0, (void*)0)!=0){
	    printf("Erreur dans la creation du thread %i",NumTrain);
		return EXIT_FAILURE;
	}
	if(rc=pthread_create(&(aiguil[1]), NULL, fonc_P1, (void*)1)!=0){
	    printf("Erreur dans la creation du thread %i",NumTrain);
		return EXIT_FAILURE;
	}
	if(rc=pthread_create(&(aiguil[2]), NULL, fonc_P2, (void*)2)!=0){
	    printf("Erreur dans la creation du thread %i",NumTrain);
		return EXIT_FAILURE;
	}
	

	//Génération des trains à des intervalles de temps aléatoires
	while(NumTrain<NbTrains){
		k=rand()%7;
		//Création des threads trains
		if(k<2){
	        if(rc=pthread_create(&(tid[NumTrain]), NULL, fonc_Train, (void*)NumTrain)!=0){
	        	printf("Erreur dans la creation du thread %i",NumTrain);
				return EXIT_FAILURE;
	    	}
	    	else{
	    		NumTrain++;
	    	}
	    }
	    usleep(100000);
    }


    printf("\n Attention : Etat d'urgence - Fermeture de la gare imminente!\n\n");
    
    int i;
   	for(i=0;i<NbTrains;i ++){
   		pthread_join(tid[i],NULL);
   	}
   	stop=1;
   	//printf("Join trains OK\n");
   	int j;
   	for(j=0;j<3;j++){
   		pthread_join(aiguil[j],NULL);
   	}
   	//printf("Join aiguil OK\n");
   	deleteReseau();
   	//printf("Delete reseau OK\n");
   	printf("\n\n Fermeture de la gare pour cause d'état d'urgence!\n\n");
   	pthread_exit(NULL);
   	return(0);
}