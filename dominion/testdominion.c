/*
 * Created by: Nathan Healea
 * Date: May 11, 2016
 * Assignment 2
 * File name: randometestadventurer.c
 * Description:
 *      Random testing adventurer card effect
 */

#define _CRT_SECURE_NO_DEPRECATE

#include "dominion.h"
#include "dominion_helpers.h"
#include "testdominion.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include "rngs.h"

void generateDeck(int k[]);

void preformCardBuys(struct cardState *cards, struct gameState *game, int *money, int *playerTurn, FILE *fp);

void preformCardAction(struct cardState *cards, struct gameState *game, int *money, int *playerTurn, FILE *fp);

// Helper functions
int gen_random(int min, int max);

void checkCardInDeck(int *card, int *hasCardFlag, int *deckCount, int k[]);

void checkDeckContents(struct cardState *cards, struct gameState *game, int *money);

void resetCardState(struct cardState *cards);

int main(int argc, char **argv) {
    srand(time(NULL));

    // Variables definition
    int i, q, j;
    int money;
    struct gameState game;
    struct cardState cards;
    int k[10];
    int playerNum; // number of players for a test
    int testNum; // number of test to be ran
    int playerTurn;
    int seed; // random seed f

    if(argc == 2){
        seed = atoi(argv[1]);
        printf("%d", seed);

    }else{
        seed = 24;
        printf("%d", seed);
    }

    //Using IO to write game status to gameResults.out
    FILE *fp;
    fp = fopen("gameResults.out", "w");

    // Getting random number of test
    testNum = gen_random(0, 20);

    // Initializing game with random players and decks.
    for (q = 0; q < testNum; q++) {
        printf("Getting Random Cards for game [%d]\n", q);
        fprintf(fp, "Getting Random Cards for game [%d] \n", q);

        // Generate deck of cards
        generateDeck(k);

        // Get num of players
        playerNum = gen_random(2, 5);

        // Initialize game with random
        initializeGame(playerNum, k, seed, &game);

        resetCardState(&cards);
        money = 0;

        while (!isGameOver(&game)) {
            resetCardState(&cards);
            playerTurn = whoseTurn(&game);

            // Play Actions
            printf("Player [%d]: Start Actions\n", playerTurn + 1);
            fprintf(fp, "\t Player [%d]: Start Actions\n", playerTurn + 1);
            preformCardAction(&cards, &game, &money, &playerTurn, fp);
            printf("Player [%d]: End Actions\n", playerTurn + 1);
            fprintf(fp, "\t Player [%d]: End Actions\n", playerTurn + 1);

            // Buy Cards
            printf("Player [%d]: Start Buy\n", playerTurn + 1);
            fprintf(fp, "\t Player [%d]: Start Actions\n", playerTurn + 1);
            preformCardBuys(&cards, &game, &money, &playerTurn, fp);
            printf("Player [%d]: End Buys\n", playerTurn + 1);
            fprintf(fp, "\t Player [%d]: End Buys\n", playerTurn + 1);

            printf("1: endTurn\n");

            endTurn(&game);
            printf("\n");
            fprintf(fp, "\n");

        } // end of while loop

        for (j = 0; j < playerNum; j++) {
            printf("Player %d: %d \n", j + 1, scoreFor(j, &game));
            fprintf(fp, "Player %d: %d \n", j + 1, scoreFor(j, &game));
        }
        printf("\n\n\n\n");
        fprintf(fp, "\n\n\n\n");

    } // end of for loop

    fclose(fp);
    return 0;

}

/**
 * Generated a deck of cards to be used in the game.
 */
