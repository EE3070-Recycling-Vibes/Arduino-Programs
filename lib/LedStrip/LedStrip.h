#ifndef LEDSTRIP_H
#define LEDSTRIP_H

#include <FastLED.h>

#define LED_PIN     5
#define NUM_LEDS    7
#define BRIGHTNESS  64
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;

#define UPDATES_PER_SECOND 100
CRGBPalette16 currentPalette;
TBlendType    currentBlending;

void ledSetup();
void checkHeight();

#endif // MYPALETTES_H