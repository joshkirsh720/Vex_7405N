#include "functions.h"
#include "main.h"
#include <api.h>




void chassisSet(int left, int right) {
  motorSet(LEFT_MOTOR_PORT_1, left);
  motorSet(LEFT_MOTOR_PORT_2, left);
  motorSet(RIGHT_MOTOR_PORT_1, right);
  motorSet(RIGHT_MOTOR_PORT_2, right);
}

void resetIMEs() {
  imeReset(LEFT_IME);
  imeReset(RIGHT_IME);
}

bool updateIMEs(int *left, int *right) {
  return imeGet(LEFT_IME, left);
}

void gyroCheck(direction direc) {

  //don't gyro check if the robot is turning
  if(direc == straight) {
  //checks gyro to make sure the robot is going in the right direction
    if(gyroGet(gyro) < 0) {
      printf("%s\n", "adjusting to the right");
      chassisSet(50, 127);
    }
    else if(gyroGet(gyro) > 0) {
      printf("%s\n", "adjusting to the left");
      chassisSet(127, 50);
    }
    else {
      printf("%s\n", "moving straight");
      chassisSet(127, 127);
    }
  }

  else if(direc == backwards) {
    //checks gyro to make sure the robot is going in the right direction
      if(gyroGet(gyro) < 0) {
        printf("%s\n", "adjusting to the right");
        chassisSet(-127 , -80);
      }
      else if(gyroGet(gyro) > 0) {
        printf("%s\n", "adjusting to the left");
        chassisSet(-80, -127);
      }
      else {
        printf("%s\n", "moving straight");
        chassisSet(-127, -127);
      }
  }
}




void waitForIMEs(int value, direction direc) {

  int leftIME=0,rightIME=0,count=0;
  resetIMEs();

  //until the IMEs have reached a certain amount of rotations
  while(abs(leftIME) <= value && abs(rightIME) <= value) {

    //update the variables leftIME and rightIME with the newest IME values
    updateIMEs(&leftIME, &rightIME);

    if(count%20==0){
      //checks gyro to make sure the robot is going in the right direction
      if(direc != left && direc != right) gyroCheck(direc);
    }
    count++;
  }

  resetIMEs();
}
