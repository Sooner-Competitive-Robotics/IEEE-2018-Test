#include <RobotLib.h>
#include <IEEErobot2018.h>

#define Kp .3// experiment to determine this, start by something small that just makes your bot follow the line at a slow speed
#define Kd .8// experiment to determine this, slowly increase the speeds and adjust this value. ( Note: Kp < Kd) 
#define rightBaseSpeed .2 // this is the speed at which the motors should spin when the robot is perfectly on the line
#define leftBaseSpeed .2 // this is the speed at which the motors should spin when the robot is perfectly on the line

SensorBar mySensorBar( 0x3E );

void setup()
{
  robotSetup();
} 

int lastError = 0;

void loop()
{
  int error = lineFollower.getPosition();
  error /=127;

  float mSpeed = Kp * error + Kd * (error - lastError);
  mSpeed = mSpeed;
  Serial.print("mspeed");
  Serial.println(mSpeed);
  
  lastError = error;

  float rightMotorSpeed = rightBaseSpeed + mSpeed;
  Serial.print("right");
  Serial.println(rightMotorSpeed);
  float leftMotorSpeed = leftBaseSpeed - mSpeed;
  Serial.print("left");
  Serial.println(leftMotorSpeed);

  
  drivetrain.setOutput(-leftBaseSpeed, rightBaseSpeed);
}
  
void wait(){
     drivetrain.setOutput(0, 0);
}
