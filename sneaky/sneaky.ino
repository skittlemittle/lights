/*
 * Lights that turn on when I walk into my room, but with pretty effects
 */

#include <FastLED.h>
#include <LowPower.h>

const int pins[] = {3, 5, 6, 9, 10, 11}; // rgb rgb
bool LIGHT = false;
CHSV wheel(0, 255, 255);
CRGB out;

void setup()
{
  digitalWrite(13, LOW);

  for (const int p : pins) {
    pinMode(p, INPUT);
    digitalWrite(p, HIGH);
  }
}

void deezNuts()
{
  int hue = 0;
  for (int i = 0; i < 1500; i++) {
    wheel.hue = hue;
    hsv2rgb_rainbow(wheel, out);

    int r = 255 - out.red;
    int g = 255 - out.green;
    int b = 255 - out.blue;

    analogWrite(pins[0], r);
    analogWrite(pins[1], g);
    analogWrite(pins[2], b);

    analogWrite(pins[3], r);
    analogWrite(pins[4], g);
    analogWrite(pins[5], b);

    delay(10);
    hue = (hue + 1) % 255;
  }
  for (const int p : pins) digitalWrite(p, HIGH);
}

void loop()
{
  attachInterrupt(0, onMovement, RISING);

  deezNuts();
  LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
  detachInterrupt(0);

}

void onMovement()
{
  LIGHT = true;
}
