#include <ESC.h>

void ESC::attach(pin_size_t pin)
{
  pwm_generator.attach(pin, DEFAULT_MIN_PULSE_WIDTH, DEFAULT_MAX_PULSE_WIDTH, DEFAULT_MIN_PULSE_WIDTH);
}

void ESC::setPower(int percent)
{
  pwm_generator.writeMicroseconds(map(percent, 0, 100, DEFAULT_MIN_PULSE_WIDTH, DEFAULT_MAX_PULSE_WIDTH));
}