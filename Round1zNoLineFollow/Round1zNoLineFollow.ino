#include <RobotLib.h>
#include <IEEErobot2018.h>

//Drive Status Flag
bool driveComplete = false;
bool resetDrive = true;

//float distances[10] = {12, 0, 24, 0, 12, 0, 24, 0, 24, 0};
//float angles[10] = {0, -90, -90, 0, 0, 90, 90, 180, 180, 0};
//int index = 0;

int coinCount = 0;
int doneThis = 0;

bool pickUpDoThis = true;

//Debug vars
float left, right, dist;

void setup() 
{  
  robotSetup();
}

void loop() {
  // put your main code here, to run repeatedly:
  while(drivetrain.drive(17, 0, yaw, resetDrive))
  {
    updateGyro();
  }
  updateGyro();
  drivetrain.searchForward(lineFollower.getDensity(), yaw, resetDrive);

  while(drivetrain.drive(0, 90, yaw, resetDrive));
  {
    updateGyro();
  }
  while(!intake.coinDetected())
  {
    updateGyro();
    drivetrain.driveIndefinitely(0.2, 0, yaw, resetDrive);
  }
  while(drivetrain.drive(0, 0, yaw, resetDrive))
  {
    updateGyro();
  }
  
  pickUpTurnDrive(-135);
  coinCount++;
  while(coinCount != 3)
  {
    pickUpDrive();
    coinCount++;
  }
  pickUpTurnDrive(-135);
  coinCount++;
  pickUpTurnDrive(-90);
  coinCount++;
  while(coinCount != 7)
  {
    pickUpDrive();
    coinCount++;
  }
  pickUpTurnDrive(-90);
  coinCount++;
  pickUpTurnDrive(-135);
  coinCount++;
  while(coinCount != 11)
  {
    pickUpDrive()
    coinCount++;
  }
  sitStillPickup();
  coinCount++;

  while(drivetrain.drive(25.4, 0, yaw, resetDrive))
  {
    updateGyro();
  }
  intake.dropOffSequence(blue);
  while(drivetrain.drive(0, 135, yaw, resetDrive))
  {
    updateGyro();
  }
  while(drivetrain.drive(42, 0, yaw, resetDrive))
  {
    updateGyro();
  }
  intake.dropOffSequence(green);
  while(drivetrain.drive(42, 0, yaw, resetDrive))
  {
    updateGyro();
  }
  intake.dropOffSequence(red);
  while(drivetrain.drive(0, 135, yaw, resetDrive))
  {
    updateGyro();
  }
  while(drivetrain.drive(118.79, 0, yaw, resetDrive))
  {
    updateGyro();
  }
  intake.dropOffSequence(yellow);
  while(drivetrain.drive(0, -135, yaw, resetDrive))
  {
    updateGyro();
  }
  while(drivetrain.drive(42, 0, yaw, resetDrive))
  {
    updateGyro();
  }
  intake.dropOffSequence(magenta);
  while(drivetrain.drive(42, 0, yaw, resetDrive))
  {
    updateGyro();
  }
  intake.dropOffSequence(cyan);
  while(drivetrain.drive(0, -90, yaw, resetDrive))
  {
    updateGyro();
  }
  while(drivetrain.drive(42, 0, yaw, resetDrive))
  {
    updateGyro();
  }
}
