#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "tribute"


int myAssert(int expected, int actual){
	return expected == actual;
}

int main() {

    int seed = 1000;
    int numPlayers = 2;
	int handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int currentPlayer = 0, nextPlayer = 1;
    int numActionsOld = 0, numActionsNew = 0;
	struct gameState G;
	
	int k[10] = { adventurer, embargo, village, minion, mine, 
				baron, cutpurse, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 9: Tribute card correctly adds two numActions in case of duplicate revealed cards. --------------
	printf("TEST 9: Tribute card incorrectly adds numActions in case of duplicate revealed treasures.\n");

	

	// Make next player have no cards in deck and two cards in discard
	G.hand[currentPlayer][handPos] = tribute;	// Set card at handPos as tribute
	G.deckCount[nextPlayer] = 2;
	G.discardCount[nextPlayer] = 2;
	G.deck[nextPlayer][0] = copper;	// Deck has two copper cards only
	G.deck[nextPlayer][1] = copper;	

	numActionsOld = G.numActions;

	cardEffect(tribute, choice1, choice2, choice3, &G, handPos, &bonus);

	numActionsNew = G.numActions;

	printf("num actions before function call = %d\n", numActionsOld);
	printf("expected num actions after function call = %d\n", numActionsOld);
	printf("actual num actions = %d\n", numActionsNew);
	printf("assert = %d\n\n", myAssert(numActionsOld, numActionsNew));		

	// ----------- TESTS FINISHED. --------------
	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

	return 0;
}
