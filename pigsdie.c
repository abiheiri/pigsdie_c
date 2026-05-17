#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int health = 100;
int money = 100;
int day = 1;
int bullets = 0;
int mary, coke, heron = 0;

void clearScreen() {
    printf("\033[2J\033[H");  // Clear screen and move cursor to top-left
    fflush(stdout);            // Ensure it prints immediately
}

void genChoice(void); // Duplicate to tell travel() that it exists

void genDrugs(void){

    int genCoke = 300 + (rand() % 3500);
    printf("%-10s %d\n", "Coke:", genCoke);

    int genMary = 80 + (rand() % 1200);
    printf("%-10s %d\n", "Weed:", genMary);

    int genHeron = 100 + (rand() % 2500);
    printf("%-10s %d\n", "Heroin:", genHeron);

}

void genStats(void){
    printf("======= Day %d =======\n\n", day);

    printf("Health: %d\n", health);
    printf("Money: %d\n\n", money);
}

void genInventory(void){
    printf("Your inventory is:\n");
    printf("Weed: %d\nCoke: %d\nHeroin: %d\nBullets: %d\n", mary, coke, heron, bullets);
}

void genCops(void){
    srand(time(NULL));
    int randomNumber = (rand() % 5) + 1;
    printf("DEBUG COPS: %d\n", randomNumber);

    if (randomNumber == 1 ){
            char choice;

        while (1) {
            printf("Shit, its the cops! What should we do?\n");
            printf("[r]un, [s]hoot them, [g]ive up, [q]uit\n");

            scanf(" %c", &choice);

            if (choice == 'r' || choice == 'R') {
                break;
            }
            else if (choice == 's' || choice == 'S') {
                break;
            }
            else if (choice == 'g' || choice == 'G') {
                printf ("Cops took all your stuff and held you in prison for 10 days.\n");
                day = day + 10;
                mary = 0; 
                coke = 0;
                heron = 0;
                genChoice();
            }
            else if (choice == 'q' || choice == 'Q') {
                printf("See ya!\n");
                break;
            }
            else {
                printf("Invalid choice.\n");
            }
        }
    }
}

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
        clearScreen();
        printf("\nYou traveled to %s.\n", cities[city_choice - 1]);
        genCops();
        genStats();
        genDrugs();
        return;
    } else {
        int c; // Clear buffer
        while ((c = getchar()) != '\n' && c != EOF) { } // Clear buffer
        genChoice();
    }

}


void buy(void){

}

void sell(void){

}

void genChoice(void) {

    if ( day >= 30 ) {
        printf ("!!! GaMe OvEr !!!\n");
        printf ("Results:\n");
        exit(0);
    }
    
    char choice;

    while (1) {
        printf("\nWhat do you want to do?\n");
        printf("[t]ravel, [b]uy, [s]ell, [i]nventory, [q]uit\n");

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
        else if (choice == 'i' || choice == 'I') {
            genInventory();
        }
        else if (choice == 'q' || choice == 'Q') {
            printf("See ya!\n");
            break;
        }
        else {
            printf("Invalid choice.\n");
        }
    }
}

int main (void) {

    genCops();
    genStats();

    printf("WeLcOme 2 dA cItY!\n\n");

    genDrugs();
    genChoice();

}