#include "Customer.h"

CUSTOMER NewCustomer(int waitingTime, int maxWaitingTime) {
	CUSTOMER newCustomer;

	newCustomer.waitingTime = waitingTime;
	newCustomer.maxWaitingTime = maxWaitingTime;

	return newCustomer;
}