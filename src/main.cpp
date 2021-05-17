#include <FastLED.h>
#include <OneButton.h>

#define NUM_LEDS 18
#define LED_PIN 2
#define BTN_PIN 3

CRGB leds[NUM_LEDS];
uint8_t patternCounter = 0;
bool isRunning = false;

// Push button connected between pin 7 and GND (no resistor required)
OneButton btn = OneButton(BTN_PIN, true, true);

// Include pattern files
#include "Comet.h"

// Set up pattern controllers
void nextPattern() {
  isRunning = false;
  patternCounter = (patternCounter + 1) % 3;
}

void runComet() {
  isRunning = true;
  Comet comet = Comet();
  while (isRunning) comet.runPattern();
}

// Set up arduino
void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(50);
  Serial.begin(57600);

  btn.attachClick(nextPattern);
}

// Main loop function
void loop() {
  switch (patternCounter) {
    case 0:
      runComet();
      break;
    // case 1:
    //   runRainbowBeat();
    //   break;
    // case 2:
    //   runRedWhiteBlue();
    //   break;
  }
}