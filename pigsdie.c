/*
 * pigsdie.c — A not very faithful clone of Drug Wars.
 *
 * Author:  AL Biheiri <al@forgottheaddress.com>
 * Version: v1.0.2
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int health;
    int money;
    int day;
    int bullets;
    int weed;
    int coke;
    int heroin;
    int pocket_space;
    int pocket_used;
    int level;
    int skill;
} Player;

int weed_price, coke_price, heroin_price;

void gen_choice(Player *p); // Duplicate to tell travel() that it exists

void clear_screen() {
    printf("\033[2J\033[H");  // Clear screen and move cursor to top-left
    fflush(stdout);            // Ensure it prints immediately
}

int read_int(const char *prompt) { // We validate the user is passing an int
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

void gen_drugs(void){

    coke_price = 300 + (rand() % 3500);
    printf("%-10s %d\n", "Coke:", coke_price);

    weed_price = 80 + (rand() % 800);
    printf("%-10s %d\n", "Weed:", weed_price);

    heroin_price = 100 + (rand() % 2500);
    printf("%-10s %d\n", "Heroin:", heroin_price);

}

void gen_stats(Player *p){
    printf("======= Day %d =======\n\n", p->day);
    printf("Health: %d\nMoney: %d\nSkill: %d\nYour Level: %d\n", p->health, p->money, p->skill, p->level + 1);
}

void gen_inventory(Player *p){
    printf("Your inventory is:\n");
    printf("====\n");
    printf("Weed: %d\nCoke: %d\nHeroin: %d\nBullets: %d\n", p->weed, p->coke, p->heroin, p->bullets);
    printf("====\n");
    printf("Pocket space: %d\nPockets used: %d\nMoney: %d\nHealth: %d\n", p->pocket_space, p->pocket_used, p->money, p->health);
}

void check_game_over(Player *p) {
    if (p->day >= 30 || p->health <= 0 || p->skill < 0) {
        clear_screen();
        printf ("!!! GaMe OvEr !!!\n");
        if (p->health <= 0) {
            printf("You died like a bitch.\n");
        }
        else if (p->skill < 0) {
            printf("Your skill dropped too low for the streets to trust you.\n");
        }
        else if (p->day >= 30) {
            printf("Time's up! 30 days have passed.\n");
        }
        printf ("Results:\n");
        gen_stats(p);
        gen_inventory(p);
        exit(0);
    }
}

void gen_cops(Player *p){
    int randomNumber = (rand() % 5) + 1;
    // printf("DEBUG COPS: %d\n", randomNumber);

    if (randomNumber == 1 ){
            char choice;

        while (1) {

            clear_screen();
            int cop_count = (rand() % 4) + 1;
            printf("Shit, -> %d <- cops are after you! What should we do?\n", cop_count);
            printf("[r]un, [s]hoot them, [g]ive up\n");

            scanf(" %c", &choice);

            if (choice == 'r' || choice == 'R') {
                int escape_chance = (rand() % 3) + 1;
                if (escape_chance == 1){
                    printf("You got Hit!! -50 life\n");
                    p->health -= 50;
                    p->skill--;
                    check_game_over(p);
                }
                else {
                    printf("You ran away... NOICE!\n");
                    p->skill++;
                }
                break;
            }
            else if (choice == 's' || choice == 'S') {
                if (p->bullets <= 0){
                    printf ("Shit! You dont have bullets!\nCops took all your stuff and held you in prison for 10 days.\n");
                    p->day = p->day + 10;
                    p->weed = 0; 
                    p->coke = 0;
                    p->heroin = 0;
                    p->skill--;
                    check_game_over(p);
                    break;
                }
                while (cop_count > 0 ){
                    if (p->bullets <= 0) {
                        printf ("Shit! You ran out of bullets!\nCops took all your stuff and held you in prison for 10 days.\n");
                        p->day = p->day + 10;
                        p->weed = 0; 
                        p->coke = 0;
                        p->heroin = 0;
                        p->skill--;
                        check_game_over(p);
                        break;
                    }

                    int bullets_wasted = (rand() % 4) + 1; // Rando bullet costs
                    int cop_hit = (rand() % 2) + 1; // Rando cop hit or not

                    p->bullets = p->bullets - bullets_wasted;

                    if (cop_hit == 1){
                        printf("You killed a cop....Yeeesh!\n");
                        cop_count--;
                        p->skill++;
                        if (cop_count >= 1){
                            printf("You have %d cops still remaining\n", cop_count);
                        }
                    }
                    else {
                        printf("Faaaaack! You missed a cop!\n");
                        p->skill--;
                        p->health--;
                        if (p->health <= 0) {
                            check_game_over(p);
                        }
                    }

                    if (cop_count > 0 && p->bullets > 0) {
                        printf("[s]hoot again or [r]un?\n");
                        char shoot_choice;
                        scanf(" %c", &shoot_choice);
                        if (shoot_choice == 'r' || shoot_choice == 'R') {
                            int escape_chance = (rand() % 3) + 1;
                            if (escape_chance == 1){
                                printf("You got Hit!! -50 life\n");
                                p->health -= 50;
                                p->skill--;
                                check_game_over(p);
                            }
                            else {
                                printf("You ran away... NOICE!\n");
                                p->skill++;
                            }
                            break;
                        }
                    }
                }
                break;
            }
            else if (choice == 'g' || choice == 'G') {
                clear_screen();
                printf ("Cops took all your stuff and held you in prison for 10 days.\n");
                p->day = p->day + 10;
                p->weed = 0; 
                p->coke = 0;
                p->heroin = 0;
                p->skill -= 50;
                check_game_over(p);
                break;
            }
            else {
                printf("Invalid choice.\n");
            }
        }
    }
}

void travel(Player *p) {

    check_game_over(p);

    int new_level = p->skill / 100; // int division; skill = 150 → new_level = 1
    while (new_level > p->level) {
        p->level++;
        p->pocket_space += 100;
        printf("Leveled up! You can now hold %d units.\n", p->pocket_space);
    }

    char *cities[] = {"Bronx", "Manhattan", "Queens", "Staten Island", "Brooklyn"};
    int num_cities = sizeof(cities) / sizeof(cities[0]);
    int city_choice;

    printf("\nWhere do you want to go?\n");
    for (int i = 0; i < num_cities; i++) {
        printf("  %d. %s\n", i + 1, cities[i]);
    }
    printf("\nSelect (1-%d): ", num_cities);
    city_choice = read_int("");

    if (city_choice >= 1 && city_choice <= num_cities) {
        p->day = p->day + 1;
        clear_screen();
        printf("\nYou traveled to %s.\n", cities[city_choice - 1]);
        
        int rando_thief = (rand() % 4) + 1;
        if (rando_thief == 1){
            printf("!!!! While traveling today, you got robbed in the subway !!!!\n");
            p->skill--;
            p->weed -= 5 * (p->weed > 5);
            p->coke -= (p->coke > 1);
            p->heroin -= (p->heroin > 1);
            p->bullets -= (p->bullets > 1);
        }
        else {
            gen_cops(p);
        }

        gen_stats(p);
        printf("\n========\n\n");
        gen_drugs();
        return;
    } else {
        int c; // Clear buffer
        while ((c = getchar()) != '\n' && c != EOF) { } // Clear buffer
        gen_choice(p);
    }

}

void buy(Player *p){
    char choice;
    int response;

    while (1) {
        printf("\nWhat do you want to buy?\n");
        printf("[w]eed, [c]oke, [h]eroin, [b]ullets, [l]eave\n");

        scanf(" %c", &choice);

        if (choice == 'w' || choice == 'W') {
            
            int max_afford = p->money / weed_price;
            
            printf("How many do you want to buy? (Max you can afford is %d)\n", max_afford);
            response = read_int("");

            if (response > max_afford) {
                printf("You can only afford %d units.\n", max_afford);
                response = max_afford;
            }
            if (response > p->pocket_space) {
                printf("You only have space for %d units.\n", p->pocket_space);
                response = p->pocket_space;
            }
            if (response > 0) {
                p->pocket_used += response;
                p->pocket_space -= response;
                p->weed += response;
                p->money -= response * weed_price;
                p->skill += 10;
            } else {
                printf("Dumbass, you're broke homie!\n");
            }
        }
        else if (choice == 'c' || choice == 'C') {
            int max_afford = p->money / coke_price;

            printf("How many do you want to buy? (Max you can afford is %d)\n", max_afford);
            response = read_int("");

            if (response > max_afford) {
                printf("You can only afford %d units.\n", max_afford);
                response = max_afford;
            }
            if (response > p->pocket_space) {
                printf("You only have space for %d units.\n", p->pocket_space);
                response = p->pocket_space;
            }
            if (response > 0) {
                p->pocket_used += response;
                p->pocket_space -= response;
                p->coke += response;
                p->money -= response * coke_price;
                p->skill += 30;
            } else {
                printf("Dumbass, you're broke homie!\n");
            }
        }
        else if (choice == 'h' || choice == 'H') {
            int max_afford = p->money / heroin_price;
            
            printf("How many do you want to buy? (Max you can afford is %d)\n", max_afford);
            response = read_int("");

            if (response > max_afford) {
                printf("You can only afford %d units.\n", max_afford);
                response = max_afford;
            }
            if (response > p->pocket_space) {
                printf("You only have space for %d units.\n", p->pocket_space);
                response = p->pocket_space;
            }
            if (response > 0) {
                p->pocket_used += response;
                p->pocket_space -= response;
                p->heroin += response;
                p->money -= response * heroin_price;
                p->skill += 20;
            } else {
                printf("Dumbass, you're broke homie!\n");
            }

        }
        else if (choice == 'b' || choice == 'B') {

            if (p->money > 0){
                int bullet_price = (rand() % 50) + 1;

                printf("Todays prices for bullets are $%d. Do you still want to purchase? <y/n>\n", bullet_price);
                char buyBullets;
                scanf(" %c", &buyBullets);
                if (buyBullets == 'y' || buyBullets == 'Y') {
                    printf("How many do you want to buy?");
                    response = read_int("");

                    if (response > p->pocket_space) {
                        printf("You only have space for %d units.\n", p->pocket_space);
                        response = p->pocket_space;
                    }
                    
                    if (p->money >= response * bullet_price && response > 0) {
                        p->money -= response * bullet_price;
                        p->bullets += response;
                        p->pocket_used += response;
                        p->pocket_space -= response;
                        printf("You bought %d bullets.\n", response);
                    }
                    else if (response > 0) {
                        printf("Nah bro, You dont got that much money to buy $%d\n", response * bullet_price);
                    }
                }
            }
            else {
                printf("You dont have the money to buy bullets. You have $%d\n", p->money);
            }
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

void sell(Player *p){

    char choice;
    int response;

    while (1) {
        printf("\nWhat do you want to sell?\n");
        printf("[w]eed, [c]oke, [h]eroin, [l]eave\n");

        scanf(" %c", &choice);

        if (choice == 'w' || choice == 'W') {
            printf("How many do you want to sell? (You have %d units)\n", p->weed);
            response = read_int("");

            if (response > p->weed) {
                printf("You only have %d units.\n", p->weed);
            }
            else if (response > 0) {
                p->pocket_used -= response;
                p->pocket_space += response;
                p->weed -= response;
                p->money += response * weed_price;
                p->skill += 10;
            }
        }
        else if (choice == 'c' || choice == 'C') {
            printf("How many do you want to sell? (You have %d units)\n", p->coke);
            response = read_int("");

            if (response > p->coke) {
                printf("You only have %d units.\n", p->coke);
            }
            else if (response > 0) {
                p->pocket_used -= response;
                p->pocket_space += response;
                p->coke -= response;
                p->money += response * coke_price;
                p->skill += 30;
            }
        }
        else if (choice == 'h' || choice == 'H') {
            printf("How many do you want to sell? (You have %d units)\n", p->heroin);
            response = read_int("");

            if (response > p->heroin) {
                printf("You only have %d units.\n", p->heroin);
            }
            else if (response > 0) {
                p->pocket_used -= response;
                p->pocket_space += response;
                p->heroin -= response;
                p->money += response * heroin_price;
                p->skill += 20;
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

void gen_choice(Player *p) {
    
    char choice;

    while (1) {
        printf("\nWhat do you want to do?\n");
        printf("[t]ravel, [b]uy, [s]ell, [i]nventory, [q]uit\n");

        scanf(" %c", &choice);

        if (choice == 't' || choice == 'T') {
            travel(p);
        }
        else if (choice == 'b' || choice == 'B') {
            buy(p);
        }
        else if (choice == 's' || choice == 'S') {
            sell(p);
        }
        else if (choice == 'i' || choice == 'I') {
            gen_inventory(p);
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

    Player player = {
        .health = 100,
        .money = 1000,
        .day = 1,
        .bullets = 0,
        .weed = 0,
        .coke = 0,
        .heroin = 0,
        .pocket_space = 10,
        .pocket_used = 0,
        .level = 0,
        .skill = 1
    };

    srand(time(NULL)); // Rando generator for services that leverage it later.
    clear_screen();
    printf("WeLcOme 2 dA cItY!\n\n");
    gen_stats(&player);
    printf("\n========\n\n");
    gen_drugs();
    gen_choice(&player);

}
