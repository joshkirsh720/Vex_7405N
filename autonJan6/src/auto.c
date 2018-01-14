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
void auton1(bool blueTeam);

void autonomous() {

  gyroReset(gyro);
  imeReset(0);
  imeReset(1);

  auton = 1;

  if(auton == 1) {
    auton1(true);
  }
  else if(auton == 2) {
    auton1(false);
  }
  //...continue with more autonomous functions when more are written
}

void auton1(bool blueTeam) {
  //stop all motors
  chassisSet(0,0);
  liftSet(0,0);
  mobileLiftSet(0);

  //move mobile goal lift down
  mobileLiftSet(127);
  //start moving
  chassisSet(127,127);

  delay(700);
  //stop mobile goal lift movement but keep driving forward
  mobileLiftSet(0);

  delay(250);
  chassisSet(0, 0);

  chassisSet(127, 127);
  //stop forward movement after time
  delay(700);
  chassisSet(0, 0);

  //move mobile goal lift up
  mobileLiftSet(-127);
  delay(1000);
  mobileLiftSet(0);


  //move backwards
  chassisSet(-127, -127);
  delay(1750);
  chassisSet(0, 0);

  //turn right if blue team left if red team
  blueTeam ? chassisSet(127, -127) : chassisSet(-127, 127);
  delay(800);
  //quickly reverse motors to stop overrotation
  blueTeam ? chassisSet(-127, 127) : chassisSet(127, -127);
  chassisSet(0, 0);


  //move forward
  chassisSet(127, 127);
  delay(550);
  chassisSet(0, 0);

  //turn to face goal
  blueTeam ? chassisSet(127, -127) : chassisSet(-127, 127);
  delay(650);
  chassisSet(0, 0);

  //lift needs to move down for 300 ms
  //drive needs to move forward for 1250 ms

  //move forward into 20 pt zone
  chassisSet(127, 127);

  delay(200);
  mobileLiftSet(127);

  delay(250);
  mobileLiftSet(0);

  delay(700);
  chassisSet(0, 0);

  //back up
  chassisSet(-127, -127);
  delay(1000);
  chassisSet(0, 0);
}
