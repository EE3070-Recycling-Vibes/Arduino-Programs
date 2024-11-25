#include "Config.h"
#include "Sensor.h"
#include "ObjDetection.h"
#include "QRCode.h"
#include "LEDControl.h"

void setup() {
    Serial.begin(115200);

    // Initialize serial ports
    WiFiSerial.begin(ESP_BAUDRATE);
    ESP32Serial.begin(9600);
    QRCodeSerial.begin(9600);

    WiFi.init(&WiFiSerial);

    if (WiFi.status() != WL_CONNECTED) {
        Serial.print("Attempting to connect to SSID: ");
        Serial.println(ssid);
        while (WiFi.status() != WL_CONNECTED) {
            WiFi.begin(ssid, pass);
            Serial.print(".");
            delay(5000);
        }
        Serial.println("\nConnected");
        delay(1000); // power-up safety delay
    }

    ThingSpeak.begin(client);

    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(BRIGHTNESS);

    currentPalette = RainbowColors_p;
    currentBlending = LINEARBLEND;

    // Initialize sensors and servo
    initializeSensors();
    servo1.attach(servoPin);

    // Output the scale data after setup
    Serial.println("After setting up the scale:");
    Serial.print("read: \t\t");
    Serial.println(scale.read());
    Serial.print("read average: \t\t");
    Serial.println(scale.read_average(20));
    Serial.print("get value: \t\t");
    Serial.println(scale.get_value(5));
    Serial.print("get units: \t\t");
    Serial.println(scale.get_units(5), 1);
}

void loop() {
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("WiFi not connected. Reconnecting...");
        while (WiFi.status() != WL_CONNECTED) {
            WiFi.begin(ssid, pass);
            delay(5000);
        }
        Serial.println("Connected");
        ThingSpeak.begin(client);
    }

    // Read weight
    float weight = readWeight();
    Serial.print("Weight: ");
    Serial.println(weight);

    // Upload weight data to ThingSpeak
    int roundedWeight = int(weight + 0.5);
    int writeWeight = ThingSpeak.writeField(CHANNEL_ID, 4, roundedWeight, WRITE_API_KEY);
    if (writeWeight == 200) {
        Serial.print(" | Weight data uploaded to ThingSpeak successfully: ");
        Serial.println(roundedWeight);
    } else {
        Serial.println(" | Failed to upload weight data to ThingSpeak.");
    }

    // Read height
    distance = measureHeight();
    Serial.print("Distance: ");
    Serial.println(distance);

    // Upload distance data to ThingSpeak
    int writeDistance = ThingSpeak.writeField(CHANNEL_ID, 1, round(distance), WRITE_API_KEY);
    if (writeDistance == 200) {
        Serial.print(" | Distance data uploaded to ThingSpeak successfully: ");
        Serial.println(distance);
    } else {
        Serial.println(" | Failed to upload Distance data to ThingSpeak.");
    }

    // Update LEDs
    static uint8_t startIndex = 0;
    startIndex = startIndex + 1;
    FillLEDsFromPaletteColors(startIndex);
    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);
    FastLED.clear();

    // Object detection
    objDetection();

    // QR Code scanning
    String qrCode = getQRCode();
    if (qrCode != "") {
        Serial.print("QR Code: ");
        Serial.println(qrCode);
        // Process QR Code as needed
    }

    delay(500); // Adjust delay as needed
}
