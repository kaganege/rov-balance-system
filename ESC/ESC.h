#pragma once

#include <Arduino.h>
#include <Servo.h>

class ESC
{
private:
  Servo pwm_generator;

public:
  void attach(pin_size_t pin);
  void setPower(int percent);
};