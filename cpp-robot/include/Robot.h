#ifndef ROBOT_H_
#define ROBOT_H_

#include "API.h"



class Robot {

private:
  Gyro gyro;
public:

  enum SensorPorts {
    imeLeft, imeRight, leftLiftPoten, rightLiftPoten, chainbarPoten, gyroscope
  };

  enum MotorPorts {
    rightDrive1=2, leftLift, intake, leftDrive1, rightLift, leftDrive2, rightDrive2, chainbar, mobileGoalLift
  };

  void chassisSet(int left, int right);
  void liftSet(int move);
  void mobileGoalLiftSet(int move);

  int readIME(int port);
  int readPoten(int port);
  int readGyro(int port);

  Robot();
};

#endif
