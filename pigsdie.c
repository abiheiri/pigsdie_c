#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main (void) {
    
    int mary, coke, heron;

    srand(time(NULL));
    int randomNumber = (rand() % 3) + 1;
    printf("%d\n", randomNumber);

    if (randomNumber == 1 ){
        printf("Cops! Tuck your butthole\n");

    }

    int genCoke = 300 + (rand() % 3500);
    printf("%-10s %d\n", "Coke:", genCoke);

    int genMary = 80 + (rand() % 1200);
    printf("%-10s %d\n", "Weed:", genMary);

    int genHeron = 100 + (rand() % 2500);
    printf("%-10s %d\n", "Heroin:", genHeron);

    
}