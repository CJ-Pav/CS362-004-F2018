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
 #include "unittest2.h"

/***
 * unit test 2
 * testing: shuffle()
***/
int unittest2() {
	struct gameState preCall, *postCall=NULL;
    int numPassed, numFailed, i, j, k, numUnAltered, curFails, status;
    int cards[10] = {adventurer, council_room, cutpurse, embargo, mine,
        minion, sea_hag, smithy, tribute, village};

	srand(time(NULL));
    numPassed = 0;
    numFailed = 0;
    j = 0;

    printf("\n *** UNIT TEST 1 *** \n");
    printf("Test function: shuffle()\n");

    while(j < 25) {
        ++j;
        curFails = 0;
		status = 0;
		initializeGame(i, cards, 1000, &preCall);
        while(preCall.deckCount[i] <= 20 || preCall.deckCount[i] >= 450)
            preCall.deckCount[i] = rand() % MAX_DECK;
            // preCall.deckCount[i] = 20;
        while(preCall.handCount[i] <= 3 || preCall.handCount[i] >= 100)
            preCall.handCount[i] = rand() % MAX_HAND;
            // preCall.handCount[i] = 3;
        if(preCall.playedCardCount < 0)
            preCall.playedCardCount = 0;

		// function call
		status = shuffle(i, &preCall);
		memcpy(postCall, &preCall, sizeof(struct gameState));
		status += shuffle(i, postCall);

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

	return 0;
}
