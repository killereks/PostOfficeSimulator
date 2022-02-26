#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <limits.h>

#include "helperfuncs.h"
#include "LinkedList.h"
#include "Settings.h"

#define SIZE 100

void FileReadSettings(char inputFile[], SETTINGS* target);
void WriteToFile(char fileName[], char line[]);
CUSTOMER* GetCustomerAtIndex(int index);

// argc - how many arguments
// argv - values starting at index 1 (0 = path)
int main(int argc, char *argv[]) {
	srand(time(NULL));
	if (argc != 4){
		printf("Invalid number of arguments. [input file] [amount of simulations] [output file]");
		return 0;
	}

	char fileInput[50];
	char fileOutput[50] = "";
	int numOfSims = 5;

	strcpy(fileInput, argv[1]);
	sscanf(argv[2], "%i", &numOfSims);
	strcpy(fileOutput, argv[3]);

	SETTINGS settings;
	FileReadSettings(fileInput, &settings);
	
	PrintSettings(&settings);

	printf("Starting simulation\n\n");

	if (numOfSims == 1){
		printf("\nMEANINGS: \n");
		printf("F - Finished serving the customer\n");
		printf("L - Left due to impatience.\n\n");

		printf("%15s", "SERVICE POINTS");
		printf("%40s", "CUSTOMERS QUEUE\n");
	}

	int ticks = 0;
	int served = 0; // successfully served a customer
	int annoyed = 0; // impatient customers
	int didntfit = 0; // queue was full

	// for multiple simulations
	int servedTotal = 0;
	int annoyedTotal = 0;
	int didntfitTotal = 0;
	int ticksTotal = 0;

	int totalWaitTime = 0;
	int totalCustomers = 0;

	printf("Num of sims %i\n\n", numOfSims);
	
	char line[150];
	/*
	int maxQueueLength;
	int numServicePoints;
	int closingTime;
	int averageNewCustomersPerInterval;
	*/

	sprintf(line, "Max queue length - %i", settings.maxQueueLength);
	WriteToFile(fileOutput, line);
	sprintf(line, "Number of service points - %i", settings.numServicePoints);
	WriteToFile(fileOutput, line);
	sprintf(line, "Closing Time - %i", settings.closingTime);
	WriteToFile(fileOutput, line);
	sprintf(line, "Average New Customers Per Interval - %i\n\n", settings.averageNewCustomersPerInterval);
	WriteToFile(fileOutput, line);

	for (int sim = 0; sim < numOfSims; sim++){
		ticks = 0;
		served = 0;
		annoyed = 0;
		didntfit = 0;
		printf("Starting simulation %i\n", sim);
		while (GetLength() > 0 || ticks < settings.closingTime){
			int currentlyServedNO = 0;
			int currentlyInQueueNO = 0;

			//printf("[%03i@%03i] ", GetLength(), ticks);
			for (int j = 0; j < settings.numServicePoints; j++){
				if (j >= GetLength()) break;
				CUSTOMER* customer = GetCustomerAtIndex(j);

				currentlyServedNO++;
				customer->beingServed = true;
				customer->taskTime--;

				if (customer->taskTime <= 0){
					//printf("F ");
					Delete(j);
					served++;
				} else {
					//printf("%02i ", customer->taskTime);
				}
			}
			//printf("%20s ","#");
			for (int i = 0; i < GetLength(); i++){
				CUSTOMER* customer = GetCustomerAtIndex(i);
				if (customer->beingServed){
					continue;
				}

				currentlyInQueueNO++;
				customer->waitingTime--;
				totalWaitTime++;
				if (customer->waitingTime <= 0){
					Delete(i);
					annoyed++;
					//printf("L ");
				} else {
					//printf("%02i ", customer->waitingTime);
				}
			}

			ticks++;
			ticksTotal++;

			if (ticks < settings.closingTime){
				for (int k = 0; k < settings.averageNewCustomersPerInterval; k++){
					if (GetLength() >= settings.maxQueueLength){
						didntfit++;
					} else {
						InsertFirst(NewCustomer(RandomNumber(1, 100), RandomNumber(1, 10)));
					}
					totalCustomers++;
				}
			}

			if (numOfSims == 1){
				char line[200];
				sprintf(line, "[%03i] Serving %i / In Queue %i / Fulfilled %i / Unfilfilled %i / Timed out %i", 
							ticks, currentlyServedNO, currentlyInQueueNO, served, annoyed, didntfit);

				WriteToFile(fileOutput, line);

				if (ticks == settings.closingTime){
					WriteToFile(fileOutput, "==================== CLOSED ====================");
				}

				//printf("\n");
			}
		}

		servedTotal += served;
		annoyedTotal += annoyed;
		didntfitTotal += didntfit;
	}

	char line2[200];

	float averageTicksOver = (float) (ticksTotal - settings.closingTime * numOfSims) / (float) numOfSims;
	float averageServed = (float) servedTotal / (float) numOfSims;
	float averageAnnoyed = (float) annoyedTotal / (float) numOfSims;
	float averageDidntfit = (float) didntfitTotal / (float) numOfSims;
	float averageWaitTime = (float) totalWaitTime / (float) totalCustomers;

	sprintf(line2, "It took extra %.2f ticks to serve all customers\nFulfilled - %.2f\nUnfulfilled - %.2f\nTimed-out - %.2f\nAverage waiting time - %.2f",
				averageTicksOver, averageServed, averageAnnoyed, averageDidntfit, averageWaitTime);
	WriteToFile(fileOutput, line2);

	if (numOfSims == 1){
		printf("\nSIMULATION ENDED\n");
		printf("Customers served - %i\nCustomers left due to impatience - %i\nCustomers that left due to a full queue - %i", served, annoyed, didntfit);
	}
	//PrintList();

	return 0;
}

