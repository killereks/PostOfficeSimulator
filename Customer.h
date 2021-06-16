#pragma once

typedef struct Customer CUSTOMER;

struct Customer NewCustomer(int waitingTime, int maxWaitingTime);

struct Customer {
	int waitingTime;
	int maxWaitingTime;
};