// Scott Marley's moving dot pattern https://github.com/s-marley/FastLED-basics/tree/main/5.%20Multiple%20patterns
// Dave Garage's Comet pattern https://github.com/davepl/DavesGarageLEDSeries/blob/master/LED%20Episode%2006/src/comet.h

// Create colour pallete
DEFINE_GRADIENT_PALETTE(starGP_init){
    0, 250, 100, 0,
    255, 255, 160, 20};

CRGBPalette16 starGP = starGP_init;

class Comet {
 public:
  Comet(){
      // Empty constructor
  };
  void runPattern(bool addComet = false);
  void runPatternOld();

 private:
  uint8_t fadeAmt = 30;
  uint8_t maxComets = NUM_LEDS / 20;
  uint32_t cometMillisArray[NUM_LEDS];
};

void Comet::runPattern(bool addComet) {
  // Add a comet
  if (addComet) {
    // find empty array spot and put in
    for (size_t i = 0; i < maxComets; i++) {
      if (cometMillisArray[i] == 0) {
        cometMillisArray[i] = millis();  // defines the comet as it's offset
        break;
      }
    }
  }

  // Move comets
  for (size_t i = 0; i < maxComets; i++) {
    if (cometMillisArray[i] == 0) continue;
    uint8_t posBeat = map(beat16(30, cometMillisArray[i]), 0, 65535, 0, NUM_LEDS + 4);
    if (posBeat >= NUM_LEDS) {
      cometMillisArray[i] = 0;
      continue;
    };
    uint8_t colIndex = beatsin8(map((uint8_t)cometMillisArray[i], 0, 255, 20, 60), 0, 255, cometMillisArray[i], 0);
    leds[posBeat] += ColorFromPalette(starGP, colIndex, 127);
  }

  // Randomly fade all pixels for sparkled trail
  for (size_t i = 0; i < NUM_LEDS; i++) {
    if (random(100) < 50)
      leds[i] = leds[i].fadeToBlackBy(fadeAmt * (NUM_LEDS / 50));
  }

  btn.tick();
  FastLED.show();
}

// The first test of the comet system
void Comet::runPatternOld() {
  // Calc LED position
  uint8_t posBeat = map(beat8(60, 0), 0, 255, 0, NUM_LEDS - 1);
  uint8_t posBeat2 = map(beat8(60, 500), 0, 255, 0, NUM_LEDS - 1);  // timebase is ms offset

  // Wave for LED color
  uint8_t colBeat = beatsin8(45, 0, 255, 0, 0);

  // Add colBeat color to led at location of posBeat
  leds[posBeat] += CHSV(colBeat, 255, 255);
  leds[posBeat2] += CHSV(colBeat, 255, 255);

  // Randomly fade all pixels for sparkled trail
  for (size_t i = 0; i < NUM_LEDS; i++) {
    if (random(100) < 50)
      leds[i] = leds[i].fadeToBlackBy(fadeAmt);
  }

  btn.tick();
  FastLED.show();
}