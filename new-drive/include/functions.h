#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include <API.h>
#define LEFT_MOTOR_PORT_1 3
#define LEFT_MOTOR_PORT_2 5
#define RIGHT_MOTOR_PORT_1 2
#define RIGHT_MOTOR_PORT_2 6
#define GYRO_PORT 0
#define RIGHT_IME 0
#define LEFT_IME 1

//params left and right for the motor speeds
//sets the drive motors to the values of left and right
void chassisSet(int left, int right);

//resets both the left and the right IMEs
void resetIMEs();

bool updateIMEs(int *left, int *right);

//checks to make sure that the robot is moving straight
void gyroCheck();

#endif
