#include <stdlib.h>

int RandomNumber(int min, int max) {
	return rand() % (max - min + 1) + min;
}