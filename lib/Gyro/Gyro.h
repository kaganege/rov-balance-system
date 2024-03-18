#include <KalmanFilter.h>
#include <MPU6050.h>

// TODO: Change for ICM42688-P

enum Motions
{
  ACC_X,
  ACC_Y,
  ACC_Z,
  GYRO_X,
  GYRO_Y,
  GYRO_Z,
  LENGTH
};

class Gyro
{
private:
  bool _initalized = false;
  KalmanFilter *_filters = (KalmanFilter *)malloc(sizeof(KalmanFilter) * Motions::LENGTH);
  MPU6050 _sensor;

public:
  Gyro();

  void waitUntilConnect();
  void init();
  bool initalized();
  bool connected();

  int16_t *getData();
  int16_t *getFilteredData();
};