#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void travel(void) {

    char *cities[] = {"Bronx", "Manhattan", "Queens", "Staten Island", "Brooklyn"};
    int num_cities = sizeof(cities) / sizeof(cities[0]);
    int city_choice;

    printf("\nWhere do you want to go?\n");
    for (int i = 0; i < num_cities; i++) {
        printf("  %d. %s\n", i + 1, cities[i]);
    }
    printf("\nSelect (1-%d): ", num_cities);
    scanf("%d", &city_choice);

    if (city_choice >= 1 && city_choice <= num_cities) {
        printf("\nYou traveled to %s.\n", cities[city_choice - 1]);
    } else {
        printf("\nInvalid choice.\n");
    }
}

int main (void) {
    
    int mary, coke, heron;
    int health = 100;
    int money = 100;
    int day = 1;

    char choice;

    srand(time(NULL));
    int randomNumber = (rand() % 5) + 1;
    printf("%d\n", randomNumber);

    if (randomNumber == 1 ){
        printf("Cops! Tuck your butthole\n");
    }

    printf("======= Day %d =======\n\n", day);

    printf("==== Stats ====\n");
    printf("Health: %d\n\n", health);

    printf("WeLcOme 2 dA cItY!\n\n");

    int genCoke = 300 + (rand() % 3500);
    printf("%-10s %d\n", "Coke:", genCoke);

    int genMary = 80 + (rand() % 1200);
    printf("%-10s %d\n", "Weed:", genMary);

    int genHeron = 100 + (rand() % 2500);
    printf("%-10s %d\n", "Heroin:", genHeron);

    printf("What do you want to do?\n");
    printf ("[t]ravel, [b]uy, [s]ell\n");

    scanf(" %c", &choice);

    if (choice == 't' || choice == 't') {
        travel();
    }


}