#include <Arduino.h>
#include <FastLED.h>
#include "LedStrip.h"
#include "Config.h"

int LED;
float duration, distance;

void ledSetup() {
    delay(1000); // power-up safety delay
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(BRIGHTNESS);
    
    currentPalette = RainbowColors_p;
    currentBlending = LINEARBLEND;
    Serial.begin(9600);
    pinMode(HEIGHT_TRIG_PIN, OUTPUT);
    pinMode(HEIGHT_ECHO_PIN, INPUT);
}

void checkHeight() {
    digitalWrite(HEIGHT_TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(HEIGHT_TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(HEIGHT_TRIG_PIN, LOW);

    duration = pulseIn(HEIGHT_ECHO_PIN, HIGH);
    distance = (duration / 2) * 0.0343;
    //LED = distance;

    static uint8_t startIndex = 0;
    startIndex = startIndex + 1; /* motion speed */    //change color
        
    FillLEDsFromPaletteColors( startIndex);     //fill color
        
    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);
    Serial.print("Distance = ");
    Serial.print(distance);
    Serial.print(" cm");
    Serial.print(" LED = ");
    Serial.println(LED);
    FastLED.clear();
}

void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
    uint8_t brightness = 255;
    LED = 9 - round(0.6 * distance);
    for( int i = LED-1; i >= 0; i--) {    //change num here
        leds[6-i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
}