#define FASTLED_ESP8266_NODEMCU_PIN_ORDER
#include <FastLED.h>

#define PIN_OUT 7
#define NUM_LEDS 5
CRGB leds[NUM_LEDS];
int x = 0;

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
    Serial.println(noise);
    uint8_t mapped = map(noise, 30, 300, 0, 120);
    if (mapped > 120)
    {
      mapped = 0;
    }
    uint8_t saturation = 255;
    for (int i = 0; i < NUM_LEDS; i++)
    {
      int value = (((-255) / ((NUM_LEDS - i) * (120 / 5))) * mapped) + 255;

      if (value < 0)
      {
        value = 0;
      }
      if (value > 255)
      {
        value = 255;
      }

      leds[i] = CHSV(mapped, saturation, value);
    }

    FastLED.show();
    x += 50;
  }

}