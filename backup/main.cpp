#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Servo.h>
#include "LedHandler.h"
#include "ObjDetection.h"
#include "Config.h"
#include "GetQrCode.h"
#include "Sensor.h"
#include "Network.h"

SoftwareSerial espSerial(ESP_RX_PIN, ESP_TX_PIN); // RX, TX
SoftwareSerial qrcodeSerial(QRCODE_RX_PIN, QRCODE_TX_PIN); // RX, TX

Servo servo1;

String userid = "";

// uss = Ultrasonic Sensor
int weight;
float ussHeight, ussDistance;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  espSerial.begin(115200); // Must match ESP32 baud rate
  qrcodeSerial.begin(115200);

  // Initialize Wifi connection
  initializeWiFi();
  // Initialize sensors
  initializeSensors();
  // Initialize LEDs
  initializeLEDs();

  // Initialize motor pins for the lid
  servo1.attach(servoPin);
  Serial.println("Motor Initialized");
}

void loop() {
  updateLEDs(0);
  userid = getQRCode(qrcodeSerial);

  weight = readWeight();
  Serial.println("Weight: " + String(weight) + " g");
  
  ussHeight = measureHeight();
  Serial.println("Height: " + String(ussHeight) + " cm");

}