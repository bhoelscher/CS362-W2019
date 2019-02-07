

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
    int failures = 0;
    int tests = 0;

    printf("TESTING getCost():\n");

    //Check cards in the intialized supply
    printf("Checking cost of a curse.\n");
    failures += assertTrue(0,getCost(curse));
    tests++;

    printf("Checking cost of an estate.\n");
    failures += assertTrue(2,getCost(estate));
    tests++;

    printf("Checking cost of a duchy.\n");
    failures += assertTrue(5,getCost(duchy));
    tests++;

    printf("Checking cost of a province.\n");
    failures += assertTrue(8,getCost(province));
    tests++;

    printf("Checking cost of a copper.\n");
    failures += assertTrue(0,getCost(copper));
    tests++;

    printf("Checking cost of a silver.\n");
    failures += assertTrue(3,getCost(silver));
    tests++;

    printf("Checking cost of a gold.\n");
    failures += assertTrue(6,getCost(gold));
    tests++;

    printf("Checking cost of a adventurer.\n");
    failures += assertTrue(6,getCost(adventurer));
    tests++;

    printf("Checking cost of a council room.\n");
    failures += assertTrue(5,getCost(council_room));
    tests++;

    printf("Checking cost of a feast.\n");
    failures += assertTrue(4,getCost(feast));
    tests++;

    printf("Checking cost of a gardens.\n");
    failures += assertTrue(4,getCost(gardens));
    tests++;

    printf("Checking cost of a mine.\n");
    failures += assertTrue(5,getCost(mine));
    tests++;

    printf("Checking cost of a remodel.\n");
    failures += assertTrue(4,getCost(remodel));
    tests++;

    printf("Checking cost of a smithy.\n");
    failures += assertTrue(4,getCost(smithy));
    tests++;

    printf("Checking cost of a village.\n");
    failures += assertTrue(3,getCost(village));
    tests++;

    printf("Checking cost of a baron.\n");
    failures += assertTrue(4,getCost(baron));
    tests++;

    printf("Checking cost of a great_hall.\n");
    failures += assertTrue(3,getCost(great_hall));
    tests++;

    printf("Checking cost of a minion.\n");
    failures += assertTrue(5,getCost(minion));
    tests++;

    printf("Checking cost of a steward.\n");
    failures += assertTrue(3,getCost(steward));
    tests++;

    printf("Checking cost of a tribute.\n");
    failures += assertTrue(5,getCost(tribute));
    tests++;

    printf("Checking cost of an ambassador.\n");
    failures += assertTrue(3,getCost(ambassador));
    tests++;

    printf("Checking cost of a cutpurse.\n");
    failures += assertTrue(4,getCost(cutpurse));
    tests++;

    printf("Checking cost of an embargo.\n");
    failures += assertTrue(2,getCost(embargo));
    tests++;

    printf("Checking cost of a outpost.\n");
    failures += assertTrue(5,getCost(outpost));
    tests++;

    printf("Checking cost of a salvager.\n");
    failures += assertTrue(4,getCost(salvager));
    tests++;

    printf("Checking cost of a sea_hag.\n");
    failures += assertTrue(4,getCost(sea_hag));
    tests++;

    printf("Checking cost of a treasure_map.\n");
    failures += assertTrue(4,getCost(treasure_map));
    tests++;

    //Checking non-exist cards
    printf("Checking the cost of a non-existant card.\n");
    failures += assertTrue(-1,getCost(100));
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