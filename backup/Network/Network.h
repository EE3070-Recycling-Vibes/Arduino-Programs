#ifndef NETWORK_H
#define NETWORK_H

#include <Arduino.h>
#include "Config.h"
#include <WiFiEsp.h>
#include <ThingSpeak.h>

/**
 * @brief Initializes WiFi connection.
 */
void initializeWiFi();

/**
 * @brief Uploads weight data to ThingSpeak.
 * 
 * @param weight The weight value to upload.
 * @return int HTTP response code.
 */
int uploadWeight(float weight);

/**
 * @brief Uploads distance data to ThingSpeak.
 * 
 * @param distance The distance value to upload.
 * @return int HTTP response code.
 */
int uploadDistance(float distance);

#endif // NETWORK_H
