/** @file auto.c
 * @brief File for autonomous code
 *
 * This file should contain the user autonomous() function and any functions related to it.
 *
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"
#define LEFT_DRIVE 2
#define RIGHT_DRIVE 4 //needs to be reversed
#define LEFT_LIFT_MOTOR 3
#define RIGHT_LIFT_MOTOR 6 //needs to be reversed
#define CLAW 7
#define CHAINBAR 5
#define MOBILE_LIFT 8
#define RIGHT_LIFT_POT 1
#define LEFT_LIFT_POT 2


#define LEFT_IME 0
#define RIGHT_IME 2


/*
 * Runs the user autonomous code. This function will be started in its own task with the default
 * priority and stack size whenever the robot is enabled via the Field Management System or the
 * VEX Competition Switch in the autonomous mode. If the robot is disabled or communications is
 * lost, the autonomous task will be stopped by the kernel. Re-enabling the robot will restart
 * the task, not re-start it from where it left off.
 *
 * Code running in the autonomous task cannot access information from the VEX Joystick. However,
 * the autonomous function can be invoked from another task if a VEX Competition Switch is not
 * available, and it can access joystick information if called in this way.
 *
 * The autonomous task may exit, unlike operatorControl() which should never exit. If it does
 * so, the robot will await a switch to another mode or disable/enable cycle.
 */


 void stop();
 bool resetIMEs();
 void chassisSet(int left, int right);

void autonomous() {
  int leftIME=0, rightIME=0;

  //move forward
  chassisSet(127, 127);
  delay(1657); // drive forward time
  
  chassisSet(0, 0);


  int a = 0;

	motorSet(CHAINBAR, -127);
	delay(300);
  motorSet(CHAINBAR, 0);


	liftMove(1000);// lift going up first time

	motorSet(LEFT_LIFT_MOTOR, -20); //hold power while the button is not being pressed
	motorSet(RIGHT_LIFT_MOTOR, -20);
	printf("%s", " the current height of the lift is:");
	printf("%d", abs(analogReadCalibrated(1)));
	delay(1000);

	motorSet(CHAINBAR, -127); // chainbar going down
	delay(400);
	motorSet(CHAINBAR, 0);
	delay(600);
	liftMove(700);

  motorSet(CHAINBAR, -127);
  delay(600);

  motorSet(CHAINBAR, 0);

	motorSet(LEFT_LIFT_MOTOR, -20); //hold power while the button is not being pressed
	motorSet(RIGHT_LIFT_MOTOR, -20);
	printf("%s", " the current height of the lift is:");
	printf("%d", abs(analogReadCalibrated(1)));
	delay(500);

	motorSet(CLAW, -120);
	delay(400);
	motorSet(CLAW, 80);
	delay(750);
	motorSet(CLAW, 0);

	delay(800);


	liftMove(990);
	motorSet(LEFT_LIFT_MOTOR, -20); //hold power while the button is not being pressed
	motorSet(RIGHT_LIFT_MOTOR, -20);
	delay(500);


	motorSet(CHAINBAR, 127);
	delay(150);

	liftMove(200);

  chassisSet(-127, -127);
  delay(1657);
  chassisSet(0, 0);






}
