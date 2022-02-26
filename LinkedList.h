#pragma once

#include "Customer.h"

typedef struct Node NODE;

struct Node {
	CUSTOMER customer;
	NODE* next;
};

void PrintList();
void InsertFirst(CUSTOMER customer);
NODE* DeleteFirst();
bool IsEmpty();
int GetLength();
NODE* Delete(int index);
NODE* GetAtIndex(int index);