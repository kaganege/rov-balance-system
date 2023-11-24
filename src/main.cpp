#include <Arduino.h>
#include <ESC.h>

#define ESC_PIN 2
#define POT_PIN 31

// min pulse width 1160

ESC esc;
int power = 0;
bool wait_for_zero = true;

void setup()
{
  esc.attach(ESC_PIN);

  Serial.begin();
  while (!Serial)
    ;

  Serial.println("Current power: 0%");
}

void loop()
{
  int pot_value = analogRead(POT_PIN);

  if (wait_for_zero)
  {
    if (pot_value == 0)
      wait_for_zero = false;

    return;
  }

  power = map(pot_value, 0, 4096, 0, 1000);

  if (esc.getPower() != power)
  {
    esc.setPower([](int currentPower)
                 { return currentPower < power ? currentPower + 1 : currentPower - 1; });
    delayMicroseconds(500);
  }
}