#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>
#include "Config.h"

/**
 * @brief Initializes the load cell and ultrasonic sensor.
 */
void initializeSensors();

/**
 * @brief Reads the weight from the load cell.
 * 
 * @return float The weight in appropriate units.
 */
float readWeight();

/**
 * @brief Measures the distance using the ultrasonic sensor.
 * 
 * @return float The distance in centimeters.
 */
float measureHeight();

#endif // SENSOR_H
