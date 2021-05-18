#include <FastLED.h>
#include <OneButton.h>

#define NUM_LEDS 150
#define LED_PIN 7
#define BTN_PIN 3
#define BOARD_LED 13  // NODEMCU board LED
#define ESP_LED 2     // ESP8266 LED
#define MAX_DRAW 900  // Max power draw in mW

CRGB leds[NUM_LEDS];  // Global LED array
uint8_t patternCounter = 0;
bool isRunning = false;

// Push button connected between pin 3 and GND (no resistor required)
OneButton btn = OneButton(BTN_PIN, true, true);

// Include pattern files
#include "Comet.h"

// Set up pattern controllers
void nextPattern() {
  isRunning = false;
  patternCounter = (patternCounter + 1) % 1;
}

void runComet() {
  isRunning = true;
  Comet comet = Comet();
  bool addComet;
  while (isRunning) {
    uint8_t rand = random(50);
    // Serial.println(rand);
    if (rand==42) {
      addComet = true;
    } else {
      addComet = false;
    }
    comet.runPattern(addComet);
    // yield();  // Reset watchdog(WDT) timer https://forum.arduino.cc/t/soft-wdt-reset-nodemcu/425567
  }
}

// Set up arduino
void setup() {
  // Power indicator
  pinMode(BOARD_LED, OUTPUT);
  analogWrite(BOARD_LED, HIGH);

  // Set up FastLED
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(64);
  FastLED.setMaxPowerInMilliWatts(MAX_DRAW);
  set_max_power_indicator_LED(ESP_LED);

  Serial.begin(57600);

  // Add button listener (kinda)
  btn.attachClick(nextPattern);
}

// Main loop function
void loop() {
  // Select pattern
  switch (patternCounter) {
    case 0:
      runComet();
      break;
    default:
      runComet();
      break;
  }
}