void generateDeck(int k[]) {
    int randomCard;
    int deckHasCard;
    int deckCount;

    deckCount = 0;
    //draw 10 random cards
    while (deckCount < 10) {
        deckHasCard = 0;
        randomCard = gen_random(7, 26);
        switch (randomCard) {
            case 7:
                randomCard = adventurer;
                checkCardInDeck(&randomCard, &deckHasCard, &deckCount, k);
                break;
            case 8:
                randomCard = council_room;
                checkCardInDeck(&randomCard, &deckHasCard, &deckCount, k);
                break;
            case 9:
                randomCard = feast;
                checkCardInDeck(&randomCard, &deckHasCard, &deckCount, k);
                break;
            case 10:
                randomCard = gardens;
                checkCardInDeck(&randomCard, &deckHasCard, &deckCount, k);
                break;
            case 11:
                checkCardInDeck(&randomCard, &deckHasCard, &deckCount, k);
                break;
            case 12:
                randomCard = remodel;
                checkCardInDeck(&randomCard, &deckHasCard, &deckCount, k);
                break;
            case 13:
                randomCard = smithy;
                checkCardInDeck(&randomCard, &deckHasCard, &deckCount, k);
                break;
            case 14:
                randomCard = village;
                checkCardInDeck(&randomCard, &deckHasCard, &deckCount, k);
                break;
            case 15:
                randomCard = baron;
                checkCardInDeck(&randomCard, &deckHasCard, &deckCount, k);
                break;
            case 16:
                randomCard = great_hall;
                checkCardInDeck(&randomCard, &deckHasCard, &deckCount, k);
                break;
            case 17:
                randomCard = minion;
                checkCardInDeck(&randomCard, &deckHasCard, &deckCount, k);
                break;
            case 18:
                randomCard = steward;
                checkCardInDeck(&randomCard, &deckHasCard, &deckCount, k);
                break;
            case 19:
                randomCard = tribute;
                checkCardInDeck(&randomCard, &deckHasCard, &deckCount, k);
                break;
            case 20:
                randomCard = ambassador;
                checkCardInDeck(&randomCard, &deckHasCard, &deckCount, k);
                break;
            case 21:
                randomCard = cutpurse;
                checkCardInDeck(&randomCard, &deckHasCard, &deckCount, k);
                break;
            case 22:
                randomCard = embargo;
                checkCardInDeck(&randomCard, &deckHasCard, &deckCount, k);
                break;
            case 23:
                randomCard = outpost;
                checkCardInDeck(&randomCard, &deckHasCard, &deckCount, k);
                break;
            case 24:
                randomCard = salvager;
                checkCardInDeck(&randomCard, &deckHasCard, &deckCount, k);
                break;
            case 25:
                randomCard = sea_hag;
                checkCardInDeck(&randomCard, &deckHasCard, &deckCount, k);
                break;
            case 26:
                randomCard = treasure_map;
                checkCardInDeck(&randomCard, &deckHasCard, &deckCount, k);
                break;
            default:
                break;
        }
    }
}

/**
 * Preform buys for the current player
 */
