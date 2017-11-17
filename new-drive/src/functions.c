#include "functions.h"
#include "main.h"
#include <api.h>

void chassisSet(int left, int right) {
  motorSet(LEFT_MOTOR_PORT_1, left);
  motorSet(LEFT_MOTOR_PORT_2, left);
  motorSet(RIGHT_MOTOR_PORT_1, right);
  motorSet(RIGHT_MOTOR_PORT_2, right);
}

void resetIMEs() {
  imeReset(LEFT_IME);
  imeReset(RIGHT_IME);
}

bool updateIMEs(int *left, int *right) {
  return imeGet(LEFT_IME, left);
}

void gyroCheck() {
  //checks gyro to make sure the robot is going in the right direction
  if(gyroGet(gyro) < 0) {
    chassisSet(105, 127);
  }
  else if(gyroGet(gyro) > 0) {
    chassisSet(127, 105);
  }
  else {
    chassisSet(127, 127);
  }
}
