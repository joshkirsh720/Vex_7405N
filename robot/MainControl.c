#pragma config(Sensor, in1,    gyro,           sensorGyro)
#pragma config(Sensor, dgtl1,  rightDriveEncoder, sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  leftDriveEncoder, sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  rightLiftEncoder, sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  leftLiftEncoder, sensorQuadEncoder)
#pragma config(Motor,  port1,           mobileGoalLift, tmotorNone, openLoop)
#pragma config(Motor,  port2,           rightDriveBack, tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           leftDriveBack, tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port4,           intake,        tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port5,           rightLift,     tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port6,           leftLift,      tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           fourBar,       tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           leftDriveFront, tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port9,           rightDriveFront, tmotorVex393HighSpeed_MC29, openLoop, reversed)
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
void waitForEncoders(int objective, bool moveMG);
void initialConeStack();
void dropMobileGoal(bool time);
void gyroCorrect();

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
  const int imeValue = 1475; //4704
  const bool blueTeam = true;


  //reset all the stuff
  SensorValue[gyro] = 0;
	SensorValue[rightDriveEncoder] = 0;
	SensorValue[leftDriveEncoder] = 0;
	SensorValue[rightLiftEncoder] = 0;
	SensorValue[leftLiftEncoder] = 0;

	chassisSet(0, 0);
	liftSet(0, 0);
	fourBarSet(0);
	intakeSet(0);

	//start the thing
  intakeSet(40);

  chassisSet(0, 0);
  liftSet(100, 100);
  fourBarSet(-100);
  mobileLiftSet(127);
  delay(100);
  fourBarSet(0);
  delay(200); //give time for lift to go up
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

  //move forward for second cone
  chassisSet(127, 127);
  waitForEncoders(100, false);
  chassisSet(0, 0);

  //get the cone
  fourBarSet(-127);
  liftSet(-100, -100);
  delay(400);
  liftSet(-30, -30);
  intakeSet(100);
  delay(400);
  intakeSet(15);

  //cone is picked up
  fourBarSet(127);
  delay(300);
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
  waitForEncoders(imeValue + 100, false);
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
  blueTeam ? chassisSet(rotationSpeed, -rotationSpeed) : chassisSet(-rotationSpeed, rotationSpeed);
  while(abs(SensorValue[gyro]) < 1200);
  blueTeam ? chassisSet(-rotationSpeed, rotationSpeed) : chassisSet(rotationSpeed, -rotationSpeed);
  chassisSet(0, 0);

  encoderReset();
  //move forward
  chassisSet(127, 127);
  waitForEncoders(275, false);
  chassisSet(0, 0);

  //turn to face goal
  SensorValue[gyro] = 0;
  blueTeam ? chassisSet(rotationSpeed, -rotationSpeed) : chassisSet(-rotationSpeed, rotationSpeed);
  while(abs(SensorValue[gyro]) < 700);
  blueTeam ? chassisSet(-rotationSpeed, rotationSpeed) : chassisSet(rotationSpeed, -rotationSpeed);
  chassisSet(0, 0);

  liftSet(100, 100);
  delay(150);
  liftSet(0, 0);

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


//add Xmtr2 to the end to make it second controller ex Btn5DXmtr2
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

  	int forwardMotionXmtr2 = vexRT[Ch3Xmtr2];
  	int sideMotionXmtr2 = vexRT[Ch1Xmtr2];

		if(abs(sideMotionXmtr2) > 20 || abs(forwardMotionXmtr2) > 20) {
			chassisSet(forwardMotionXmtr2 + sideMotionXmtr2, forwardMotionXmtr2 - sideMotionXmtr2);
		}
		//if neither joystick is being moved
		else {
			//stop
			chassisSet(0, 0);
		}

		//END DRIVE CODE

		//AUTOSTACK
		if(vexRT[Btn7U] == 1){
			coneCount++;
			autoStack(coneCount);
		}else if(vexRT[Btn7D] == 1) {
			if(coneCount > 0) coneCount--;
	  }
		//AUTOSTACK


		//START MOBILE GOAL LIFT CODE

	  //FOR PARTNER CONTROL TESTING ONLY
		if(vexRT[Btn6DXmtr2] == 1) mobileLiftSet(127);
	  else if(vexRT[Btn6UXmtr2] == 1) mobileLiftSet(-127);
	  else mobileLiftSet(0);
	  //FOR PARTNER CONTROL TESTING ONLY

		//END MOBILE GOAL LIFT CODE

	  //START FOUR BAR
	  if(vexRT[Btn8R]) fourBarSet(-127);
		else if(vexRT[Btn8L]) fourBarSet(127);
		else fourBarSet(0);

		//four bar auto move
		if(vexRT[Btn7L] == 1){
		  fourBarSet(127);
		  wait1Msec(550);
		  fourBarSet(0);
		}else if(vexRT(Btn7R) == 1){
			fourBarSet(-127);
		  wait1Msec(550);
		  fourBarSet(0);
		}
	  //END FOUR BAR CODE


	  //START INTAKE CODE
	  if(vexRT[Btn5D])intakeSet(-40);
		else if(vexRT[Btn5U])intakeSet(40);
		else {
		intakeSet(0);
		}
		//END INTAKE CODE



	  //START LIFT CODE
		int liftEncoderDiff = SensorValue[leftLiftEncoder] - SensorValue[rightLiftEncoder];

	  if(vexRT[Btn8U] == 1) {
	  	if(liftEncoderDiff > 15) liftSet(75, 90);
	  	else if(liftEncoderDiff < -15) liftSet(90, 75);
	  	else liftSet(90, 90);
		}
		else if(vexRT[Btn8D] == 1) {
			if(liftEncoderDiff > 15) liftSet(-90, -75);
	  	else if(liftEncoderDiff < -15) liftSet(-75, -90);
	  	else liftSet(-90, -90);
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

void waitForEncoders(int objective, bool moveMG) {
	while( abs(SensorValue[rightDriveEncoder]) <= objective) {

		if(moveMG && abs(SensorValue[rightDriveEncoder]) >= objective/1.90) mobileLiftSet(0);

		//because it's only necessary going forward for the first time
		if(moveMG) gyroCorrect();
	}
}

void initialConeStack() {

  intakeSet(-50);
  delay(300);
  intakeSet(0);
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

//might need to be changed if direcs are + vs. -
//dependent on the fact that left is +
void gyroCorrect() {
	if(SensorValue[gyro] > 10) chassisSet(127, 80);
	else if(SensorValue[gyro] < -10) chassisSet(80, 127);
	else chassisSet(127, 127);
}
