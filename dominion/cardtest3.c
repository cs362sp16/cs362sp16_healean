/*
 * Created by: Nathan Healea
 * Date: April 26, 2016
 * Assignment 2
 * File name: cardtest3.c
 * Description:
 *      Testing card effect smithy
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
#define MIN_PLAYERS 2


int main(int argc, char **argv) {

    printf("/* ---------------- */\n");
    printf("/*    Cardtest3     */\n");
    printf("/* ---------------- */\n\n");

    // Defining game variables
    struct gameState *gamestate = newGame();    // Hold the game state
    int kCard[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

    // Loop variables
    int i = 0;
    int j = 0;

    // Testing Result
    int testResult = 0;
    int overall = 0;
    int expectedHandCount = 0;

    // Testing parameters
    int card = smithy; //Set the flag for the current card
    int choice1 = -1;
    int choice2 = -1;
    int choice3 = -1;
    int handPos = -1;
    int *bonus = 0; //tracks coins gained from actions

    // Test Variables


    for (i = MIN_PLAYERS; i < MAX_PLAYERS; i++) { // number of players
        for (j = 1; j < 10; j++) { // number of seeds

            // Initializing game
            initializeGame(i, kCard, j, gamestate);

            int testHandCount = gamestate->handCount[whoseTurn(gamestate)];

            // Testing smithy
            testResult = cardEffect(card, choice1, choice2, choice3, gamestate, handPos, bonus);

            // Get hand count after card effect
            expectedHandCount = testHandCount + 2;

            if (testResult == -1) {
                printf("cardEffect outpost return: \n", testResult);
                overall = 1;
            }
            else if (testResult == 0) {
            if (gamestate->handCount[whoseTurn(gamestate)] != expectedHandCount) {
                    printf("cardEffect smithy: Failed \n");
                    printf("\tExpected: %d, actual: %d\n",expectedHandCount, gamestate->handCount[whoseTurn(gamestate)]);
                    overall = 1;
                }
            }
        }
    }

    if(overall == 0){
        printf("All test pass\n");
    }
    printf("\n");

    return 0;
}


