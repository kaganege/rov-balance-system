#pragma once

// https://howtomechatronics.com/tutorials/arduino/arduino-brushless-motor-control-tutorial-esc-bldc/

#include <Arduino.h>
#include <hardware/pio.h>

#define PWM_SIGNAL_FREQ 50
#define MIN_PULSE_WIDTH 1000
#define MAX_PULSE_WIDTH 2000
#define REFRESH_INTERVAL 20000

class ESC
{
private:
  bool _attached = false;
  int _pulse_width = MIN_PULSE_WIDTH;
  PIO _pio;
  int _sm = -1;
  int _offset = -1;
  pin_size_t _pin;

public:
  ESC();
  ~ESC();

  void attach(pin_size_t pin);
  void detach();
  bool attached();

  void setPulseWidth(int value);
  int getPulseWidth();

  void setPower(int percent);
  void setPower(int (*percent)(int currentPower));
  int getPower();
};