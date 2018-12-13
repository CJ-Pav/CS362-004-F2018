#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "rngs.h"
#include "assert.h"
#include <time.h>

#define DEBUG 0
#define NOISY_TEST 1

/***
 * unit test 1
 * testing: discard()
***/

void test(struct gameState *preCall) {

}

int main() {
    struct gameState *preCall;
    int numPassed = 0, numFailed = 0, i, is, seed, handLen, deckSize, discardCount;

    printf("\n *** UNIT TEST 1 *** \n");

    for(i = 0; i < 2; i++) {
        int cards[10] = {adventurer, council_room, cutpurse, embargo, mine,
                         minion, sea_hag, smithy, tribute, village};
        is = 2;
        seed = rand();
        game = (struct gameState *) malloc(sizeof(struct gameState));
        initializeGame(i, cards, seed, game);
        i = 0;

        while(game->deckCount[i] <= 20)
            game->deckCount[i] = rand() % MAX_DECK;
        while(game->handCount[i] <= 3)
            game->handCount[i] = rand() % MAX_HAND;

        handLen = game->handCount[i];
        deckSize = game->deckCount[i];
        discardCount = game->playedCardCount;

        // function call
        game->discardCard(0, player, preCall, );

        if(game->playedCardCount != (discardCount+1)) {
            printf("Test %d failed: Smithy card not succesfully discarded\n", i+1);
            numFailed++;
        } else if(game->handCount[i] != (handLen+2)) {
            printf("Test %d failed: not enough cards drawn\n", i+1);
            numFailed++;
        } else if(game->deckCount[i] != (deckSize-3)) {
            printf("Test %d failed: not enough cards drawn\n", i+1);
            numFailed++;
        } else {
            printf("Test %d passed\n", i+1);
            passed++;
        }
        free(game);
    }

    printf("Smithy test results: %d tests passed, %d tests failed\n\n", numPassed, numFailed);

    return 0;
}
