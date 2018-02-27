#include <RobotLib.h>

Motor motor;
MotorController mc;
int limitSwitchA = 2;  //first limit switch
int limitSwitchB = 12;  //second limit switch

void setup() {
  
  Serial.begin(9600); //Open up serial communications

  motor.begin(7,8,9);    //initialize motor
  mc.begin(motor, motor);  //initialize motorcontroller
}

void loop() {
  
  //Until 1st limit switch hit, run forward
  while(digitalRead(limitSwitchA) != HIGH){
  mc.outputMotorA(1);
  }

  //stop motor
  mc.outputMotorA(-1);
  delay(2500);

  //Until 2nd limit switch hit, run backward
  while(digitalRead(limitSwitchB) != HIGH){ 
  mc.outputMotorA(-.9);
  }

  //stop motor
  mc.outputMotorA(0);
  delay(2500);
}
