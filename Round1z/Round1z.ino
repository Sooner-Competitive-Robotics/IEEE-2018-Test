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

void loop() 
{
	Serial.print("Stage 1");
	while (!driveComplete)                   				//18" from middle of white square to edge of 4x4' square
	{
		updateGyro();
		driveComplete = drivetrain.drive(15, 0, yaw, resetDrive);
		resetDrive = false;
	}
	resetDrive = true;
	driveComplete = false;
		
	Serial.print("Stage 2");
	while (lineFollower.getDensity() < 3)
	{
		Serial.println(lineFollower.getDensity());
		updateGyro();
		drivetrain.driveIndefinitely(.3, 0, yaw, resetDrive);
		resetDrive = false;
	}
	drivetrain.drive(0,0,yaw,true);
	resetDrive = true;
	
	Serial.print("Stage 3");
	while (!driveComplete)                   				//18" from middle of white square to edge of 4x4' square
	{
		updateGyro();
		Serial.println(yaw);
		driveComplete = drivetrain.drive(0, 90, yaw, resetDrive);
		resetDrive = false;
	}
	resetDrive = true;
	driveComplete = false;
	
	Serial.print("Stage 4");
	while(!drivetrain.followLineUntilCoin(lineFollower.getDensity(), lineFollower.getPosition(), yaw))
	{
		updateGyro();
	}
  
	Serial.println("Stage 5");
	pickUpTurnDrive(-135); //Now aiming UP & LEFT across diagonal
	coinCount++;
	
	/*
	while(coinCount != 2)										//follow diagonal and pick up coins
	{
		drivetrain.followLineUntilCoin();
		if(intake.coinDetected())
    {
		drivetrain.drive(distMetalDetectToIntake, 0, yaw, resetDrive);
		updateColorSensor();
		intake.pickUpSequence(currentColor);
		coinCount++;
    }  
}															//end bot right corner 2x2'
  
  drivetrain.drive(25.5, 0, yaw, resetDrive);          //drive over gray square
  drivetrain.followLineUntilCoin();
  
  while(coinCount != 4)										//follow diagonal and pick up coins
  {
    drivetrain.followLineUntilCoin();
    if(intake.coinDetected())
    {
      drivetrain.drive(distMetalDetectToIntake, 0, yaw, resetDrive);
      updateColorSensor();
      intake.pickUpSequence(currentColor);
      coinCount++;
    }  
  }	                                          //end at top left corner 4x4'   
  
  
  drivetrain.drive(distIntakeToMatrix, 0, yaw, resetDrive);
  drivetrain.drive(0, -135, yaw, resetDrive);								//turn to face down on left side 4x4' sq

  while(coinCount != 5)										//follow left side 4x4' sq down 
  {
    drivetrain.followLineUntilCoin();
    if(intake.coinDetected())
    {
      drivetrain.drive(distMetalDetectToIntake, 0, yaw, resetDrive);
      updateColorSensor();
      intake.pickUpSequence(currentColor);
      coinCount++;
    }  
  }															//ends on middle outside 4x4'
  
  drivetrain.drive(distIntakeToMatrix, 0, yaw, resetDrive);
  drivetrain.turnToAngle(0, -90, yaw, resetDrive);								//turn to horizontal

  while(coinCount != 6)										//follow horizontal and pick up coins
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
  
  drivetrain.drive(23, 0, yaw, resetDrive);                //drive over gray square horizontally
  
  while(coinCount != 8)										//follow horizontal and pick up coins
  {
    drivetrain.followLineUntilCoin();
    if(intake.coinDetected())
    {
      drivetrain.drive(distMetalDetectToIntake, 0, yaw, resetDrive);
      updateColorSensor();
      intake.pickUpSequence(currentColor);
      coinCount++;
    }  
  }	                                            //end on opposite side of 4x4'
  
  drivetrain.drive(0, -90, yaw, resetDrive);
  
  while(coinCount != 9)										//follow vertical upwards and pick up coins
  {
    drivetrain.followLineUntilCoin();
    if(intake.coinDetected())
    {
      drivetrain.drive(distMetalDetectToIntake, 0, yaw, resetDrive);
      updateColorSensor();
      intake.pickUpSequence(currentColor);
      coinCount++;
    }  
  }															            //end top right corner 4x4'
  
  drivetrain.drive(distIntakeToMatrix, 0, yaw, resetDrive);
  drivetrain.turnToAngle(0, -135, yaw, resetDrive);								

  while(coinCount != 10)									 //follow diagonal towards blue square and pick up coins
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
  
  drivetrain.drive(25.5, 0, yaw, resetDrive);									//Skip Gray Square

  while(coinCount != 12)									//Follow to bottom left corner of 4x4'
  {
    drivetrain.followLineUntilCoin();
    if(intake.coinDetected())
    {
      drivetrain.drive(distMetalDetectToIntake, 0, yaw, resetDrive);
      updateColorSensor();
      intake.pickUpSequence(currentColor);
      coinCount++;
    }  
  }															//ends on bottom left of 4x4'

  drivetrain.drive(25.4, 0, yaw, resetDrive);							//drive till reach color and drive to all colors and go back to white square

  intake.dropOffSequence(blue);		

  drivetrain.drive(0, 135, yaw, resetDrive);
  drivetrain.drive(42, 0, yaw, resetDrive);                                               //3.5' is distance between centers of color squares, DRVING to green
  intake.dropOffSequence(green);

  drivetrain.drive(42, 0, yaw, resetDrive);                                               //3.5' is distance between centers of color squares, Driving to Red
  intake.dropOffSequence(red);
  
  drivetrain.drive(0, 135, yaw, resetDrive);
  drivetrain.drive(118.79, 0, yaw, resetDrive);                                               //Going diagonal to Yellow. Doing Z
  intake.dropOffSequence(yellow);
  
  drivetrain.drive(0, -135, yaw, resetDrive);
  drivetrain.drive(42, 0, yaw, resetDrive);                                               //3.5' is distance between centers of color squares, DRVING to Purple
  intake.dropOffSequence(magenta);
  
  drivetrain.drive(42, 0, yaw, resetDrive);                                               //3.5' is distance between centers of color squares, DRVING to Cyan
  intake.dropOffSequence(cyan);
  
  drivetrain.drive(0, -90, yaw, resetDrive);
  drivetrain.drive(42, 0, yaw, resetDrive);                                               //3.5' is distance between centers of color squares, RETURN to WHITE SQUARE
  */
}

