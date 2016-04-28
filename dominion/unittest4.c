/*
 * Created by: Nathan Healea
 * Date: April 26, 2016
 * Assignment 2
 * File name: unittest3.c
 * Description:
 *      Testing whoseTurn method
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

int main(int argc, char **argv) {

    printf("/* ---------------- */\n");
    printf("/*    Unittest4     */\n");
    printf("/* ---------------- */\n\n");

    // Defining variables
    struct gameState *gamestate = newGame();    // Hold the game state
    int handCount[MAX_PLAYERS];
    int i = 0;
    int playerNum = 0;
    int test = 1;


    for (playerNum = MIN_PLAYERS; playerNum < MAX_PLAYERS; playerNum++) {

        printf("/* ---- Test: %d ---- */ \n", test);

        // Setting Number of player
        gamestate->numPlayers = playerNum;

        for(i = 0; i < gamestate->numPlayers; i++){
            gamestate->whoseTurn = i;

            if(whoseTurn(gamestate) != i){
                printError("whoseTurn", "Failed", i, whoseTurn(gamestate));
            }
        }

        // Reset whose turn
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

