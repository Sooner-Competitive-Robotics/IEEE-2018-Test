#include <RobotLib.h>
<<<<<<< Updated upstream
#include <IEEErobot2018.h>				
=======
#include <IEEErobot2018.h>					
>>>>>>> Stashed changes

//Drive Status Flag
bool driveComplete = false;
bool resetDrive = true;

float distances[10] = {12, 0, 24, 0, 12, 0, 24, 0, 24, 0};
float angles[10] = {0, -90, -90, 0, 0, 90, 90, 180, 180, 0};

int index = 0;

int coinCount = 0;

void setup() {
<<<<<<< Updated upstream
	robotSetup();
=======
	
	Serial.begin(9600);
	Serial.print(" -Has Begun- \n");
	
	//--Drivetrain
	Motor leftMot;
	Motor rightMot;
	Encoder leftEnc(pinLeftEnc1, pinLeftEnc2);
	Encoder rightEnc(pinRightEnc1, pinRightEnc2);
	DigitalDevice mDetector(pinMetDet, INPUT);
	IRMatrix mat(pinIRMatrix1, pinIRMatrix2, pinIRMatrix3, pinIRMatrix4, pinIRMatrix5);

	//Set the encoder constants
	leftEnc.setConstant(leftEncoderConstant);
	rightEnc.setConstant(rightEncoderConstant);

	//--Drivetrain
	leftMot.begin(pinLeftMot1, pinLeftMot2, pinLeftMotEnb);
	rightMot.begin(pinRightMot1, pinRightMot2, pinRightMotEnb);
	drivetrain.begin(leftMot, rightMot, leftEnc, rightEnc, mat, mDetector);
	
	//Setup PID
	drivetrain.initializeTurnPID(TURN_KP, TURN_KI, TURN_KD, 1, -1);
	drivetrain.initializeDistancePID(DIST_KP, DIST_KI, DIST_KD, 1, -1);
	
	Serial.print(" -Drive Has Begun- \n");
	
	//--Intake
	Encoder tEncoder(pinIntakeEnc1, pinIntakeEnc2);
	DigitalDevice lSwitch(pinLimSwitch, INPUT);
	Electromagnet eMagnet(pinElecMag);
	Motor iMotor;	
	Turntable turntable(turntableServoPin);
	
	//--Intake
	iMotor.begin(pinIntakeMot1, pinIntakeMot2, pinIntakeMotEnb);
	eMagnet.initialize(pinElecMag);
	intake.begin(iMotor, tEncoder, mDetector, loSwitch, hiSwitch, eMagnet, turntable, colorServoPin);
  
	Serial.print(" -Intake Has Begun- \n");
	
	//--Interrupts
	attachInterrupt(0, encLeftInterrupt, CHANGE);
	attachInterrupt(1, encRightInterrupt, CHANGE);
	
	//Interrupt for Turntable Encoder needed + method
	Serial.print(" -Interrupts- \n");
>>>>>>> Stashed changes
}

void loop() {
	// put your main code here, to run repeatedly:
	drivetrain.drive(11, 0, yaw, resetDrive);
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
  
	while(coinCount != 3)                   //follow diagonal and pick up coins
	{
		drivetrain.followLineUntilCoin();
		if(intake.coinDetected())
		{
			drivetrain.drive(distMetalDetectToIntake, 0, yaw, resetDrive);
			updateColorSensor();
			intake.pickUpSequence(currentColor);
			coinCount++;
		}  
	}                            				 //end on bottom right 2' sq
  
	drivetrain.drive(34, 0, yaw, resetDrive);					//jump across gray square
  
	while(coinCount != 6)                   //follow diagonal and pick up coins
	{
		drivetrain.followLineUntilCoin();
		if(intake.coinDetected())
		{
			drivetrain.drive(distMetalDetectToIntake, 0, yaw, resetDrive);
			updateColorSensor();
			intake.pickUpSequence(currentColor);
			coinCount++;
		}  
	}												//end on top left 4' sq

	drivetrain.drive(distIntakeToMatrix, 0, yaw, resetDrive);
	drivetrain.drive(0, -135, yaw, resetDrive);               //turn to face down on left side 4' sq

	while(coinCount != 8)                   //follow left side 4' sq down 
	{
		drivetrain.followLineUntilCoin();
		if(intake.coinDetected())
		{
			drivetrain.drive(distMetalDetectToIntake, 0, yaw, resetDrive);
			updateColorSensor();
			intake.pickUpSequence(currentColor);
			coinCount++;
		}  
	}                            				 //ends on bottom left 4' corner
  
	drivetrain.drive(distIntakeToMatrix, 0, yaw, resetDrive);
	drivetrain.drive(0, -135, yaw, resetDrive);               //turn to diagonal (from bottom left to top right)

	while(coinCount != 10)                   //follow diagonal and pick up coins
	{
		drivetrain.followLineUntilCoin();
		if(intake.coinDetected())
		{
			drivetrain.drive(distMetalDetectToIntake, 0, yaw, resetDrive);
			updateColorSensor();
			intake.pickUpSequence(currentColor);
			coinCount++;
		}  
	}                            					 //ends on bottom left 2' corner
  
	drivetrain.drive(34, 0, yaw, resetDrive);					//jump across the gray square
  
	while(coinCount != 13)                   //continue follow diagonal and pick up coins
	{
		drivetrain.followLineUntilCoin();
		if(intake.coinDetected())
		{
			drivetrain.drive(distMetalDetectToIntake, 0, yaw, resetDrive);
			updateColorSensor();
			intake.pickUpSequence(currentColor);
			coinCount++;
		}  
	}                            					 //ends on top right 4' corner
  
	drivetrain.drive(distIntakeToMatrix, 0, yaw, resetDrive);
	drivetrain.drive(0, 135, yaw, resetDrive);                //turn to face down on right side 6' sq

	while(coinCount != 14)                  //follow right side 4' sq down
	{
		drivetrain.followLineUntilCoin();
		if(intake.coinDetected())
		{
			drivetrain.drive(distMetalDetectToIntake, 0, yaw, resetDrive);
			updateColorSensor();
			intake.pickUpSequence(currentColor);
			coinCount++;
		}  
	}                            				 //ends on middle right 4' sq
	drivetrain.drive(distIntakeToMatrix, 0, yaw, resetDrive);
	drivetrain.drive(0, 90, yaw, resetDrive);               //turn to face left on middle of right side 6' sq

	while(coinCount != 16)                  //follow the middle line up to gray sqaure
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
  
	while(coinCount != 18)                  //continue to follow the middle line to the left
	{
		drivetrain.followLineUntilCoin();
		if(intake.coinDetected())
		{
			drivetrain.drive(distMetalDetectToIntake, 0, yaw, resetDrive);
			updateColorSensor();
			intake.pickUpSequence(currentColor);
			coinCount++;
		}  
	}    							//ends on middle 

	//drive till reach color and drive to all colors and go back to white square

	/*
	drivetrain.drive(180); 
	drivetrain.drive(18, 0);  
	intake.dropOffSequence(gray); 
	drivetrain.drive(180);
	*/
  
	drivetrain.drive(24, 0, yaw, resetDrive);                                 //2' is distance from last coin to center of color square, DRIVING to GREEN SQUARE
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