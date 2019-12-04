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
    int bonus = 0;

    // Elements of gamestate
    g.whoseTurn = 0;
    g.handCount[0] = 5;
    g.discardCount[0] = 3;
    g.supplyCount[silver] = 10;
    g.numPlayers = 2;
    g.playedCardCount = 0;

    // Set up player's hand
    g.hand[0][0] = mine;
    g.hand[0][1] = copper;

    // Set up player's discard
    g.discard[0][0] = sea_hag;
    g.discard[0][1] = steward;
    g.discard[0][2] = silver;
    g.discard[0][3] = -1;
    g.discard[0][4] = -1;
    g.discard[0][5] = -1;

    // Call function
    int e = cardEffect(mine, 1, silver, 0, &g, 0, &bonus);
    
    // Compare expected v actual output
    if (e != 0) printf ("cardEffect failed!\n");
    if (g.playedCardCount != 1) printf ("Incorrect number of discards!\n");
    if (g.playedCards[0] == copper || g.playedCards[1] == copper) printf ("Copper not trashed, heading to discard pile!\n");

    return 0;
}