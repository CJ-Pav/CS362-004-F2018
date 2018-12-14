/************************************************
 * Name: Christopher Pavlovich
 * Program: cardtest1.c
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
 #include "cardtest1.h"

/***
 * testing: smithy()
***/
int cardtest1() {
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
