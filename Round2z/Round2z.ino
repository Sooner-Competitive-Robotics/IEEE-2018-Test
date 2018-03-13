#include <RobotLib.h>
#include <IEEErobot2018.h>

//Drive Status Flag
bool driveComplete = false;
bool resetDrive = true;

float distances[10] = {12, 0, 24, 0, 12, 0, 24, 0, 24, 0};
float angles[10] = {0, -90, -90, 0, 0, 90, 90, 180, 180, 0};
int index = 0;

int coinCount = 0;

//Debug vars
float left, right, dist;

void setup() 
{
  robotSetup()
}

void loop() {
  // put your main code here, to run repeatedly:
  drivetrain.drive(47, 0, yaw, resetDrive);                        //drive 1' to 2nd line
  drivetrain.searchForward(yaw);

  drivetrain.drive(0, 90, yaw, resetDrive);
  drivetrain.followLineUntilCoin();                         
  if(intake.coinDetected())
  {
    drivetrain.drive(distMetalDetectToIntake, 0, yaw, resetDrive);
    updateColorSensor();
    intake.pickUpSequence(currentColor);
    coinCount++;
  }
  drivetrain.drive(distIntakeToMatrix, 0, yaw, resetDrive);        //on bottom right 6' sq
  drivetrain.drive(0, -135, yaw, resetDrive);                   //turn onto diagonal (from top left to bottom right)
  
  while(coinCount != 3)                           //follow diagonal and pick up coins
  {
    drivetrain.followLineUntilCoin();
    if(intake.coinDetected())
    {
      drivetrain.drive(distMetalDetectToIntake, 0, yaw, resetDrive);
      updateColorSensor();
      intake.pickUpSequence(currentColor);
      coinCount++;
    }  
  }                                               //bottom right corner of 2x2' square
  
  drivetrain.drive(25.5, 0, yaw, resetDrive);                       //drive across gray square  
  
  while(coinCount != 6)                           //follow diagonal and pick up coins
  {
    drivetrain.followLineUntilCoin();
    if(intake.coinDetected())
    {
      drivetrain.drive(distMetalDetectToIntake, 0, yaw, resetDrive);
      updateColorSensor();
      intake.pickUpSequence(currentColor);
      coinCount++;
    }  
  } 
  
  drivetrain.drive(distIntakeToMatrix, 0, yaw, resetDrive);
  drivetrain.drive(0, -135, yaw, resetDrive);                   //turn to face down on left side 5' sq

  while(coinCount != 7)                           //follow left side 5' sq down 
  {
    drivetrain.followLineUntilCoin();
    if(intake.coinDetected())
    {
      drivetrain.drive(distMetalDetectToIntake, 0, yaw, resetDrive);
      updateColorSensor();
      intake.pickUpSequence(currentColor);
      coinCount++;
    }  
  }                                               //ends on middle of 5' sq outside
  
  drivetrain.drive(distIntakeToMatrix, 0, yaw, resetDrive);
  drivetrain.drive(0, -90, yaw, resetDrive);                    //turn to horizontal

    while(coinCount != 9)                        //follow horizontal and pick up coins
  {
    drivetrain.followLineUntilCoin();
    if(intake.coinDetected())
    {
      drivetrain.drive(distMetalDetectToIntake, 0, yaw, resetDrive);
      updateColorSensor();
      intake.pickUpSequence(currentColor);
      coinCount++;
    }  
  }                                               //left side of 2x2' sq
  
  drivetrain.drive(23, 0, yaw, resetDrive);                         //drive across gray square
  
  while(coinCount != 12)                          //follow horizontal and pick up coins
  {
    drivetrain.followLineUntilCoin();
    if(intake.coinDetected())
    {
      drivetrain.drive(distMetalDetectToIntake, 0, yaw, resetDrive);
      updateColorSensor();
      intake.pickUpSequence(currentColor);
      coinCount++;
    }  
  } 
  
  drivetrain.drive(0, -90, yaw, resetDrive);                           //on right side of 5x5' sq facing up
  
  while(coinCount != 13)                          //follow vertical and pick up coins
  {
    drivetrain.followLineUntilCoin();
    if(intake.coinDetected())
    {
      drivetrain.drive(distMetalDetectToIntake, 0, yaw, resetDrive);
      updateColorSensor();
      intake.pickUpSequence(currentColor);
      coinCount++;
    }  
  }                    
           
  drivetrain.drive(distIntakeToMatrix, 0, yaw, resetDrive);
  drivetrain.drive(0, -135, yaw, resetDrive);                   //top right corner of 5x5' sq    

  while(coinCount != 15)                  
  {
    drivetrain.followLineUntilCoin();
    if(intake.coinDetected())
    {
      drivetrain.drive(distMetalDetectToIntake, 0, yaw, resetDrive);
      updateColorSensor();
      intake.pickUpSequence(currentColor);
      coinCount++;
    }  
  }                             
  
  drivetrain.drive(25.5, 0, yaw, resetDrive);                       //Skip Gray Square

  while(coinCount != 18)                          //Follow to bottom left corner
  {
    drivetrain.followLineUntilCoin();
    if(intake.coinDetected())
    {
      drivetrain.drive(distMetalDetectToIntake, 0, yaw, resetDrive);
      updateColorSensor();
      intake.pickUpSequence(currentColor);
      coinCount++;
    }  
  }                                               //ends on bottom left 

  drivetrain.drive(25.4, 0, yaw, resetDrive);                         //drive till reach dark blue color and drive to all colors and go back to white square

  intake.dropOffSequence(blue);   

  drivetrain.drive(0, 135, yaw, resetDrive);
  drivetrain.drive(42, 0, yaw, resetDrive);                        //3.5' is distance between centers of color squares, DRVING to green
  intake.dropOffSequence(green);

  drivetrain.drive(42, 0, yaw, resetDrive);                        //3.5' is distance between centers of color squares, Driving to Red
  intake.dropOffSequence(red);
  
  drivetrain.drive(135, yaw, resetDrive);
  drivetrain.drive(59.4, 0, yaw, resetDrive);                      //Going diagonal to Gray. Doing Z
  intake.dropOffSequence(gray);
  
  drivetrain.drive(59.4, 0, yaw, resetDrive);                      //Going diagonal to Yellow. Doing Z
  intake.dropOffSequence(yellow);
    
  drivetrain.turn(0, -135, yaw, resetDrive);
  drivetrain.drive(42, 0, yaw, resetDrive);                        //3.5' is distance between centers of color squares, DRVING to Purple
  intake.dropOffSequence(magenta);
  
  drivetrain.drive(42, 0, yaw, resetDrive);                        //3.5' is distance between centers of color squares, DRVING to Cyan
  intake.dropOffSequence(cyan);
  
  drivetrain.drive(0, -90, yaw, resetDrive);
  drivetrain.drive(42, 0, yaw, resetDrive);                        //3.5' is distance between centers of color squares, RETURN to WHITE SQUARE
  
}
