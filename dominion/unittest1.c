/*
 * Created by: Nathan Healea
 * Date: April 26, 2016
 * Assignment 2
 * File name: unittest1.c
 * Description:
 *      Testing game initialization method.
 */

#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <math.h>

#define MAX_HAND 500
#define MAX_DECK 500

#define MAX_PLAYERS 4
#define MIN_PLAYERS 2

/**
 * Prints an error message with test name and result
 */
void printError(char *test, char *result, int expected, int acutal);

/**
 * Check a given card in the gamestate to expected value.
 */
void checkSupplyCount(char* card, struct gameState *state,  enum CARD c, int expected);

int main(int argc, char **argv) {

    printf("/* ---------------- */\n");
    printf("/*    Unittest1     */\n");
    printf("/* ---------------- */\n\n");

    // Defining variables
    struct gameState *gamestate = newGame();    // Hold the game state
    int kCard[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
    int i = 0;  // Loop irritater
    int j = 0;  // Seed irritater
    int init = 5; // checker for initialize game function
    int test = 1;
    int copperAct = 0;

    for (i = MIN_PLAYERS; i < MAX_PLAYERS; i++) { // number of players
        for (j = 1; j < 10; j++) { // number of seeds
            // Displaying test number
            printf("/* ---- Test: %d ---- */ \n", test);
            init = 5;
            // Initializing game
            init = initializeGame(i, kCard, j, gamestate);

            if (init != 5 && init != 0) { // Testing for initialization error
                printf("Game State Initialize: Failed \n");
                printf("Expected: %d or %d, Actual: %d \n", 5, 0, init);
                printf("\n");
            }

            if (gamestate->numPlayers != i) { // Testing Number of Players
                printError("NumPlayer", "Failed", i, gamestate->numPlayers);
            }

            // Testing Supply Count
            if (gamestate->numPlayers == 2) { // Test for two players
                checkSupplyCount("curse", gamestate, curse, 10);
                checkSupplyCount("estate", gamestate, estate, 8);
                checkSupplyCount("duchy", gamestate, duchy, 8);
                checkSupplyCount("province", gamestate, province, 8);
            }
            else if (gamestate->numPlayers == 3) { // Test for three players
                checkSupplyCount("curse", gamestate, curse, 20);
                checkSupplyCount("estate", gamestate, estate, 12);
                checkSupplyCount("duchy", gamestate, duchy, 12);
                checkSupplyCount("province", gamestate, province, 12);
            }
            else if (gamestate->numPlayers > 3) { // Test for more then three players
                checkSupplyCount("curse", gamestate, curse, 30);
                checkSupplyCount("estate", gamestate, estate, 12);
                checkSupplyCount("duchy", gamestate, duchy, 12);
                checkSupplyCount("province", gamestate, province, 12);
            }

            // Checking coins
            // copper = 60 - (7 * number of players)
            copperAct = (60 - (7 * i));
            checkSupplyCount("copper", gamestate, copper, copperAct);
            checkSupplyCount("silver", gamestate, silver, 40);
            checkSupplyCount("gold", gamestate, gold, 30);

            // Could not figure out now to test Kingdon cards

            // Testing players decks, hand, discard
            int k = 0;
            for (k = 0; k < gamestate->numPlayers; k++) {

                if (gamestate->deckCount[k] == 0) { // Testing Player Deck
                    printError("deckCount", "fail", 10, gamestate->deckCount[j]);
                }

                if (gamestate->handCount[k] != 5 && k == 0) { // Testing Player handcount
                    printf("Player: %d", k);
                    printError("handCount", "fail", 5, gamestate->handCount[j]);
                }
                else if (gamestate->handCount[k] != 0 && k > 0) {
                    printf("Player: %d", k);
                    printError("handCount", "fail", 5, gamestate->handCount[j]);
                }

                if (gamestate->discardCount[k] != 0) {  // Testing Player discardcount
                    printf("Player: %d", k);
                    printError("discardCount", "fail", 5, gamestate->discardCount[j]);
                }

            }


            test++;
        }
    }
    printf("\n");

    return 0;
}

void printError(char *test, char *result, int expected, int acutal) {
    // printing test
    printf("Test %s: %s", test, result);
    printf(" Expected: %d, Actual: %d \n", expected, acutal);
}

void checkSupplyCount(char* card, struct gameState *state,  enum CARD c, int expected) {
    if (state->supplyCount[c] != expected) { // Testing province
        printError(card, "failed", expected, state->supplyCount[c]);
    }

}
