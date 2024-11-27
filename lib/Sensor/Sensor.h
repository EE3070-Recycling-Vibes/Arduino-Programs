#ifndef SENSOR_H
#define SENSOR_H

#include "Config.h"

// Function Declarations
void initializeSensors();
float readWeight();
float measureHeight();
bool isObjectDetected(); // Added function declaration

#endif // SENSOR_H
