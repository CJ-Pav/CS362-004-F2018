/************************************************
 * Name: Christopher Pavlovich
 * Program: unittest2.c
 ************************************************/
 #include "dominion.h"
 #include "dominion_helpers.h"
 #include "interface.h"
 #include <string.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include "rngs.h"
 #include <assert.h>
 #include <time.h>
 #include "unittest1.h"

#define DEBUG 0
#define NOISY_TEST 1

/***
 * unit test 1
 * testing: discardCard()
***/
int unittest1() {
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

    for(i = 0; i < 2; ++i) { // i is current player
        printf("Running tests for player %d\n", i+1);
        while(j < 25) {
            ++j;
            curFails = 0;

            initializeGame(i, cards, 1000, &curGame);


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

    printf("Smithy test results: %d tests passed, %d tests failed\n\n", numPassed, numFailed);

    return 0;
}

int _assertTrue(int tof) {
    if(tof != 0)
        return 1;
    return 0;
}
