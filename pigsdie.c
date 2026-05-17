#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int health = 100;
int money = 1000;
int day = 1;
int bullets = 0;
int weed, coke, heroin = 0;
int my_weed, my_coke, my_heroin = 0;
int pocket_space = 10;
int pocket_used = 0;
int level, skill = 1;

void genChoice(void); // Duplicate to tell travel() that it exists

void clearScreen() {
    printf("\033[2J\033[H");  // Clear screen and move cursor to top-left
    fflush(stdout);            // Ensure it prints immediately
}

int readInt(const char *prompt) { // We validate the user is passing an int
    int value;
    int result;
    while (1) {
        printf("%s", prompt);
        result = scanf("%d", &value);
        if (result == 1) {
            return value;
        }
        printf("Invalid input. Please enter a number.\n");
        // Clear buffer
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}
    }
}

void genDrugs(void){

    coke = 300 + (rand() % 3500);
    printf("%-10s %d\n", "Coke:", coke);

    weed = 80 + (rand() % 800);
    printf("%-10s %d\n", "Weed:", weed);

    heroin = 100 + (rand() % 2500);
    printf("%-10s %d\n", "Heroin:", heroin);

}

void genStats(void){
    printf("======= Day %d =======\n\n", day);

    printf("Health: %d\n", health);
    printf("Money: %d\n\n", money);
}

void genInventory(void){
    printf("Your inventory is:\n");
    printf("====\n");
    printf("Weed: %d\nCoke: %d\nHeroin: %d\nBullets: %d\n", my_weed, my_coke, my_heroin, bullets);
    printf("====\n");
    printf("Pocket space: %d\nPockets used: %d\nMoney: %d\nHealth: %d", pocket_space, pocket_used, money, health);
}

void genCops(void){
    srand(time(NULL));
    int randomNumber = (rand() % 5) + 1;
    printf("DEBUG COPS: %d\n", randomNumber);

    if (randomNumber == 1 ){
            char choice;

        while (1) {
            printf("Shit, its the cops! What should we do?\n");
            printf("[r]un, [s]hoot them, [g]ive up\n");

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
                my_weed = 0; 
                my_coke = 0;
                my_heroin = 0;
                break;
            }
            else {
                printf("Invalid choice.\n");
            }
        }
    }
}

void travel(void) {

    if ( day >= 30 ) {
        printf ("!!! GaMe OvEr !!!\n");
        printf ("Results:\n");
        genStats();
        exit(0);
    }

    char *cities[] = {"Bronx", "Manhattan", "Queens", "Staten Island", "Brooklyn"};
    int num_cities = sizeof(cities) / sizeof(cities[0]);
    int city_choice;

    printf("\nWhere do you want to go?\n");
    for (int i = 0; i < num_cities; i++) {
        printf("  %d. %s\n", i + 1, cities[i]);
    }
    printf("\nSelect (1-%d): ", num_cities);
    city_choice = readInt("");

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
    char choice;
    int num, result, response;

    while (1) {
        printf("\nWhat do you want to buy?\n");
        printf("[w]eed, [c]oke, [h]erion, [b]ullets, [l]eave\n");

        scanf(" %c", &choice);

        if (choice == 'w' || choice == 'W') {
            printf("How many do you want to buy?\n");
            response = readInt(""); // Validate its a number
            
            if (response > pocket_space) {
                printf("You dont have the space for %d. You only have %d pocket space.\n", response, pocket_space);
            }
            else if (weed > money){
                printf("You dont have enough money to buy. It costs %d and you have $%d\n", weed, money);
            }
            else {
                my_weed = my_weed + response;
                pocket_used = pocket_used + response;
                pocket_space = pocket_space - response;
                money = money - (response * weed);
                skill += 10;
            }
        }
        else if (choice == 'c' || choice == 'C') {

            printf("How many do you want to buy?\n");
            response = readInt(""); // Validate its a number
            
            if (response > pocket_space) {
                printf("You dont have the space for %d. You only have %d pocket space.\n", response, pocket_space);
            }
            else if (weed > money){
                printf("You dont have enough money to buy. It costs %d and you have $%d\n", coke, money);
            }
            else {
                my_coke = my_coke + response;
                pocket_used = pocket_used + response;
                pocket_space = pocket_space - response;
                money = money - (response * coke);
                skill += 20;
            }

        }
        else if (choice == 'h' || choice == 'H') {

            printf("How many do you want to buy?\n");
            response = readInt(""); // Validate its a number
            
            if (response > pocket_space) {
                printf("You dont have the space for %d. You only have %d pocket space.\n", response, pocket_space);
            }
            else if (weed > money){
                printf("You dont have enough money to buy. It costs %d and you have $%d\n", heroin, money);
            }
            else {
                my_heroin = my_heroin + response;
                pocket_used = pocket_used + response;
                pocket_space = pocket_space - response;
                money = money - (response * heroin);
                skill += 20;
            }

        }
        else if (choice == 'b' || choice == 'B') {
            break;
        }
        else if (choice == 'l' || choice == 'l') {
            printf("See ya!\n");
            break;
        }
        else {
            printf("Invalid choice.\n");
        }
    }
}

void sell(void){
    
}

void genChoice(void) {
    
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