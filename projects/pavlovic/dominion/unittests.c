/************************************************
 * Name: Christopher Pavlovich
 * Program: cardtests.c
 ************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include "rngs.h"
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
// #include "unittest1.h"
// #include "unittest2.h"
// #include "unittest3.h"
// #include "unittest4.h"
// #include "cardtest1.h"
// #include "cardtest2.h"
// #include "cardtest3.h"
// #include "cardtest4.h"

void unittest1();
void unittest2();
void unittest3();
void unittest4();
void cardtest1();
void cardtest2();
void cardtest3();
void cardtest4();

int cardSmithy(struct gameState *, int, int);

int main() {
    unittest1();
    unittest2();
    // unittest3();
    // unittest4();
    // cardtest1();
    // cardtest2();
    // cardtest3();
    // cardtest4();

    return 0;
}

void unittest1() {
    struct gameState curGame;
    int numPassed, numFailed, i, j, handLen, deckSize, discardCount, curFails;
    int cards[10] = {adventurer, council_room, cutpurse, embargo, mine,
        minion, sea_hag, smithy, tribute, village};

    srand(time(NULL));

    numPassed = 0;
    numFailed = 0;
    j = 0;

    printf("\n *** UNIT TEST 1 *** \n");
    printf("Test function: discardCard()\n");

    initializeGame(2, cards, 1000, &curGame);

    for(i = 0; i < 2; ++i) { // i is current player
        printf("Running tests for player %d\n", i+1);
        while(j < 25) {
            ++j;
            curFails = 0;

            while(curGame.deckCount[i] <= 20 || curGame.deckCount[i] >= 450)
                curGame.deckCount[i] = rand() % MAX_DECK;
                // curGame.deckCount[i] = 20;
            while(curGame.handCount[i] <= 3 || curGame.handCount[i] >= 100)
                curGame.handCount[i] = rand() % MAX_HAND;
                // curGame.handCount[i] = 3;
            if(curGame.playedCardCount < 0)
                curGame.playedCardCount = 0;

            // flag: remove the following prints
            // printf("Player hand card count: %d\n", curGame.handCount[i]);
            // printf("Deck card count: %d\n", curGame.deckCount[i]);
            // printf("Played card count: %d\n", curGame.playedCardCount);

            handLen = curGame.handCount[i];
            deckSize = curGame.deckCount[i];
            discardCount = curGame.playedCardCount;

            // function call
            discardCard(0, i, &curGame, 0);

            if(curGame.playedCardCount != (discardCount+1)) {
                printf("ERROR: card not succesfully discarded\n");
                ++curFails;
            }
            if((curGame.handCount[i] != (handLen+2)) || (curGame.deckCount[i] != (deckSize-3))) {
                printf("ERROR: not enough cards drawn\n");
                ++curFails;
            }

            if(curFails) {
                printf("Test %d failed with %d errors\n", j, curFails);
                ++numFailed;
            } else {
                printf("Test %d passed\n", j+1);
                ++numPassed;
            }
            curFails = 0;
        }
    }

    printf("discardCard() test results: %d tests passed, %d tests failed\n\n", numPassed, numFailed);

}

void unittest2() {
	struct gameState preCall, *postCall=NULL;
    int numPassed, numFailed, i, j, k, numUnAltered, curFails, status;
    int cards[10] = {adventurer, council_room, cutpurse, embargo, mine,
        minion, sea_hag, smithy, tribute, village};

	srand(time(NULL));
    numPassed = 0;
    numFailed = 0;
    j = 0;

    printf("\n *** UNIT TEST 2 *** \n");
    printf("Test function: shuffle()\n");

    while(j < 25) {
        ++j;
        curFails = 0;
		status = 0;
		initializeGame(2, cards, 1000, &preCall);
        while(preCall.deckCount[i] <= 20 || preCall.deckCount[i] >= 450)
            preCall.deckCount[i] = rand() % MAX_DECK;
            // preCall.deckCount[i] = 20;
        while(preCall.handCount[i] <= 3 || preCall.handCount[i] >= 100)
            preCall.handCount[i] = rand() % MAX_HAND;
            // preCall.handCount[i] = 3;
        if(preCall.playedCardCount < 0)
            preCall.playedCardCount = 0;

        postCall = newGame();

        postCall->deckCount[i] = preCall.deckCount[i];
        postCall->handCount[i] = preCall.handCount[i];
        postCall->playedCardCount = preCall.playedCardCount;

		// function call
		status = shuffle(i, &preCall);
        // status += shuffle(i, postCall);
		// memcpy(postCall, &preCall, sizeof(struct gameState *));

		// validate
		if(status) {
			printf("Error: shuffle returned non-zero status\n");
			++curFails;
		}
		for(i = 0; i < 2; ++i) { // i is current player
			if(sizeof(preCall.deck[i]) != sizeof(postCall->deck[i])) {
				printf("Error: shuffle altered deck size\n");
				++curFails;
			} else {
				numUnAltered = 0;
				for(k = 0; k < sizeof(preCall.deck[i]); ++k) {
					if(preCall.deck[i][k] == postCall->deck[i][k]) {
						++numUnAltered;
					}
				}
				if(numUnAltered) {
					printf("Error: %d cards were not moved\n", numUnAltered);
					++curFails;
				}
			}
		}

        if(curFails) {
            printf("Test %d failed with %d errors\n", j, curFails);
            ++numFailed;
        } else {
            printf("Test %d passed\n", j+1);
            ++numPassed;
        }
    }

    printf("shuffle() test results: %d tests passed, %d tests failed\n\n", numPassed, numFailed);
}


int _assertTrue(int tof) {
    if(tof != 0)
        return 1;
    return 0;
}


void cardtest1() {
    struct gameState *game;
    int i, testPassed = 0, testFailed = 0, player, players, seed,
        handLen, deckSize, discardCount;

    player = 0;
    players = 2;

    printf("\n *** CARD TEST 1: SMITHY *** \n");
    for(player = 0; player < players; ++players) {
        printf("Running tests for player %d\n", player+1);
        for(i = 0; i < 100; i++) {
            int cards[10] = {adventurer, council_room, cutpurse, embargo, mine,
                             minion, sea_hag, smithy, tribute, village};
            seed = rand();
            game = (struct gameState *) malloc(sizeof(struct gameState));
            // initializeGame(players, cards, seed, game);
            game->deckCount[player] = rand() % MAX_DECK;
            game->handCount[player] = rand() % MAX_HAND;

            handLen = game->handCount[player];
            deckSize = game->deckCount[player];
            discardCount = game->playedCardCount;

            // card call
            cardSmithy(game, 0, player);

            if(game->playedCardCount != (discardCount+1)) {
                printf("Test %d failed: no discard\n", i+1);
                testFailed++;
            } else if(game->handCount[player] != (handLen + 2)) {
                printf("Test %d failed: not enough cards drawn\n", i+1);
                testFailed++;
            } else if(game->deckCount[player] != (deckSize - 3)) {
                printf("Test %d failed: not enough cards drawn\n", i+1);
                testFailed++;
            } else {
                printf("Test %d passed\n", i+1);
                testPassed++;
            }
            free(game);
        }
    }

    printf("Smithy test results: %d tests passed, %d tests failed\n\n", testPassed, testFailed);
}



int cardSmithy(struct gameState *game, int handPos, int player) {
    int i;

    //+3 Cards
    for (i = 0; i < 3; i++) {
        drawCard(player, game);
    }

    //discard card from hand
    discardCard(handPos, player, game, 0);
    return 0;

}
