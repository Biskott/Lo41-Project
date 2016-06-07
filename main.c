#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "train.c"

int main()
{
    printf("Salut !\n");
    Train* T[8];
    srand(time(NULL));
    for(int i=0; i<8; i++){
    	T[i]=randomTrain(i);
    	printf(" %i",(rand()%18));
    }


    return 0;
}
