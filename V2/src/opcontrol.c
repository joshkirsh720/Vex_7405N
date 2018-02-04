
#include "main.h"

#ifndef OPCONTORL
#define OPCONTROL

//drive definitions
#define LEFT_MOTOR_PORT_1 5
#define LEFT_MOTOR_PORT_2 7
#define RIGHT_MOTOR_PORT_1 2
#define RIGHT_MOTOR_PORT_2 8

//lift definitions
#define LEFT_LIFT_MOTOR 3  // Left lift motor
#define RIGHT_LIFT_MOTOR 6 //Right lift motor
#define LEFT_LIFT_POT 2 //Leftlift potentiometer
#define RIGHT_LIFT_POT 1 //Right lift potentiometer


#define LIFT_SP


//intake definitions
#define INTAKE_MOTOR 4 //cone intake motor

//chainbar definitions
#define CHAINBAR_MOTOR 9 //chainbar motor
#define CHAINBAR_POT //chainbar potentiometer

//mobile goal definition
#define MOBILE_LIFT_MOTOR 10 //mobile goal

int autoStackBreaker = 0;
int c;
int b;
int autoStackCounter = 0;

int matchStackCounter = 0;

int chainbarHold;




void operatorControl() {
//try {

	encoderReset(encoder); //resetting the encoder values for the encoder
	int a = 3;
	while (1) {

		//START PRE DETERMINED HOLD POWER FOR DIFFERENT PARTS OF THE ROBOT

		printf("%d \n", abs(encoderGet(rightLiftEncoder)));
		printf("%d \n", abs(encoderGet(leftLiftEncoder)));

		//START OF HOLD POWER FOR THE CHAINBAR
		//START OF HOLD POWER FOR THE CHAINBAR


		if (analogRead(4) < 900){
			chainbarHold = -10;

		}else if ((analogRead(4) > 1000) && (analogRead(4) < 1150)){
			chainbarHold = -5;
		}else if (analogRead(4) > 1150){
			chainbarHold = 15;
		}else {
			chainbarHold = 0;
		}
		//END OF HOLD POWER FOR THE CHAINBAR







		//END OF PRINT TESTING


		//START DRIVE CODE

		//get input
		int forwardMotion = joystickGetAnalog(1, 3);
		int sideMotion = joystickGetAnalog(1, 1);


		//if the right joystick is being moved horizontally
		if(abs(sideMotion )>20 || abs(forwardMotion )>20) {
			//turn
			chassisSet(forwardMotion+sideMotion, forwardMotion- sideMotion);
		}

		//if neither joystick is being moved
		else {
			//stop
			chassisSet(0, 0);
		}

		//END DRIVE CODE


		//START OF THE LIFT CODE

		int upSpeedRight = 127;
		int upSpeedLeft = -127;

		int downSpeedRight = -80;
		int downSpeedLeft = 80;

		float p = 13.0f;

		/*
		if (abs(encoderGet(rightLiftEncoder)) < abs((encoderGet(leftLiftEncoder)) -	 5)) {
            upSpeedLeft = -70;
            upSpeedRight = 100;
        } else if (abs(encoderGet(leftLiftEncoder)) < abs((encoderGet(rightLiftEncoder)) - 5)) {
            upSpeedRight = 70;
            upSpeedLeft = -100;
        } else {
            upSpeedRight = 125;
            upSpeedLeft = -125;




        //Tele op Lift controls
        if (joystickGetDigital(1, 8, JOY_UP)) { //lift comes up on button click
            motorSet(LEFT_LIFT_MOTOR, upSpeedLeft);
            motorSet(RIGHT_LIFT_MOTOR, upSpeedRight);
            c = 1;
        } else if (joystickGetDigital(1, 8, JOY_DOWN)) { //lift goes down on button click
            c = 0;
            motorSet(LEFT_LIFT_MOTOR, - upSpeedLeft);
            motorSet(RIGHT_LIFT_MOTOR, - upSpeedRight);
            c = 2;
        } else if (abs(encoderGet(rightLiftEncoder)) < 5){
					motorSet(LEFT_LIFT_MOTOR, 15); //hold power while the button is not being pressed
          motorSet(RIGHT_LIFT_MOTOR, -15);


 				}else {
          motorSet(LEFT_LIFT_MOTOR, 0); //hold power while the button is not being pressed
          motorSet(RIGHT_LIFT_MOTOR, 0);


				*/
				//Tele op Lift controls
        if (joystickGetDigital(1, 8, JOY_UP)) { //lift comes up on button click
            motorSet(LEFT_LIFT_MOTOR, -127 );
            motorSet(RIGHT_LIFT_MOTOR, 127);

        } else if (joystickGetDigital(1, 8, JOY_DOWN)) { //lift goes down on button click

            motorSet(LEFT_LIFT_MOTOR, - upSpeedLeft);

            motorSet(RIGHT_LIFT_MOTOR, - upSpeedRight);

        } else if(encoderGet(leftLiftEncoder) < 15){
					motorSet(LEFT_LIFT_MOTOR, 15);
					motorSet(RIGHT_LIFT_MOTOR, -15);

				}else{
					motorSet(LEFT_LIFT_MOTOR, -15);
					motorSet(RIGHT_LIFT_MOTOR, 15);
				}
		/*

		if (joystickGetDigital(1, 8, JOY_UP)) { //lift comes up on button click
				motorSet(LEFT_LIFT_MOTOR, upSpeedLeft);
				motorSet(RIGHT_LIFT_MOTOR, upSpeedRight);
				c = encoderGet(rightLiftEncoder);
				b = encoderGet(leftLiftEncoder);

		} else if (joystickGetDigital(1, 8, JOY_DOWN)) { //lift goes down on button click
				c = encoderGet(rightLiftEncoder);
				b = encoderGet(leftLiftEncoder);
				motorSet(LEFT_LIFT_MOTOR, downSpeedLeft );
				motorSet(RIGHT_LIFT_MOTOR, downSpeedRight);

		}else {
			if(abs( (b - c))  > 8){
				motorSet(LEFT_LIFT_MOTOR,  ((b - c) * p) );
				motorSet(RIGHT_LIFT_MOTOR, ((b - c) * p));
			}else {
				//motorSet(LEFT_LIFT_MOTOR, -30);
				//motorSet(RIGHT_LIFT_MOTOR, 30);
			}

		}

		*/

		//END OF THE LIFT CODE


		//START OF THE CHAINBAR CODE

		int chainbarUpSpeed = 127;
		int chainbarDownSpeed = -127;
		int chainbarHold = 15;


		if(joystickGetDigital(1, 8, JOY_RIGHT)){
			motorSet(CHAINBAR_MOTOR, chainbarUpSpeed);
		}else if(joystickGetDigital(1 , 8, JOY_LEFT)){
			motorSet(CHAINBAR_MOTOR, chainbarDownSpeed);
		}else {
			motorSet(CHAINBAR_MOTOR, chainbarHold);
		}

		//END OF THE CHAINBAR CODE


		//START OF INTAKE CODE

		int intakeUpSpeed = -120;
		int intakeDownSpeed = 60;

		if(joystickGetDigital(1, 5, JOY_UP)) {
			motorSet(INTAKE_MOTOR, intakeUpSpeed);
		}else if (joystickGetDigital(1, 5, JOY_DOWN)) {
			motorSet(INTAKE_MOTOR, intakeDownSpeed);
		}else {
			motorSet(INTAKE_MOTOR, 0);
		}

		//END OF INTAKE CODE

		//START OF MOBILE GOAL CODE

		int mobileliftUpSpeed = -127;
		int mobileliftDownSpeed = 127;
		int mobileliftHoldSpeed = 0;

		if (joystickGetDigital(1, 6, JOY_UP)){
			motorSet(MOBILE_LIFT_MOTOR, mobileliftUpSpeed);
		}else if (joystickGetDigital(1, 6, JOY_DOWN)){
			motorSet(MOBILE_LIFT_MOTOR, mobileliftDownSpeed);
		}else {
			motorSet(MOBILE_LIFT_MOTOR, mobileliftHoldSpeed);
		}

		//END OF MOBILE GOAL CODE


		//START OF AUTO STACK CODE



		if(joystickGetDigital(1, 7, JOY_LEFT)){
			autoStackBreaker = 1;
		}else if(joystickGetDigital(1, 7 , JOY_RIGHT)){
			autoStackCounter--;
		}


		//END OF AUTO STACK CODE


		delay(10);
	}
/*} catch(...) {
	print("test exception ");
}*/
}

