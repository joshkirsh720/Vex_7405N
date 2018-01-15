#include "functions.h"


//motor sets
void chassisSet(int left, int right) {
  motorSet(LEFT_MOTOR_PORT_1, left);
  motorSet(LEFT_MOTOR_PORT_2, left);
  motorSet(RIGHT_MOTOR_PORT_1, -right);
  motorSet(RIGHT_MOTOR_PORT_2, right);
}

void liftSet(int left, int right) {
  motorSet(LEFT_LIFT_MOTOR, -left);
  motorSet(RIGHT_LIFT_MOTOR, right);
}

void mobileLiftSet(int speed) {
  motorSet(MOBILE_LIFT, speed);
}

void chainbarSet(int speed) {
  motorSet(CHAINBAR, speed);
}

void intakeSet(int speed) {
  motorSet(INTAKE, speed);
}

void chainbarHoldSet(int position){
  int chainbarHold = 0;


	if (analogRead(4) < 900){
		chainbarHold = -20;

	}else if ((analogRead(4) > 1000) && (analogRead(4) < 1600)){
		chainbarHold = -10;
	}else if (analogRead(4) > 1300){
		chainbarHold = 15;
	}else {
		chainbarHold = 0;
	}

  motorSet(CHAINBAR, chainbarHold);
}

//INCOMPLETE
//NO GYRO CORRECT AND NEEDS TO BE ABLE TO GO BACKWARDS
void imeWait(int val) {
  int leftIme, rightIme;

  while(abs(leftIme) < val || abs(rightIme) < val) {
    imeGet(0, &rightIme);
    imeGet(1, &leftIme);

    gyroCorrect();
  }
}

void gyroCorrect() {
    //RIGHT IS NEGATIVE LEFT IS POSITIVE
}

void gyroTurn(int val) {

}

void dropMobileGoal() {
  //total time delayed should be 1475

  //move forward into 20 pt zone
  //and mobile goal down
  chassisSet(127, 127);

  delay(975);
  mobileLiftSet(127);

  delay(500);
  mobileLiftSet(0);

  //back up a bit
  chassisSet(-127, -127);
  delay(300);
  chassisSet(0, 0);
}
