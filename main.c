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

#define NB_TRAINS 12

sem_t * voieA, *voieB, *voieC, *voieD, *aig1, *aig2, *gTGV, *gM1, *gM2, *gGL, *tunnel, *voieL;



void greve()
{
	sleep(5);
	printf("\nSuite à une grève du personnel, aucun train ne circulera aujourd'hui.\n");
	printf("\nVeuillez nous excuser pour la gène occasionnée.\n\n");
	sleep (5);
	printf("\nLa SNCF ne contrôle pas ce programme : reprise normale du trafic.\n\n");
	sleep(4);
	system("clear");
	printf("\n");
}


void createVoie()
{
	voieA=sem_open("/voieA", O_RDWR | O_CREAT, 0666, 1);
	voieB=sem_open("/voieB", O_RDWR | O_CREAT, 0666, 1);
   	voieC =sem_open("/voieC", O_RDWR | O_CREAT, 0666, 2);
   	voieD=sem_open("/voieD", O_RDWR | O_CREAT, 0666, 2);
	aig1=sem_open("/aig1", O_RDWR | O_CREAT, 0666, 1);
   	aig2 =sem_open("/aig2", O_RDWR | O_CREAT, 0666, 1);
   	gTGV=sem_open("/gTGV", O_RDWR | O_CREAT, 0666, 1);
	gM1=sem_open("/gM1", O_RDWR | O_CREAT, 0666, 1);
   	gM2 =sem_open("/gM2", O_RDWR | O_CREAT, 0666, 1);
   	gGL=sem_open("/gGL", O_RDWR | O_CREAT, 0666, 1);
	tunnel=sem_open("/tunnel", O_RDWR | O_CREAT, 0666, 1);
}

void deleteVoie(){
	sem_unlink("/voieA");
   	sem_unlink("/voieB");
   	sem_unlink("/voieC");
   	sem_unlink("/voieD");
   	sem_unlink("/aig1");
   	sem_unlink("/aig2");
   	sem_unlink("/gTGV");
   	sem_unlink("/gM2");
   	sem_unlink("/gM1");
   	sem_unlink("/gGL");
   	sem_unlink("/tunnel");
   	sem_unlink("/voieL");
}

void TGV_EO ()
{
	printf("TGV_EO\n");
}

void TGV_OE ()
{
	printf("TGV_OE\n");
}

void GL_EO ()
{
	printf("GL_EO\n");

}

void GL_OE ()
{
	printf("GL_OE\n");
}

void M_EO ()
{
	printf("M_EO\n");
}	

void M_OE ()
{
	printf("M_OE\n");
}

void * fonc_Train(void *num)
{
	printf("num thread %i \n",(int)num);
    printf("de TID : %ld \n", (long) pthread_self());
	Train * t=randomTrain((int)num);
	switch(t->type){
		case TGV:
					if (t->direction==EO){TGV_EO();}
					else{TGV_OE();}
					break;
		case GL:
					if (t->direction==EO){GL_EO();}
					else{GL_OE();}
					break;
		case M:
					if (t->direction==EO){M_EO();}
					else{M_OE();}
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
	greve();
	srand(time(NULL));
	// nombre de trains déf en paramètre ou via la constante
	int NbTrains = (argc > 1 ? atoi(argv[1]) : NB_TRAINS); 
	
	printf("nbtrains : %i \n",NbTrains);
	int NumTrain =0;
	pthread_t tid[NbTrains];
	createVoie();
	//getchar();
	int rc,k;
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
	    usleep(1000000);
    }




    int i;
   	for(i=0;i<NbTrains;i ++){
   		pthread_join(tid[i],NULL);
   	}
   	printf("\n\nFermeture de la gare pour cause d'état d'urgence!\n\n");
   	deleteVoie();
   	pthread_exit(NULL);
   	return(0);
}
