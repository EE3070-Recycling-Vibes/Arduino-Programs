#include "Network.h"

void initializeWiFi() {
    Serial.begin(115200);
    Serial1.begin(ESP_BAUDRATE);

    WiFi.init(&Serial1);

    if (WiFi.status() != WL_CONNECTED) {
        Serial.print("Attempting to connect to SSID: ");
        Serial.println(ssid);
        while (WiFi.status() != WL_CONNECTED) {
            WiFi.begin(ssid, pass);
            Serial.print(".");
            delay(5000);
        }
        Serial.println("\nConnected");
        delay(1000); // Power-up safety delay
    }

    ThingSpeak.begin(client);
}

int uploadWeight(float weight) {
    int roundedWeight = static_cast<int>(weight + 0.5);
    int response = ThingSpeak.writeField(CHANNEL_ID, 4, roundedWeight, WRITE_API_KEY);
    return response;
}

int uploadDistance(float distance) {
    int roundedDistance = static_cast<int>(round(distance));
    int response = ThingSpeak.writeField(CHANNEL_ID, 1, roundedDistance, WRITE_API_KEY);
    return response;
}
