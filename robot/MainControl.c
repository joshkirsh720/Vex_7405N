#pragma config(Sensor, in1,    gyro,           sensorGyro)
#pragma config(Sensor, dgtl1,  rightDriveEncoder, sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  leftDriveEncoder, sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  rightLiftEncoder, sensorRotation)
#pragma config(Sensor, dgtl6,  leftLiftEncoder, sensorRotation)
#pragma config(Sensor, dgtl7,  chainbarEncoder, sensorRotation)
#pragma config(Motor,  port1,           mobileGoalLift, tmotorNone, openLoop)
#pragma config(Motor,  port2,           rightDriveBack, tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           leftDriveBack, tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port4,           intake,        tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port5,           rightLift,     tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port6,           leftLift,      tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port7,           fourBar,       tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port8,           leftDriveFront, tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port9,           rightDriveFront, tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port10,           ,             tmotorVex393HighSpeed_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VEX EDR                      */
/*                                                                           */
/*---------------------------------------------------------------------------*/

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

//functions
void chassisSet(int left, int right);
void liftSet(int left, int right);
void fourBarSet(int val);
void intakeSet(int val);
void mobileLiftSet(int val);

void encoderReset();

void autoStack(int cone);
void encoderLiftMove(int objective);
void waitForEncoders(int objective);
void waitForEncoders(int objective, bool moveMG);
void initialConeStack();
void dropMobileGoal(bool time);