CUSTOMER* GetCustomerAtIndex(int index){
	NODE* node = GetAtIndex(index);
	return &(node->customer);
}

void FileReadSettings(char fileName[], SETTINGS* targetSettings){
	FILE *fp;
	char* line = NULL;
	size_t len = 0;
	size_t read;

	char delim[] = "=";

	fp = fopen(fileName, "r");

	if (fp == NULL){
		printf("ERROR: File does not exist.");
		exit(EXIT_FAILURE);
	}

	char settingName[200] = "";
	int settingValue;

	int maxQueueLength = 5;
    int numServicePoints = 2;
    int closingTime = 10;
    int averageNewCustomersPerInterval = 2;

	while ((read = getline(&line, &len, fp)) != -1){
		if (line[0] == '#' || line[0] == '\0') continue;

		sscanf(line, "%s %i", &settingName, &settingValue);

		if (strcmp(settingName, "maxQueueLength") == 0) maxQueueLength = settingValue;
		else if (strcmp(settingName, "numServicePoints") == 0) numServicePoints = settingValue;
		else if (strcmp(settingName, "closingTime") == 0) closingTime = settingValue;
		else if (strcmp(settingName, "averageNewCustomersPerInterval") == 0) averageNewCustomersPerInterval = settingValue;
	}

	targetSettings->maxQueueLength = maxQueueLength;
	targetSettings->numServicePoints = numServicePoints;
	targetSettings->closingTime = closingTime;
	targetSettings->averageNewCustomersPerInterval = averageNewCustomersPerInterval;

	if (targetSettings->maxQueueLength == -1){
		targetSettings->maxQueueLength = INT_MAX;
	}

	fclose(fp);
	if (line){
		free(line);
	}
	//exit(EXIT_SUCCESS);
}

void WriteToFile(char fileName[], char line[]){
	FILE *fp;

	fp = fopen(fileName, "a+");
	fprintf(fp, "%s\n", line);

	fclose(fp);
}