#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int health = 100;
int money = 1000;
int day = 1;
int bullets = 0;
int weed, coke, heroin;
int my_weed, my_coke, my_heroin = 0;
int pocket_space = 10;
int pocket_used = 0;
int level = 0;
int skill = 1;

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
    printf("Health: %d\nMoney: %d\nSkill: %d\nYour Level: %d\n", health, money, skill, level + 1);
}

void genInventory(void){
    printf("Your inventory is:\n");
    printf("====\n");
    printf("Weed: %d\nCoke: %d\nHeroin: %d\nBullets: %d\n", my_weed, my_coke, my_heroin, bullets);
    printf("====\n");
    printf("Pocket space: %d\nPockets used: %d\nMoney: %d\nHealth: %d", pocket_space, pocket_used, money, health);
}

void checkGameOver(void) {
    if (day >= 30 || health <= 0 || skill < 0) {
        clearScreen();
        printf ("!!! GaMe OvEr !!!\n");
        printf ("Results:\n");
        genStats();
        genInventory();
        exit(0);
    }
}

void genCops(void){
    int randomNumber = (rand() % 5) + 1;
    // printf("DEBUG COPS: %d\n", randomNumber);

    if (randomNumber == 1 ){
            char choice;

        while (1) {

            clearScreen();
            int cop_count = (rand() % 4) + 1;
            printf("Shit, -> %d <- cops are after you! What should we do?\n", cop_count);
            printf("[r]un, [s]hoot them, [g]ive up\n");

            scanf(" %c", &choice);

            if (choice == 'r' || choice == 'R') {
                int escape_chance = (rand() % 3) + 1;
                if (escape_chance == 1){
                    printf("You got Hit!! -50 life\n");
                    health -= 50;
                    skill--;
                    checkGameOver();
                }
                else {
                    printf("You ran away... NOICE!\n");
                    skill++;
                }
                break;
            }
            else if (choice == 's' || choice == 'S') {
                if (bullets <= 0){
                    printf ("Shit! You dont have bullets!\nCops took all your stuff and held you in prison for 10 days.\n");
                    day = day + 10;
                    my_weed = 0; 
                    my_coke = 0;
                    my_heroin = 0;
                    skill--;
                    checkGameOver();
                    break;
                }
                while (cop_count > 0 ){
                    if (bullets <= 0) {
                        printf ("Shit! You ran out of bullets!\nCops took all your stuff and held you in prison for 10 days.\n");
                        day = day + 10;
                        my_weed = 0; 
                        my_coke = 0;
                        my_heroin = 0;
                        skill--;
                        checkGameOver();
                        break;
                    }

                    int bullets_wasted = (rand() % 4) + 1; // Rando bullet costs
                    int cop_hit = (rand() % 2) + 1; // Rando cop hit or not

                    bullets = bullets - bullets_wasted;

                    if (cop_hit == 1){
                        printf("You killed a cop....Yeeesh!\n");
                        cop_count--;
                        skill++;
                        if (cop_count >= 1){
                            printf("You have %d cops still remaining\n", cop_count);
                        }
                    }
                    else {
                        printf("Faaaaack! You missed a cop!\n");
                        skill--;
                        health--;
                        if (health <= 0) {
                            checkGameOver();
                        }
                    }
                }
                break;
            }
            else if (choice == 'g' || choice == 'G') {
                clearScreen();
                printf ("Cops took all your stuff and held you in prison for 10 days.\n");
                day = day + 10;
                my_weed = 0; 
                my_coke = 0;
                my_heroin = 0;
                skill -= 50;
                checkGameOver();
                break;
            }
            else {
                printf("Invalid choice.\n");
            }
        }
    }
}

