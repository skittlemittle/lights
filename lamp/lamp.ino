#include <FastLED.h>

const int hue_dial = A0;
const int saturation_dial = A1;
const int o_pin = 5;

const int NUM_LEDS = 8;
CRGB leds[NUM_LEDS];
CHSV wheel(0, 255, 255);

void setup()
{
  pinMode(o_pin, INPUT_PULLUP);
  FastLED.addLeds<WS2811, 4, BRG>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(255);
}


void loop()
{
  static bool o_mode = false;
  static bool o_oldbval = false;

  readButton(o_pin, &o_mode, &o_oldbval);
  if (o_mode) {
    orange();
    o_mode = false;
  }

  wheel.hue = map(analogRead(hue_dial), 0, 1023, 0, 255);
  wheel.saturation = map(analogRead(saturation_dial), 0, 1023, 0, 255);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = wheel;
  }
  FastLED.show();
}

void orange()
{
  wheel.hue = 30;
  int piss = analogRead(hue_dial);
  while(true) {
    wheel.saturation = map(analogRead(saturation_dial), 0, 1023, 0, 255);
    for (int i = 0; i < NUM_LEDS; i++)
      leds[i] = wheel;

    FastLED.show();
    if (abs(analogRead(hue_dial) - piss) > 70) break;
  }
}

/** toggle pushbutton 
  @param pin: what could this possibly be
  @param bstate: the current toggle state
  @param old_bval: previous button reading
*/
void readButton(const int pin, bool* bstate, bool* old_bval)
{
  bool bval = digitalRead(pin);
  if (!bval && &old_bval) {
    *bstate = !*bstate;
    delay(10);
  }
  *old_bval = bval;
}
