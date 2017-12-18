#ifndef _ROBOT_H_
#define _ROBOT_H_

#include "API.h"

enum class SensorPorts {

} SensorPorts;

enum class MotorPorts {
  leftDrive
} MotorPorts;

class Robot {

private:
  Gyro gyro;
public:
  Robot();
};

#endif
