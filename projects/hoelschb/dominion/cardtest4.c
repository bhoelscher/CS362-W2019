

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
    G.hand[0][0] = council_room;
    G.handCount[0] = 1;
    G.numActions = 1;
    G.numBuys = 1;
    G.whoseTurn = 0;
    G.handCount[1] = 0;

    printf("TESTING Council Room Card:\n");

    s = playCard(0, 0, 0, 0, &G);

    printf("Checking action count.\n");
    failures += assertTrue(0, G.numActions);
    tests++;

    printf("Checking hand size of player 1.\n");
    failures += assertTrue(4, G.handCount[0]);
    tests++;

    printf("Checking hand size of player 2.\n");
    failures += assertTrue(1, G.handCount[1]);
    tests++;

    printf("Checking buys count.\n");
    failures += assertTrue(2, G.numBuys);
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