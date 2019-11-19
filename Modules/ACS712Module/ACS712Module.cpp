#include "ACS712Module.h"


int sensitivity = 100; // độ nhạy là 100 với 20A và 66 cho 30A
int offsetvoltage = 2500;

double getCurrent(int adcvalue)
{
    double voltage = (adcvalue / 4096.0) * 5000; // mV
    double current = ((voltage - offsetvoltage) / sensitivity); // CT tính dòng điện
    return current;
}

double getVoltage(int adcvalue)
{
    double voltage = (adcvalue / 4096.0) * 5000; // mV
    return voltage;
}