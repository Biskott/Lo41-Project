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
   	voieL =sem_open("/voieL", O_RDWR | O_CREAT, 0666, 1);
}

void deleteVoie(){
	sem_destroy(voieA);
   	sem_destroy(voieB);
   	sem_destroy(voieC);
   	sem_destroy(voieD);
   	sem_destroy(aig1);
   	sem_destroy(aig2);
   	sem_destroy(gTGV);
   	sem_destroy(gM2);
   	sem_destroy(gM1);
   	sem_destroy(gGL);
   	sem_destroy(tunnel);
   	sem_destroy(voieL);
}

void TGV_EO ()
{
	printf("TGV_EO\n");
	pthread_setschedprio(pthread_self(), 20);
}

void TGV_OE ()
{
	printf("TGV_OE\n");
	pthread_setschedprio(pthread_self(), 20);
}

void GL_EO ()
{
	printf("GL_EO\n");

	pthread_setschedprio(pthread_self(), 5);
}

void GL_OE ()
{
	printf("GL_OE\n");
	pthread_setschedprio(pthread_self(), 5);
}

void M_EO ()
{
	printf("M_EO\n");
	pthread_setschedprio(pthread_self(), 1);
}	

void M_OE ()
{
	printf("M_OE\n");
	pthread_setschedprio(pthread_self(), 1);
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
	//greve();
	srand(time(NULL));
	int NbTrains = (argc > 1 ? atoi(argv[1]) : NB_TRAINS); 
	/* nombre de trains déf en paramètre ou via la constante */
	printf("nbtrains : %i \n",NbTrains);
	int NumTrain =0;
	pthread_t tid[NbTrains];
	createVoie();
	//getchar();
	int rc,j;
	for(j=0;j<NbTrains;j ++){
		
		//getchar();
        if(rc=pthread_create(&(tid[j]), NULL, fonc_Train, (void*)j)!=0){
        	printf("Erreur dans la creation du thread %i",j);
			return EXIT_FAILURE;
    	}
    	else{
    		
    		NumTrain++;
    	}
    }

    int i;
   	for(i=0;i<NbTrains;i ++){
   		pthread_join(tid[i],NULL);
   	}



   	printf("FIN\n");
   	deleteVoie();
   	pthread_exit(NULL);
   	return(0);
}
