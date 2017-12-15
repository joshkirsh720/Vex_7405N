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
void operatorControl() {

	direction liftDirec;
	int imeLeft, imeRight;

	while (1) {


		//IME GET
		if(joystickGetDigital(1,8,JOY_LEFT)) {
			resetIMEs();
			gyroReset(gyro);
		}


		imeGet(RIGHT_IME, &imeLeft);
		imeGet(LEFT_IME, &imeRight);
		printf("Left IME: %d\n", imeLeft);
		printf("Right IME: %d\n", imeRight);
		printf("Gyro Value: %d\n\n", gyroGet(gyro));




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

		//START LIFT CODE
		if(joystickGetDigital(1, 8, JOY_UP)) {
			liftDirec = up;
			liftSet(127, 127);
		}
		else if(joystickGetDigital(1, 8, JOY_DOWN)) {
			liftDirec = down;
			liftSet(-127, -127);
		}
		else {
			liftDirec = still;
			liftSet(20, 20);
		}

		//adjust for potentiometers

		//END LIFT CODE

		//START MOBILE GOAL CODE
		if(joystickGetDigital(1, 7, JOY_DOWN)) {
			mobileSet(-127);
		}
		else if(joystickGetDigital(1, 7, JOY_UP)) {
			mobileSet(127);
		}
		else {
			mobileSet(0);
		}
		//END MOBILE GOAL CODE


		delay(20);
	}
}
