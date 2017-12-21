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




void waitForIMEs(int value, direction direc, bool moveMobile) {

  int leftIME=0,rightIME=0,count=0;

  resetIMEs();

  if(moveMobile) mobileSet(127);


  //until the IMEs have reached a certain amount of rotations
  while(abs(leftIME) <= value && abs(rightIME) <= value) {

    //update the variables leftIME and rightIME with the newest IME values
    updateIMEs(&leftIME, &rightIME);

    if(count%20==0){
      //checks gyro to make sure the robot is going in the right direction
      //if(direc != left && direc != right) gyroCheck(direc);
    }

    if(moveMobile && rightIME>= 520 && leftIME >= 520) mobileSet(0);

    count++;
  }

  resetIMEs();
}


//ALWAYS RESET GYRO AFTER YOU'RE FINISHED
void waitForGyro(int degrees, direction direc) {

  int speed = 127;

  //if turning to the left
  if(direc == left) {
    //wait for gyro to hit a certain amount
    while(gyroGet(gyro) < degrees) {
      //decrement speed with the formula speed = -sqrt(x) + 127
      if(speed >= 0) speed = -sqrt(50 * gyroGet(gyro)) + 127;
      else speed = 127;
      printf("Gyro Value: %d\n", gyroGet(gyro));
      chassisSet(-speed, speed);
    }
    //quickly move in the opposite direction to undo overturning
    chassisSet(speed, -speed);
    chassisSet(0, 0);
  }
  //if turning to the right
  else if(direc == right) {
    //wait for gyro to hit a certain amount
    while(gyroGet(gyro) > -degrees) {
      //decrement speed with the formula speed = -sqrt(x) + 127
      if(speed >= 0) speed = -sqrt(50 * gyroGet(gyro)) + 127;
      else speed = 127;
      printf("Gyro Value: %d\n", gyroGet(gyro));
      chassisSet(speed, -speed);
    }
    //quickly move in the opposite direction to undo overturning
    chassisSet(-speed, speed);
    chassisSet(0, 0);
  }
  //reset gyro
  gyroReset(gyro);
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

void liftSet(int left, int right) {
  motorSet(LEFT_LIFT_MOTOR, -left);
  motorSet(RIGHT_LIFT_MOTOR, right);
}

void mobileSet(int speed) {
  motorSet(MOBILE_LIFT, speed);
}

void chainbarSet(int speed) {
  motorSet(CHAINBAR, speed);
}

//PRECONDITION: 0 < stacked <= 10
void restIntake(int stacked) {
  //heights array such that index 0 is the height necessary when one cone is stacked, index 1 for 2, etc.
  int heights[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  int top = heights[stacked - 1];
  int speed = 0;

  //NEED TO BE GIVEN VALUES LATER
  int parralelValue = 0;
  int holdPower = 0;
  int aboveStackValue = 0;

  //moves chainbar to be parallel to the floor
  if(analogReadCalibrated(CHAINBAR_POTEN) > parralelValue) speed = -80;
  else if(analogReadCalibrated(CHAINBAR_POTEN) < parralelValue) speed = 80;
  else speed = holdPower;

  chainbarSet(speed);

  //wait until chainbar hits the right value, then hold power
  while(analogReadCalibrated(CHAINBAR_POTEN) != parralelValue);
  chainbarSet(holdPower);

  //move lift up
  liftSet(127, 127);

  //while lift is moving to the top, check poten values and adjust speed accordingly
  int left = analogReadCalibrated(LEFT_POTEN);
  int right = analogReadCalibrated(RIGHT_POTEN);
  int rightSpeed, leftSpeed;

  //while lift is moving up
  while(analogReadCalibrated(LEFT_POTEN) < top && analogReadCalibrated(RIGHT_POTEN) < top) {
    left = analogReadCalibrated(LEFT_POTEN);
    right = analogReadCalibrated(RIGHT_POTEN);

    //adjust speed based on potentiometer values
    if(left > right) {
      rightSpeed = 127;
      leftSpeed = 80;
    }
    else if(left < right) {
      rightSpeed = 80;
      leftSpeed = 127;
    }
    else {
      rightSpeed = 127;
      leftSpeed = 127;
    }

    liftSet(leftSpeed, rightSpeed);
  }

  //may be -127, change it if the chainbar moves the wrong way at this step
  chainbarSet(127);

  //wait until the chainbar is above the stack, then stop
  while(analogReadCalibrated(CHAINBAR_POTEN) != aboveStackValue);
  chainbarSet(0);

  //move lift down a tiny bit so that the chainbar is on top of the stack
  liftSet(-20, -20);
  delay(100);
  liftSet(0,0);

}
