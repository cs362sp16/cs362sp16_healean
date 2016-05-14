/*
 * Created by: Nathan Healea
 * Date: May 11, 2016
 * Assignment 2
 * File name: randometestadventurer.c
 * Description:
 *      Random testing adventurer card effect
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <math.h>

int gen_random(int min, int max);

int main(int argc, char **argv) {
    srand(time(NULL));

    printf("/* ----------------------- */\n");
    printf("/*  Random Test Adventure  */\n");
    printf("/* ----------------------- */\n\n");

    // Defining variables
    struct gameState gamestate;    // Hold the game state
    int kCard[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
    int i;  // Loop irritater
    int j;  // Loop irritater
    int currentplayer;
    int choise1 = -1;
    int choice2 = -1;
    int choice3 = -1;
    int handPos = -1;
    int bonus = 0;
    int curr_coins;
    int test_pass = 1; // 0 == false: failing test, 1 == true: all test passed


    for (i = 0; i < gen_random(0,100); i++) { // number of random games to be tested
        initializeGame(gen_random(2,4), kCard, gen_random(1,9), &gamestate);

        currentplayer = gamestate.whoseTurn; // Initialize and get current player


        for (j = 0; j < 100; j++) { // number of test to run for current initialized game.
            curr_coins = gamestate.coins;

            cardEffect(adventurer, choise1, choice2, choice3, &gamestate, handPos, &bonus);

            if(curr_coins > gamestate.coins){
                printf("Error: curr_coins [%d] game.coins[%d]\n", curr_coins, gamestate.coins);
                test_pass = 0;
            }

        }
    }

    if(test_pass) {
        printf("All test have passed. \n");
    }

    return 0;
}

int gen_random(int min_num, int max_num){
    int return_num = 0;
    int low_num = 0;
    int high_num = 0;

    if(min_num < max_num){ // if min is less then max set low and high
        low_num = min_num;
        high_num = max_num;
    }
    else{ // if min is greater max them set min to high and max to low
        low_num = max_num + 1;
        high_num = min_num;
    }

    return_num = rand()%(high_num - low_num) + low_num;
    return return_num;
}
