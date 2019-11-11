// unit test for mine
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "mine"

int main(){
    int i, r, discarded1, discarded2, newCards; // need to figure out
    int handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 100;
    int currentPlayer = 0;
    int numPlayers = 2;
    // set card array
    int k[10] = { adventurer, council_room, feast, gardens, mine
    , remodel, smithy, village, baron, great_hall };
    // declare the game state
    struct gameState G, testG;
    // declare the arrays
    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];
    for(i = 0; i < MAX_HAND; i++){
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
    }
    printf("Begin Testing mineCard():\n");
    //
    // set the state of your variables
    // comment on what this is going to test
    //
    memset(&G, 23, sizeof(struct gameState));    // set the game state
    r = initializeGame(2, k, seed, &G);          // initialize a new game
    memcpy(&testG, &G, sizeof(struct gameState));
    discarded1 = testG.discardCount[currentPlayer]; // set any other variables

    // call the refactored function
    mineCard(currentPlayer, choice1, choice2, &G, handPos);
    discarded2 = testG.discardCount[currentPlayer];
    newCards = 2;



    // verify that your asserts pass, for the bugs your asserts may fail
    printf("cost of choice1 = %d, cost of choice2 = %d\n", getCost(G.hand[currentPlayer][choice1]), getCost(choice2));
    assert(getCost(G.hand[currentPlayer][choice1]) + 3 > getCost(choice2)); // check a condition
    //assert(some condition);
    //assert(some condition);

    //
    // adjust the state of your variables to continue testing the function
    // comment on what this is going to test
    //
    memset(&G, 0, sizeof(struct gameState)); // set the game state
    r = initializeGame(3, k, seed, &G);      // initialize a new game
    G.coins = 0;              // set any other variables
    //memcpy(G.hand[p], silvers, sizeof(int) *handCount);

    // call the refactored function again
    mineCard(currentPlayer, choice1, choice2, &G, handPos);

    // verify that your asserts pass, for the bugs your asserts may fail
    printf("deck count = %d, expected = %d\n", G.deckCount[currentPlayer], G.deckCount[currentPlayer] - newCards - discarded2 + discarded1);     // should be add to deck instead of adding to hand
    assert(testG.deckCount[currentPlayer] == G.deckCount[currentPlayer] - newCards - discarded2 + discarded1); // check a condition
    //assert(some condition);
    //assert(some condition);

    printf("Test completed!\n");

    return 0;

}
