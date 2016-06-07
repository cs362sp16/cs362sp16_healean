/*
 * Created by: Nathan Healea
 * Date: June 6, 2016
 * Final Project
 * File name: cardtest3.c
 * Description:
 *      Testing card effect village
 */

#include "dominion.h"
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
    printf("/*    Cardtest4    */\n");
    printf("/* ---------------- */\n\n");

    // Defining game variables
    struct gameState *gamestate = newGame();    // Hold the game state
    int kCard[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

    // Loop variables
    int i = 0;
    int j = 0;

    // Testing Result
    int overall = 0;
    int cardEffectResult = 0;
    int expectedActionTaken = 0;
    int acualActionTaken = 0;

    // Testing parameters
    int card = village; //Set the flag for the current card
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

            // Get num of action
            expectedActionTaken = gamestate->numActions + 2;

            printf("Number of Actions: %d \n", gamestate->numActions);

            // Testing great_hall
            cardEffectResult = cardEffect(card, choice1, choice2, choice3, gamestate, handPos, bonus);

            acualActionTaken = gamestate->numActions;



            if (cardEffectResult == -1) {
                printf("cardEffect Village return: \n", cardEffectResult);
                overall = 1;
            }
            else if (cardEffectResult == 0) {
                if (expectedActionTaken != acualActionTaken) {
                    printf("cardEffect Village: Failed \n");
                    printf("\tExpected: %d, Actual: %d\n", expectedActionTaken, acualActionTaken);
                    overall = 1;
                }
            }
        }
    }

    if(overall == 0){
        printf("All test pass\n");
    }

    return 0;
}


