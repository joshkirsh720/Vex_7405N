#include "functions.h"
#include "main.h"
#include <api.h>
#include <math.h>


void setControl(int joystick, int buttonGroup, char button, int motors[], motorSpeed[]){
  if(joystickGetDigital(joystick, buttonGroup, char button)){
    for(int idx = 0; idx < motors.sizeof(); idx++){
      motorSet(motors[idx], motorSpeed[idx]);
    }
  }else {
    for(int idx = 0; idx < motors.sizeof(); idx++){
      motorSet(motors[idx], 0);
    }
  }
}


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



void liftMove(int position){
  float p = 1.0f;
  int thresh = 100;
  while(abs(position - analogReadCalibrated(1)) > thresh ) {
      liftSet( ((position - analogRead(2)) * p), (( position-analogReadCalibrated(1)) *p ) );
  }
}

void chainbarMove(int position){
  float p = 1.0f;
  int thresh = 100;

  while(abs(position - analogReadCalibrated(1)) > thresh ) {
    chainbarSet((position - analogRead(4)) * p);
  }
}
