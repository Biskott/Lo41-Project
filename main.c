#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "train.c"

int main()
{
	srand(time(NULL));
    //printf("Salut !\n");
    Train* T[8];
    int i;
    for(i=0; i<8; i++){
    	T[i]=randomTrain(i);
    }
}
