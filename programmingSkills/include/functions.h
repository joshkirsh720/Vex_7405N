#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include <API.h>

#define LEFT_MOTOR_PORT_1 5
#define LEFT_MOTOR_PORT_2 7
#define RIGHT_MOTOR_PORT_1 2
#define RIGHT_MOTOR_PORT_2 8
#define MOBILE_LIFT 10
#define GYRO_PORT 3
#define RIGHT_IME 0
#define LEFT_IME 1
#define RIGHT_POTEN 1
#define LEFT_POTEN 2
#define LEFT_LIFT_MOTOR 3
#define RIGHT_LIFT_MOTOR 6
#define CHAINBAR 9
#define CHAINBAR_POTEN 4
#define INTAKE 4

int auton;
Gyro gyro;

void chassisSet(int left, int right);
void liftSet(int left, int right);
void mobileLiftSet(int val);
void chainbarSet(int speed);
void intakeSet(int speed);
//moves forwards until the IMEs hit a certain value
//PRECONDITION: val >= 0
void imeWait(int val);

//corrects forward motion using the gyro
void gyroCorrect();

void chainbarHoldSet(int position);

//turn with the gyro
void gyroWait(int val);

//drop mobile goal in 20 pt zone correctly
void dropMobileGoal();
#endif
