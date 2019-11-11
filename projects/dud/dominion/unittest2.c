// unit test for minion
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "minion"

int main(){
    int i, r, card, newBuys; // need to figure out
    int handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 100;
    int thisPlayer = 0;
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
    printf("Begin Testing minionCard():\n");
    //
    // set the state of your variables
    // comment on what this is going to test
    //
    memset(&G, 23, sizeof(struct gameState));    // set the game state
    r = initializeGame(2, k, seed, &G);          // initialize a new game
    G.handCount[thisPlayer] = 0;                  // set any other variables
    memcpy(&testG, &G, sizeof(struct gameState));

    // call the refactored function
    minionCard(card, choice1, choice2, &G, handPos);

    printf("action count = %d, expected = %d\n", testG.numActions, G.numActions + newActions);


    // verify that your asserts pass, for the bugs your asserts may fail
    assert(testG.numActions == G.numActions + newActions); // check a condition
    //assert(some condition);
    //assert(some condition);

    //
    // adjust the state of your variables to continue testing the function
    // comment on what this is going to test
    //
    memset(&G, 0, sizeof(struct gameState)); // set the game state
    r = initializeGame(3, k, seed, &G);      // initialize a new game
    G.handCount[thisPlayer] = 0;              // set any other variables
    memcpy(&testG, &G, sizeof(struct gameState));

    // call the refactored function again
    minionCard(card, choice1, choice2, &G, handPos);

    printf("hand count = %d, expected = %d\n", testG.handCount[currentPlayer], G.handCount[currentPlayer] + newCards - discarded);

    // verify that your asserts pass, for the bugs your asserts may fail
    assert(testG.handCount[currentPlayer] == G.handCount[currentPlayer] + newCards - discarded); // check a condition
    //assert(some condition);
    //assert(some condition);

    printf("Test completed!\n");

    return 0;

}
