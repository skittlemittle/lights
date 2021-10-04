/*
 lamp with hue knob + a mode switch
*/

#include <FastLED.h>

const int button = 8;
const int hue_dial = A0;
const int red = 5;
const int green = 3;
const int blue = 6;
CHSV colorWheel(0, 255, 255);
CRGB outColor;

void setup()
{
  pinMode(button, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop()
{
  static uint8_t mode = 0; // 0 to 2: cold white, warm white, colors
  static bool old_bval = false;

  readButton(button, &mode, &old_bval);
  if (mode == 0) {
    white(true);
  } else if (mode == 1) {
    white(false);
  } else if (mode == 2) {
    colorWheel.hue = map(analogRead(hue_dial), 0, 1023, 0 ,255);
    hsv2rgb_rainbow(colorWheel, outColor);
    analogWrite(red, 255 - outColor.red);
    analogWrite(blue, 255 - outColor.blue);
    analogWrite(green, 255 - outColor.green);
  }
  delay(2);
}

/** white */
void white(bool select)
{
  if (select) {
    analogWrite(red, 0);
    analogWrite(blue, 0);
    analogWrite(green, 0);
  } else {
    analogWrite(red, 0);
    analogWrite(green, 143);
    analogWrite(blue, 197);
  }
}

/** button with debouncing; increments bstate and updates old_bval
  @param pin: button pin (input pullup)
  @param bstate: the current button state
  @param old_bval: previous button reading
*/
void readButton(const int pin, uint8_t* bstate, bool* old_bval)
{
  bool bval = digitalRead(pin);
  if (!bval && old_bval) {
    *bstate = (*bstate + 1) % 3;
    delay(10);
  }
  *old_bval = bval;
}
