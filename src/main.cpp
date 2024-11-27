#include "Config.h"
#include "Sensor.h"
#include "ObjDetection.h"
#include "QRCode.h"
#include "LEDControl.h"

void setup() {
    Serial.begin(115200);

    // Initialize serial ports
    WiFiSerial.begin(ESP_BAUDRATE);   // Serial1 for WiFi

    // Initialize WiFi
    WiFi.init(&WiFiSerial);

    // Wait for connection
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

    ESP32Serial.begin(ESP_BAUDRATE);          // Serial2 for ESP32
    QRCodeSerial.begin(ESP_BAUDRATE);         // Serial3 for QR Code Scanner

    // Initialize FastLED
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(BRIGHTNESS);

    currentPalette = RainbowColors_p;
    currentBlending = LINEARBLEND;

    // Initialize sensors and servo
    initializeSensors();
    servo1.attach(servo1Pin);
    servo1.write(10); // Close the lid
    servo2.attach(servo2Pin);
    servo2.write(10); // Close the lid
    servo3.attach(servo3Pin);
    servo3.write(10); // Close the lid

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
    // Check WiFi connection
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("WiFi not connected. Reconnecting...");
        while (WiFi.status() != WL_CONNECTED) {
            WiFi.begin(ssid, pass);
            delay(5000);
        }
        Serial.println("Connected");
        ThingSpeak.begin(client);
    }

    // 1. Height is checked for every loop
    height = measureHeight();
    Serial.print("Height: ");
    Serial.println(height);

    // 2. Weight is checked for every loop, show weight only when there's something on the scale
    float weight = readWeight();
    if (weight > 0) {
        Serial.print("Weight: ");
        Serial.println(weight);
    }

    // 5. Sync to cloud for every loop
    // Upload height and weight data to ThingSpeak
    int writeHeight = ThingSpeak.writeField(CHANNEL_ID, 1, round(height), WRITE_API_KEY);
    int roundedWeight = int(weight + 0.5);
    int writeWeight = ThingSpeak.writeField(CHANNEL_ID, 4, roundedWeight, WRITE_API_KEY);

    while (writeHeight != 200) {
        writeHeight = ThingSpeak.writeField(CHANNEL_ID, 1, round(height), WRITE_API_KEY);
    }
    while (writeWeight != 200) {
        writeWeight = ThingSpeak.writeField(CHANNEL_ID, 4, roundedWeight, WRITE_API_KEY);
        roundedWeight = int(weight + 0.5);
    }

    if (writeHeight == 200 && writeWeight == 200) {
        Serial.print(" | Height data uploaded to ThingSpeak successfully: ");
        Serial.println(height);
        Serial.print(" | Weight data uploaded to ThingSpeak successfully: ");
        Serial.println(roundedWeight);
    }

    // Update LEDs
    static uint8_t startIndex = 0;
    startIndex = startIndex + 1;
    FillLEDsFromPaletteColors(startIndex);
    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);
    FastLED.clear();

    // 3. QR code is scanned when there's something on the scale
    if (weight > 0) {
        delay(3000);
        Serial.println("Scanning QR code...");
        String qrCode = getQRCode();
        delay(2000);
        if (qrCode != "") {
            Serial.print("QR Code: ");
            Serial.println(qrCode);

            // Process QR Code as needed
            String usrID = qrCode;
            int writeUserID = ThingSpeak.writeField(2709428, 3, qrCode, "Y9PPUAJ1X51FB4HQ");
            while (writeUserID != 200) {
                writeUserID = ThingSpeak.writeField(2709428, 3, qrCode, "Y9PPUAJ1X51FB4HQ");
            }
            if (writeUserID == 200) {
                Serial.print(" | UserID data uploaded to ThingSpeak successfully: ");
                Serial.println(qrCode);
            } 
        }
    }

    // 4. Object detection is done when the detection ultrasonic sensor detected something <10cm and there's something on the scale
    if (weight > 0 || isObjectDetected()) {
        Serial.println("Starting object detection...");
        objDetection();
    }

    delay(500); // Adjust delay as needed
}
