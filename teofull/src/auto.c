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

  gyroReset(gyro);
  imeReset(0);
  imeReset(1);

  bool blueTeam = true, useTime = false;
  int speed = 90, degree = 5;

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

  delay(300);
  chassisSet(0, 0);

  // blueTeam ? chassisSet(127, -127) : chassisSet(-127, 127);
  // delay(300);
  // blueTeam ? chassisSet(-127, 127) : chassisSet(127, -127);
  // delay(300);
  // blueTeam ? chassisSet(127, -127) : chassisSet(-127, 127);
  // chassisSet(0,0);

  chassisSet(127, 127);
  //stop forward movement after time
  delay(1000);
  chassisSet(0, 0);

  //move mobile goal lift up
  mobileLiftSet(-127);
  delay(1000);
  mobileLiftSet(0);

  //1360 move value up
  //down is negative for the motor
  /*motorSet(CHAINBAR, -127);
  while(analogRead(CHAINBAR_POTEN) < 1360);
  chainbarHoldSet(1360);
  motorSet(INTAKE, -127);
  delay(500);
  motorSet(INTAKE, 0);
  motorSet(CHAINBAR, 127);
  delay(600);
  motorSet(CHAINBAR, 0);*/


  /*//right is negative left is positive
  if(gyroGet(gyro) < -5) {
    chassisSet(-speed, speed);
    while(gyroGet(gyro) < -5);
    chassisSet(speed, -speed);
    chassisSet(0, 0);
  }
  else if(gyroGet(gyro) > 5) {
    chassisSet(speed, -speed);
    while(gyroGet(gyro) > 5);
    chassisSet(-speed, speed);
    chassisSet(0, 0);
  }*/


  //move backwards
  chassisSet(-127, -127);
  delay(1500);
  chassisSet(0, 0);

  //turn right if blue team left if red team
  blueTeam ? chassisSet(127, -127) : chassisSet(-127, 127);
  delay(800);
  //quickly reverse motors to stop overrotation
  blueTeam ? chassisSet(-127, 127) : chassisSet(127, -127);
  chassisSet(0, 0);


  //move forward
  chassisSet(127, 127);
  delay(600);
  chassisSet(0, 0);

  //turn to face goal
  blueTeam ? chassisSet(127, -127) : chassisSet(-127, 127);
  delay(550);
  chassisSet(0, 0);

  //move forward into 20 pt zone
  chassisSet(127, 127);
  delay(1250);
  chassisSet(0, 0);

  //mobile goal lift down
  mobileLiftSet(127);
  delay(600);
  mobileLiftSet(0);

  //back up
  chassisSet(-127, -127);
  delay(1000);
  chassisSet(0, 0);

}
