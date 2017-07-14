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
	// Gather function results
	int* k = kingdomCards(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);

	// Test array item values
	int i;
	for (i = 0; i < 10; i++){
		assertEq((i+1), k[i]);
	}

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