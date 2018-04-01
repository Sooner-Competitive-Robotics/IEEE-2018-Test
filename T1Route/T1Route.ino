#include <RobotLib.h>
#include <IEEErobot2018.h>

//Drive Status Flag
int coinCount = 0;
int doneThis = 0;

void setup() 
{  
  robotSetup();
}

void loop() {
  // put your main code here, to run repeatedly:
  while(!driveComplete)
  {
    driveComplete = drivetrain.drive(20, 0, yaw, resetDrive, 2000);
    updateGyro();
    resetDrive = false;
  }
  commandTransition();
  
  while(!driveComplete)
  {
    driveComplete = drivetrain.drive(0, -90, yaw, resetDrive, 2000);
    updateGyro();
    resetDrive = false;
  }
  commandTransition();
  
  while(true)
  {
    
  }

  /*while(coinCount != 3)
  {
    while(!intake.coinDetected())
    {
      drivetrain.driveIndefinitely(0.25, 0, yaw, resetDrive);
      updateGyro();
      resetDrive = false;
    }
    drivetrain.driveIndefinitely(0, 0, yaw, true);
    while (!driveComplete)
    {
      driveComplete = drivetrain.drive(distMetalDetectToIntake, 0, yaw, resetDrive);
      updateGyro();
      resetDrive = false;
    }
    resetGyro();
    driveComplete = false;
    resetDrive = true;
    
    while(intake.getIntakeReturn() != 2)
    {
      updateColorSensor();
      
      if(!finishedPickingUp)
      {
        intake.pickUpSequence(currentColor, colorScanned);
      }
      
      if(intake.getIntakeReturn() == 2)
      {
        colorScanned = false;
        finishedPickingUp = true;
        coinCount++;
      }
      else if(intake.getIntakeReturn() == 1)
      {
        colorScanned = true;
      }
      else
      {
        delay(50);
      }
    }
  }

  while(!driveComplete)
  {
    driveComplete = drivetrain.drive(17, 0, yaw, resetDrive);
    updateGyro();
    resetDrive = false;
  }
  resetGyro();
  driveComplete = false;
  resetDrive = true;

  while(!driveComplete)
  {
    driveComplete = drivetrain.drive(0, 90, yaw, resetDrive);
    updateGyro();
    resetDrive = false;
  }
  resetGyro();
  driveComplete = false;
  resetDrive = true;

  while(!driveComplete)
  {
    driveComplete = drivetrain.drive(17, 0, yaw, resetDrive);
    updateGyro();
    resetDrive = false;
  }
  resetGyro();
  driveComplete = false;
  resetDrive = true;

  intake.dropOffSequence(red);

  while(!driveComplete)
  {
    driveComplete = drivetrain.drive(-41, 0, yaw, resetDrive);
    updateGyro();
    resetDrive = false;
  }
  resetGyro();
  driveComplete = false;
  resetDrive = true;*/
}
