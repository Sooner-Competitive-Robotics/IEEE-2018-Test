#include <RobotLib.h>

Motor motor;
MotorController mc;
int limitSwitchA = 17;  //first limit switch
int limitSwitchB = 18;  //second limit switch

void setup() {
  
  Serial.begin(9600); //Open up serial communications

  motor.begin(15,16,2);    //initialize motor
  mc.begin(motor, motor);  //initialize motorcontroller
}

void loop() {
  
  //Until 1st limit switch hit, run forward
  while(digitalRead(limitSwitchA) != HIGH){
  mc.outputMotorA(.3);
  }

  //stop motor
  mc.outputMotorA(0);
  delay(2500);

  //Until 2nd limit switch hit, run backward
  while(digitalRead(limitSwitchB) != HIGH){ 
  mc.outputMotorA(-.3);
  }

  //stop motor
  mc.outputMotorA(0);
  delay(2500);
}
