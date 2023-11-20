#include <Arduino.h>
#include <ESC.h>

#define ESC_PIN 2

// min pulse width 1160

ESC esc;
void setPower(int power);

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
  if (Serial.available())
  {
    const int data = Serial.readStringUntil('\n').toInt();

    setPower(data);
  }
}

void setPower(int power)
{
  int currentPower = esc.getPower();
  bool positive = currentPower < power;

  for (int i = currentPower; positive ? i < power : i > power; positive ? i++ : i--)
  {
    int p = positive ? i + 1 : i - 1;

    Serial.printf("Current power: %d%\n", p);
    esc.setPower(p);

    delay(50);
  }
}