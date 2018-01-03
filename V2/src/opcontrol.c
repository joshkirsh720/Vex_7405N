
#include "main.h"

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

int autoStackCounter = 0;

int chainbarHold;




void operatorControl() {

	  encoderReset(encoder); //resetting the encoder values for the encoder

	while (1) {

		//START PRE DETERMINED HOLD POWER FOR DIFFERENT PARTS OF THE ROBOT


		//START OF HOLD POWER FOR THE CHAINBAR
		//START OF HOLD POWER FOR THE CHAINBAR


		if (analogRead(4) < 1200){
			chainbarHold = -15;

		}else if (analogRead(4) > 1300){
			chainbarHold = 20;
		}else {
			chainbarHold = 0;
		}
		//END OF HOLD POWER FOR THE CHAINBAR




		//END PRE DETERMINED HOLD POWER FOR DIFFERENT PARTS OF THE ROBOT


		//ANY PRINT TESTING SHOULD BE PUT IN HERE
		printf("%d \n", analogRead(4));

		//END OF PRINT TESTING


		//START DRIVE CODE

		//get input
		int forwardMotion = joystickGetAnalog(1, 3);
		int sideMotion = joystickGetAnalog(1, 1);


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


		//START OF THE LIFT CODE

		int upSpeedRight = 100;
		int upSpeedLeft = 100;

		int rightLiftPot = abs(analogReadCalibrated(1));
		int leftLiftPot = abs(analogReadCalibrated(2));


		if ((rightLiftPot < (leftLiftPot - 150)) && (rightLiftPot > 100)) {
				upSpeedLeft = -70;
				upSpeedRight = 125;
		} else if ((leftLiftPot < (rightLiftPot + 300)) && (rightLiftPot > 100) ){
				upSpeedRight = 40;
				upSpeedLeft = -125;
		} else {
				upSpeedRight = 100;
				upSpeedLeft = -100;
		}


		if (joystickGetDigital(1, 8, JOY_UP)) { //lift comes up on button click
				motorSet(LEFT_LIFT_MOTOR, upSpeedLeft);
				motorSet(RIGHT_LIFT_MOTOR, upSpeedRight);
				c = 1;
		} else if (joystickGetDigital(1, 8, JOY_DOWN)) { //lift goes down on button click
				c = 0;
				motorSet(LEFT_LIFT_MOTOR, 25);
				motorSet(RIGHT_LIFT_MOTOR, -25);
				c = 2;
		} else {
			motorSet(LEFT_LIFT_MOTOR, 0);
			motorSet(RIGHT_LIFT_MOTOR, 0);

		}


		//END OF THE LIFT CODE


		//START OF THE CHAINBAR CODE

		int chainbarUpSpeed = 127;
		int chainbarDownSpeed = -127;

		if(joystickGetDigital(1, 8, JOY_RIGHT)){
			motorSet(CHAINBAR_MOTOR, chainbarUpSpeed);
		}else if(joystickGetDigital(1 , 8, JOY_LEFT)){
			motorSet(CHAINBAR_MOTOR, chainbarDownSpeed);
		}else {
			motorSet(CHAINBAR_MOTOR, chainbarHold);
		}

		//END OF THE CHAINBAR CODE


		//START OF INTAKE CODE

		int intakeUpSpeed = 127;
		int intakeDownSpeed = -50;

		if(joystickGetDigital(1, 7, JOY_UP)) {
			motorSet(INTAKE_MOTOR, intakeUpSpeed);
		}else if (joystickGetDigital(1, 7, JOY_DOWN)) {
			motorSet(INTAKE_MOTOR, intakeDownSpeed);
		}else {
			motorSet(INTAKE_MOTOR, 0);
		}

		//END OF INTAKE CODE

		//START OF MOBILE GOAL CODE

		int mobileliftUpSpeed = -127;
		int mobileliftDownSpeed = 127;
		int mobileliftHoldSpeed = 0;

		if (joystickGetDigital(1, 7, JOY_RIGHT)){
			motorSet(MOBILE_LIFT_MOTOR, mobileliftUpSpeed);
		}else if (joystickGetDigital(1, 7, JOY_LEFT)){
			motorSet(MOBILE_LIFT_MOTOR, mobileliftDownSpeed);
		}else {
			motorSet(MOBILE_LIFT_MOTOR, mobileliftHoldSpeed);
		}

		//END OF MOBILE GOAL CODE


		//START OF AUTO STACK CODE

		if (joystickGetDigital(1, 5, JOY_UP)) {
				autoStack();
				printf("%d \n", autoStackCounter);
				c = 1;
				autoStackCounter++;

		}else if (joystickGetDigital(1, 5, JOY_DOWN)){
				autoStackCounter = 0;
		}


		//END OF AUTO STACK CODE

		delay(20);
	}
}

void autoStack() {

		int chainbarHeight = 1370;


			if (analogRead(4) < 850){
				chainbarHold = -10;

			}else if (analogRead(4) > 1400){
				chainbarHold = 10;
			}else {
				chainbarHold = 5;
			}


		int liftHeight = 0;


		if (autoStackCounter == 1) {
				liftHeight = 100;
				chainbarHeight = 1500;
		} else if (autoStackCounter == 2) {
				liftHeight = 200;
				chainbarHeight = 1500;
		} else if (autoStackCounter == 3) {
				liftHeight = 300;
				chainbarHeight = 1500;
		} else if (autoStackCounter == 4) {
				liftHeight = 400;
				chainbarHeight = 1500;

		} else if (autoStackCounter == 5) {
				liftHeight = 750;
		} else if (autoStackCounter == 6) {
				liftHeight = 950;
		}



		motorSet(INTAKE_MOTOR, 60);
		delay(500);
		motorSet(INTAKE_MOTOR, 30);
		printf("%s \n", "intake");

		chainbarMove(2300);

		motorSet(CHAINBAR_MOTOR,chainbarHold);

		if(autoStackCounter > 0){
			liftMove(100);
			motorSet(LEFT_LIFT_MOTOR, -20); //hold power while the button is not being pressed
			motorSet(RIGHT_LIFT_MOTOR, 20);

		}

		chainbarMove(chainbarHeight);
		motorSet(CHAINBAR_MOTOR,chainbarHold);

		if(autoStackCounter > 0){
			liftMove(liftHeight);
			motorSet(LEFT_LIFT_MOTOR, -20); //hold power while the button is not being pressed
			motorSet(RIGHT_LIFT_MOTOR, 20);
			liftMove(liftHeight -20);
			motorSet(LEFT_LIFT_MOTOR, -20); //hold power while the button is not being pressede4
			motorSet(RIGHT_LIFT_MOTOR, 20);


		}

		delay(100);
		motorSet(INTAKE_MOTOR, -60);

		delay(400);
		motorSet(INTAKE_MOTOR, 0);



		chainbarMove(1700);






}
