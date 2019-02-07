

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
    int i, s;
    int failures = 0;
    int tests = 0;


    s = initializeGame(numPlayer, supply, seed, &G);

    G.whoseTurn = 0;
    for (i = 0; i < MAX_HAND; i++)
    {
        G.hand[0][i] = i % (treasure_map + 1);
        G.hand[1][i] = (i + 5) % (treasure_map + 1);
    }

    printf("TESTING handCard():\n");

    //Check cards in the intialized supply
    for (i = 0; i <= treasure_map; i++)
    {
        printf("Checking card in position %d of Player 1's hand\n", i);
        failures += assertTrue(i,handCard(i, &G));
        tests++;
    }

    printf("Checking last card in Player 1's hand.\n");
    failures += assertTrue((MAX_HAND - 1) % (treasure_map + 1),handCard(MAX_HAND-1, &G));
    tests++;

    G.whoseTurn = 1;

    printf("Checking first card of Player 2's hand.\n");
    failures += assertTrue(5,handCard(0, &G));
    tests++;

    printf("Checking last card of Player 2's hand.\n");
    failures += assertTrue((MAX_HAND + 4) % (treasure_map + 1),handCard(MAX_HAND-1, &G));
    tests++;

    printf("Checking 376th card of Player 2's hand.\n");
    failures += assertTrue(380 % (treasure_map + 1),handCard(375, &G));
    tests++;

    printf("Checking card position above MAX_HAND.\n");
    failures += assertTrue(-1, handCard(MAX_HAND+1, &G));
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