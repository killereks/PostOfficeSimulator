#include <stdlib.h>

int RandomNumber(int min, int max) {
	return rand() % (max - min + 1) + min;
}

/*double RandomGauss(double mean, double sigma){
	return gsl_ran_gaussian_pdf(mean, sigma);
}*/