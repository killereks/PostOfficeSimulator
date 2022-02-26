#pragma once

typedef struct Settings SETTINGS;

SETTINGS NewSettings(int maxQueueLength, int numServicePoints, int closingTime, int averageNewCustomersPerInterval);
void PrintSettings(SETTINGS* settings);

struct Settings {
    int maxQueueLength;
    int numServicePoints;
    int closingTime;
    int averageNewCustomersPerInterval;
};