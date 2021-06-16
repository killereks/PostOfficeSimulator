#include "Customer.h"
#include "LinkedList.h"

NODE* head = NULL;
NODE* current = NULL;

void PrintList() {
	NODE* pointer = head;
	printf("\n[ ");

	while (pointer != NULL) {
		printf("%i / %i", pointer->customer.waitingTime, pointer->customer.maxWaitingTime);
		pointer = pointer->next;
	}

	printf(" ]");
}

void InsertFirst(CUSTOMER customer) {
	NODE* link = malloc(sizeof(NODE));

	link->customer = customer;

	link->next = head;
	head = link;
}

NODE* DeleteFirst() {
	NODE* temp = head;

	head = head->next;

	return temp;
}

bool IsEmpty() {
	return head == NULL;
}

int GetLength() {
	int length = 0;
	NODE* current;

	current = head;
	while (current != NULL) {
		length++;
		current = current->next;
	}

	return length;
}

NODE* Delete(int index) {
	NODE* current = head;
	NODE* previous = NULL;

	if (head == NULL) {
		return NULL;
	}

	for (int i = 0; i < index; i++) {
		if (current->next == NULL) {
			return NULL;
		}
		else {
			previous = current;
			current = current->next;
		}
	}

	if (current == head) {
		head = head->next;
	}
	else {
		previous->next = current->next;
	}

	return current;
}