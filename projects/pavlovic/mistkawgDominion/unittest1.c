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

/***
 * unit test 1
 * testing: compare()
***/
int main(int argc, char *argv[]) {
	struct gameState G;
	int i, status[5], a = -1;
	int set[10] = {adventurer, gardens, embargo, mine, cutpurse,
		sea_hag, tribute, village, minion, smithy};

	printf("Begin unit test 1...\n");
	printf("Test function: compare()\n");

	memset(&G, 0, sizeof(struct gameState));

	initializeGame(4, set, atoi(argv[1]), &G);

	printf("Layout...\n");
	printf("0: numPlayers\n");
	printf("%ld: supplyCount[0]\n", ((long)&(G.supplyCount[0]))-((long)&G));
	printf("%ld: embargoTokens[0]\n", ((long)&(G.embargoTokens[0]))-((long)&G));
	printf("%ld: hand[0][0]\n", ((long)&(G.hand[0][0]))-(long)(&G));
	printf("%ld: deck[0][0]\n", ((long)&(G.deck[0][0]))-(long)(&G));
	printf("%ld: discard[0][0]\n", ((long)&(G.discard[0][0]))-(long)(&G));
	printf("%ld: playerCards[0]\n", ((long)&(G.playedCards[0]))-(long)(&G));



	char c, b;
	c = '1';
	b = '0';
	status[0] = compare(c, '0');
	status[1] = compare(2, 17);
	status[2] = compare(23, -3);
	status[3] = compare(-2, 21);
	status[4] = compare(6, -14);

	printf("Result of compare %d %d: %d", 1, 0, status[0]);
	printf("Result of compare %d %d: %d", 2, 17, status[0]);
	printf("Result of compare %d %d: %d", 23, -3, status[0]);
	printf("Result of compare %d %d: %d", -2, 21, status[0]);
	printf("Result of compare %d %d: %d", 6, -14, status[0]);

	return 0;
}
