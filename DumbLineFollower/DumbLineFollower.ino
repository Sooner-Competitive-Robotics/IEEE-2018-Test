#include <RobotLib.h>
#include <IEEErobot2018.h>

bool initDrive = true;
String step = "";

void setup() {
  // put your setup code here, to run once:
  robotSetup();
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("\tpos: ");
  Serial.println(lineFollower.getPosition());
  Serial.print("\tden: ");
  Serial.println(lineFollower.getDensity());
  int density = lineFollower.getDensity();
  int position = lineFollower.getPosition();
  if (density == 0)
  {
    if(step = "RIGHT")
    {
      drivetrain.drive(0, -25, yaw, initDrive);
      delay(100);
      drivetrain.drive(6, 0, yaw, initDrive);
    }
    else if(step = "LEFT")
    {
      drivetrain.drive(0, 25, yaw, initDrive);
      delay(100);
      drivetrain.drive(6, 0, yaw, initDrive);
    }
    else
    {
      drivetrain.drive(6, 0, yaw, initDrive);
    }
  }
  else if(density > 0 && density < 3)
  {
    if(position > 50)
    {
      drivetrain.drive(0, -25, yaw, initDrive);
      delay(100);
      drivetrain.drive(6, 0, yaw, initDrive);
      step = "LEFT";
    }
    else if(position < -50)
    {
      drivetrain.drive(0, 25, yaw, initDrive);
      delay(100);
      drivetrain.drive(6, 0, yaw, initDrive);
      step = "RIGHT";
    }
    else
    {
      drivetrain.drive(6, 0, yaw, initDrive);
    }
  }
  /*else
  {
    if(lineFollower.getPosition() > 0)
    {
      drivetrain.drive(0, 90, yaw, initDrive);
    }
    else if (lineFollower.getPosition() < 0)
    {
      drivetrain.drive(0, -90, yaw, initDrive);
    }
    
  }*/

}