void travel(void) {

    checkGameOver();

    int new_level = skill / 100;
    while (new_level > level) {
        level++;
        pocket_space += 100;
        printf("Leveled up! You can now hold %d units.\n", pocket_space);
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
        
        int rando_thief = (rand() % 3) + 1;
        if (rando_thief == 1){
            printf("While traveling today, you got robbed in the subway.\n");
            skill--;
            my_weed -= 5 * (my_weed > 5);
            my_coke -= (my_coke > 1);
            my_heroin -= (my_heroin > 1);
            bullets -= (bullets > 1);
        }
        else {
            genCops();
        }

        genStats();
        printf("\n========\n\n");
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
        printf("[w]eed, [c]oke, [h]eroin, [b]ullets, [l]eave\n");

        scanf(" %c", &choice);

        if (choice == 'w' || choice == 'W') {
            
            int max_afford = money / weed;
            
            printf("How many do you want to buy? (Max you can afford is %d)\n", max_afford);
            response = readInt("");

            if (response > max_afford) {
                printf("You can only afford %d units.\n", max_afford);
                response = max_afford;
            }
            if (response > pocket_space) {
                printf("You only have space for %d units.\n", pocket_space);
                response = pocket_space;
            }
            if (response > 0) {
                pocket_used += response;
                pocket_space -= response;
                my_weed += response;
                money -= response * weed;
                skill += 10;
            } else {
                printf("Dumbass, you're broke homie!\n");
            }
        }
        else if (choice == 'c' || choice == 'C') {
            int max_afford = money / coke;

            printf("How many do you want to buy? (Max you can afford is %d)\n", max_afford);
            response = readInt("");

            if (response > max_afford) {
                printf("You can only afford %d units.\n", max_afford);
                response = max_afford;
            }
            if (response > pocket_space) {
                printf("You only have space for %d units.\n", pocket_space);
                response = pocket_space;
            }
            if (response > 0) {
                pocket_used += response;
                pocket_space -= response;
                my_coke += response;
                money -= response * coke;
                skill += 30;
            } else {
                printf("Dumbass, you're broke homie!\n");
            }
        }
        else if (choice == 'h' || choice == 'H') {
            int max_afford = money / heroin;
            
            printf("How many do you want to buy? (Max you can afford is %d)\n", max_afford);
            response = readInt("");

            if (response > max_afford) {
                printf("You can only afford %d units.\n", max_afford);
                response = max_afford;
            }
            if (response > pocket_space) {
                printf("You only have space for %d units.\n", pocket_space);
                response = pocket_space;
            }
            if (response > 0) {
                pocket_used += response;
                pocket_space -= response;
                my_heroin += response;
                money -= response * heroin;
                skill += 20;
            } else {
                printf("Dumbass, you're broke homie!\n");
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

    char choice;
    int num, result, response;

    while (1) {
        printf("\nWhat do you want to sell?\n");
        printf("[w]eed, [c]oke, [h]eroin, [l]eave\n");

        scanf(" %c", &choice);

        if (choice == 'w' || choice == 'W') {
            printf("How many do you want to sell? (You have %d units)\n", my_weed);
            response = readInt("");

            if (response > my_weed) {
                printf("You only have %d units.\n", my_weed);
            }
            else if (response > 0) {
                pocket_used -= response;
                pocket_space += response;
                my_weed -= response;
                money += response * weed;
                skill += 10;
            }
        }
        else if (choice == 'c' || choice == 'C') {
            printf("How many do you want to sell? (You have %d units)\n", my_coke);
            response = readInt("");

            if (response > my_coke) {
                printf("You only have %d units.\n", my_coke);
            }
            else if (response > 0) {
                pocket_used -= response;
                pocket_space += response;
                my_coke -= response;
                money += response * coke;
                skill += 30;
            }
        }
        else if (choice == 'h' || choice == 'H') {
            printf("How many do you want to sell? (You have %d units)\n", my_heroin);
            response = readInt("");

            if (response > my_heroin) {
                printf("You only have %d units.\n", my_heroin);
            }
            else if (response > 0) {
                pocket_used -= response;
                pocket_space += response;
                my_heroin -= response;
                money += response * heroin;
                skill += 20;
            }
        }
        else if (choice == 'l' || choice == 'L') {
            break;
        }
        else {
            printf("Invalid choice.\n");
        }
    }
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

    srand(time(NULL)); // Rando generator for services that leverage it later.
    clearScreen();
    printf("WeLcOme 2 dA cItY!\n\n");
    genStats();
    printf("\n========\n\n");
    genDrugs();
    genChoice();

}