/*
 * Created by: Nathan Healea
 * Date: April 26, 2016
 * Assignment 2
 * File name: unittest2.c
 * Description
 *  Tested shuffle method
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
    printf("/*    Unittest2     */\n");
    printf("/* ---------------- */\n\n");

    // Defining variables
    struct gameState *gamestate = newGame();    // Hold the game state
    int deck[MAX_PLAYERS][MAX_DECK];
    int deckCount[MAX_PLAYERS];
    int i = 0;
    int j = 0;
    int playerNum = 0;
    int test = 1;


    for (playerNum = MIN_PLAYERS; playerNum < MAX_PLAYERS; playerNum++) {

        printf("/* ---- Test: %d ---- */ \n", test);
        // Setting Number of player
        gamestate->numPlayers = playerNum;


        //set player decks
        for (i = 0; i < gamestate->numPlayers; i++) {
            gamestate->deckCount[i] = 0;
            for (j = 0; j < 3; j++) {
                gamestate->deck[i][j] = estate;
                gamestate->deckCount[i]++;
                deck[i][j] = estate;
                deckCount[i]++;
            }
            for (j = 3; j < 10; j++) {
                gamestate->deck[i][j] = copper;
                gamestate->deckCount[i]++;
                deck[i][j] = copper;
                deckCount[i]++;
            }
            shuffle(i, gamestate);
        }


        for (i = 0; i < gamestate->numPlayers; i++) {

            for (j = 0; j < gamestate->deckCount[i]; j++) {
                if (gamestate->deck[i] == deck[i]) {
                    printf("Expected: %d,  Actual: %d \n", deck[i][j], gamestate->deck[i][j]);
                }
            }
        }
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
