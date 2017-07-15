/* -----------------------------------------------------------------------
 * Unit Test of cardCouncilRoom()
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


void test(char*, int);
int assertEq(int, int);
int assertNotEq(int, int);


int main () {
	printf("\nCard CouncilRoom Test\n");
	
	struct gameState* G;

	// Init data
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

	G = newGame();
	initializeGame(2, k, 1234, G);

	// Test cardCouncilRoom
	int prevDeckCount = G->deckCount[0];
	int prevHandCount = G->handCount[0];
	int prevNumBuys = G->numBuys;
	cardCouncilRoom(G, 0, 0);
	test("Player 0 deck has four less cards", assertEq(prevDeckCount - G->deckCount[0], 4));
	test("Player 0 hand has three more cards", assertEq(G->handCount[0] - prevHandCount, 3));
	test("Number of Buys increased by 1", assertEq( prevNumBuys+1, G->numBuys));




	printf("ALL TESTS FINISHED\n\n");
	exit(0);
}




void test(char* testString, int result){
	printf(testString);
	if (result==1){ printf(":Pass!\n"); }
	else { printf(":Fail!\n"); }
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

int assertNotEq(int term1, int term2){
	if (term1 == term2){
		printf("Assert failed! %d and %d are equal!\n", term1, term2);
		return 0;
	}
	else {
		return 1;
	}
}