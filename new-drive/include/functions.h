#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include <API.h>
#define LEFT_MOTOR_PORT_1 5
#define LEFT_MOTOR_PORT_2 7
#define RIGHT_MOTOR_PORT_1 2
#define RIGHT_MOTOR_PORT_2 8
#define MOBILE_LIFT 4
#define GYRO_PORT 3
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

//waits for the gyro to reach a certain value
//only to be used when turning
void waitForGyro(int degrees, direction direc);

//turns then adjusts so that the turn is accurate
void accurateTurn(int degrees, direction startingDirec);

#endif
