#include <Arduino.h>
#include <ESC.h>

#define FIT(value, _min, _max) min(max(value, _min), _max)

#define ESC_PIN 2
#define POT_PIN 26

// min pulse width 1160

ESC esc;
int power = 0;
int pot_min, pot_max;
bool wait_for_zero = true;

// template <typename T>
// T fit(T value, T _min, T _max)
// {
//   return min(max(value, _min), _max);
// }

void setup()
{
  analogReadResolution(12); // 12 bit (0 - 4096)

  // We are driving high GPIO 23 because forcing the power supply into PWM mode reduces ADC noise.
  pinMode(23, OUTPUT);
  digitalWrite(23, HIGH);

  pinMode(POT_PIN, INPUT);
  // esc.attach(ESC_PIN);

  Serial.begin();
}

void loop()
{
  int pot_value = analogRead(POT_PIN);

  if (!pot_min && BOOTSEL)
  {
    pot_min = pot_value + 10;

    while (BOOTSEL)
      ;
  }
  else if (!pot_max && BOOTSEL)
  {
    pot_max = pot_value - 10;

    while (BOOTSEL)
      ;
  }
  else if (pot_min && pot_max)
  {
    pot_value = map(FIT(pot_value, pot_min, pot_max), pot_min, pot_max, 0, 1000);

    if (wait_for_zero)
    {
      if (pot_value == 0)
        wait_for_zero = false;
    }
    else
    {
      power = pot_value;

      if (esc.getPower() != power)
      {
        esc.setPower([](int currentPower)
                     { return currentPower < power ? currentPower + 1 : currentPower - 1; });
        delay(1);
      }
    }
  }
  Serial.printf("Potentiometer value: %d\n", pot_value);

  delayMicroseconds(500);
}