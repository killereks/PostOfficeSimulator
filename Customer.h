#pragma once

#include <stdbool.h>

typedef struct Customer CUSTOMER;

struct Customer NewCustomer(int waitingTime, int taskTime);

struct Customer {
	int waitingTime;
	int taskTime;
	bool beingServed;
};