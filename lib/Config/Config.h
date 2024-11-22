#ifndef CONFIG_H
#define CONFIG_H
#include <FastLED.h>

// LED Configuration
#define LED_PIN     5
#define NUM_LEDS    7
#define BRIGHTNESS  64
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB

extern CRGB leds[NUM_LEDS];

// Height Ultrasonic Sensor Pins
#define HEIGHT_TRIG_PIN    13
#define HEIGHT_ECHO_PIN    12

// Detect Ultrasonic Sensor Pins
#define OBJ_DETECT_TRIG_PIN    13
#define OBJ_DETECT_ECHO_PIN    12

// Motor Pins
#define servoPin A0

// SoftwareSerial Pins for communication with ESP32
#define ESP_RX_PIN 10  // Receive Pin
#define ESP_TX_PIN 11  // Transmit Pin

// SoftwareSerial Pins for communication with ESP32
#define QRCODE_RX_PIN 22  // Receive Pin
#define QRCODE_TX_PIN 23  // Transmit Pin

#endif // CONFIG_H
