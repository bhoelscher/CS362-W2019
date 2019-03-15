

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
    //int seed = 1234;
    //int numPlayer = 2;
    //int supply[10] = {adventurer, smithy, village, council_room, steward, great_hall, embargo, mine, tribute, minion};
    struct gameState G;
    int failures = 0;
    int tests = 0;

    //Initialize supply count values
    G.supplyCount[adventurer] = 10;
    G.supplyCount[smithy] = 0;
    G.supplyCount[great_hall] = 8;
    G.supplyCount[gold] = 30;
    G.supplyCount[baron] = -1;
    G.supplyCount[estate] = 8;
    G.supplyCount[steward] = -200;


    printf("TESTING supplyCount():\n");

    //Check cards in the intialized supply
    printf("Checking initial standard kingdom card supply count.\n");
    failures += assertTrue(10,supplyCount(adventurer, &G));
    tests++;

    printf("Checking initial Victory kingdom card supply count.\n");
    failures += assertTrue(8,supplyCount(great_hall, &G));
    tests++;

    printf("Checking initial Estate supply count.\n");
    failures += assertTrue(8,supplyCount(estate, &G));
    tests++;

    printf("Checking initial Gold supply count.\n");
    failures += assertTrue(30,supplyCount(gold, &G));
    tests++;

    printf("Checking card outside of card range.\n");
    failures += assertTrue(-1,supplyCount(treasure_map+1, &G));
    tests++;

    printf("Checking card with negative supply count.\n");
    failures += assertTrue(-200,supplyCount(steward, &G));
    tests++;

    //Check cards not included in this game's supply
    printf("Checking supply count of Baron, which is not in the intialized game.\n");
    failures += assertTrue(-1,supplyCount(baron, &G));
    tests++;

    //Check a card with 0 supply
    printf("Checking the supply of a sold out kingdom card.\n");
    failures += assertTrue(0,supplyCount(smithy, &G));
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