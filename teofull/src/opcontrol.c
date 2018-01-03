/** @file opcontrol.c
 * @brief File for operator control code
 *
 * This file should contain the user operatorControl() function and any functions related to it.
 *
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"

#define LEFT_DRIVE 5
#define RIGHT_DRIVE 2 //needs to be reversed
#define LEFT_LIFT_MOTOR 3
#define RIGHT_LIFT_MOTOR 6 //needs to be reversed
#define INTAKE_MOTOR 4
#define CHAINBAR 9
#define MOBILE_LIFT 10
#define RIGHT_LIFT_POT 1
#define LEFT_LIFT_POT 2

/*
 * Runs the user operator control code. This function will be started in its own task with the
 * default priority and stack size whenever the robot is enabled via the Field Management System
 * or the VEX Competition Switch in the operator control mode. If the robot is disabled or
 * communications is lost, the operator control task will be stopped by the kernel. Re-enabling
 * the robot will restart the task, not resume it from where it left off.
 *
 * If no VEX Competition Switch or Field Management system is plugged in, the VEX Cortex will
 * run the operator control task. Be warned that this will also occur if the VEX Cortex is
 * tethered directly to a computer via the USB A to A cable without any VEX Joystick attached.
 *
 * Code running in this task can take almost any action, as the VEX Joystick is available and
 * the scheduler is operational. However, proper use of delay() or taskDelayUntil() is highly
 * recommended to give other tasks (including system tasks such as updating LCDs) time to run.
 *
 * This task should never exit; it should end with some kind of infinite loop, even if empty.
 */

int autoCount = 0;

int chainbarBreak = 0;

int chainbarHold = 0;

int chainbar = 0;

int c = 0;

int b = 0;

int autoStackBreaker = 0;
int autoStackCounter = 0;

int chainbarBreaker = 0;
int matchLoadCounter = 0;


void operatorControl() {

    encoderReset(encoder);

    while (1) {

      //get input
  		int forwardMotion = joystickGetAnalog(1, 3);
  		int sideMotion = joystickGetAnalog(1, 1);

  		//START DRIVE CODE
  		//if the right joystick is being moved horizontally
  		if(sideMotion != 0) {
  			//turn
  			chassisSet(sideMotion, -sideMotion);
  		}
  		//if the left joystick is being moved vertically
  		else if(forwardMotion != 0) {
  			//move forwards/backwards
  			chassisSet(forwardMotion, forwardMotion);
  		}
  		//if neither joystick is being moved
  		else {
  			//stop
  			chassisSet(0, 0);
  		}
  		//END DRIVE CODE

      printf("%d \n", analogRead(4));








        //base speed for the right side of the lift
        int upSpeedRight = 125;

        //base speed for the left side of the lift
        int upSpeedLeft = -125;

        //get petentiometer values from the right lift potentiometer
        int rLiftPot = abs(analogReadCalibrated(1));

        //get potentiomemter values from the left lift potentiometer
        int lLiftPot = abs(analogReadCalibrated(2));

        printf("%d \n",analogReadCalibrated(lLiftPot));
        printf("%d \n",analogReadCalibrated(rLiftPot));
        printf("%s \n","-----------------------------------------------------");





        //Syncing lift speeds for left and right side using potentiometers
        if (rLiftPot < (lLiftPot + 300)) {
            upSpeedLeft = -60;
            upSpeedRight = 125;
        } else if (lLiftPot < (rLiftPot - 250)) {
            upSpeedRight = 60;
            upSpeedLeft = -125;
        } else {
            upSpeedRight = 125;
            upSpeedLeft = -125;
        }

        //Tele op Lift controls
        if (joystickGetDigital(1, 8, JOY_UP)) { //lift comes up on button click
            motorSet(LEFT_LIFT_MOTOR, upSpeedLeft);
            motorSet(RIGHT_LIFT_MOTOR, upSpeedRight);
            c = 1;
        } else if (joystickGetDigital(1, 8, JOY_DOWN)) { //lift goes down on button click
            c = 0;
            motorSet(LEFT_LIFT_MOTOR, 25);
            motorSet(RIGHT_LIFT_MOTOR, -25);
            c = 2;
        } else if (c == 1) {
            motorSet(LEFT_LIFT_MOTOR, -20); //hold power while the button is not being pressed
            motorSet(RIGHT_LIFT_MOTOR, 20);

        } else if (c == 2) {
            motorSet(LEFT_LIFT_MOTOR, -20); //hold power while the button is not being pressed
            motorSet(RIGHT_LIFT_MOTOR, 20);

        } else {
          motorSet(LEFT_LIFT_MOTOR, 20); //hold power while the button is not being pressed
          motorSet(RIGHT_LIFT_MOTOR, -20);

        }


        //chainbar tele op control

        if(joystickGetDigital(1, 8, JOY_RIGHT)){
          motorSet(CHAINBAR, 127);
        }else if(joystickGetDigital(1,8, JOY_LEFT)){
          motorSet(CHAINBAR, -127);
        }else {
          motorSet(CHAINBAR, 15);
        }



        //end of chainbar code




        //Start of Intake code
        if (joystickGetDigital(1, 7, JOY_UP)) {
            motorSet(INTAKE_MOTOR, -127);
        } else if (joystickGetDigital(1, 7, JOY_DOWN)) {
            motorSet(INTAKE_MOTOR, 50);
        } else {
            motorSet(INTAKE_MOTOR, 0);
        }

        //end of intake code



        //start of mobile goal code

        if (joystickGetDigital(1, 7, JOY_RIGHT)) {
            motorSet(MOBILE_LIFT, -127);
        } else if (joystickGetDigital(1, 7, JOY_LEFT)) {
            motorSet(MOBILE_LIFT, 127);
        } else {
            motorSet(10, 0);
        }

        //end of mobile goal code




        //autoStack joyStick controls



        //autoStack joyStick controls
        if (joystickGetDigital(1, 6, JOY_UP)) {
            printf("%d \n", autoStackCounter);
            matchLoadCounter++;
        }else if (joystickGetDigital(1, 6, JOY_DOWN)){
            matchLoadCounter = 0;
        }



        delay(20);
    }
}





