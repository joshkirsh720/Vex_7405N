#include "functions.h"
#include "main.h"
#include <api.h>




void chassisSet(int left, int right) {
  motorSet(LEFT_MOTOR_PORT_1, left);
  motorSet(LEFT_MOTOR_PORT_2, left);
  motorSet(RIGHT_MOTOR_PORT_1, -right);
  motorSet(RIGHT_MOTOR_PORT_2, right);
}

void resetIMEs() {
  imeReset(LEFT_IME);
  imeReset(RIGHT_IME);
}

bool updateIMEs(int *left, int *right) {
  return imeGet(LEFT_IME, left) && imeGet(RIGHT_IME, right);
}

void gyroCheck(direction direc) {

  //don't gyro check if the robot is turning
  if(direc == straight) {
  //checks gyro to make sure the robot is going in the right direction
    if(gyroGet(gyro) < 0) {
      //adjust to the right
      chassisSet(50, 127);
    }
    else if(gyroGet(gyro) > 0) {
      //adjust to the left
      chassisSet(127, 50);
    }
    else {
      //not adjusting, moving straight
      chassisSet(127, 127);
    }
  }

  else if(direc == backwards) {
    //checks gyro to make sure the robot is going in the right direction
      if(gyroGet(gyro) < 0) {
        //adjust to the right
        chassisSet(-127 , -80);
      }
      else if(gyroGet(gyro) > 0) {
        //adjust to the left
        chassisSet(-80, -127);
      }
      else {
        //not adjusting, moving straight
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


//ALWAYS RESET GYRO AFTER YOU'RE FINISHED
void waitForGyro(int degrees, direction direc) {

  printf("%s\n", "In the function");

  int speed = 127;

  //right is negative
  //left is positive
  //more than full turns will just add past 360
  if(direc == left) {
    while(gyroGet(gyro) < degrees) {
      speed = degrees / 1.5 + 7;
      chassisSet(-speed, speed);
      printf("%d\n", gyroGet(gyro));
    }
  }
  else if(direc == right) {
    while(gyroGet(gyro) > -degrees) {
      speed = degrees / 1.5 + 7;
      chassisSet(speed, -speed);
      printf("%d\n", gyroGet(gyro));
    }
  }
}



void accurateTurn(int degrees, direction startingDirec) {
/*
  int speed = 127;

  //while it isn't in the right range
  while(!(gyroGet(gyro) < degrees + 5 && gyroGet(gyro) > degrees - 5)) {

    //start to turn
    if(startingDirec == left) {
      chassisSet(-speed, speed);
    }
    else {
      chassisSet(speed, -speed);
    }

    //wait for the gyro to hit the degrees
    waitForGyro(degrees, startingDirec);

    //stop gyro
    chassisSet(0, 0);

    delay(100);

    //if the robot is facing the right way, exit the method
    if(gyroGet(gyro) < degrees + 5 && gyroGet(gyro) > degrees - 5) {
      printf("it's at the right place!  Exiting\n");
      printf("Final gyro value: %d\n", gyroGet(gyro));
      return;
    }

    //if it isn't, keep adjusting, but this time in the opposite direction
    else {
      //start to turn then wait for the gyro to pass degrees again
      if(startingDirec == left) {
        chassisSet(speed, -speed);
        while(gyroGet(gyro) > degrees);
      }
      else {
        chassisSet(-speed, speed);
        while(gyroGet(gyro) < degrees);
      }
    }
    //decreases speed so there will be less momentum the second time
    speed/=1.25;
    delay(100);
  }

  printf("Done!");
  gyroReset(gyro);*/
}
