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

int testScoreFor1(struct gameState G){
    printf("Begin first testing bug5(scoreFor fucntion):\n");
    int currentPlayer = 0;
    G.handCount[currentPlayer] = 0;
    G.deckCount[currentPlayer] = 1;
    G.deck[currentPlayer][0] = estate;
    G.discardCount[currentPlayer] = 0;
    if (scoreFor(thisPlayer, &G) == 0){
        printf("PASSED!\n");
    }
    else{
        printf("FAILED!\n");
    }

    printf("First test completed!")
}
int testScoreFor2(struct gameState G){
    printf("Begin second testing bug5(scoreFor fucntion):\n");
    int currentPlayer = 0;
    G.handCount[currentPlayer] = 0;
    G.deckCount[currentPlayer] = 1;
    G.deck[currentPlayer][0] = estate;
    G.discardCount[currentPlayer] = 2;
    G.discard[thisPlayer][0] = estate;
    G.discard[thisPlayer][1] = estate;
    if(scoreFor(thisPlayer, &G) == 1){
        printf("PASSED!\n");
    }
    else{
        printf("FAILED!\n");
    }

    printf("Second test completed!")
}
int main(){
    int numPlayers = 2, seed = 100;
    struct gameState G;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, seed, &G);

    testScoreFor1(G);
    testScoreFor2(G);

    return 0;
}
