#include "ObjDetection.h"

void objDetection() {
    long duration;
    int distance;

    // Clear the trigger
    digitalWrite(OBJ_DETECT_TRIG_PIN, LOW);
    delayMicroseconds(2);

    // Set the trigger high for 10 microseconds
    digitalWrite(OBJ_DETECT_TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(OBJ_DETECT_TRIG_PIN, LOW);

    // Read the echo pin
    duration = pulseIn(OBJ_DETECT_ECHO_PIN, HIGH);

    // Calculate distance in cm
    distance = duration * 0.034 / 2;

    Serial.print("Object Detection Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    if (distance > 0 && distance < 10) {
        Serial.println("Object detected within 10 cm");
        // Send activation message to ESP32
        ESP32Serial.println("Activate");

        // Wait for response from ESP32
        unsigned long startTime = millis();
        while (!ESP32Serial.available()) {
            if (millis() - startTime > 5000) { // 5-second timeout
                Serial.println("No response from ESP32");
                return;
            }
        }

        // Read and process the object type from ESP32
        String objectType = "";
        while (ESP32Serial.available()) {
            char c = ESP32Serial.read();
            objectType += c;
        }
        objectType.trim();
        Serial.print("Detected Object: ");
        Serial.println(objectType);

        lidMotor(objectType);
    }

    // Wait before next measurement
    delay(500);
}

void lidMotor(String trash_type) {
    if (trash_type == "plastic") {
        servo1.write(10);
        delay(5000);
        servo1.write(180);
    }
    // Add more conditions for other trash types if needed
}
