#include "QRCode.h"

String getQRCode() {
    String qrCode = "";
    unsigned long startTime = millis();
    while (!QRCodeSerial.available()) {
        if (millis() - startTime > 5000) { // 5-second timeout
            Serial.println("No QR code detected");
            return "";
        }
    }

    while (QRCodeSerial.available()) {
        char c = QRCodeSerial.read();
        qrCode += c;
    }
    qrCode.trim();
    return qrCode;
}
