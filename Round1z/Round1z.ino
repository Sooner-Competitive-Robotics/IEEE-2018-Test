#include <RobotLib.h>
#include <IEEErobot2018.h>

//Drive Status Flag
bool driveComplete = false;
bool resetDrive = true;

float distances[10] = {12, 0, 24, 0, 12, 0, 24, 0, 24, 0};
float angles[10] = {0, -90, -90, 0, 0, 90, 90, 180, 180, 0};
int index = 0;

//Debug vars
float left, right, dist;

void setup() 
{	
	robotSetup();
}

void loop() {
  // put your main code here, to run repeatedly:
  drivetrain.drive(17, 0);                       //18" from middle of white square to edge of 4x4' square
  drivetrain.searchForward();

  drivetrain.turnToAngle(90);
  drivetrain.followLineUntilCoin();                         
  if(intake.coinDetected())
  {
    drivetrain.drive(distMetalDetectToIntake, 0);
    intake.pickUpSequenceA();
    coinCount++;
  }
  
  drivetrain.drive(distIntakeToMatrix, 0);					//on bottom right 4x4' sq
  drivetrain.turnToAngle(-135);								//turn onto diagonal (from top left to bottom right)
  
  while(coinCount != 2)										//follow diagonal and pick up coins
  {
    drivetrain.followLineUntilCoin();
    if(intake.coinDetected())
    {
      drivetrain.drive(distMetalDetectToIntake, 0);
      intake.pickUpSequenceA();
      coinCount++;
    }  
  }															//end bot right corner 2x2'
  
  drivetrain.drive(25.5,0);          //drive over gray square
  drivetrain.followLineUntilCoin();
  
    while(coinCount != 4)										//follow diagonal and pick up coins
  {
    drivetrain.followLineUntilCoin();
    if(intake.coinDetected())
    {
      drivetrain.drive(distMetalDetectToIntake, 0);
      intake.pickUpSequenceA();
      coinCount++;
    }  
  }	                                          //end at top left corner 4x4'   
  
  
  drivetrain.drive(distIntakeToMatrix, 0);
  drivetrain.turnToAngle(-135);								//turn to face down on left side 4x4' sq

  while(coinCount != 5)										//follow left side 4x4' sq down 
  {
    drivetrain.followLineUntilCoin();
    if(intake.coinDetected())
    {
      drivetrain.drive(distMetalDetectToIntake, 0);
      intake.pickUpSequenceA();
      coinCount++;
    }  
  }															//ends on middle outside 4x4'
  
  drivetrain.drive(distIntakeToMatrix, 0);
  drivetrain.turnToAngle(-90);								//turn to horizontal

  while(coinCount != 6)										//follow horizontal and pick up coins
  {
    drivetrain.followLineUntilCoin();
    if(intake.coinDetected())
    {
      drivetrain.drive(distMetalDetectToIntake, 0);
      intake.pickUpSequenceA();
      coinCount++;
    }  
  }	
  
  drivetrain.drive(23,0);                //drive over gray square horizontally
  
  while(coinCount != 8)										//follow horizontal and pick up coins
  {
    drivetrain.followLineUntilCoin();
    if(intake.coinDetected())
    {
      drivetrain.drive(distMetalDetectToIntake, 0);
      intake.pickUpSequenceA();
      coinCount++;
    }  
  }	                                            //end on opposite side of 4x4'
  
  drivetrain.turn(-90);
  
  while(coinCount != 9)										//follow vertical upwards and pick up coins
  {
    drivetrain.followLineUntilCoin();
    if(intake.coinDetected())
    {
      drivetrain.drive(distMetalDetectToIntake, 0);
      intake.pickUpSequenceA();
      coinCount++;
    }  
  }															            //end top right corner 4x4'
  
  drivetrain.drive(distIntakeToMatrix, 0);
  drivetrain.turnToAngle(-135);								

  while(coinCount != 10)									 //follow diagonal towards blue square and pick up coins
  {
    drivetrain.followLineUntilCoin();
    if(intake.coinDetected())
    {
      drivetrain.drive(distMetalDetectToIntake, 0);
      intake.pickUpSequenceA();
      coinCount++;
    }  
  }															
  
  drivetrain.drive(25.5,0);									//Skip Gray Square

  while(coinCount != 12)									//Follow to bottom left corner of 4x4'
  {
    drivetrain.followLineUntilCoin();
    if(intake.coinDetected())
    {
      drivetrain.drive(distMetalDetectToIntake, 0);
      intake.pickUpSequenceA();
      coinCount++;
    }  
  }															//ends on bottom left of 4x4'

  drivetrain.drive(25.4,0);							//drive till reach color and drive to all colors and go back to white square

  intake.dropOffSequence(blue);		

  drivetrain.turnToAngle(135);
  drivetrain.drive(42, 0);                                               //3.5' is distance between centers of color squares, DRVING to green
  intake.dropOffSequence(green);

  drivetrain.drive(42, 0);                                               //3.5' is distance between centers of color squares, Driving to Red
  intake.dropOffSequence(red);
  
  drivetrain.turnToAngle(135);
  drivetrain.drive(118.79, 0);                                               //Going diagonal to Yellow. Doing Z
  intake.dropOffSequence(yellow);
  
  drivetrain.turn(-135);
  drivetrain.drive(42, 0);                                               //3.5' is distance between centers of color squares, DRVING to Purple
  intake.dropOffSequence(purple);
  
  drivetrain.drive(42, 0);                                               //3.5' is distance between centers of color squares, DRVING to Cyan
  intake.dropOffSequence(cyan);
  
  drivetrain.turnToAngle(-90);
  drivetrain.drive(42, 0);                                               //3.5' is distance between centers of color squares, RETURN to WHITE SQUARE
  
}

void encLeftInterrupt() 
{
	leftEnc.process(); 
}
  
void encRightInterrupt() 
{  
	rightEnc.process(); 
}
