#include <Arduino.h>
#include <Gyro.h>
#include <Wire.h>
#include <math.h>

Gyro::Gyro()
{
  for (int i = 0; i < Motions::LENGTH; i++)
    _filters[i] = KalmanFilter(1000, 800, 0.01);
}

void Gyro::waitUntilConnect()
{
  while (!_sensor.testConnection())
    delay(50);
}

void Gyro::init()
{
  Wire.begin();
  _sensor.initialize();
  _initalized = true;
}

bool Gyro::initalized()
{
  return _initalized;
}

bool Gyro::connected()
{
  return _sensor.testConnection();
}

int16_t *Gyro::getData()
{
  int16_t *data[Motions::LENGTH];
  _sensor.getMotion6(data[ACC_X], data[ACC_Y], data[ACC_Z], data[GYRO_X], data[GYRO_Y], data[GYRO_Z]);

  return *data;
}

int16_t *Gyro::getFilteredData()
{
  int16_t *data = getData();

  for (int i = 0; i < Motions::LENGTH; i++)
    data[i] = (int16_t)round(_filters[i].updateEstimate(data[i]));

  return data;
}
