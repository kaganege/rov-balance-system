#include <Arduino.h>
#include <ESC.h>

#define ESC_PIN 2
#define POT_PIN 26

// min pulse width 1160

ESC esc;
int power = 0;
bool wait_for_zero = true;

void setup()
{
  analogReadResolution(12);

  pinMode(POT_PIN, INPUT);
  esc.attach(ESC_PIN);

  Serial.begin();
}

void loop()
{
  int pot_value = analogRead(POT_PIN);
  pot_value = map(max(pot_value, 20), 20, 4096, 0, 1000);

  Serial.printf("Potentiometer value: %d\n", pot_value);

  if (wait_for_zero)
  {
    if (pot_value == 0)
      wait_for_zero = false;

    return;
  }

  power = pot_value;

  if (esc.getPower() != power)
  {
    esc.setPower([](int currentPower)
                 { return currentPower < power ? currentPower + 1 : currentPower - 1; });
    delayMicroseconds(500);
  }
}