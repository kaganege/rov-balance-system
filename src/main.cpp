#include <Arduino.h>
#include <ESC.h>

#define ESC_PIN 2

ESC esc;

void setup()
{
  esc.attach(ESC_PIN);
}

void loop()
{
  int power = esc.getPower();

  // 10% power
  if (power < 10)
  {
    esc.setPower(power + 1);

    delay(1000);
  }
}