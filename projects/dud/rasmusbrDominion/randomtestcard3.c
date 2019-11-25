//random test tribute

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
int failedEffects = 0, failedDiscards = 0, failedDraws = 0, failedHands = 0, failedActions, failedCoins;

//function to check the smithyCard
void checkTributeCard(int players, struct gameState *endState){
        int r, a, b, c, d, v, bonus = 0, preHandCount, postHandCount, preDecCount, postDecCount;
        //randGameame state variable to manually act on the functions actions
        struct gameState initialState;
        //copy the passed in randGameame state to initialState
        memcpy(&initialState, endState, sizeof(struct gameState));
        //call the card effect function with the tribute card
        r = cardEffect(tribute, 0, 0, 0, endState, 0, &bonus);
        //check if tribute card failed
        if(r)
                failedEffects++;
        //have the player discard 3 cards
        a = discardCard(0, players, &initialState, 0);
        b = discardCard(0, players, &initialState, 0);
        // if the player reveal victory card, draw 2 cards
        c = drawCard(players, &initialState);
        d = drawCard(players, &initialState);
        // set the initial actions
        initialState.numActions = endState->numActions + 2;
        initialState.coins = endState->coins + 2;

        //call discardCard
        v = discardCard(0, players, &initialState, 0);
        //check if discard card failed
        if(v)
                failedDiscards++;
        //get the hand and deck to compare
        preHandCount = initialState.handCount[players];
        postHandCount = endState->handCount[players];
        preDecCount = initialState.deckCount[players];
        postDecCount = endState->deckCount[players];
        //check the numActions
        if(initialState.numActions != endState->numActions){
            failedActions++;
        }
        //check the num
        if(initialState.coins != endState->coins){
            failedCoins++;
        }
        //check if any of the draws failed
        if (a == -1 && initialState.deckCount[players] != 0)
                failedDiscards++;
        if (b == -1 && initialState.deckCount[players] != 0)
                failedDiscards++;
        if (c == -1 && initialState.deckCount[players] != 0)
                failedDraws++;
        if (d == -1 && initialState.deckCount[players] != 0)
                failedDraws++;
        //if the hand counts don't match up increase the faiilure variable
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
                // player = floor(Random() * MAX_PLAYERS);
                //initialize the variables for the game
                // randGame.deckCount[player] = floor(Random() * MAX_DECK);
                // randGame.discardCount[player] = floor(Random() * MAX_DECK);
                // randGame.handCount[player] = floor(Random() * MAX_HAND);
                // randGame.playedCardCount = floor(Random() * (MAX_DECK-1));
                randGame.whoseTurn = player;
                //after running the interation, check the card
                checkTributeCard(player,&randGame);
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
                //printf("shuffle() failed: %i\n", failedShuffles);
                printf("drawCard() failed: %i\n", failedDraws);
                printf("cardEffect() failed: %i\n", failedEffects);
                //printf("Treasure Count mismatch: %i\n", failedTreasures);
                printf("Hand/Deck Count mismatch: %i\n", failedHands);
        }
        return 0;
}
