//random test baron

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

//Failure global variable counts
int failedEffects = 0, failedDiscards = 0, failedDraws = 0, failedHands = 0, failedBuys = 0, failedCoins;

//function to check the smithyCard
void checkBaronCard(int players, struct gameState *endState){
        int r, a, v, currentPlayer,bonus = 0, preHandCount, postHandCount, preDecCount, postDecCount;
        //randGameame state variable to manually act on the functions actions
        struct gameState initialState;
        //copy the passed in randGameame state to initialState
        memcpy(&initialState, endState, sizeof(struct gameState));
        //call the card effect function with the baron card
        r = baronCard(currentPlayer, endState, 0, 0);
        //check if baron card failed
        if(r)
                failedEffects++;
        // draw 1 card
        a = drawCard(currentPlayer, &initialState);
        //+1 buy
        initialState.numBuys ++;
        // +4 coins
        initialState.coins = endState->coins + 4;

        v = discardCard(0, players, &initialState, 0);
        if(v){
            failedDiscards++;
        }

        //get the hand and deck to compare
        preHandCount = initialState.handCount[players];
        postHandCount = endState->handCount[players];
        preDecCount = initialState.deckCount[players];
        postDecCount = endState->deckCount[players];
        //check the numBuys
        if(initialState.numBuys != endState->numBuys){
            failedBuys++;
        }
        if(initialState.coins != endState->coins){
            failedCoins++;
        }
        //check if the draw failed
        if (a == -1 && initialState.deckCount[players] != 0)
                failedDraws++;

        //if the hand counts don't match up increase the failure variable
        if (!(postHandCount == preHandCount && postDecCount == preDecCount))
                failedHands++;
}

//main function that posts the tests
int main (){
        int iterations = 10000, i, n, player, totalFails;
        struct gameState randGame;
        //get the time for the seed
        srand(time(NULL));
        //initialize the randGame state and randomize the inputs
        for (n = 0; n < iterations; n++) {
                for (i = 0; i < sizeof(struct gameState); i++)
                        ((char*)&randGame)[i] = floor(Random() * 256);
                //set the random number of players
                player = floor(Random() * MAX_PLAYERS);
                //initialize the variables for the game
                randGame.deckCount[player] = floor(Random() * MAX_DECK);
                randGame.discardCount[player] = floor(Random() * MAX_DECK);
                randGame.handCount[player] = floor(Random() * MAX_HAND);
                randGame.playedCardCount = floor(Random() * (MAX_DECK-1));
                randGame.whoseTurn = player;
                //after running the interation, check the card
                checkBaronCard(player,&randGame);
        }
        //sum up all the failed results after the iterations
        totalFails = failedEffects + failedDiscards + failedDraws + failedHands;
        //edge case if all the iterations failed
        if (iterations - totalFails <= 0) {
                printf("All tests failed:\n\n");
                printf("# Passed Tests: %i\n",0);
                printf("# Failed Tests: %i\n",iterations);
        }
        //else print out how many passed and failed tests
        else{
                printf("Some tests failed:\n\n");
                printf("# Passed Tests: %i\n",iterations - totalFails);
                printf("# Failed Tests: %i\n",totalFails);
        }
        //if there are no fails in the random test
        if (totalFails == 0)
                printf ("All Tests Passed\n\n");
        //else print out what had failed
        else{
                printf("Test Failure Results:\n\n");
                printf("drawCard() failed: %i\n", failedDraws);
                printf("Hand/Deck Count mismatch: %i\n", failedHands);
        }
        return 0;
}