void preformCardBuys(struct cardState *cards, struct gameState *game, int *money, int *playerTurn, FILE *fp) {
    int randCardBuy = 0;
    int infloop = 0;

    while (game->numBuys) {

        // if there is not coins then exit loop;
        if (game->coins == 0) {
            break;
        }

        //if money is greater than 8,  purchase a province.
        if (*money >= 8) {
            if (!buyCard(province, game)) {
                *money = game->coins;
                printf("\t\tPlayer[%d]: province purchased. Money[$%d]\n", *playerTurn + 1, *money);
                fprintf(fp, "\tPurchased province. Money after purchase: [%d]\n", *money);
            }
        }

        // Card cost of 6
        // Gold, Adventurer
        if (*money >= 6) {
            randCardBuy = gen_random(1, 2);
            // Buy adventure 
            if ((randCardBuy == 1) && (game->supplyCount[adventurer] > 0)) {
                if (!buyCard(adventurer, game)) {
                    *money = game->coins;
                    printf("\tPlayer[%d]: Adventurer purchased.\n", *playerTurn + 1);
                    fprintf(fp, "\tAdventurer purchased. Money after purchase: [%d]\n", *money);
                }
            }
            else { // Buy gold
                if (!buyCard(gold, game)) {
                    *money = game->coins;
                    printf("\tPlayer[%d]: Gold card purchased.\n", *playerTurn + 1);
                    fprintf(fp, "\tGold Card purchased. Money after purchase: [%d]\n", *money);
                }
            }
        }

        // Card cost of 5
        // Minion, Mine, Duchy, Council Room, Tribute Outpost
        if (*money == 5) {
            randCardBuy = gen_random(1, 6);
            // Buy Duchy
            if ((randCardBuy == 1) && (game->supplyCount[duchy]) > 0) {
                if (!buyCard(duchy, game)) {
                    *money = game->coins;
                    printf("\tPlayer[%d]: Duchy card purchased.\n", *playerTurn + 1);
                    fprintf(fp, "\tDuchy purchased. Money after purchase: [%d]\n", *money);
                }
            }
                // Buy Minion
            else if ((randCardBuy == 2) && (game->supplyCount[minion]) > 0) {
                if (!buyCard(minion, game)) {
                    *money = game->coins;
                    printf("\tPlayer[%d]: Minion card purchased.\n", *playerTurn + 1);
                    fprintf(fp, "\tMinion purchased. Money after purchase: [%d]\n", *money);
                }
            }
                // Buy Council Room
            else if ((randCardBuy == 3) && (game->supplyCount[council_room]) > 0) {
                if (!buyCard(council_room, game)) {
                    *money = game->coins;
                    printf("\tPlayer[%d]: Council Room card purchased.\n", *playerTurn + 1);
                    fprintf(fp, "\tCouncil Room purchased. Money after purchase: [%d]\n", *money);
                }
            }
                // Buy Tribute
            else if ((randCardBuy == 4) && (game->supplyCount[tribute]) > 0) {
                if (!buyCard(tribute, game)) {
                    *money = game->coins;
                    printf("\tPlayer[%d]: Tribute card purchased.\n", *playerTurn + 1);
                    fprintf(fp, "\tTribute purchased. Money after purchase: [%d]\n", *money);
                }
            }
                // But Mine
            else if ((randCardBuy == 5) && (game->supplyCount[mine]) > 0) {
                if (!buyCard(mine, game)) {
                    *money = game->coins;
                    printf("\tPlayer[%d]: Mine card purchased.\n", *playerTurn + 1);
                    fprintf(fp, "\tMine purchased. Money after purchase: [%d]\n", *money);
                }
            }
                // Buy Council Room
            else if ((randCardBuy == 6) && (game->supplyCount[council_room]) > 0) {
                if (!buyCard(outpost, game)) {
                    *money = game->coins;
                    printf("\tPlayer[%d]: Outpost card purchased.\n", *playerTurn + 1);
                    fprintf(fp, "\tOutpost purchased. Money after purchase: [%d]\n", *money);
                }
            }
        }

        // Card cost of 4
        // Feast, Gardens, Remodel, Smithy, Baron, Cutpurse, Salvager, Sea Hag, Treasure Map
        if (*money == 4) {
            randCardBuy = gen_random(1, 9);
            // Buy Feast
            if ((randCardBuy == 1) && (game->supplyCount[feast]) > 0) {
                if (!buyCard(feast, game)) {
                    *money = game->coins;
                    printf("\tPlayer[%d]: Feast card purchased.\n", *playerTurn + 1);
                    fprintf(fp, "\tFeast purchased. Money after purchase: [%d]\n", *money);
                }
            }
                // Buy Gardens
            else if ((randCardBuy == 2) && (game->supplyCount[gardens]) > 0) {
                if (!buyCard(gardens, game)) {
                    *money = game->coins;
                    printf("\tPlayer[%d]: Gardens card purchased.\n", *playerTurn + 1);
                    fprintf(fp, "\tGardens purchased. Money after purchase: [%d]\n", *money);
                }
            }
                // Buy Remodel
            else if ((randCardBuy == 3) && (game->supplyCount[remodel]) > 0) {
                if (!buyCard(remodel, game)) {
                    *money = game->coins;
                    printf("\tPlayer[%d]: Remodel card purchased.\n", *playerTurn + 1);
                    fprintf(fp, "\tRemodel purchased. Money after purchase: [%d]\n", *money);
                }
            }
                // Buy Smithy
            else if ((randCardBuy == 4) && (game->supplyCount[smithy]) > 0) {
                if (!buyCard(smithy, game)) {
                    *money = game->coins;
                    printf("\tPlayer[%d]: Smithy card purchased.\n", *playerTurn + 1);
                    fprintf(fp, "\tSmithy purchased. Money after purchase: [%d]\n", *money);
                }
            }
                // Buy Baron
            else if ((randCardBuy == 5) && (game->supplyCount[baron]) > 0) {
                if (!buyCard(baron, game)) {
                    *money = game->coins;
                    printf("\tPlayer[%d]: Baron card purchased.\n", *playerTurn + 1);
                    fprintf(fp, "\tBaron purchased. Money after purchase: [%d]\n", *money);
                }
            }
                // Buy Cutpurse
            else if ((randCardBuy == 6) && (game->supplyCount[cutpurse]) > 0) {
                if (!buyCard(cutpurse, game)) {
                    *money = game->coins;
                    printf("\tPlayer[%d]: Cutpurse card purchased.\n", *playerTurn + 1);
                    fprintf(fp, "\tCutpurse purchased. Money after purchase: [%d]\n", *money);
                }
            }
                // But Salvager
            else if ((randCardBuy == 7) && (game->supplyCount[salvager]) > 0) {
                if (!buyCard(salvager, game)) {
                    *money = game->coins;
                    printf("\tPlayer[%d]: Salvager card purchased.\n", *playerTurn + 1);
                    fprintf(fp, "\tSalvager purchased. Money after purchase: [%d]\n", *money);
                }
            }
                // Buy Sea Hag
            else if ((randCardBuy == 8) && (game->supplyCount[sea_hag]) > 0) {
                if (!buyCard(sea_hag, game)) {
                    *money = game->coins;
                    printf("\tPlayer[%d]: Sea Hag card purchased.\n", *playerTurn + 1);
                    fprintf(fp, "\tSea Hag purchased. Money after purchase: [%d]\n", *money);
                }
            }
                // Buy Treasure Map
            else if ((randCardBuy == 9) && (game->supplyCount[treasure_map]) > 0) {
                if (!buyCard(treasure_map, game)) {
                    *money = game->coins;
                    printf("\tPlayer[%d]: Treasure Map card purchased.\n", *playerTurn + 1);
                    fprintf(fp, "\tTreasure Map purchased. Money after purchase: [%d]\n", *money);
                }
            }
        }


        // Card cost of 3
        // Silver, Village, Great Hall, Steward, Ambassador
        if (*money == 3) {
            randCardBuy = gen_random(1, 5);

            // Buy Silver
            if ((randCardBuy == 1) && (game->supplyCount[silver]) > 0) {
                if (!buyCard(silver, game)) {
                    *money = game->coins;
                    printf("\tPlayer[%d]: Silver card purchased.\n", *playerTurn + 1);
                    fprintf(fp, "\tSilver purchased. Money after purchase: [%d]\n", *money);
                }
            }
                // Buy Village
            else if ((randCardBuy == 2) && (game->supplyCount[village]) > 0) {
                if (!buyCard(village, game)) {
                    *money = game->coins;
                    printf("\tPlayer[%d]: Village card purchased.\n", *playerTurn + 1);
                    fprintf(fp, "\tVillage purchased. Money after purchase: [%d]\n", *money);
                }
            }
                // Buy Great Hall
            else if ((randCardBuy == 3) && (game->supplyCount[great_hall]) > 0) {
                if (!buyCard(great_hall, game)) {
                    *money = game->coins;
                    printf("\tPlayer[%d]: Great Hall card purchased.\n", *playerTurn + 1);
                    fprintf(fp, "\tGreat Hall purchased. Money after purchase: [%d]\n", *money);
                }
            }
                // Buy Steward
            else if ((randCardBuy == 4) && (game->supplyCount[steward]) > 0) {
                if (!buyCard(steward, game)) {
                    *money = game->coins;
                    printf("\tPlayer[%d]: Steward card purchased.\n", *playerTurn + 1);
                    fprintf(fp, "\tSteward purchased. Money after purchase: [%d]\n", *money);
                }
            }
                // Buy Ambassador
            else if ((randCardBuy == 5) && (game->supplyCount[ambassador]) > 0) {
                if (!buyCard(ambassador, game)) {
                    *money = game->coins;
                    printf("\tPlayer[%d]: Ambassador card purchased.\n", *playerTurn + 1);
                    fprintf(fp, "\tAmbassador purchased. Money after purchase: [%d]\n", *money);
                }
            }
        }

        // Card cost of 2
        // Embargo, Estate
        if (*money == 2) {
            randCardBuy = gen_random(1, 2);
            // Buy Embargo
            if ((randCardBuy == 1) && (game->supplyCount[embargo]) > 0) {
                if (!buyCard(embargo, game)) {
                    *money = game->coins;
                    printf("\tPlayer[%d]: Embargo card purchased.\n", *playerTurn + 1);
                    fprintf(fp, "\tEmbargo purchased. Money after purchase: [%d]\n", *money);
                }
            }
                // Buy Estate
            else if ((randCardBuy == 2) && (game->supplyCount[estate]) > 0) {
                if (!buyCard(estate, game)) {
                    *money = game->coins;
                    printf("\tPlayer[%d]: Estate card purchased.\n", *playerTurn + 1);
                    fprintf(fp, "\tEstate purchased. Money after purchase: [%d]\n", *money);
                }
            }
            else {
                //No purchases at this level
            }
        }

        //If money is 1 or 0, but the player still has buys...
        if (*money < 2) {
            if (!buyCard(copper, game)) {
                *money = game->coins;
                printf("\tPlayer[%d]: Copper card purchased.\n", *playerTurn + 1);
                fprintf(fp, "\tCopper purchased. Money after purchase: [%d]\n", *money);
            }
        }

        if (infloop > 10) {
            return; //Break out of endless loops
        }
        else {
            infloop++;
        }

    }
}

