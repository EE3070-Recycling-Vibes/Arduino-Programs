#include "QRCode.h"

String qrCode = "";

String getQRCode() {
    ESP32Serial.println("scan");
    unsigned long startTime = millis();
    while (!QRCodeSerial.available()) {
        if (millis() - startTime > 5000) { // 1-minute timeout
            Serial.println("No QR code detected");
            return "";
        }
    }

    while (QRCodeSerial.available()) {
        char c = QRCodeSerial.read();
        qrCode += c;
    }
    qrCode.trim();

    delay(5000);
    Serial.print("QR Code scanned: ");
    Serial.println(qrCode);

    return qrCode;
}
