#include "WiFiEsp.h"
#include "ThingSpeak.h"
#include <Arduino.h>
#include "HX711.h"
#include <FastLED.h>

const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;
int weight = 0;
#define LED_PIN     5
#define NUM_LEDS    7
#define BRIGHTNESS  64
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];
#define UPDATES_PER_SECOND 100
CRGBPalette16 currentPalette;
TBlendType    currentBlending;

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;

int trigPin = 13;
int echoPin = 12;
int LED;
float duration, distance;

HX711 scale;

#define ESP_BAUDRATE 115200
char ssid[] = "Pixel"; // your network SSID (name)
char pass[] = "apple8551";
int status = WL_IDLE_STATUS; // the Wifi radio's status

WiFiEspClient client;

void setup() {
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
    delay( 1000 ); // power-up safety delay

  }

  ThingSpeak.begin(client);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  // Initialize the scale and set parameters
  scale.set_scale(413.7878); // Set the scale factor
  scale.tare(); // Reset to zero
  delay( 1000 );

  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(BRIGHTNESS);
  
  currentPalette = RainbowColors_p;
  currentBlending = LINEARBLEND;
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

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

  float weight = scale.get_units(5);
  Serial.print("one reading:\t");
  if (weight < 0) {
    Serial.print("0");
  } else {
    int roundedWeight = int(weight + 0.5);
    Serial.print(roundedWeight);

    // Upload weight data to ThingSpeak
    int writeWeight = ThingSpeak.writeField(2709428, 4, roundedWeight, "Y9PPUAJ1X51FB4HQ");
    if (writeWeight == 200) {
      Serial.print(" | Weight data uploaded to ThingSpeak successfully: ");
      Serial.println(roundedWeight);
    } else {
      Serial.println(" | Failed to upload weight data to ThingSpeak.");
    }
  }

  Serial.print("\t| average:\t");
  Serial.println(scale.get_units(10), 5);

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = (duration / 2) * 0.0343;
  int writeDistance = ThingSpeak.writeField(2709428, 1, round(distance), "Y9PPUAJ1X51FB4HQ");
    if (writeDistance == 200) {
      Serial.print(" | Distance data uploaded to ThingSpeak successfully: ");
      Serial.println(distance);
    } else {
      Serial.println(" | Failed to upload Distance data to ThingSpeak.");
    }


  static uint8_t startIndex = 0;
  startIndex = startIndex + 1;

  FillLEDsFromPaletteColors(startIndex);

  FastLED.show();
  FastLED.delay(1000 / UPDATES_PER_SECOND);
  /*
  Serial.print("Distance = ");
  Serial.print(distance);
  Serial.print(" cm");
  Serial.print(" LED = ");
  Serial.println(LED);
  */
  FastLED.clear();
}

void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
    uint8_t brightness = 255;
    LED = 8 - floor(0.6 * distance);
    for( int i = LED-1; i >= 0; i--) {    //change num here
        leds[6-i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }

}