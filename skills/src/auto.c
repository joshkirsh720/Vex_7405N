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
#define RIGHT_DRIVE 4 //reversed in chassisSet(int, int)
#define LEFT_LIFT_MOTOR 3
#define RIGHT_LIFT_MOTOR 6 //needs to be reversed
#define CLAW 7
#define CHAINBAR 5
#define MOBILE_LIFT 8
#define RIGHT_LIFT_POT 1
#define LEFT_LIFT_POT 2

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
 void chassisSet(int left, int right);
 void moveForward(int forwardMotion);
 void turn(int sidewaysMotion);
 void stop();
void moveForTime(int timeInMS, int speed);
void turnForTime(int timeInMS, int speed);

void autonomous() {
  //turn to face mobile goal
  //left turn is negative, right turn is positive


  //move forward to mobile goal


  //pick up mobile goal



  //place preload on mobile goal


  //turn 180


  //move forward to right before 10 point zone


  //place mobile goal with stacked cone in 10 point zone

}




void chassisSet(int left, int right) {
	motorSet(LEFT_DRIVE, left);

	//right is opposite because that's how we built our robot
	motorSet(RIGHT_DRIVE, -right);
}

void moveForward(int forwardMotion) {
  chassisSet(forwardMotion, forwardMotion);
}
void turn(int sidewaysMotion) {
  chassisSet(sidewaysMotion, -sidewaysMotion);
}
void stop() {
  chassisSet(0,0);
}

void moveForTime(int timeInMS, int speed) {
  moveForward(speed);
  delay(timeInMS);
  stop();
}
void turnForTime(int timeInMS, int speed) {
  turn(speed);
  delay(timeInMS);
  stop();
}
