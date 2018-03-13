#include <RobotLib.h>
#include <IEEErobot2018.h>

//Drive Status Flag
bool driveComplete = false;
bool resetDrive = true;

float distances[10] = {12, 0, 24, 0, 12, 0, 24, 0, 24, 0};
float angles[10] = {0, -90, -90, 0, 0, 90, 90, 180, 180, 0};

int index = 0;

int coinCount = 0;

void setup() {
	robotSetup();
}

void loop() {
	// put your main code here, to run repeatedly:
	drivetrain.drive(17, 0, yaw, resetDrive);
	drivetrain.searchForward(yaw);

	drivetrain.drive(0, 90, yaw, resetDrive);
	drivetrain.followLineUntilCoin();                         //need to modify method because robot will drive through gray square where there is no line
	if(intake.coinDetected())
	{
		drivetrain.drive(distMetalDetectToIntake, 0, yaw, resetDrive);
		updateColorSensor();
		intake.pickUpSequence(currentColor);
		coinCount++;
	}
	drivetrain.drive(distIntakeToMatrix, 0, yaw, resetDrive);          //on bottom right 5' sq
	drivetrain.drive(0, -135, yaw, resetDrive);               //turn onto diagonal (from top left to bottom right)
  
	while(coinCount != 4)                   //follow diagonal and pick up coins
	{
		drivetrain.followLineUntilCoin();
		if(intake.coinDetected())
		{
			drivetrain.drive(distMetalDetectToIntake, 0, yaw, resetDrive);
			updateColorSensor();
			intake.pickUpSequence(currentColor);
			coinCount++;
		}  
	}                             			//end on bottom left 2' sq
  
  drivetrain.drive(34, 0, yaw, resetDrive);					//jump across gray square
  
	while(coinCount != 8)                   //follow diagonal and pick up coins
	{
		drivetrain.followLineUntilCoin();
		if(intake.coinDetected())
		{
			drivetrain.drive(distMetalDetectToIntake, 0, yaw, resetDrive);
			updateColorSensor();
			intake.pickUpSequence(currentColor);
			coinCount++;
		}  
	}                             //end on top left 5' sq
	
	drivetrain.drive(distIntakeToMatrix, 0, yaw, resetDrive);
	drivetrain.drive(0, -135, yaw, resetDrive);               //turn to face down on left side 5' sq

	while(coinCount != 10)                   //follow left side 5' sq down 
	{
		drivetrain.followLineUntilCoin();
		if(intake.coinDetected())
		{
			drivetrain.drive(distMetalDetectToIntake, 0, yaw, resetDrive);
			updateColorSensor();
			intake.pickUpSequence(currentColor);
			coinCount++;
		}  
	}                             //ends on bottom left 5' corner
  
	drivetrain.drive(distIntakeToMatrix, 0, yaw, resetDrive);
	drivetrain.drive(0, -135, yaw, resetDrive);               //turn to diagonal (from bottom left to top right)

	while(coinCount != 13)                   //follow diagonal and pick up coins
	{
		drivetrain.followLineUntilCoin();
		if(intake.coinDetected())
		{
			drivetrain.drive(distMetalDetectToIntake, 0, yaw, resetDrive);
			updateColorSensor();
			intake.pickUpSequence(currentColor);
			coinCount++;
		}  
	}                             //ends on bottom left 2' corner
  
	drivetrain.drive(34, 0, yaw, resetDrive);					//jump across the gray square
  
	while(coinCount != 17)                   //follow diagonal and pick up coins
	{
		drivetrain.followLineUntilCoin();
		if(intake.coinDetected())
		{
			drivetrain.drive(distMetalDetectToIntake, 0, yaw, resetDrive);
			updateColorSensor();
			intake.pickUpSequence(currentColor);
			coinCount++;
		}  
	}                             //ends on top right 5' corner
  
	drivetrain.drive(distIntakeToMatrix, 0, yaw, resetDrive);
	drivetrain.drive(0, 135, yaw, resetDrive);                //turn to face down on right side 5' sq

	while(coinCount != 18)                  //follow right side 5' sq down
	{
		drivetrain.followLineUntilCoin();
		if(intake.coinDetected())
		{
			drivetrain.drive(distMetalDetectToIntake, 0, yaw, resetDrive);
			updateColorSensor();
			intake.pickUpSequence(currentColor);
			coinCount++;
		}  
	}                             		//ends on middle right 5' sq
  
	drivetrain.drive(distIntakeToMatrix, 0, yaw, resetDrive);
	drivetrain.drive(0, 90, yaw, resetDrive);               //turn to face left on middle of right side 6' sq

	while(coinCount != 21)                  //follow the middle line to the left
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

	drivetrain.drive(23, 0, yaw, resetDrive);				//jump across the gray square

	while(coinCount != 24)                  //follow the middle line to the left
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

								//ends on middle 

	//drive till reach color and drive to all colors and go back to white square
  
	drivetrain.drive(0, 180, yaw, resetDrive); 
	drivetrain.drive(24, 0, yaw, resetDrive);  
	intake.dropOffSequence(gray); 
	drivetrain.drive(0, 180, yaw, resetDrive);

	drivetrain.drive(42, 0, yaw, resetDrive);                                 //3.5' is distance from gray sq of color square, DRIVING to GREEN SQUARE
	intake.dropOffSequence(green);    

	drivetrain.drive(0, 90, yaw, resetDrive);
	drivetrain.drive(42, 0, yaw, resetDrive);                                               //3.5' is distance between centers of color squares, DRVING to RED
	intake.dropOffSequence(red);

	drivetrain.drive(0, 90, yaw, resetDrive);
	drivetrain.drive(84, 0, yaw, resetDrive);                                               //7' is distance between centers of color squares (skipping WHITE), DRVING to CYAN
	intake.dropOffSequence(cyan);
  
	drivetrain.drive(0, 90, yaw, resetDrive);
	drivetrain.drive(42, 0, yaw, resetDrive);                                               //3.5' is distance between centers of color squares, DRVING to PURPLE
	intake.dropOffSequence(magenta);
  
	drivetrain.drive(42, 0, yaw, resetDrive);                                               //3.5' is distance between centers of color squares, DRVING to YELLOW
	intake.dropOffSequence(yellow);
  
	drivetrain.drive(0, 90, yaw, resetDrive);
	drivetrain.drive(84, 0, yaw, resetDrive);                                               //7' is distance between centers of color squares (skipping WHITE), DRVING to BLUE
	intake.dropOffSequence(blue);
  
	drivetrain.drive(0, 180, yaw, resetDrive);
	drivetrain.drive(42, 0, yaw, resetDrive);                                               //3.5' is distance between centers of color squares, RETURN to WHITE SQUARE
  
}