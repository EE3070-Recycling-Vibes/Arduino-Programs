#include "LEDControl.h"

void FillLEDsFromPaletteColors(uint8_t colorIndex) {
    uint8_t brightness = 255;
    LED = 8 - floor(0.6 * distance);
    for (int i = LED - 1; i >= 0; i--) { // Adjust as needed
        leds[6 - i] = ColorFromPalette(currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
}
