#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

int main () {

    // Set up function inputs
    struct gameState g;
    memset(&g, 0, sizeof(struct gameState));
    // Elements of gamestate (supply counts)
    for (int i = 0; i < 27; i++) {
        if (i == adventurer || i == steward || i == sea_hag) g.supplyCount[i] = 0; // sea hag empty
        else g.supplyCount[i] = 10;
    }
    // Call function
    int over = isGameOver(&g);
    // Compare expected v actual output
    if (!over) printf ("Game should have ended (sea hag), but did not!\n");

    // Test treasure map as well
    g.supplyCount[sea_hag] = 10;
    g.supplyCount[treasure_map] = 0;

    // Call function
    over = isGameOver(&g);
    // Compare expected v actual output
    if (!over) printf ("Game should have ended (treasure map), but did not!\n");
    
    return 0;
}