#include "Config.h"

// LED Variables
CRGB leds[NUM_LEDS];
CRGBPalette16 currentPalette;
TBlendType    currentBlending;

// Load Cell
HX711 scale;

// Height ultrasonic Sensor Variables
int LED = 0;
float duration = 0.0;
float distance = 0.0;

// WiFi Credentials
char ssid[] = "Pixel";          // your network SSID (name)
char pass[] = "apple8551";      // your network password

// WiFi Status
int status = WL_IDLE_STATUS;

// ThingSpeak Configuration
const unsigned long CHANNEL_ID = 2709428;
const char WRITE_API_KEY[] = "Y9PPUAJ1X51FB4HQ";
