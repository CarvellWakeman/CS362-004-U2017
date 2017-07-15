/* -----------------------------------------------------------------------
 * Unit Test of shuffle()
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
void printDeck(int deck[MAX_DECK], int);
void printDecks(struct gameState*);

int main () {
	printf("\nUnit Test 2\n");

	int i;
	int j;

	// Init data
	struct gameState G;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

	initializeGame(2, k, 1234, &G);
	printf ("Initialized game state.\n");


	// Copy data before shuffle
	int preDeck[MAX_PLAYERS][MAX_DECK];
	int preDeckCount[MAX_PLAYERS];

	for (i = 0; i < G.numPlayers; i++){
		for (j = 0; j < G.deckCount[i]; j++){
			preDeck[i][j] = G.deck[i][j];
		}
		preDeckCount[i] = G.deckCount[i];
	}


	// Run Shuffle for player 0
	printf("Shuffling player 0 deck\n");
	int P0Shuffle = shuffle(0, &G);

	// Test equality of deck sizes
	test("Player 0 deck size not affected by shuffle", assertEq(preDeckCount[0], G.deckCount[0]));
	test("Player 1 deck size not affected by shuffle", assertEq(preDeckCount[1], G.deckCount[1]));

	// Test non equality of preDeck to shuffled deck for player 0
	int numDiff = 0;
	for (i = 0; i < G.deckCount[0]; i++){
		if (preDeck[0][i] != G.deck[0][i]){ numDiff++; }
	}
	test("Player 0 deck has changed after shuffle", assertNotEq(numDiff, 0));
	numDiff = 0;
	for (i = 0; i < G.deckCount[1]; i++){
		if (preDeck[1][i] != G.deck[1][i]){ numDiff++; }
	}
	test("Player 1 deck has not changed after shuffle", assertEq(numDiff, 0));


	// Run Shuffle for player 1
	printf("Shuffling player 1 deck\n");
	int P1Shuffle = shuffle(1, &G);

	// Test equality of deck sizes
	test("Player 0 deck size not affected by shuffle", assertEq(preDeckCount[0], G.deckCount[0]));
	test("Player 1 deck size not affected by shuffle", assertEq(preDeckCount[1], G.deckCount[1]));

	// Test non equality of preDeck to shuffled deck for player 1
	numDiff = 0;
	for (i = 0; i < G.deckCount[1]; i++){
		if (preDeck[1][i] != G.deck[1][i]){ numDiff++; }
	}
	test("Player 1 deck has changed after shuffle", assertNotEq(numDiff, 0));

	test("Player 0 deck not empty", assertNotEq(P0Shuffle, -1));
	test("Player 1 deck not empty", assertNotEq(P1Shuffle, -1));

	printf("ALL TESTS FINISHED\n");
	exit(0);
}

void printDeck(int deck[MAX_DECK], int deckCount){
	int j;

	for (j = 0; j < deckCount; j++){
		printf("      Card %d: %d\n", j, deck[j]);
	}
}

void printDecks(struct gameState* G){
	int i;

	for (i = 0; i < G->numPlayers; i++){
		printf("   Player %d\n", i);
		printDeck(G->deck[i], G->deckCount[i]);
	}
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