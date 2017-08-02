/* -----------------------------------------------------------------------
 * Unit Test of kingdomCards()
 * 
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

int assertEq();

int main () {
	printf("\nUnit Test 1\n");
	
	struct gameState* G;

	// Init data
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

	G = newGame();
	//initializeGame(2, k, 1234, G);

	// Insert test data
	G->deck[0][0] = copper; //4
	G->deck[0][1] = outpost; //23
	G->deck[0][2] = outpost; //23
	G->deckCount[0] = 3;

	G->hand[0][0] = sea_hag; //25
	G->hand[0][1] = copper; //4
	G->handCount[0] = 2;

	G->discardCount[0] = 0;

	// Test array item values
	drawCard(0, G);
	

	printf("ALL TESTS FINISHED\n");
	exit(0);
}



int assertEq(int term1, int term2){
	if (term1 != term2){
		printf("Assert failed! %d and %d not equal!\n", term1, term2);
		return 0;
	}
	else {
		return 1;
	}
}