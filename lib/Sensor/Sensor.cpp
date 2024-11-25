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
    return distance;
}
