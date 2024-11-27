#include "ObjDetection.h"

String objectType = "";
int Type;


void objDetection() {
    // // Send activation message to ESP32
    ESP32Serial.println("detect");

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

    // Control the motor based on object type
    lidMotor(objectType); 
}

void lidMotor(String trash_type) {
    if (trash_type == "plastic") {
        servo1.write(180);
        delay(5000);
        servo1.write(10);
        Serial.println("Motor activated for plastic trash. Lid opened and closed."); // Success message 
        Type = 1;
    }
    else if (trash_type == "metal") {
        servo2.write(180);
        delay(5000);
        servo2.write(10);
        Serial.println("Motor activated for plastic trash. Lid opened and closed."); // Success message 
        Type = 2;
    }
    else if (trash_type == "paper") {
        servo3.write(180);
        delay(5000);
        servo3.write(10);
        Serial.println("Motor activated for plastic trash. Lid opened and closed."); // Success message 
        Type = 3;
    }
    // Add more conditions for other trash types if needed
    else {
        Serial.println("Unknown trash type. Motor not activated.");
    }

    int writeType = ThingSpeak.writeField(2709428, 5, Type, "Y9PPUAJ1X51FB4HQ");
    if (writeType == 200) {
      Serial.print(" | Type data uploaded to ThingSpeak successfully: ");
      Serial.println(Type);
    } else {
      Serial.println(" | Failed to upload Type data to ThingSpeak.");
    }
}
