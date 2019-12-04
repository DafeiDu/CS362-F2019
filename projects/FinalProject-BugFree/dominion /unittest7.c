/***
**** Name: Dafei Du
**** CS 362 final project
***/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <rngs.h>
#include <stdlib.h>

int main(){
    int numPlayers = 2, seed = 100, choice1, choice2, choice3, handPos, bonus;
    struct gameState G, testG;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, seed, &G);       //initialize gameState
    memcpy(&testG, &G, sizeof(struct gameState));
    int card = tribute;
    cardEffect(card, choice1, choice2, choice3, &testG, handPos, bonus);

    printf("Begin testing bug7(for loop overruns the array):\n");
    if((testG.numActions <= G.numActions + 4) && (testG.coins <= G.coins + 4) && (numHandCards(&testG) <= numHandCards(&G) + 2)){
        printf("PASSED\n");
    }
    else{
        printf("FAILED\n");
    }
    printf("Test completed!\n");
    
    return 0;
}
