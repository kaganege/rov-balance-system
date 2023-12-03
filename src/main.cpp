#include <Arduino.h>
#include <ESC.h>
#include <Gyro.h>

#define FIT(value, _min, _max) min(max(value, _min), _max)
#define OR(condition, default) condition ? condition : default

#define ESC_PIN 2

// min pulse width 1160

ESC esc;
Gyro gyro;

int power = 0;
bool wait_for_zero = true;

void setup()
{
  Serial.begin();

  esc.attach(ESC_PIN);
  gyro.init();

  gyro.waitUntilConnect();
}

void loop()
{
  if (BOOTSEL)
  {
    rp2040.rebootToBootloader();
    return;
  }

  // int pot_value = FIT(analogRead(POT_PIN), POT_MIN, POT_MAX);

  // if (wait_for_zero)
  // {
  //   if (pot_value == POT_MIN)
  //     wait_for_zero = false;
  // }
  // else
  // {
  //   power = map(pot_value, POT_MIN, POT_MAX, 0, 1000);

  //   if (esc.getPower() != power)
  //   {
  //     esc.setPower([](int currentPower)
  //                  { return currentPower < power ? currentPower + 1 : currentPower - 1; });
  //     delay(1);
  //   }
  // }
  Serial.printf("Motor power: %d\n", power);
}