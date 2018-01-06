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

void mobileSet(int speed) {
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


    if(analogReadCalibrated(2) < (position - 50)){
      while(analogReadCalibrated(2) < (position - 50)){
        if ((rightLiftPot < (leftLiftPot - 150)) ) {
    				upSpeedLeft = -70;
    				upSpeedRight = 125;
    		} else if ((leftLiftPot < (rightLiftPot + 300))  ){
    				upSpeedRight = 40;
    				upSpeedLeft = -125;
    		} else {
    				upSpeedRight = 100;
    				upSpeedLeft = -100;
    		}

        motorSet(LEFT_LIFT_MOTOR, upSpeedLeft);
        motorSet(RIGHT_LIFT_MOTOR, upSpeedRight);




      }


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
    } else if (analogRead(4) < (position - 200)){
        while(analogRead(4) < (position - 200)) {
          motorSet(CHAINBAR_MOTOR, chainbarDownSpeed);
        }
      }

      	chainbarHoldSet(position);

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

  motorSet(CHAINBAR_MOTOR, chainbarHold);
}
