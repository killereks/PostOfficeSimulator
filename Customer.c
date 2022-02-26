#include "Customer.h"
#include <stdbool.h>

CUSTOMER NewCustomer(int waitingTime, int taskTime) {
	CUSTOMER newCustomer;

	newCustomer.waitingTime = waitingTime;
	newCustomer.taskTime = taskTime;
	newCustomer.beingServed = false;

	return newCustomer;
}