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
#define _ 0
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
  gyroReset(gyro);
  imeReset(0);
  imeReset(1);

  bool useTime = true;

  //move mobile goal down
  mobileLiftSet(127);
  delay(1000);
  mobileLiftSet(0);

  //move forwards
  chassisSet(127, 127);
  useTime ? delay(1900) : imeWait(1700);
  chassisSet(0, 0);

  //move mobile goal up
  mobileLiftSet(-127);
  delay(1000);
  mobileLiftSet(0);

  //move backwards
  chassisSet(-127, -127);
  useTime ? delay(1500) : imeWait(-850);
  chassisSet(0, 0);

  //turn to the right
  chassisSet(127, -127);
  useTime ? delay(800) : gyroTurn(-135);
  chassisSet(-127, 127);
  chassisSet(0, 0);


  //FOLLOWING CODE HAS DUMMY VALUES THAT SHOULD BE CHANGED
  //move forward
  chassisSet(127, 127);
  useTime ? delay(500) : imeWait(_);
  chassisSet(0, 0);

  //turn to face goal
  chassisSet(127, -127);
  useTime ? delay(400) : gyroTurn(_);
  chassisSet(0, 0);

}
