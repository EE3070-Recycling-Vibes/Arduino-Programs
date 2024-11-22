#include <Arduino.h>
#include <SoftwareSerial.h>
#include "lid_motor.h"

// Ultrasonic Sensor Pins
#define TRIG_PIN 9
#define ECHO_PIN 8

// SoftwareSerial Pins for communication with ESP32
#define RX_PIN 10  // Receive Pin
#define TX_PIN 11  // Transmit Pin

SoftwareSerial espSerial(RX_PIN, TX_PIN); // RX, TX

// Motor Pins
#define motorPin1 2
#define motorPin2 3
#define motorPin3 4

void setup() {
  // Initialize serial communications
  Serial.begin(9600);      // For serial monitor
  espSerial.begin(115200); // Must match ESP32 baud rate

  // Initialize ultrasonic sensor pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  Serial.println("Ultrasonic Sensor Initialized");

  // Initialize motor pins
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  Serial.println("Motor Initialized");
}

void loop() {
  long duration;
  int distance;

  // Clear the trigger
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  // Set the trigger high for 10 microseconds
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Read the echo pin
  duration = pulseIn(ECHO_PIN, HIGH);

  // Calculate distance in cm
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance > 0 && distance < 10) {
    Serial.println("Object detected within 10 cm");
    // Send activation message to ESP32
    espSerial.println("Activate");

    // Wait for response from ESP32
    unsigned long startTime = millis();
    while (!espSerial.available()) {
      if (millis() - startTime > 5000) { // 5-second timeout
        Serial.println("No response from ESP32");
        return;
      }
    }

    // Read and process the object type from ESP32
    String objectType = "";
    while (espSerial.available()) {
      char c = espSerial.read();
      objectType += c;
    }
    objectType.trim(); 
    Serial.print("Detected Object: ");
    Serial.println(objectType);   
  
    lid_motor(objectType, motorPin1, motorPin2, motorPin3);
  }

  // Wait before next measurement
  delay(500);
}
