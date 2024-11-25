#ifndef CONFIG_H
#define CONFIG_H
#include <FastLED.h>
#include "HX711.h"
#include "WiFiEsp.h"

// LED Configuration
#define LED_PIN     5
#define NUM_LEDS    7
#define BRIGHTNESS  64
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB

extern CRGB leds[NUM_LEDS];
extern CRGBPalette16 currentPalette;
extern TBlendType    currentBlending;

#define UPDATES_PER_SECOND 100

// Load Cell Configuration
#define LOADCELL_DOUT_PIN 2
#define LOADCELL_SCK_PIN  3

extern HX711 scale;

// Height Ultrasonic Sensor Pins
#define HEIGHT_TRIG_PIN    13
#define HEIGHT_ECHO_PIN    12
extern int LED;
extern float duration, distance;

// Detect Ultrasonic Sensor Pins
#define OBJ_DETECT_TRIG_PIN    9
#define OBJ_DETECT_ECHO_PIN    8

// Motor Pins
#define servoPin A0

// SoftwareSerial Pins for communication with ESP32
#define ESP_RX_PIN 25  // Receive Pin
#define ESP_TX_PIN 23  // Transmit Pin

// SoftwareSerial Pins for communication with ESP32
#define QRCODE_RX_PIN 22  // Receive Pin
#define QRCODE_TX_PIN 24  // Transmit Pin

// WiFi Configuration
#define ESP_BAUDRATE    115200
extern char ssid[];
extern char pass[];
extern int status;
extern WiFiEspClient client;

// ThingSpeak Configuration
extern const unsigned long CHANNEL_ID;
extern const char WRITE_API_KEY[];

#endif // CONFIG_H
