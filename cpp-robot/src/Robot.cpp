#include "Robot.h"

Robot::Robot() {

}


int Robot::readIME(int port) {
  int imeVal = 0;
  imeGet(port, &imeVal);
  return imeVal;
}
int Robot::readPoten(int port) {
  return analogReadCalibrated(port);
}
int Robot::readGyro(){
  return gyroGet(this->gyro);
}
int Robot::readPotenUncalibrated(int port) {
  return analogRead(port);
}


void Robot::resetIMEs(){
  imeReset(Robot::SensorPorts::imeLeft);
  imeReset(Robot::SensorPorts::imeRight);
}
void Robot::resetGyro(){
  gyroReset(this->gyro);
}
