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
void auton1(bool blueTeam), initialConeStack(), auton2(bool blueTeam);

void autonomous() {
/*


  printf("Power Level: %d\n", powerLevelMain());

  gyroReset(gyro);
  imeReset(0);

  int auton =  2;

  if(auton == 1) {
    auton1(true);
  }
  else if(auton == 2) {
    auton1(false);
  }
  else if(auton == 3){
    auton2(true);
  }
  else if(auton == 4) {
    auton2(false);
  }
  //...continue with more autonomous functions when more are written

  imeShutdown();
*/
}

void initialConeStack() {

  chainbarSet(-127);
  delay(700);
  chainbarSet(127);
  delay(600);
  chainbarSet(0);

  liftSet(-100, -100);
  delay(200);
  intakeSet(-50);
  delay(200);
  liftSet(0, 0);
  intakeSet(0);

  delay(200);
}

void auton1(bool blueTeam) {


  const int imeValue = 1424; //4704

  imeReset(0);

  intakeSet(15);
  chassisSet(0, 0);
  liftSet(100, 100);
  mobileLiftSet(127);
  delay(300); //give time for lift to go up
  liftSet(0, 0);

  delay(300);

  gyroReset(gyro);

  //start moving forward
  chassisSet(127, 127);

  if(!imeWait(imeValue, true)) return;

  chassisSet(0, 0);

  //pick up mobile goal
  mobileLiftSet(-127);
  delay(1400);
  mobileLiftSet(0);


  initialConeStack();

  imeReset(0);
  //second cone
  chassisSet(127, 127);
  imeWait(200, false);
  chassisSet(0, 0);

  chainbarSet(-127);
  liftSet(-100, -100);
  delay(400);
  liftSet(-30, -30);
  intakeSet(100);
  delay(500);
  intakeSet(15);

  //cone is picked up
  chainbarSet(127);
  delay(900);
  liftSet(100, 100);
  delay(400);
  liftSet(0, 0);
  chainbarSet(0);

  liftSet(-100, -100);
  delay(200);
  liftSet(0, 0);

  intakeSet(-100);
  delay(500);
  intakeSet(0);

  //move backwards
  imeReset(0);
  chassisSet(-127, -127);
  imeWait(imeValue + 100 , false);
  chassisSet(0, 0);

  delay(200);


  int rotationSpeed = 85;



/*
//BEGIN TEMP ADDITION
  //turn
  gyroReset(gyro);
  blueTeam ? chassisSet(rotationSpeed, -rotationSpeed) : chassisSet(-rotationSpeed, rotationSpeed);
  while(abs(gyroGet(gyro)) < 180);
  blueTeam ? chassisSet(-rotationSpeed, rotationSpeed) : chassisSet(rotationSpeed, -rotationSpeed);
  chassisSet(0, 0);

  chassisSet(127, 127);
  delay(300);
  chassisSet(0, 0);

  mobileLiftSet(127);
  delay(1400);
  mobileLiftSet(0);

  chassisSet(-127, -127);
  delay(500);
  chassisSet(0, 0);
//END TEMP ADDITION
*/




  //turn
  gyroReset(gyro);
  blueTeam ? chassisSet(rotationSpeed, -rotationSpeed) : chassisSet(-rotationSpeed, rotationSpeed);
  while(abs(gyroGet(gyro)) < 128);
  blueTeam ? chassisSet(-rotationSpeed, rotationSpeed) : chassisSet(rotationSpeed, -rotationSpeed);
  chassisSet(0, 0);

  imeReset(0);
  //move forward
  chassisSet(127, 127);
  imeWait(600, false);
  chassisSet(0, 0);

  //turn to face goal
  gyroReset(gyro);
  blueTeam ? chassisSet(rotationSpeed, -rotationSpeed) : chassisSet(-rotationSpeed, rotationSpeed);
  while(abs(gyroGet(gyro)) < 80);
  blueTeam ? chassisSet(-rotationSpeed, rotationSpeed) : chassisSet(rotationSpeed, -rotationSpeed);
  chassisSet(0, 0);

  //drop off mobile goal
  dropMobileGoal(false);

  //if lift gets stuck
  mobileLiftSet(-127);
  delay(600);
  mobileLiftSet(0);

  chassisSet(-127, -127);
  delay(500);
  chassisSet(0, 0);

}

void auton2(bool blueTeam) {


}
