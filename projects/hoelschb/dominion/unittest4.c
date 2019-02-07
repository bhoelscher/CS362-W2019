

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
    int numPlayer = 4;
    int supply[10] = {adventurer, smithy, village, council_room, steward, great_hall, embargo, mine, tribute, minion};
    struct gameState G;
    int i, j, s;
    int failures = 0;
    int tests = 0;
    int bonus = 0;
    int carryover;


    s = initializeGame(numPlayer, supply, seed, &G);

    G.whoseTurn = 0;
    for (i = 0; i < MAX_HAND; i++)
    {
        G.hand[0][i] = copper;
        G.hand[1][i] = silver;
        G.hand[2][i] = gold;
        //hand that repeats copper, silver, gold in order
        G.hand[3][i] = copper + (i % 3);
    }

    printf("TESTING updateCoins():\n");

    //Check cards in the intialized supply
    for (i = 0; i < MAX_HAND; i++)
    {
        for (j = 0; j <numPlayer; j++)
        {
            G.handCount[j] = i+1;
        }
        bonus = i % 11;
        printf("Checking Player 1 with %d copper cards and %d bonus\n", i+1, bonus);
        updateCoins(0, &G, bonus);
        failures += assertTrue((i+1)*1 + bonus,G.coins);
        tests++;

        if (bonus == 10)
        {
            bonus = 0;
        }
        else
        {
            bonus++;
        }
        printf("Checking Player 2 with %d silver cards and %d bonus\n", i+1, bonus);
        updateCoins(1, &G, bonus);
        failures += assertTrue((i+1)*2 + bonus,G.coins);
        tests++;

        if (bonus == 10)
        {
            bonus = 0;
        }
        else
        {
            bonus++;
        }
        printf("Checking Player 3 with %d gold cards and %d bonus\n", i+1, bonus);
        updateCoins(2, &G, bonus);
        failures += assertTrue((i+1)*3 + bonus,G.coins);
        tests++;

        if (bonus == 10)
        {
            bonus = 0;
        }
        else
        {
            bonus++;
        }
        printf("Checking Player 2 with %d assorted treasure cards and %d bonus\n", i+1, bonus);
        carryover = (i+1) % 3;
        if (carryover == 2)
        {
            carryover++;
        }
        updateCoins(3, &G, bonus);
        failures += assertTrue((((i+1) / 3) * 6) + carryover + bonus,G.coins);
        tests++;
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