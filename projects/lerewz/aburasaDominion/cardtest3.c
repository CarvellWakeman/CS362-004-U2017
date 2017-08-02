/* -----------------------------------------------------------------------
 * Unit Test of cardGarden()
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
	printf("\nCard Garden Test\n");
	
	struct gameState* G;
	int bonus = 0;

	// Init data
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

	G = newGame();
	initializeGame(2, k, 1234, G);

	// Test cardGarden
	int result = cardEffect(gardens, 0,0,0, G, 0, &bonus);
	test("Garden card should return -1", assertEq(result, -1));


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