//function that lifts the chainbar to a certain height that is indicated by potentiometer values.
void chainbarMove(int position) { //takes in the desired position of the chainbar
    if(analogRead(4) > position){
      while(analogRead(4) > position) {
        motorSet(CHAINBAR, 80);
      }
    } else if (analogRead(4) < position){
        while(analogRead(4) < position) {
          motorSet(CHAINBAR, -80);
        }
      }

      motorSet(CHAINBAR, 0);
}


//intake function for the auton

void intakeMove(int direction) {
    if (direction == 1) {
        motorSet(INTAKE_MOTOR, 127);
    } else if (direction == -1) {
        motorSet(INTAKE_MOTOR, -127);
    } else if (direction == 0) {
        motorSet(INTAKE_MOTOR, 15);
    }
}

//

//function that lifts the lift to a certain height that is indicated by potentiometer values.
void liftMove(int position) {
    int c = 1;


    //base speed for the right side of the lift
    int upSpeedRight = 125;

    //base speed for the left side of the lift

    int upSpeedLeft = -125;

    //get petentiometer values from the right lift potentiometer
    int rLiftPot = abs(analogReadCalibrated(1));

    //get potentiomemter values from the left lift potentiometer
    int lLiftPot = abs(analogReadCalibrated(2));

    if (rLiftPot < (lLiftPot - 100)) {
        upSpeedLeft = -40;
        upSpeedRight = 70;
    } else if (lLiftPot < (rLiftPot - 100)){
        upSpeedRight = 40;
        upSpeedLeft = -70;
    } else {
        upSpeedRight = 70;
        upSpeedLeft = -70;
    }



    if(analogReadCalibrated(2) < position){
      while(analogReadCalibrated(2) < position){
        motorSet(LEFT_LIFT_MOTOR, -80);
        motorSet(RIGHT_LIFT_MOTOR, 90);

      }


    }else if(analogReadCalibrated(2) > position){
      while(analogReadCalibrated(2) > position){
        motorSet(LEFT_LIFT_MOTOR, 95);
        motorSet(RIGHT_LIFT_MOTOR, -90);

      }

    }

    motorSet(LEFT_LIFT_MOTOR, 0); //hold power while the button is not being pressed
    motorSet(RIGHT_LIFT_MOTOR, 0);
}


//autoStack function
void autoStack() {

        int liftHeight = 0;
        int chainbarHeight = 1400;

        if (autoStackCounter == 1) {
            liftHeight = 150;
            chainbarHeight = 1360;
        } else if (autoStackCounter == 2) {
            liftHeight = 350;
            chainbarHeight = 1400;
        } else if (autoStackCounter == 3) {
            liftHeight = 500;
            chainbarHeight = 1350;
        } else if (autoStackCounter == 4) {
            liftHeight = 800;
            chainbarHeight = 1410;
        } else if (autoStackCounter == 5) {
            liftHeight = 950;
            chainbarHeight = 1600;
        } else if (autoStackCounter == 6) {
            liftHeight = 1100;
        }



        motorSet(INTAKE_MOTOR, 60);
        delay(500);
        motorSet(INTAKE_MOTOR, 30);
        printf("%s \n", "intake");
        chainbarMove(2300);

        chainbarMove(chainbarHeight);






}
