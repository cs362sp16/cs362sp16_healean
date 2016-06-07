/*
 * Created by: Nathan Healea
 * Date: April 26, 2016
 * Assignment 2
 * File name: unittest3.c
 * Description:
 *      Testing numHandCards method
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
void checkSupplyCount(char *card, struct gameState *state, enum CARD c, int expected);

int main(int argc, char **argv) {
    printf("/* ---------------- */\n");
    printf("/*    Unittest3     */\n");
    printf("/* ---------------- */\n\n");

    // Defining variables
    struct gameState *gamestate = newGame();    // Hold the game state
    int handCount[MAX_PLAYERS];
    int i = 0;
    int j = 0;
    int playerNum = 0;
    int test = 1;
    int randomSeed = 0;


    for (playerNum = MIN_PLAYERS; playerNum < MAX_PLAYERS; playerNum++) {

        printf("/* ---- Test: %d ---- */ \n", test);

        // Setting Number of player
        gamestate->numPlayers = playerNum;


        // Filling hand for each player
        for (i = 0; i < gamestate->numPlayers; i++) {

            // Getting random number
            srand(time(NULL));
            randomSeed = rand() % 500 + 0;

            // Saving count
            handCount[i] = randomSeed;

            // Adding cards to player hand
            for (j = 0; j < randomSeed; j++) {
                gamestate->hand[i][j] = j;
                gamestate->handCount[i]++;
            }

            // Setting whose turn it is
            gamestate->whoseTurn = i;
            if (numHandCards(gamestate) != handCount[i]) { // Test for comparison of cards in hand
                printf("Player %d: ", i);
                printError("numHandCard", "Failed", handCount[i], numHandCards(gamestate));

            }
        }

        // Reset test variables
        for (i = 0; i < gamestate->numPlayers; i++) {
            for (j = 0; j < handCount[i]; j++) {
                gamestate->hand[i][j] = 0;
                gamestate->handCount[i]--;

            }
            handCount[i] = 0;
        }

        gamestate->whoseTurn = 0;

        test++;
    }
    printf("\n");

    return 0;
}

void printError(char *test, char *result, int expected, int acutal) {
    // printing test
    printf("Test %s: %s", test, result);
    printf(" Expected: %d, Actual: %d \n", expected, acutal);
}

void checkSupplyCount(char *card, struct gameState *state, enum CARD c, int expected) {
    if (state->supplyCount[c] != expected) { // Testing province
        printError(card, "failed", expected, state->supplyCount[c]);
    }

}
