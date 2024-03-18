#include <Arduino.h>
#include <ESC.h>
#include <hardware/pio.h>
#include <hardware/clocks.h>

#include "esc.pio.h"
static PIOProgram _escPgm(&esc_program);

ESC::ESC()
{
  _pio = nullptr;
}

ESC::~ESC()
{
  detach();
}

void ESC::attach(pin_size_t pin)
{
  if (!attached())
  {
    digitalWrite(pin, LOW);
    pinMode(pin, OUTPUT);
    _pin = pin;

    if (!_escPgm.prepare(&_pio, &_sm, &_offset))
    {
      return;
    }
    _attached = true;

    esc_program_init(_pio, _sm, _offset, pin);
    pio_sm_set_enabled(_pio, _sm, false);
    pio_sm_put_blocking(_pio, _sm, RP2040::usToPIOCycles(REFRESH_INTERVAL) / 3);
    pio_sm_exec(_pio, _sm, pio_encode_pull(false, false));
    pio_sm_exec(_pio, _sm, pio_encode_out(pio_isr, 32));
    setPower(0);
    pio_sm_exec(_pio, _sm, pio_encode_pull(false, false));
    pio_sm_exec(_pio, _sm, pio_encode_mov(pio_x, pio_osr));
    pio_sm_set_enabled(_pio, _sm, true);
  }

  setPower(0);
}

void ESC::detach()
{
  if (attached())
  {
    // Set a 0 for the width and then wait for the halt loop
    pio_sm_put_blocking(_pio, _sm, 0);
    delayMicroseconds(5); // Avoid race condition
    do
    {
      // Do nothing until we are stuck in the halt loop (avoid short pulses)
    } while (pio_sm_get_pc(_pio, _sm) != esc_offset_halt + _offset);
    pio_sm_set_enabled(_pio, _sm, false);
    pio_sm_unclaim(_pio, _sm);
    _attached = false;
    _pulse_width = MIN_PULSE_WIDTH;
    _pio = nullptr;
  }
}

bool ESC::attached()
{
  return _attached;
}

void ESC::setPulseWidth(int value)
{
  _pulse_width = max(0, min(value, MAX_PULSE_WIDTH));

  if (_attached)
  {
    pio_sm_clear_fifos(_pio, _sm);
    pio_sm_put_blocking(_pio, _sm, RP2040::usToPIOCycles(_pulse_width) / 3);
  }
}

int ESC::getPulseWidth()
{
  return attached() ? _pulse_width : NULL;
}

void ESC::setPower(int percent)
{
  percent = max(0, min(percent, 1000));
  int pulse_width = map(percent, 0, 1000, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);

  setPulseWidth(pulse_width);
}

void ESC::setPower(int (*percent)(int currentPower))
{
  return setPower(percent(getPower()));
}

int ESC::getPower()
{
  return map(_pulse_width, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH, 0, 1000);
}
