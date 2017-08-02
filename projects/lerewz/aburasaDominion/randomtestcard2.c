/* -----------------------------------------------------------------------
 * Random Test of cardCouncilRoom()
 * 
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#define CARDS_MAX 200

char* testEquality(struct gameState*, struct gameState*);
int randVal(int, int);

int main () {
	printf("\nCard Council Room Random Test BEGIN\n\n");
	
	int i;
	int j;
	int currentPlayer;
	int handPos;
	struct gameState* actual;
	struct gameState* expected;	// Build expected game state by hand
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	int bonus = 0;

	// Seed random
	srand(time(NULL));

	// Loop through number of tests
	for (i = 0; i < 100; i++){
		// Set up gamestates
		actual = newGame();
		expected = newGame();

		// Randomize contents of gamestate
		for (j = 0; j < sizeof(struct gameState); j++){
			((char*)actual)[j] = randVal(1,256);
		}

		// Initialize game
		initializeGame(2, k, 1234, actual);

		// Set some values
		for (j = 0; j < 2; j++){
			actual->deckCount[j] = randVal(0,CARDS_MAX);
			actual->discardCount[j] = randVal(0,CARDS_MAX);
			actual->playedCards[j] = randVal(0,CARDS_MAX);
			actual->handCount[j] = randVal(0,CARDS_MAX);

			if (actual->deckCount[j] == 0) actual->deckCount[j] = randVal(0,CARDS_MAX) + 1;
			if (actual->discardCount[j] == 0) actual->discardCount[j] = randVal(0,CARDS_MAX) + 1;

			// Build expected state
			expected->deckCount[j] = (actual->deckCount[j])-4;
			expected->handCount[j] = (actual->handCount[j])+4;
			expected->numBuys = (actual->numBuys)+1;
		}
		actual->playedCardCount = randVal(0,CARDS_MAX);


		// Other random values		
		currentPlayer = randVal(0,1);
		handPos = randVal(0,actual->handCount[currentPlayer]);

		// Call Council Room card
		int result = cardEffect(council_room, 0,0,0, actual, 0, &bonus);

		// Test results against expectations
		char* reason = testEquality(expected, actual);

		if (strcmp(reason, "") != 0){
			printf("Fail test%d: %s\n", i, reason);
		}
		free(reason);
	}

	printf("\nRandom Test END\n");
	exit(0);
}

int randVal(int min, int max){
	return (rand()%(max-min))+min;
}

// Zero equal, one not equal
char* testEquality(struct gameState* expected, struct gameState* actual){

	// Locals
	int i = 0;
	int player;
	char* ret = (char*)malloc(512);

	for (player = 0; player < 2; player++){
		// Check deck count
		if (actual->deckCount[player] != expected->deckCount[player]) {
			sprintf(ret, "3 cards should be removed from player %d's deckCount. Expected:%d, Actual:%d", player, expected->deckCount[player], actual->deckCount[player]);
			return ret;
		}
		// Check hand count
		if (actual->handCount[player] != expected->handCount[player]) {
			sprintf(ret, "3 cards should be added to player %d's hand. Expected:%d, Actual:%d", player, expected->handCount[player], actual->handCount[player]);
			return ret;
		}
		// Check num buys
		if (actual->numBuys != expected->numBuys) {
			sprintf(ret, "Buys should have increased by 1. Expected:%d, Actual:%d", 1, actual->numBuys);
			return ret;
		}
	}

	return ret;
}
