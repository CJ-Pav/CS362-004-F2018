/************************************************
 * Name: Christopher Pavlovich
 * Program: unittest1.c
 ************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

/***
 * unit test 1
 * testing: compare()
***/
int main(int argc, char *argv[]) {
	struct gameState G;
	int i, status[5], a = -1, expectedHandCount = 0;
	int set[10] = {adventurer, gardens, embargo, mine, cutpurse,
		sea_hag, tribute, village, minion, smithy};

	srand(time(NULL));


	printf("Begin smithy test 1...\n");

	printf("Checking deck count.\n");

	for(int i = 0; i < 100; ++i) {
		// reset randomizer & reinit gameState
		seed = rand();
		memset(&G, 0, sizeof(struct gameState));
		initializeGame(2, set, atoi(argv[1]), &G);

		// set random deck count & player hand
		G.deckCount[1] = rand() % MAX_DECK;
		G.handCount[1] = rand() % MAX_HAND;

		// printf("Player 1 pre-smithy deck count: %d\n", G.deckCount[1]);
		// printf("Player 2 pre-smithy deck count: %d\n", G.deckCount[2]);
		// printf("Player 1 pre-smithy hand count: %d\n", G.handCount[1]);
		// printf("Player 2 pre-smithy hand count: %d\n", G.handCount[2]);

		// int expectedDeckCount = G.deckCount[1] - 3;
		// expectedHandCount = G.handCount[1] + 2;
		expectedHandCount = G.handCount[1] + 2;

		cardSmithy(&G, int 1, int 1);

		actualHandCount = G.handCount[1];

		if(G.deckCount[j] != expectedHandCount) {
			printf("Incorrect card draw. Expected hand count: %d, Actual hand count: %d\n", expectedHandCount, actualHandCount)
		}

	}




	return 0;
}
