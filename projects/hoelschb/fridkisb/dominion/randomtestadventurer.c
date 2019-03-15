#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

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
    struct gameState G, pre;
    int s, i, j;
    int failures = 0;
    int tests = 0;
    int randomInt;
    int numTests = 2000;
    int treasureCount;
    int shuffle;

    srand(time(NULL));

    for(j=0; j<numTests; j++)
    {

        s = initializeGame(numPlayer, supply, seed, &G);
        G.hand[0][0] = adventurer;
        G.handCount[0] = 1;

        randomInt = rand() % MAX_HAND;
        G.handCount[0] = 1 + randomInt;

        randomInt = rand() % (MAX_HAND + 1);
        G.deckCount[0] = randomInt;

        randomInt = rand() % (MAX_HAND + 1);
        G.discardCount[0] = randomInt;

        for(i=1; i<G.handCount[0]; i++)
        {
            G.hand[0][i] = rand() % 27;
        }

        treasureCount = 0;
        shuffle = 0;

        for(i=0; i<G.deckCount[0]; i++)
        {
            G.deck[0][i] = rand() % 27;
            if(G.deck[0][i] == 4 || G.deck[0][i] == 5 || G.deck[0][i] == 6)
            {
                treasureCount++;
            }
        }

        if(treasureCount < 2)
        {
            shuffle = 1;
        }

        for(i=0; i<G.discardCount[0]; i++)
        {
            G.discard[0][i] = rand() % 27;
            if(G.discard[0][i] == 4 || G.discard[0][i] == 5 || G.discard[0][i] == 6)
            {
                treasureCount++;
            }
        }

        G.numActions = 1 + (rand() % 10);

        G.numBuys = 1;
        G.whoseTurn = 0;

        memcpy(&pre, &G, sizeof(G));

        printf("\nTESTING Adventurer Card, iteration %d:\n", j);

        s = playCard(0, 0, 0, 0, &G);

        printf("Checking action count.\n");
        failures += assertTrue(pre.numActions - 1, G.numActions);
        tests++;

        if(treasureCount >= 2)
        {
            printf("Checking hand size.\n");
            failures += assertTrue(pre.handCount[0] + 1, G.handCount[0]);
            tests++;
        }
        else
        {
            printf("Checking hand size.\n");
            failures += assertTrue(pre.handCount[0] + treasureCount - 1, G.handCount[0]);
            tests++;
        }

        printf("Checking buys count.\n");
        failures += assertTrue(pre.numBuys, G.numBuys);
        tests++;


        if(treasureCount >= 2)
        {
            printf("Checking Deck + Discard Count.\n");
            failures += assertTrue(pre.discardCount[0] + pre.deckCount[0] - 2, G.deckCount[0] + G.deckCount[0]);
            tests++;
        }
        else
        {
            printf("Checking Deck + Discard Count.\n");
            failures += assertTrue(pre.discardCount[0] + pre.deckCount[0] - treasureCount, G.deckCount[0] + G.deckCount[0]);
            tests++;
        }

        printf("Checking played count.\n");
        failures += assertTrue(pre.playedCardCount + 1, G.playedCardCount);
        tests++;

        printf("Checking return code.\n");
        failures += assertTrue(0, s);
        tests++;

        if(s != 0)
        {
            printf("Pre conditions: Actions: %d, handsize: %d, decksize: %d, discardsize %d\n", pre.numActions, pre.handCount[0], pre.deckCount[0], pre.discardCount[0]);
        }

    }

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