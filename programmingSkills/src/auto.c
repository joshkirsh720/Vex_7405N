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
void autonomous() {

  //downward lift hold power
  liftSet(-30, -30);

  //START ON BLUE SIDE LEFT MOBILE GOAL

  //stop all motors
  chassisSet(0,0);
  liftSet(0,0);
  mobileLiftSet(0);

  //move forward to get red mobile goal
  chassisSet(127, 127);
  mobileLiftSet(127);
  delay(700);
  mobileLiftSet(0);
  //stop mobile goal but keep moving, then stop chassis
  delay(550);
  chassisSet(0, 0);


  //lift up mobile goal
  mobileLiftSet(-127);
  delay(700);
  mobileLiftSet(0);

  //back up
  chassisSet(-127, -127);
  delay(1000);

  //turn right
  chassisSet(127, -127);
  delay(550);
  chassisSet(-127, 127);
  chassisSet(0, 0);

  //move forward
  chassisSet(127, 127);
  delay(375);
  chassisSet(0, 0);

  //turn to face 20 pt zone
  chassisSet(127, -127);
  delay(450);
  chassisSet(0, 0);

  //move back an inch
  chassisSet(-127, -127);
  delay(100);
  chassisSet(0, 0);

  dropMobileGoal();

  //back up
  chassisSet(-127, -127);
  delay(700);
  chassisSet(0, 0);


  //FIRST MOBILE GOAL SCORED, SECOND ONE NOW
  //turn right
  chassisSet(127, -127);
  delay(650);
  chassisSet(-127, 127);
  chassisSet(0, 0);

  //move forward
  chassisSet(127, 127);
  delay(450);
  chassisSet(0, 0);

  //turn right
  chassisSet(127, -127);
  gyro == NULL ? delay(600) : gyroWait(0);
  chassisSet(-127, 127);
  chassisSet(0, 0);

  //move forward to grab mobile goal
  //also move mobile goal lift down while moving
  chassisSet(127, 127);
  mobileLiftSet(127);
  delay(700);
  mobileLiftSet(0);
  //stop mobile goal but keep moving, then stop chassis
  delay(1700);
  chassisSet(0, 0);

  //move mobile goal up
  mobileLiftSet(-127);
  delay(700);
  mobileLiftSet(0);

  //turn right
  chassisSet(127, -127);
  delay(600);
  chassisSet(-127, 127);
  chassisSet(0, 0);

  //move forward
  chassisSet(127, 127);
  delay(450);
  chassisSet(0, 0);

  //turn left to face 20 pt zone
  chassisSet(-127, 127);
  delay(650);
  chassisSet(0, 0);

  //move back an inch
  chassisSet(-127, -127);
  delay(100);
  chassisSet(0, 0);

  dropMobileGoal();

  //back up
  chassisSet(-127, 127);
  delay(600);
  chassisSet(0, 0);
}