/**
 * Preforms actions for the current player
 */
void preformCardAction(struct cardState *cards, struct gameState *game, int *money, int *playerTurn, FILE *fp) {
    int actionTest;
    checkDeckContents(cards, game, money);
    actionTest = 1;
    while (game->numActions) {

        //Smithy Card
        //If the player has the smithy then play it... always
        if (cards->smithyPos != -1) {
            if (playCard(cards->smithyPos, -1, -1, -1, game) != -1) {
                // -1 Action, +3 Cards
                fprintf(fp, "\tSmithy Played\n");
                actionTest = 0;
                //Look at the deck again
                cards->smithyPos = -1;
                checkDeckContents(cards, game, money);
            }
            else {
                fprintf(fp, "\tError: playCard(Smithy) returned -1.\n");
                printf("\tError: playCard(Smithy) returned -1.\n");
                return;
            }
        } // End Smithy

        //Adventurer Card
        if (cards->adventurerPos != -1) {
            printf("\tPlayer[%d]: Adventurer played from position %d\n", *playerTurn + 1, cards->adventurerPos);
            if (playCard(cards->adventurerPos, -1, -1, -1, game) != -1) {
                // -1 Action, +3 Cards
                fprintf(fp, "\tAdventurer Played\n");
                actionTest = 0;
                //Look at the deck again
                cards->adventurerPos = -1;
                checkDeckContents(cards, game, money);
            }
            else {
                fprintf(fp, "\tError: playCard(Adventurer) returned -1.\n");
                printf("\tError: playCard(Adventurer) returned -1.\n");
                return;
            }
        } // End Adventurer

        //End Council Room
        if (cards->council_roomPos != -1) {
            printf("\tPlayer[%d]: Council Room played from position %d\n", *playerTurn + 1, cards->council_roomPos);
            if (playCard(cards->council_roomPos, -1, -1, -1, game) != -1) {
                // -1 Action, +3 Cards
                fprintf(fp, "\tCouncil Room Played\n");
                actionTest = 0;
                //Look at the deck again
                cards->council_roomPos = -1;
                checkDeckContents(cards, game, money);
            }
            else {
                fprintf(fp, "\tError: playCard(Council Room) returned -1.\n");
                printf("\tError: playCard(Council Room) returned -1.\n");
                return;
            }
        } // End Council Room

        //Village Card
        if (cards->villagePos != -1) {
            printf("\tPlayer[%d]: Village played from position %d\n", *playerTurn + 1, cards->villagePos);
            if (playCard(cards->villagePos, -1, -1, -1, game) != -1) {
                // -1 Action, +3 Cards
                fprintf(fp, "\tVillage Played\n");
                actionTest = 0;
                //Look at the deck again
                cards->villagePos = -1;
                checkDeckContents(cards, game, money);
            }
            else {
                fprintf(fp, "\tError: playCard(Village) returned -1.\n");
                printf("\tError: playCard(Village) returned -1.\n");
                return;
            }
        } // End Village

        //Great Hall
        if (cards->great_hallPos != -1) {
            printf("\tPlayer[%d]: Great Hall played from position %d\n", *playerTurn + 1, cards->great_hallPos);
            if (playCard(cards->great_hallPos, -1, -1, -1, game) != -1) {
                // -1 Action, +3 Cards
                fprintf(fp, "\tGreat Hall Played\n");
                actionTest = 0;
                //Look at the deck again
                cards->great_hallPos = -1;
                checkDeckContents(cards, game, money);
            }
            else {
                fprintf(fp, "\tError: playCard(Great Hall) returned -1.\n");
                printf("\tError: playCard(Great Hall) returned -1.\n");
                return;
            }
        } // End Great Hall

        /* * *
         * Had to remove this from testing because it keep giving my segfaults that I could not track down.
         * * */
        //Tribute
        /*if (cards->tributePos != -1) {
            printf("\tPlayer[%d]:: Tribute played from position %d\n", *playerTurn + 1, cards->tributePos);
            if (playCard(cards->tributePos, -1, -1, -1, game) != -1) {
                // -1 Action, +3 Cards
                fprintf(fp, "\tTribute Played\n");
                actionTest = 0;
                //Look at the deck again
                cards->tributePos = -1;
                checkDeckContents(cards, game, money);
            }
            else {
                fprintf(fp, "\tError: playCard(Tribute) returned -1.\n");
                printf("\tError: playCard(Tribute) returned -1.\n");
                return;
            }
        }*/ // End Tribute*/

        //Cut Purse
        if (cards->cutpursePos != -1) {
            printf("\tPlayer[%d]: Cutpurse played from position %d\n", *playerTurn + 1, cards->cutpursePos);
            if (playCard(cards->cutpursePos, -1, -1, -1, game) != -1) {
                // -1 Action, +3 Cards
                fprintf(fp, "\tCutpurse Played\n");
                actionTest = 0;
                //Look at the deck again
                cards->cutpursePos = -1;
                checkDeckContents(cards, game, money);
            }
            else {
                fprintf(fp, "\tError: playCard(Cutpurse) returned -1.\n");
                printf("\tError: playCard(Cutpurse) returned -1.\n");
                return;
            }
        } // End Cutpurse

        //Outpost Card
        if (cards->outpostPos != -1) {
            printf("\tPlayer[%d]: Outpost played from position %d\n", *playerTurn + 1, cards->outpostPos);
            if (playCard(cards->outpostPos, -1, -1, -1, game) != -1) {
                // -1 Action, +3 Cards
                fprintf(fp, "\tOutpost Played\n");
                actionTest = 0;
                //Look at the deck again
                cards->outpostPos = -1;
                checkDeckContents(cards, game, money);
            }
            else {
                fprintf(fp, "\tError: playCard(Outpost) returned -1.\n");
                printf("\tError: playCard(Outpost) returned -1.\n");
                return;
            }
        } // End Outpost

        //Sea Hag
        if (cards->sea_hagPos != -1) {
            printf("\tPlayer[%d]: Sea Hag played from position %d\n", *playerTurn + 1, cards->sea_hagPos);
            if (playCard(cards->sea_hagPos, -1, -1, -1, game) != -1) {
                // -1 Action, +3 Cards
                fprintf(fp, "\tSea Hag Played\n");
                actionTest = 0;
                //Look at the deck again
                cards->sea_hagPos = -1;
                checkDeckContents(cards, game, money);
            }
            else {
                fprintf(fp, "\tError: playCard(Sea Hag) returned -1.\n");
                printf("\tError: playCard(Sea Hag) returned -1.\n");
                return;
            }
        } // End Sea Hag

        //Treasure Map
        if (cards->treasure_mapPos != -1) {
            printf("\tPlayer[%d]: Treasure Map played from position %d\n", *playerTurn + 1, cards->treasure_mapPos);
            if (playCard(cards->treasure_mapPos, -1, -1, -1, game) != -1) {
                // -1 Action, +3 Cards
                fprintf(fp, "\tTreasure Map Played\n");
                actionTest = 0;
                //Look at the deck again
                cards->treasure_mapPos = -1;
                checkDeckContents(cards, game, money);
            }
            else {
                fprintf(fp, "\tError: playCard(Treasure Map) returned -1.\n");
                printf("\tError: playCard(Treasure Map) returned -1.\n");
                return;
            }
        } // End Treasure Map

        //If no action is taken...
        if (actionTest == 1) {
            printf("\tPlayer[%d] No Action taken this turn.\n", *playerTurn + 1);
            fprintf(fp, "\tPlayer %d No Action taken this turn.\n", *playerTurn + 1);
            return;
        }
        else if (actionTest <= 1) {
            if (actionTest <= -1) {
                fprintf(fp, "\tPlayer[%d] No More Action Cards to play this turn.\n", *playerTurn + 1);
                printf("\tPlayer[%d] No More Cards to play this turn.\n", *playerTurn + 1);
                return;
            }
            actionTest--;
        }
        else if (actionTest == 0) {
            if (game->numActions > 10) {
                printf("\t\tAbnormally High Actions for this turn [%d], examine last card played.\n", game->numActions);
                fprintf(fp, "\t\tAbnormally High Actions for this turn [%d], examine last card played.\n",
                        game->numActions);
                return;
            }
        }
    }
}

