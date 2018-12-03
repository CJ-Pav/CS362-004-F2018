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

	memset(&G, 0, sizeof(struct gameState));
	initializeGame(4, set, atoi(argv[1]), &G);

	printf("Begin smithy test 1...\n");

	printf("Checking deck count.\n");



	printf("Current deck count: %ld", status[0]);

	return 0;
}