void pre_auton()
{
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks
  // running between Autonomous and Driver controlled modes. You will need to
  // manage all user created tasks if set to false.
  bStopTasksBetweenModes = true;

	SensorValue[gyro] = 0;
	SensorValue[rightDriveEncoder] = 0;
	SensorValue[leftDriveEncoder] = 0;
	SensorValue[rightLiftEncoder] = 0;
	SensorValue[leftLiftEncoder] = 0;
	SensorValue[chainbarEncoder] = 0;

	chassisSet(0, 0);
	liftSet(0, 0);
	fourBarSet(0);
	intakeSet(0);
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

task autonomous()
{
  const int imeValue = 1424; //4704
  const bool blueTeam = true;

  intakeSet(15);
  chassisSet(0, 0);
  liftSet(100, 100);
  mobileLiftSet(127);
  delay(300); //give time for lift to go up
  liftSet(0, 0);

  delay(300);

  //start moving forward
  chassisSet(127, 127);
	waitForEncoders(imeValue, true);
  chassisSet(0, 0);

  //pick up mobile goal
  mobileLiftSet(-127);
  delay(1400);
  mobileLiftSet(0);

  initialConeStack();

  encoderReset();
  //second cone
  chassisSet(127, 127);
  waitForEncoders(200);
  chassisSet(0, 0);

  fourBarSet(-127);
  liftSet(-100, -100);
  delay(400);
  liftSet(-30, -30);
  intakeSet(100);
  delay(500);
  intakeSet(15);

  //cone is picked up
  fourBarSet(127);
  delay(900);
  liftSet(100, 100);
  delay(400);
  liftSet(0, 0);
  fourBarSet(0);

  liftSet(-100, -100);
  delay(200);
  liftSet(0, 0);

  intakeSet(-100);
  delay(500);
  intakeSet(0);

  //move backwards
  encoderReset();
  chassisSet(-127, -127);
  waitForEncoders(imeValue + 100);
  chassisSet(0, 0);

  delay(200);


  int rotationSpeed = 85;



/*
//BEGIN TEMP ADDITION
  //turn
  gyroReset(gyro);
  blueTeam ? chassisSet(rotationSpeed, -rotationSpeed) : chassisSet(-rotationSpeed, rotationSpeed);
  while(abs(gyroGet(gyro)) < 180);
  blueTeam ? chassisSet(-rotationSpeed, rotationSpeed) : chassisSet(rotationSpeed, -rotationSpeed);
  chassisSet(0, 0);

  chassisSet(127, 127);
  delay(300);
  chassisSet(0, 0);

  mobileLiftSet(127);
  delay(1400);
  mobileLiftSet(0);

  chassisSet(-127, -127);
  delay(500);
  chassisSet(0, 0);
//END TEMP ADDITION
*/




  //turn
  SensorValue[gyro] = 0;
  blueTeam ? chassisSet(rotationSpeed, -rotationSpeed) : chassisSet(-rotationSpeed, rotationSpeed);
  while(abs(SensorValue[gyro]) < 128);
  blueTeam ? chassisSet(-rotationSpeed, rotationSpeed) : chassisSet(rotationSpeed, -rotationSpeed);
  chassisSet(0, 0);

  encoderReset();
  //move forward
  chassisSet(127, 127);
  waitForEncoders(600);
  chassisSet(0, 0);

  //turn to face goal
  SensorValue[gyro] = 0;
  blueTeam ? chassisSet(rotationSpeed, -rotationSpeed) : chassisSet(-rotationSpeed, rotationSpeed);
  while(abs(SensorValue[gyro]) < 80);
  blueTeam ? chassisSet(-rotationSpeed, rotationSpeed) : chassisSet(rotationSpeed, -rotationSpeed);
  chassisSet(0, 0);

  //drop off mobile goal
  dropMobileGoal(false);

  //if lift gets stuck
  mobileLiftSet(-127);
  delay(600);
  mobileLiftSet(0);

  chassisSet(-127, -127);
  delay(500);
  chassisSet(0, 0);
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

task usercontrol() {
  // User control code here, inside the loop
	int coneCount = 0;


  while (true) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

  	//START DRIVE CODE
  	int forwardMotion = vexRT[Ch3];
  	int sideMotion = vexRT[Ch1];

		//if the right joystick is being moved horizontally
		if(abs(sideMotion ) > 20 || abs(forwardMotion ) > 20) {
			chassisSet(forwardMotion + sideMotion, forwardMotion - sideMotion);
		}
		//if neither joystick is being moved
		else {
			//stop
			chassisSet(0, 0);
		}
		//END DRIVE CODE


		//START MOBILE GOAL LIFT CODE
		if(vexRT[Btn6D] == 1) mobileLiftSet(127);
	  else if(vexRT[Btn6U] == 1) mobileLiftSet(-127);
	  else mobileLiftSet(0);
		//END MOBILE GOAL LIFT CODE

	  //START FOUR BAR CODE
	  if(vexRT[Btn8R]) fourBarSet(127);
		else if(vexRT[Btn8L]) fourBarSet(-127);
		else fourBarSet(0);
	  //END FOUR BAR CODE


	  //START INTAKE CODE
	  if(vexRT[Btn5D]) intakeSet(127);
		else if(vexRT[Btn5U]) intakeSet(-127);
		else intakeSet(0);
	  //END INTAKE CODE


	  //START LIFT CODE
	  if(vexRT[Btn8U] == 1) {
	  	liftSet(90, 90);
		}
		else if(vexRT[Btn8D] == 1) {
			liftSet(-90, -90);
		}
		else {
			liftSet(0, 0);
		}
	  //END LIFT CODE
  }
}

//begin function definitions
void chassisSet(int left, int right) {
	motor[leftDriveBack] = left;
	motor[leftDriveFront] = left;
	motor[rightDriveBack] = right;
	motor[rightDriveFront] = right;
}
void liftSet(int left, int right) {
	motor[leftLift] = left;
	motor[rightLift] = right;
}
void fourBarSet(int val) {
	motor[fourBar] = val;
}
void intakeSet(int val) {
	motor[intake] = val;
}
void mobileLiftSet(int val) {
	motor[mobileGoalLift] = val;
}


void encoderReset() {
	SensorValue[leftDriveEncoder] = 0;
	SensorValue[rightDriveEncoder] = 0;
}


void autoStack(int cone) {
	int startingEncoder = abs(SensorValue[leftLiftEncoder]);
  const int stackHeights[6] = {0, 6, 0, 0, 0, 0};

  int objectiveHeight = stackHeights[cone];


  //move chainbar down and grab cone
  fourBarSet(-127);
  intakeSet(50);
  delay(300);
  intakeSet(15);
  fourBarSet(0);

  //move to position to stack cone
  encoderLiftMove(objectiveHeight);

  //move chainbar into stacking position
  fourBarSet(127);
  delay(900);
  fourBarSet(0);

  //drop cone
  intakeSet(-100);
  delay(500);
  intakeSet(0);

  //move chainbar back
  fourBarSet(-127);
  delay(700);
  fourBarSet(0);

  //lift back to starting position
  encoderLiftMove(startingEncoder);
}

void encoderLiftMove(int objective) {
	int startingEncoder = abs(SensorValue[leftLiftEncoder]);
  //may need to be switched depending on whether the encoder count up or down (negative)
  //using only the left encoder
  int speed = 0;

  //choose direction based off of
  if(startingEncoder < objective) {
    speed = 127;
  }
  else if(startingEncoder > objective) {
    speed = -127;
  }
  else {
    return;
  }

  liftSet(speed, speed);

  while(startingEncoder < objective ?
    SensorValue[leftLiftEncoder] <= objective :
    SensorValue[leftLiftEncoder] >= objective);

  liftSet(0, 0);
}

void waitForEncoders(int objective) {
	while( abs(SensorValue[rightDriveEncoder]) <= objective ||
				abs(SensorValue[leftDriveEncoder]) <= objective);
}
void waitForEncoders(int objective, bool moveMG) {
	while( abs(SensorValue[rightDriveEncoder]) <= objective || abs(SensorValue[leftDriveEncoder]) <= objective) {

		if(moveMG && abs(SensorValue[rightDriveEncoder]) >= objective/2) mobileLiftSet(0);

	}
}

void initialConeStack() {

  fourBarSet(-127);
  delay(700);
  fourBarSet(127);
  delay(600);
  fourBarSet(0);

  liftSet(-100, -100);
  delay(200);
  intakeSet(-50);
  delay(200);
  liftSet(0, 0);
  intakeSet(0);

  delay(200);
}

void dropMobileGoal(bool time) {
  //total time delayed should be 1475

  //move forward into 20 pt zone
  //and mobile goal down
  mobileLiftSet(127);
  delay(300);
  mobileLiftSet(0);

  chassisSet(127, 127);

  delay(500);
  mobileLiftSet(127);

  delay(800);
  mobileLiftSet(0);

  //back up a bit
  chassisSet(-127, -127);
  delay(300);
  chassisSet(0, 0);

  //mobile goal up
  mobileLiftSet(-127);
  delay(600);
  mobileLiftSet(0);
}