/*
 * Generates a random number between the min and max number.
 */
int gen_random(int min_num, int max_num) {
    int return_num = 0;
    int low_num = 0;
    int high_num = 0;

    if (min_num < max_num) { // if min is less then max set low and high
        low_num = min_num;
        high_num = max_num;
    }
    else { // if min is greater max them set min to high and max to low
        low_num = max_num + 1;
        high_num = min_num;
    }

    return_num = rand() % (high_num - low_num) + low_num;
    return return_num;
}

/**
 * Check if a card is in the deck
 */
void checkCardInDeck(int *card, int *hasCardFlag, int *deckCount, int k[]) {
    int y;
    for (y = 0; y < 10; y++) {
        if (k[y] == *card) {
            *hasCardFlag = 1;
        }
    }
    if (*hasCardFlag != 1) {
        k[*deckCount] = *card;
        *deckCount = *deckCount + 1;
    }
}

/**
 * checks the contest of the current users deck.
 */
void checkDeckContents(struct cardState *cards, struct gameState *game, int *money) {
    int i;
    *money = 0;

    for (i = 0; i < numHandCards(game); i++) {
        if (handCard(i, game) == copper) {
            *money = *money + 1;
        }
        if (handCard(i, game) == silver) {
            *money = *money + 2;
        }
        if (handCard(i, game) == gold) {
            *money = *money + 3;
        }
        if (handCard(i, game) == smithy) {
            cards->smithyPos = i;
        }
        if (handCard(i, game) == adventurer) {
            cards->adventurerPos = i;
        }
        if (handCard(i, game) == council_room) {
            cards->council_roomPos = i;
        }
        if (handCard(i, game) == feast) {
            cards->feastPos = i;
        }
        if (handCard(i, game) == gardens) {
            cards->gardensPos = i;
        }
        if (handCard(i, game) == mine) {
            cards->minePos = i;
        }
        if (handCard(i, game) == remodel) {
            cards->remodelPos = i;
        }
        if (handCard(i, game) == village) {
            cards->villagePos = i;
        }
        if (handCard(i, game) == baron) {
            cards->baronPos = i;
        }
        if (handCard(i, game) == great_hall) {
            cards->great_hallPos = i;
        }
        if (handCard(i, game) == minion) {
            cards->minionPos = i;
        }
        if (handCard(i, game) == steward) {
            cards->stewardPos = i;
        }
        if (handCard(i, game) == tribute) {
            cards->tributePos = i;
        }
        if (handCard(i, game) == ambassador) {
            cards->ambassadorPos = i;
        }
        if (handCard(i, game) == cutpurse) {
            cards->cutpursePos = i;
        }
        if (handCard(i, game) == embargo) {
            cards->embargoPos = i;
        }
        if (handCard(i, game) == outpost) {
            cards->outpostPos = i;
        }
        if (handCard(i, game) == salvager) {
            cards->salvagerPos = i;
        }
        if (handCard(i, game) == sea_hag) {
            cards->sea_hagPos = i;
        }
        if (handCard(i, game) == treasure_map) {
            cards->treasure_mapPos = i;
        }
    }
}

