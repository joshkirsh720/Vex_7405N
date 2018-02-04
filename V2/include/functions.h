#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include <API.h>
#define LEFT_MOTOR_PORT_1 5
#define LEFT_MOTOR_PORT_2 7
#define RIGHT_MOTOR_PORT_1 2
#define RIGHT_MOTOR_PORT_2 8

//lift definitions
#define LEFT_LIFT_MOTOR 3  // Left lift motor
#define RIGHT_LIFT_MOTOR 6 //Right lift motor
#define LEFT_LIFT_POT 2 //Leftlift potentiometer
#define RIGHT_LIFT_POT 1 //Right lift potentiometer


#define LIFT_SP


//intake definitions
#define INTAKE_MOTOR 4 //cone intake motor

//chainbar definitions
#define CHAINBAR_MOTOR 9 //chainbar motor
#define CHAINBAR_POT //chainbar potentiometer

//mobile goal definition
#define MOBILE_LIFT_MOTOR 10 //mobile goal

#define GYRO 2


typedef enum {
  left,
  right,
  straight,
  backwards,
  up,
  down,
  still
} direction;


//params left and right for the motor speeds
//sets the drive motors to the values of left and right
void chassisSet(int left, int right);

//resets both the left and the right IMEs
void resetIMEs();

bool updateIMEs(int *left, int *right);

//checks to make sure that the robot is moving straight
void gyroCheck(direction direc);

//waits for the gyro to reach a certain value
//only to be used when turning
void waitForGyro(int degrees, direction direc);

//turns then adjusts so that the turn is accurate
void accurateTurn(int degrees, direction startingDirec);

//sets lift
void liftSet(int left, int right);

//sets mobile goal speed
void mobileLiftSet(int speed);

void chainbarHoldSet(int position);

void imeWait(int val, bool moveML);

void gyroCorrect();

void gyroTurn(int val);

void intakeSet(int speed);

void chainbarSet(int speed);

void dropMobileGoal(bool time);


#endif
