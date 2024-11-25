#include "Config.h"

// WiFi Credentials
char ssid[] = "skyz";          // your network SSID (name)
char pass[] = "12345678";      // your network password
int status = WL_IDLE_STATUS;

WiFiEspClient client;

// ThingSpeak Configuration
const unsigned long CHANNEL_ID = 2709428;
const char WRITE_API_KEY[] = "Y9PPUAJ1X51FB4HQ";

// LED Variables
CRGB leds[NUM_LEDS];
CRGBPalette16 currentPalette;
TBlendType    currentBlending;

// Load Cell
HX711 scale;

// Servo Motor
Servo servo1;

// Global Variables
float duration = 0.0;
float distance = 0.0;
int LED = 0;
