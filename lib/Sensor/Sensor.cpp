#include "Sensor.h"

void initializeSensors() {
    // Initialize Height Ultrasonic Sensor Pins
    pinMode(HEIGHT_TRIG_PIN, OUTPUT);
    pinMode(HEIGHT_ECHO_PIN, INPUT);
    Serial.println("Height Ultrasonic Sensor Initialized");

    // Initialize Object Detection Ultrasonic Sensor Pins
    pinMode(OBJ_DETECT_TRIG_PIN, OUTPUT);
    pinMode(OBJ_DETECT_ECHO_PIN, INPUT);
    Serial.println("Object Detection Ultrasonic Sensor Initialized");

    // Initialize the scale and set parameters
    scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
    scale.set_scale(413.7878); // Set the scale factor
    scale.tare(); // Reset to zero
    delay(1000);
}

float readWeight() {
    float weight = scale.get_units(5);
    if (weight < 0) {
        return 0.0;
    } else {
        Serial.print("Weight: " + String(weight) + " kg");
        return weight;
    }
}

float measureHeight() {
    // Trigger Ultrasonic Sensor
    digitalWrite(HEIGHT_TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(HEIGHT_TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(HEIGHT_TRIG_PIN, LOW);

    // Read Echo Pin
    duration = pulseIn(HEIGHT_ECHO_PIN, HIGH);

    // Calculate Distance in cm
    distance = (duration / 2.0) * 0.0343;
    // Serial.println("The distance is " + String(distance));
    return distance;
}

// Added function implementation
bool isObjectDetected() {
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

    Serial.println("distance > 0 && distance < 15: " + String(distance > 0 && distance < 15));

    return (distance > 0 && distance < 15);
}
