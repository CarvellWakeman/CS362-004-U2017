/* -----------------------------------------------------------------------
 * Unit Test of initializeGame()
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
	printf("\nUnit Test 3\n");

	int i;
	int j;
	struct gameState* G;

	// Init data
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	int victoryK[10] = {adventurer, gardens, embargo, village, great_hall, mine, cutpurse, sea_hag, tribute, smithy};
	int badK[10] = {adventurer, gardens, embargo, village, minion, mine, sea_hag, sea_hag, tribute, smithy}; // Has two sea_hag

	G = newGame();
	test("Return -1 on too many players", assertEq(initializeGame(MAX_PLAYERS+1, k, 1234, G), -1));
	test("Return -1 on too few players", assertEq(initializeGame(1, k, 1234, G), -1));

	// Initialize Players
	free(G); G = newGame();
	int result = initializeGame(2, k, 1234, G);

	// Test player count
	test("Player Count = 2", assertEq(G->numPlayers, 2));

	// Test repeat kingdom cards
	free(G); G = newGame();
	test("Return -1 on repeated kingdom cards", assertEq(initializeGame(2, badK, 1234, G), -1));

	// Test supply Count for curse
	free(G); G = newGame();
	initializeGame(2, k, 1234, G);
	test("SupplyCount[curse] should be 10 for 2 players", assertEq(G->supplyCount[curse], 10));
	free(G); G = newGame();
	initializeGame(3, k, 1234, G);
	test("SupplyCount[curse] should be 20 for 3 players", assertEq(G->supplyCount[curse], 20));
	free(G); G = newGame();
	initializeGame(4, k, 1234, G);
	test("SupplyCount[curse] should be 30 for >2 players", assertEq(G->supplyCount[curse], 30));
	
	// Test supply count for estate, duchy, province
	free(G); G = newGame();
	initializeGame(2, k, 1234, G);
	test("SupplyCount[estate] should be 8 for 2 players", assertEq(G->supplyCount[estate], 8));
	test("SupplyCount[duchy] should be 8 for 2 players", assertEq(G->supplyCount[duchy], 8));
	test("SupplyCount[province] should be 8 for 2 players", assertEq(G->supplyCount[province], 8));
	free(G); G = newGame();
	initializeGame(3, k, 1234, G);
	test("SupplyCount[estate] should be 12 for >2 players", assertEq(G->supplyCount[estate], 12));
	test("SupplyCount[duchy] should be 12 for >2 players", assertEq(G->supplyCount[duchy], 12));
	test("SupplyCount[province] should be 12 for >2 players", assertEq(G->supplyCount[province], 12));

	// Test supply count for copper, silver, and gold
	free(G); G = newGame();
	initializeGame(2, k, 1234, G);
	test("SupplyCount[copper] should be 46 for 2 players", assertEq(G->supplyCount[copper], 46));
	test("SupplyCount[silver] should be 40", assertEq(G->supplyCount[silver], 40));
	test("SupplyCount[gold] should be 30", assertEq(G->supplyCount[gold], 30));
	free(G); G = newGame();
	initializeGame(4, k, 1234, G);
	test("SupplyCount[copper] should be 32 for 4 players", assertEq(G->supplyCount[copper], 32));

	// Test supply count for victory cards
	free(G); G = newGame();
	initializeGame(2, victoryK, 1234, G);
	test("SupplyCount[gardens] should be 8 for 2 players", assertEq(G->supplyCount[gardens], 8));
	test("SupplyCount[great_hall] should be 8 for 2 players", assertEq(G->supplyCount[great_hall], 8));
	free(G); G = newGame();
	initializeGame(3, victoryK, 1234, G);
	test("SupplyCount[gardens] should be 12 for >2 players", assertEq(G->supplyCount[gardens], 12));
	test("SupplyCount[great_hall] should be 12 for >2 players", assertEq(G->supplyCount[great_hall], 12));
	test("SupplyCount[minion] should be -1 because it is not in the kingdom cards list", assertEq(G->supplyCount[minion], -1));
	test("SupplyCount[embargo] should be 10 because it is not great_hall or gardens", assertEq(G->supplyCount[embargo], 10));


	// DrawCard and updateCoins should be tested separately


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