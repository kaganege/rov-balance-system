#include <Arduino.h>
#include <ESC.h>
#include <Gyro.h>

#define ESC_PIN 2
#define POT_PIN 26

// min pulse width 1160

ESC esc;
Gyro gyro = Gyro();
int power = 0;
bool wait_for_zero = true;

void setup()
{
  analogReadResolution(12);

  // We are driving high GPIO 23 because forcing the power supply into PWM mode reduces ADC noise. I mean, I hope so. I didn't tested.
  // pinMode(23, OUTPUT);
  // digitalWrite(23, HIGH);
  // Does not work :(

  pinMode(POT_PIN, INPUT);
  esc.attach(ESC_PIN);
  gyro.init();

  // gyro.waitUntilConnect();

  Serial.begin();
}

void loop()
{
  int pot_value = analogRead(POT_PIN);
  power = map(min(max(pot_value, 50), 4090), 50, 4090, 0, 1000);

  Serial.printf("Potentiometer value: %d, Motor power: %d\n", pot_value, power);

  if (wait_for_zero)
  {
    if (power == 0)
      wait_for_zero = false;

    return;
  }

  if (esc.getPower() != power)
  {
    esc.setPower([](int currentPower)
                 { return currentPower < power ? currentPower + 1 : currentPower - 1; });
  }

  delay(1);
}