void autoStack() {

			int chainbarHeight = 1300;
			int liftHeight = 0;

			int breaker = 0;


			if (autoStackCounter == 1) {
					liftHeight = 60;
					chainbarHeight = 1380;
			} else if (autoStackCounter == 2) {
					liftHeight = 140;
					chainbarHeight = 1380;
			} else if (autoStackCounter == 3) {
					liftHeight = 270;
					chainbarHeight = 1380;
			} else if (autoStackCounter == 4) {
					liftHeight = 350;
					chainbarHeight = 1360;
			} else if (autoStackCounter == 5) {
					liftHeight = 490;
					chainbarHeight = 1380;
			}



			motorSet(INTAKE_MOTOR, 100); //ORIGINAL INTAKE BLOCK WHICH TAKES THE CODE IN
			delay(700);


			motorSet(INTAKE_MOTOR, 30); //SETS HOLD POWER FOR THE INTAKE


			chainbarMove(chainbarHeight + 900);// BRINGS THE CHAINBAR TO THE pre height
			//chainbarHoldSet(chainbarHeight + 900);

			if(autoStackCounter > 0){

				liftMove(liftHeight);
				motorSet(LEFT_LIFT_MOTOR, -25);
				motorSet(RIGHT_LIFT_MOTOR, 25);

			}

			chainbarMove(chainbarHeight );// BRINGS THE CHAINBAR TO THE pre height
			//chainbarHoldSet(chainbarHeight );

			delay(150);



			motorSet(INTAKE_MOTOR, -60);
			delay(500);
			motorSet(INTAKE_MOTOR, 0);

			delay(200);


			chainbarMove(2600);
			//chainbarHoldSet(2600);

			if(autoStackCounter > 0 ){
				liftMove(10);
				motorSet(LEFT_LIFT_MOTOR,  0); //hold power while the button is not being pressed
				motorSet(RIGHT_LIFT_MOTOR, 0);
			}




}


