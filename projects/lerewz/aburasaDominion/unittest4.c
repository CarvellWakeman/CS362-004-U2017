/* -----------------------------------------------------------------------
 * Unit Test of updateCoins()
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
	printf("\nUnit Test 4\n");

	int i;
	int j;
	struct gameState* G;

	// Init data
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	G = newGame();
	int result = initializeGame(2, k, 1234, G);
	
	// Test initial coins
	test("Initial Coins should be 4", assertEq(G->coins, 4));

	// Test update coins
	updateCoins(0, G, 0);
	test("Coins should be 4", assertEq(G->coins, 4));
	updateCoins(0, G, 1);
	test("Coins should be 5", assertEq(G->coins, 5));
	G->hand[0][0] = gold;
	updateCoins(0, G, 0);
	test("Coins should be 6", assertEq(G->coins, 6));


	printf("ALL TESTS FINISHED\n");
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