#define FASTLED_ESP8266_NODEMCU_PIN_ORDER
#include <FastLED.h>

#define PIN_OUT 7
#define NUM_LEDS 5
CRGB leds[NUM_LEDS];
int x = 0;

DEFINE_GRADIENT_PALETTE(redgreen_gp){
    127, 0, 255, 0,
    127, 255, 0, 0};

CRGBPalette16 redgreen = redgreen_gp;

void setup()
{
  Serial.begin(115200);
  FastLED.addLeds<WS2812, PIN_OUT, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(64);
}
void loop()
{
  EVERY_N_MILLISECONDS(100)
  {
    uint8_t noise = inoise8(x);
    Serial.println('.');
    for (int i = 0; i < NUM_LEDS; i++)
    {
      uint8_t alpha = constrain((5 * noise) + (250 * i), 0, 255);
      leds[i] = ColorFromPalette(redgreen, noise, alpha);
    }

    FastLED.show();
    x += 50;
  }
}