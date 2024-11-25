#include "LEDHandler.h"

void initializeLEDs() {
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS)
           .setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(BRIGHTNESS);

    currentPalette = RainbowColors_p;
    currentBlending = LINEARBLEND;
}

void FillLEDsFromPaletteColors(uint8_t colorIndex) {
    uint8_t brightness = 255;
    LED = 8 - floor(0.6 * distance);
    LED = constrain(LED, 0, NUM_LEDS); // Ensure LED does not exceed NUM_LEDS

    for(int i = LED - 1; i >= 0; i--) {
        leds[NUM_LEDS - 1 - i] = ColorFromPalette(currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
}

void updateLEDs(uint8_t colorIndex) {
    FillLEDsFromPaletteColors(colorIndex);
    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);
    FastLED.clear();
}
