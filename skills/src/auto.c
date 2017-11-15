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
#define MOBILE_LIFT 8 //negative is up
#define RIGHT_LIFT_POT 1
#define LEFT_LIFT_POT 2
#define CHAINBAR_POT 3

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

void chassisSet(int left, int right);
void liftSet(int left, int right);
void stop();
bool resetIMEs();

void autonomous() {

  motorSet(CLAW, 30);

  int leftIME=0, rightIME=0;

  printf("%s", "reseting IMEs before moving forward: ");
  printf("%s", resetIMEs() + "");
  printf("%s", "\n");

  //move forward
  chassisSet(127, 127);
  while(leftIME <= 2050 && rightIME >= -2050) { //goes until the wheels have rotated a certain amount
    imeGet(LEFT_IME, &leftIME); //updates the value of the IME variables
    imeGet(RIGHT_IME, &rightIME);
  }
  stop();

  //pick up mobile goal
  motorSet(MOBILE_LIFT, -127);
  motorSet(MOBILE_LIFT, -30);

  //place cone on top of goal
        //lift lift
        //move chainbar down to a vertical position
        //open claw

  //turn 180 to the right
  printf("%s", "reseting IMEs before turning around: ");
  printf("%s", resetIMEs() + "");
  printf("%s", "\n");
  leftIME=0;rightIME=0;

  chassisSet(127, -127);
  while(leftIME <= 1400 && rightIME <= 1400) {
    imeGet(LEFT_IME, &leftIME);
    imeGet(RIGHT_IME, &rightIME);
  }
  stop();

  //move to 10 point zone
  printf("%s", "reseting IMEs before moving to 10 point zone: ");
  printf("%s", resetIMEs() + "");
  printf("%s", "\n");
  leftIME=0;rightIME=0;

  chassisSet(127, 127);
  while(leftIME <= 2150 && rightIME >= -2150) {
    imeGet(LEFT_IME, &leftIME);
    imeGet(RIGHT_IME, &rightIME);
  }
  stop();

  //drop mobile goal
  motorSet(MOBILE_LIFT, 10);
  delay(500);
  motorSet(MOBILE_LIFT, 0);

  //back up
  chassisSet(-127, -127);
  delay(750);
  stop();
}




void chassisSet(int left, int right) {
  motorSet(LEFT_DRIVE, left);
  motorSet(RIGHT_DRIVE, -right);
}
void liftSet(int left, int right) {
  motorSet(LEFT_LIFT_MOTOR, left);
  motorSet(RIGHT_LIFT_MOTOR, -right);
}
void stop() {
  chassisSet(0, 0);
}
bool resetIMEs() {
  return imeReset(LEFT_IME) && imeReset(RIGHT_IME);
}
