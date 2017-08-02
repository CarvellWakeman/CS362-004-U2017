/* -----------------------------------------------------------------------
 * Random Test of cardAdventurer()
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

char* testEquality(struct gameState*, struct gameState*, struct gameState*);
int randVal(int, int);

int main () {
	printf("\nCard Adventurer Random Test BEGIN\n\n");
	
	int i;
	int j;
	int drawnTreasure;
	int currentPlayer;
	int cardDrawn;
	struct gameState* pre;
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
		pre = newGame();

		// Randomize contents of gamestate
		for (j = 0; j < sizeof(struct gameState); j++){
			((char*)actual)[j] = randVal(1,256);
		}

		// Initialize game
		initializeGame(2, k, 1234, actual);

		// Set some values that are out of the scope of cardAdventurer
		for (j = 0; j < 2; j++){
			actual->deckCount[j] = randVal(0,CARDS_MAX);
			actual->discardCount[j] = randVal(0,CARDS_MAX);
			actual->playedCards[j] = randVal(0,CARDS_MAX);
			actual->handCount[j] = randVal(0,CARDS_MAX);

			if (actual->deckCount[j] == 0) actual->deckCount[j] = randVal(0,CARDS_MAX) + 1;
			if (actual->discardCount[j] == 0) actual->discardCount[j] = randVal(0,CARDS_MAX) + 1;

			// Build expected state
			expected->deckCount[j] = (actual->deckCount[j])-2;
			expected->handCount[j] = (actual->handCount[j])+2;
			expected->discardCount[j] = (actual->discardCount[j]);

		}
		actual->playedCardCount = randVal(0,CARDS_MAX);


		// Other random values		
		drawnTreasure = randVal(0,10);
		currentPlayer = randVal(0,1);
		cardDrawn = randVal(0,actual->deckCount[currentPlayer]);

		// Copy pre-call gamestate
		memcpy(pre, actual, sizeof(struct gameState));

		// Call adventurer card
		//int result = cardAdventurer(drawnTreasure, actual, currentPlayer, cardDrawn);
		int result = cardEffect(adventurer, 0,0,0, actual, 0, &bonus);

		// Test results against expectations
		char* reason = testEquality(expected, actual, pre);

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
char* testEquality(struct gameState* expected, struct gameState* actual, struct gameState* pre){

	// Locals
	int i = 0;
	int before;
	int after;
	int player;
	char* ret = (char*)malloc(512);

	for (player = 0; player < 2; player++){
		// Check cards
		if (actual->deckCount[player] <= expected->deckCount[player]) {
			sprintf(ret, "At least 2 cards should be removed from player %d's deckCount. Expected:%d, Actual:%d", player, expected->deckCount[player], actual->deckCount[player]);
			return ret;
		}

		if (actual->handCount[player] == expected->handCount[player]) {
			sprintf(ret, "2 cards should be added to player %d's hand. Expected:%d, Actual:%d", player, expected->handCount[player], actual->handCount[player]);
			return ret;
		}

		int incBy = (pre->deckCount[player] - actual->deckCount[player]);
		if (incBy < 2) {
			sprintf(ret, "Player %d's discard pile should have increased by at least 2. Expected:%d, Actual:%d", player, 2, incBy);
			return ret;
		}

		// Check treasures
		int treasure_pre = 0;
		for(i = 0; i < pre->handCount[player]; i++) {
			if(pre->hand[player][i] == copper || pre->hand[player][i] == silver || pre->hand[player][i] == gold) { treasure_pre ++; }
		}
		int treasure_act = 0;
		for(i = 0; i < actual->handCount[player]; i++) {
			if(actual->hand[player][i] == copper || actual->hand[player][i] == silver || actual->hand[player][i] == gold) { treasure_act ++; }
		}
		if (treasure_act == treasure_pre+2) {
			sprintf(ret, "Player %d should have 2 additional treasures. Expected:%d, Actual:%d", player, 2, treasure_act);
			return ret;
		}

	}

	return ret;
}
