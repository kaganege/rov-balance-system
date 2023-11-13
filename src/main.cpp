#include <Arduino.h>
#include <ESC.h>

#define ESC_PIN 2

ESC esc;

void setup()
{
  esc.attach(ESC_PIN);

  // 10% power
  esc.setPower(10);
}

void loop()
{
  int power = esc.getPower();

  if (power < 10)
  {
    esc.setPower(power + 1);

    delay(1000);
  }
}