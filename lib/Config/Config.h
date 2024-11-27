#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <WiFiEsp.h>
#include <ThingSpeak.h>
#include <HX711.h>
#include <FastLED.h>
#include <Servo.h>

// WiFi Configuration
#define ESP_BAUDRATE    115200
extern char ssid[];
extern char pass[];
extern int status;
extern WiFiEspClient client;
#define WiFiSerial Serial1

// ThingSpeak Configuration
extern const unsigned long CHANNEL_ID;
extern const char WRITE_API_KEY[];

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

// Detect Ultrasonic Sensor Pins
#define OBJ_DETECT_TRIG_PIN    9
#define OBJ_DETECT_ECHO_PIN    8

// Motor Pin
#define servo1Pin A0
#define servo2Pin A1
#define servo3Pin A2
extern Servo servo1;
extern Servo servo2;
extern Servo servo3;

// Communication with ESP32 and QR Code Scanner
#define ESP32Serial Serial2
#define QRCodeSerial Serial3

// Global Variables
extern float duration;
extern float distance;
extern float height;
extern int LED;

#endif // CONFIG_H
