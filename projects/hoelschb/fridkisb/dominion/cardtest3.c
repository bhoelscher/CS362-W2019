

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


int assertTrue(int expected, int actual)
{
    if (expected == actual)
    {
        printf("\tTest condition passed\n");
        return 0;
    }
    else
    {
        printf("\tTest condition FAILED. Expected value: %d Actual value: %d\n", expected, actual);
        return 1;
    }
}

int main() {
    int seed = 1234;
    int numPlayer = 2;
    int supply[10] = {adventurer, smithy, village, council_room, steward, great_hall, embargo, mine, tribute, minion};
    struct gameState G;
    int s;
    int failures = 0;
    int tests = 0;

    s = initializeGame(numPlayer, supply, seed, &G);
    G.hand[0][0] = adventurer;
    G.handCount[0] = 1;
    G.numActions = 1;
    G.numBuys = 1;
    G.whoseTurn = 0;

    printf("TESTING Adventurer Card:\n");

    //Test with two or more treasures in the deck
    printf("Testing Adventurer with 2 or more treasure cards in the deck.\n");

    s = playCard(0, 0, 0, 0, &G);

    printf("Checking action count.\n");
    failures += assertTrue(0, G.numActions);
    tests++;

    printf("Checking hand size.\n");
    failures += assertTrue(2, G.handCount[0]);
    tests++;

    printf("Checking that two treasures were drawn.\n");
    if (G.hand[0][0] >= copper && G.hand[0][0] <= gold && G.hand[0][1] >= copper && G.hand[0][1] <= gold)
    {
        printf("\tTest condition passed\n");
    }
    else
    {
        printf("\tTest condition FAILED. Card drawn is not a treasure.\n");
        failures++;
    }
    tests++;

    printf("Checking buys count.\n");
    failures += assertTrue(1, G.numBuys);
    tests++;

    printf("Checking return code.\n");
    failures += assertTrue(0, s);
    tests++;

    //Test with less than two treasures in the deck, with two or more treasures in the discard pile
    printf("Testing Adventurer with one treasure in the deck and one or more treasures in the discard pile.\n");

    G.handCount[0] = 1;
    G.hand[0][0] = adventurer;

    G.deckCount[0] = 4;
    G.deck[0][0] = gold;
    G.deck[0][1] = embargo;
    G.deck[0][2] = smithy;
    G.deck[0][3] = duchy;

    G.discardCount[0] = 3;
    G.discard[0][0] = silver;
    G.discard[0][1] = copper;
    G.discard[0][2] = silver;

    G.numActions = 1;

    s = playCard(0, 0, 0, 0, &G);

    printf("Checking action count.\n");
    failures += assertTrue(0, G.numActions);
    tests++;

    printf("Checking hand size.\n");
    failures += assertTrue(2, G.handCount[0]);
    tests++;

    printf("Checking that two treasures were drawn.\n");
    if (G.hand[0][0] >= copper && G.hand[0][0] <= gold && G.hand[0][1] >= copper && G.hand[0][1] <= gold)
    {
        printf("\tTest condition passed\n");
    }
    else
    {
        printf("\tTest condition FAILED. Card drawn is not a treasure.\n");
        failures++;
    }
    tests++;

    printf("Checking buys count.\n");
    failures += assertTrue(1, G.numBuys);
    tests++;

    printf("Checking discard count.\n");
    failures += assertTrue(3, G.discardCount[0]);
    tests++;

    printf("Checking return code.\n");
    failures += assertTrue(0, s);
    tests++;

    // Test with less than two drawable treasures

    printf("Testing Adventurer with only one treasure in deck and discard combined.\n");

    G.handCount[0] = 1;
    G.hand[0][0] = adventurer;

    G.deckCount[0] = 2;
    G.deck[0][0] = gold;
    G.deck[0][1] = embargo;

    G.discardCount[0] = 3;
    G.discard[0][0] = duchy;
    G.discard[0][1] = province;
    G.discard[0][2] = estate;

    G.numActions = 1;

    s = playCard(0, 0, 0, 0, &G);

    printf("Checking action count.\n");
    failures += assertTrue(0, G.numActions);
    tests++;

    printf("Checking hand size.\n");
    failures += assertTrue(1, G.handCount[0]);
    tests++;

    printf("Checking that two treasures were drawn.\n");
    if (G.hand[0][0] >= copper && G.hand[0][0] <= gold)
    {
        printf("\tTest condition passed\n");
    }
    else
    {
        printf("\tTest condition FAILED. Card drawn is not a treasure.\n");
        failures++;
    }
    tests++;

    printf("Checking buys count.\n");
    failures += assertTrue(1, G.numBuys);
    tests++;

    printf("Checking return code.\n");
    failures += assertTrue(0, s);
    tests++;


    if (failures == 0)
    {
        printf("All %d tests PASSED!\n", tests);
    }
    else
    {
        printf("%d out of %d tests FAILED\n", failures, tests);
    }

    return 0;
}