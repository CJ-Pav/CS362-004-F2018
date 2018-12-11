#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "rngs.h"
#include "assert.h"
#include <time.h>

/***
 * unit test 1
 * testing: shuffle()
***/
int main() {
    struct gameState *game;
    int i, testPassed = 0, testFailed = 0, player, players, seed, handLen, deckSize, discardCount;

	srand(time(NULL));

    printf("\nStarting testing for Smithy\n");

    for(i = 0; i < 1000; i++) {
        int cards[10] = {adventurer, council_room, cutpurse, embargo, mine,
                         minion, sea_hag, smithy, tribute, village};
        players = rand() % MAX_PLAYERS;
        seed = rand();
        game = (struct gameState *) malloc(sizeof(struct gameState));
        initializeGame(players, cards, seed, game);
        player = 0;
        game->deckCount[player] = rand() % MAX_DECK;
        game->handCount[player] = rand() % MAX_HAND;

        handLen = game->handCount[player];
        deckSize = game->deckCount[player];
        discardCount = game->playedCardCount;

        cardSmithy(game, 0, player);

        if(game->playedCardCount != (discardCount+1)) {
            printf("Test %d failed: Smithy card not succesfully discarded\n", i+1);
            testFailed++;
        } else if(game->handCount[player] != (handLen+2)) {
            printf("Test %d failed: not enough cards drawn\n", i+1);
            testFailed++;
        } else if(game->deckCount[player] != (deckSize-3)) {
            printf("Test %d failed: not enough cards drawn\n", i+1);
            testFailed++;
        } else {
            printf("Test %d passed\n", i+1);
            testPassed++;
        }

        free(game);
    }

    printf("Smithy test results: %d tests passed, %d tests failed\n\n", testPassed, testFailed);
}
