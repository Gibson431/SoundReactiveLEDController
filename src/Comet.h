#include <Arduino.h>

class Comet {
 public:
  Comet(){
      // Empty constructor
  };
  void runPattern();

 private:
  int HALF_LEDS = NUM_LEDS / 2;
  int count = 0;
};

void Comet::runPattern() {
  leds[count % NUM_LEDS] = CRGB(255, 0, 0);
  fadeToBlackBy(leds, NUM_LEDS, 100);
  FastLED.show();
  count += 1;
}