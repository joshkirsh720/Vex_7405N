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
    		int upSpeedLeft = 100;

    		int rightLiftPot = abs(analogReadCalibrated(1));
    		int leftLiftPot = abs(analogReadCalibrated(2));


    if(analogReadCalibrated(2) < position){
      while(analogReadCalibrated(2) < position){


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


        motorSet(LEFT_LIFT_MOTOR, upSpeedLeft);
        motorSet(RIGHT_LIFT_MOTOR, upSpeedRight);

      }


    }else if(analogReadCalibrated(2) > position){
      while(analogReadCalibrated(2) > position){

        if ((rightLiftPot < (leftLiftPot - 150)) && (rightLiftPot > 50)) {
    				upSpeedLeft = -70;
    				upSpeedRight = 125;
    		} else if ((leftLiftPot < (rightLiftPot + 300)) && (rightLiftPot > 50) ){
    				upSpeedRight = 40;
    				upSpeedLeft = -125;
    		} else {
    				upSpeedRight = 100;
    				upSpeedLeft = -100;
    		}

        motorSet(LEFT_LIFT_MOTOR, -upSpeedLeft);
        motorSet(RIGHT_LIFT_MOTOR, -upSpeedRight);

      }

    }

    motorSet(LEFT_LIFT_MOTOR, 25);
    motorSet(RIGHT_LIFT_MOTOR, -25);
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
}
