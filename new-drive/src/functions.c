#include "functions.h"


void chassisSet(int left, int right) {
  motorSet(LEFT_MOTOR_PORT_1, left);
  motorSet(LEFT_MOTOR_PORT_2, left);
  motorSet(RIGHT_MOTOR_PORT_1, right);
  motorSet(RIGHT_MOTOR_PORT_2, right);
}
