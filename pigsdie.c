#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int health = 100;
int money = 100;
int day = 1;

void genChoice(void); // Duplicate to tell travel() that it exists

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
        day = day + 1;
        printf("\nYou traveled to %s.\n", cities[city_choice - 1]);
        return;
    } else {
        int c; // Clear buffer
        while ((c = getchar()) != '\n' && c != EOF) { } // Clear buffer
        genChoice();
    }
}

void genDrugs(void){

    int genCoke = 300 + (rand() % 3500);
    printf("%-10s %d\n", "Coke:", genCoke);

    int genMary = 80 + (rand() % 1200);
    printf("%-10s %d\n", "Weed:", genMary);

    int genHeron = 100 + (rand() % 2500);
    printf("%-10s %d\n", "Heroin:", genHeron);

}

void buy(void){

}

void sell(void){

}

void genChoice(void) {
    char choice;

    while (1) {
        printf("\nWhat do you want to do?\n");
        printf("[t]ravel, [b]uy, [s]ell, [q]uit\n");

        scanf(" %c", &choice);

        if (choice == 't' || choice == 'T') {
            travel();
        }
        else if (choice == 'b' || choice == 'B') {
            buy();
        }
        else if (choice == 's' || choice == 'S') {
            sell();
        }
        else if (choice == 'q' || choice == 'Q') {
            printf("See ya!\n");
            break;   /* exits the while(1) loop */
        }
        else {
            printf("Invalid choice.\n");
        }
    }
}

int main (void) {
    
    int mary, coke, heron;



    srand(time(NULL));
    int randomNumber = (rand() % 5) + 1;
    printf("%d\n", randomNumber);

    if (randomNumber == 1 ){
        printf("Cops! Tuck your butthole\n");
    }

    printf("======= Day %d =======\n\n", day);

    printf("Health: %d\n", health);
    printf("Money: %d\n\n", money);

    printf("WeLcOme 2 dA cItY!\n\n");

    genDrugs();
    genChoice();



}