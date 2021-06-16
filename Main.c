#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "helperfuncs.h"
#include "Customer.h"
#include "LinkedList.h"

#define SIZE 1000

int main(char fileIn[], int numSims, char fileOut[]) {
	/*CUSTOMER customers[SIZE];

	for (int i = 0; i < SIZE; i++) {
		customers[i] = NewCustomer(RandomNumber(1, 100), RandomNumber(1, 100));
	}

	for (int i = 0; i < SIZE; i++) {
		printf("Waiting time: %i / %i \n", customers[i].waitingTime, customers[i].maxWaitingTime);
	}*/

	for (int i = 0; i < 10; i++) {
		InsertFirst(NewCustomer(RandomNumber(1, 100), RandomNumber(1, 100)));
	}

	PrintList();

	return 0;
}