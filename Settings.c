#include "Settings.h"
#include <stdio.h>

SETTINGS NewSettings(int maxQueueLength, int numServicePoints, int closingTime, int averageNewCustomersPerInterval){
    SETTINGS newSettings = {maxQueueLength, numServicePoints, closingTime, averageNewCustomersPerInterval};

    return newSettings;
}

void PrintSettings(SETTINGS *settings){
    printf("\nSETTINGS:\n");
    printf("============================\n");
    printf("%s = %i\n", "Max Queue Length", settings->maxQueueLength);
    printf("%s = %i\n", "Number of Service Points", settings->numServicePoints);
    printf("%s = %i\n", "Closing Time", settings->closingTime);
    printf("%s = %i\n", "Average New Customers per Interval", settings->averageNewCustomersPerInterval);
    printf("\n");
}