void matchStack() {

		while(autoStackBreaker == 0){

			int chainbarHeight = 1300;
			int liftHeight = 0;

			int breaker = 0;


			if (matchStackCounter == 1) {
					liftHeight = 0;
					chainbarHeight = 1360;
			} else if (matchStackCounter == 2) {
					liftHeight = 300;
					chainbarHeight = 1380;
			} else if (matchStackCounter == 3) {
					liftHeight = 300;
					chainbarHeight = 1390;
			} else if (matchStackCounter == 4) {
					liftHeight = 130;
					chainbarHeight = 1410;
			} else if (matchStackCounter == 5) {
					liftHeight = 180;
					chainbarHeight = 1410;
			}

			if(matchStackCounter == 0){
				liftMove(100);
				motorSet(LEFT_LIFT_MOTOR, -25);
				motorSet(RIGHT_LIFT_MOTOR, 25);

				chainbarMove(1700);
				chainbarHoldSet(1800);

			}






			motorSet(INTAKE_MOTOR, 100); //ORIGINAL INTAKE BLOCK WHICH TAKES THE CODE IN
			delay(700);



			motorSet(INTAKE_MOTOR, 30); //SETS HOLD POWER FOR THE INTAKE

			if(matchStackCounter > 1){

				liftMove(liftHeight);
				motorSet(LEFT_LIFT_MOTOR, -25);
				motorSet(RIGHT_LIFT_MOTOR, 25);

			}

			chainbarMove(chainbarHeight );// BRINGS THE CHAINBAR TO THE pre height
			chainbarHoldSet(chainbarHeight );

			delay(150);


			liftMove(50);
			motorSet(LEFT_LIFT_MOTOR, -25);
			motorSet(RIGHT_LIFT_MOTOR, 25);





			motorSet(INTAKE_MOTOR, -60);
			delay(500);
			motorSet(INTAKE_MOTOR, 0);

			delay(200);

			chainbarMove(800);
			chainbarHoldSet(800);


				liftMove(150);
				motorSet(LEFT_LIFT_MOTOR,  -40); //hold power while the button is not being pressed
				motorSet(RIGHT_LIFT_MOTOR, 40);


		}



}
#endif
