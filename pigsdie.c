#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main (void) {
    
    int mary, coke, weed;

    srand(time(NULL));
    int randomNumber = (rand() % 3) + 1;
    printf("%d\n", randomNumber);

    if (randomNumber == 1 ){
        printf("Cops! Tuck your butthole\n");

    }

}