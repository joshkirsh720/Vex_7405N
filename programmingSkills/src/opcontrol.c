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
	while (1) {
		int forward, sideways;
		forward = joystickGetAnalog(1, 3);
		sideways = joystickGetAnalog(1, 1);

		if(sideways != 0) {
			chassisSet(sideways, -sideways);
		}
		else if(forward != 0) {
			chassisSet(forward, forward);
		}
		else {
			chassisSet(0, 0);
		}

		//lift code
		if(joystickGetDigital(1, 8, JOY_UP)) {
			liftSet(127, 127);
		}
		else if(joystickGetDigital(1, 8, JOY_DOWN)) {
			liftSet(-127, -127);
		}
		else {
			liftSet(0, 0);;
		}

		//mobile goal
		if(joystickGetDigital(1, 6, JOY_UP)) {
			mobileLiftSet(127);
		}
		else if(joystickGetDigital(1, 6, JOY_DOWN)) {
			mobileLiftSet(-127);
		}
		else {
			mobileLiftSet(0);
		}

		//chainbar
		if(joystickGetDigital(1, 5, JOY_UP)) {
			chainbarSet(127);
		}
		else if(joystickGetDigital(1, 5, JOY_DOWN)) {
			chainbarSet(-127);
		}
		else {
			chainbarHoldSet(analogReadCalibrated(CHAINBAR_POTEN));
		}

		//intake
		if(joystickGetDigital(1, 7, JOY_UP)) {
			intakeSet(127);
		}
		else if(joystickGetDigital(1, 7, JOY_DOWN)) {
			intakeSet(-127);
		}
		else {
			intakeSet(0);
		}



		delay(20);
	}
}
