#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include <API.h>
#define LEFT_MOTOR_PORT_1 4
#define LEFT_MOTOR_PORT_2 7
#define RIGHT_MOTOR_PORT_1 2
#define RIGHT_MOTOR_PORT_2 8
#define GYRO_PORT 1
#define RIGHT_IME 0
#define LEFT_IME 1

typedef enum {
  left,
  right,
  straight,
  backwards
} direction;


//params left and right for the motor speeds
//sets the drive motors to the values of left and right
void chassisSet(int left, int right);

//resets both the left and the right IMEs
void resetIMEs();

bool updateIMEs(int *left, int *right);

//checks to make sure that the robot is moving straight
void gyroCheck(direction direc);

//wait for IMEs to reach a certain value
void waitForIMEs(int value, direction direc);

#endif