/**
 * Resets the cardState after each action.
 */
void resetCardState(struct cardState *cards) {
    cards->smithyPos = -1;
    cards->adventurerPos = -1;
    cards->embargoPos = -1;
    cards->villagePos = -1;
    cards->great_hallPos = -1;
    cards->stewardPos = -1;
    cards->ambassadorPos = -1;
    cards->feastPos = -1;
    cards->gardensPos = -1;
    cards->remodelPos = -1;
    cards->baronPos = -1;
    cards->cutpursePos = -1;
    cards->salvagerPos = -1;
    cards->sea_hagPos = -1;
    cards->treasure_mapPos = -1;
    cards->council_roomPos = -1;
    cards->minePos = -1;
    cards->minionPos = -1;
    cards->tributePos = -1;
    cards->outpostPos = -1;

    cards->numSmithies = 0;
    cards->numAdventurers = 0;
    cards->numEmbargo = 0;
    cards->numVillage = 0;
    cards->numGreat_Hall = 0;
    cards->numSteward = 0;
    cards->numAmbassador = 0;
    cards->numFeast = 0;
    cards->numGarden = 0;
    cards->numRemodel = 0;
    cards->numBaron = 0;
    cards->numCutpurse = 0;
    cards->numSalvager = 0;
    cards->numSea_Hag = 0;
    cards->numTreasure_Map = 0;
    cards->numCouncil_Room = 0;
    cards->numMine = 0;
    cards->numMinion = 0;
    cards->numTribute = 0;
    cards->numOutpost = 0;
}
