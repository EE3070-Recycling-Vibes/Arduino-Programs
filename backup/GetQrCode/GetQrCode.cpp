#include <Arduino.h>
#include <SoftwareSerial.h>
#include "Config.h"

String getQRCode(SoftwareSerial qrcodeSerial) {
    String qrCode = "";
    unsigned long startTime = millis();
    while (!qrcodeSerial.available()) {
        if (millis() - startTime > 5000) { // 5-second timeout
        Serial.println("No QR code detected");
        return "";
        }
    }
    
    while (qrcodeSerial.available()) {
        char c = qrcodeSerial.read();
        qrCode += c;
    }
    qrCode.trim();
    return qrCode;
}