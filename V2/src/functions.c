#include "functions.h"
#include "main.h"
#include <api.h>
#include <math.h>



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
  motorSet(MOBILE_LIFT_MOTOR, speed);
}


void liftMove(int position) {
    int c = 1;


    		int upSpeedRight = 100;
    		int upSpeedLeft = -100;

        int downSpeedRight = -50;
        int downSpeedLeft = 50;

    		int rightLiftPot = abs(analogReadCalibrated(1));
    		int leftLiftPot = abs(analogReadCalibrated(2));


    if(analogReadCalibrated(2) < (position )){
      while(analogReadCalibrated(2) < (position)){
        if ((rightLiftPot < (leftLiftPot - 150))  && (rightLiftPot > 350)) {
    				upSpeedLeft = -70;
    				upSpeedRight = 90;
    		} else if ((leftLiftPot < (rightLiftPot + 200) && (rightLiftPot > 350))  ){
    				upSpeedRight = 70;
    				upSpeedLeft = -90;
    		} else {
    				upSpeedRight = 90;
    				upSpeedLeft = -90;
    		}
        motorSet(LEFT_LIFT_MOTOR, -90);
        motorSet(RIGHT_LIFT_MOTOR, 90);
      }
      motorSet(LEFT_LIFT_MOTOR, -20); //hold power while the button is not being pressed
      motorSet(RIGHT_LIFT_MOTOR, 20);


    }else if(analogReadCalibrated(2) > position){
      while(analogReadCalibrated(2) > position){

        if ((rightLiftPot < (leftLiftPot - 150)) && (rightLiftPot > 100)) {
    				downSpeedLeft = 70;
    				downSpeedRight = -40;
    		} else if ((leftLiftPot < (rightLiftPot + 300)) && (rightLiftPot > 100) ){
    				downSpeedRight = -40;
    				downSpeedLeft = 70;
    		} else {
    				downSpeedRight = -50;
    				downSpeedLeft = -0;
    		}


        motorSet(LEFT_LIFT_MOTOR, downSpeedLeft);
        motorSet(RIGHT_LIFT_MOTOR, downSpeedRight);

      }

      motorSet(LEFT_LIFT_MOTOR, -20); //hold power while the button is not being pressed
      motorSet(RIGHT_LIFT_MOTOR, 20);

    }



    motorSet(LEFT_LIFT_MOTOR, -20); //hold power while the button is not being pressed
    motorSet(RIGHT_LIFT_MOTOR, 20);
}



void chainbarMove(int position) { //takes in the desired position of the chainbar


    int chainbarUpSpeed = 127;
    int chainbarDownSpeed = -127;

    if(analogRead(4) > position){
      while(analogRead(4) > position) {
        motorSet(CHAINBAR_MOTOR, chainbarUpSpeed);
      }
    } else if (analogRead(4) < (position)){
        while(analogRead(4) < (position )) {
          motorSet(CHAINBAR_MOTOR, chainbarDownSpeed);
        }
      }

      	//chainbarHoldSet(position);

}


void liftMoveP(int position){
  float p = 1.0f;
  int thresh = 100;
  while(abs(position - analogReadCalibrated(1)) > thresh ) {
      liftSet( ((position - analogRead(2)) * p), (( position-analogReadCalibrated(1)) *p ) );
  }
}

void chainbarMoveP(int position){
  float p = 1.0f;
  int thresh = 100;

  while(abs(position - analogReadCalibrated(1)) > thresh ) {
    //chainbarSet((position - analogRead(4)) * p);
  }
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
