#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Servo.h>
#include "LedStrip.h"
#include "ObjDetection.h"
#include "Config.h"
#include "GetQrCode.h"

SoftwareSerial espSerial(ESP_RX_PIN, ESP_TX_PIN); // RX, TX
SoftwareSerial qrcodeSerial(QRCODE_RX_PIN, QRCODE_TX_PIN); // RX, TX

Servo servo1;

String qrCodeMsg = "";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  espSerial.begin(115200); // Must match ESP32 baud rate
  qrcodeSerial.begin(115200);

  // Initialize height ultrasonic sensor pins
  pinMode(HEIGHT_TRIG_PIN, OUTPUT);
  pinMode(HEIGHT_ECHO_PIN, INPUT);
  Serial.println("Height Ultrasonic Sensor Initialized");

  ledSetup();

  // Initialize height ultrasonic sensor pins
  pinMode(OBJ_DETECT_TRIG_PIN, OUTPUT);
  pinMode(OBJ_DETECT_ECHO_PIN, INPUT);
  Serial.println("Height Ultrasonic Sensor Initialized");

  // Initialize motor pins
  servo1.attach(servoPin);
  Serial.println("Motor Initialized");
}

void loop() {
  checkHeight();
  objDetection(espSerial, servo1);
  qrCodeMsg = getQRCode(qrcodeSerial);
}