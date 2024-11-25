#ifndef LEDHANDLER_H
#define LEDHANDLER_H

#include <FastLED.h>
#include "Config.h"

/**
 * @brief Initializes the LED strip.
 */
void initializeLEDs();

/**
 * @brief Fills the LEDs based on the current palette and color index.
 * 
 * @param colorIndex The starting color index for the palette.
 */
void FillLEDsFromPaletteColors(uint8_t colorIndex);

/**
 * @brief Updates the LED strip display.
 * 
 * @param colorIndex The starting color index for the palette.
 */
void updateLEDs(uint8_t colorIndex);

#endif // LEDHANDLER_H
