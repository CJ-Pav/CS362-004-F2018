/************************************************
 * Name: Christopher Pavlovich
 * Program: unittest2.cpp
 ************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

/***
 * unit test 2
 * testing: shuffle()
***/
int main(int argc, char *argv[]) {
	struct gameState G;
	int i, status = 0, a = -1, set[10] = {adventurer, gardens, embargo, mine, cutpurse,
		sea_hag, tribute, village, minion, smithy};

	printf("Begin unit test 2...\n");
	printf("Test function: shuffle\n");

	memset(&G, 'z', sizeof(struct gameState));

	initializeGame(4, set, argv[1]-48, &G);

	printf ("Rough guide to locations in structure:\n");
	printf ("0: numPlayers\n");
	printf ("%ld: supplyCount[0]\n", ((long)&(G.supplyCount[0]))-((long)&G));
	printf ("%ld: embargoTokens[0]\n", ((long)&(G.embargoTokens[0]))-((long)&G));
	printf ("%ld: hand[0][0]\n", ((long)&(G.hand[0][0]))-(long)(&G));
	printf ("%ld: deck[0][0]\n", ((long)&(G.deck[0][0]))-(long)(&G));
	printf ("%ld: discard[0][0]\n", ((long)&(G.discard[0][0]))-(long)(&G));
	printf ("%ld: playerCards[0]\n", ((long)&(G.playedCards[0]))-(long)(&G));

	for (i = 0; i < sizeof(struct gameState); i++) {
		if (((char*)&G)[i] == 'z') {
			if (a == -1) {
				a = i;
			}
		}
		else{
			if (a != -1) {
				if (a == (i-1)) {
					printf ("Byte %d not initialized.\n", a);
				}
				else {
					printf ("Bytes %d-%d not initialized.\n", a, i-1);
				}
				a = -1;
			}
		}
	}

	if (a != -1) {
		if (a == (i-1)) {
			printf ("Byte %d not initialized.\n", a);
		}
		else {
			printf ("Bytes %d-%d not initialized.\n", a, i-1);
		}
	}

	status = shuffle(0, G);

	printf("shuffle return value: %d", status);

	return 0;
}
