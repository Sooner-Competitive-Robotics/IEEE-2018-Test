#include <RobotLib.h>
#include <IEEErobot2018.h>

Drivetrain drivetrain;
Intake intake;						

//Drive Status Flag
bool driveComplete = false;
bool resetDrive = true;

float distances[10] = {12, 0, 24, 0, 12, 0, 24, 0, 24, 0};
float angles[10] = {0, -90, -90, 0, 0, 90, 90, 180, 180, 0};
int index = 0;

void setup() {
	
	Serial.begin(9600);
	Serial.print(" -Has Begun- \n");
	
	Collection<float> turnK(3);
	Collection<float> distanceK(3);
	
	//Add Turn Constants
	turnK.add(TURN_KP);
	turnK.add(TURN_KI);
	turnK.add(TURN_KD);
	
	//Add Distance Constants
	distanceK.add(DIST_KP);
	distanceK.add(DIST_KI);
	distanceK.add(DIST_KD);
	
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
	drivetrain.initializeTurnPID(turnK);
	drivetrain.initializeDistancePID(distanceK);
	
	Serial.print(" -Drive Has Begun- \n");
	
	//--Intake
	Encoder tEncoder(pinIntakeEnc1, pinIntakeEnc2);
	DigitalDevice lSwitch(pinLimSwitch, INPUT);
	Electromagnet eMagnet(pinElecMag);
	Motor iMotor;	
	Turntable turntable(turntableServoPin);
	
	//--Intake
	iMotor.begin(pinIbtakeMot1, pinIbtakeMot2, pinIbtakeMotEnb);
	eMagnet.initialize(pinElecMag);
	intake.begin(iMotor, tEncoder, mDetector, lSwitch, eMagnet, turntable, colorServoPin);
  
	Serial.print(" -Intake Has Begun- \n");
	
	//--Interrupts
	attachInterrupt(0, encLeftInterrupt, CHANGE);
	attachInterrupt(1, encRightInterrupt, CHANGE);
	
	//Interrupt for Turntable Encoder needed + method
	Serial.print(" -Interrupts- \n");
}

void loop() {
	// put your main code here, to run repeatedly:
	drivetrain.drive(17, 0);
	drivetrain.searchForward();

	drivetrain.turnToAngle(90);
	drivetrain.followLineUntilCoin();                         //need to modify method because robot will drive through gray square where there is no line
	if(intake.coinDetected())
	{
		drivetrain.drive(distMetalDetectToIntake, 0);
		intake.pickUpSequenceA();
		coinCount++;
	}
	drivetrain.drive(distIntakeToMatrix, 0);          //on bottom right 4' sq
	drivetrain.turnToAngle(-135);               //turn onto diagonal (from top left to bottom right)
  
	while(coinCount != 2)                   //follow diagonal and pick up coins
	{
		drivetrain.followLineUntilCoin();
		if(intake.coinDetected())
		{
			drivetrain.drive(distMetalDetectToIntake, 0);
			intake.pickUpSequenceA();
			coinCount++;
		}  
	}                             			//end on bottom left 2' sq
  
	drivetrain.drive(34, 0);					//jump across gray square
	
	while(coinCount != 4)                   //follow diagonal and pick up coins
	{
		drivetrain.followLineUntilCoin();
		if(intake.coinDetected())
		{
		drivetrain.drive(distMetalDetectToIntake, 0);
		intake.pickUpSequenceA();
		coinCount++;
		}  
	}                             //end on top left 4' sq
  
	drivetrain.drive(distIntakeToMatrix, 0);
	drivetrain.turnToAngle(-135);               //turn to face down on left side 4' sq

	while(coinCount != 6)                   //follow left side 4' sq down 
	{
		drivetrain.followLineUntilCoin();
		if(intake.coinDetected())
		{
		drivetrain.drive(distMetalDetectToIntake, 0);
		intake.pickUpSequenceA();
		coinCount++;
		}  
	}                             //ends on bottom left 4' corner
  
	drivetrain.drive(distIntakeToMatrix, 0);
	drivetrain.turnToAngle(-135);               //turn to diagonal (from bottom left to top right)

	while(coinCount != 7)                   //follow diagonal and pick up coins
	{
		drivetrain.followLineUntilCoin();
		if(intake.coinDetected())
		{
			drivetrain.drive(distMetalDetectToIntake, 0);
			intake.pickUpSequenceA();
			coinCount++;
		}  
	}                             //ends on bottom left 2' corner
  
	drivetrain.drive(34, 0);					//jump across the gray square
  
	while(coinCount != 9)                   //follow diagonal and pick up coins
	{
		drivetrain.followLineUntilCoin();
		if(intake.coinDetected())
		{
			drivetrain.drive(distMetalDetectToIntake, 0);
			intake.pickUpSequenceA();
			coinCount++;
		}  
	}                             //ends on top right 4' corner
  
	drivetrain.drive(distIntakeToMatrix, 0);
	drivetrain.turnToAngle(135);                //turn to face down on right side 6' sq

	while(coinCount != 10)                  //follow right side 4' sq down
	{
		drivetrain.followLineUntilCoin();
		if(intake.coinDetected())
		{
			drivetrain.drive(distMetalDetectToIntake, 0);
			intake.pickUpSequenceA();
			coinCount++;
		}  
	}                             		//ends on middle right 4' sq
	drivetrain.drive(distIntakeToMatrix, 0);
	drivetrain.turnToAngle(90);               //turn to face left on middle of right side 6' sq

	while(coinCount != 11)                  //follow the middle line to the left
	{
		drivetrain.followLineUntilCoin();
		if(intake.coinDetected())
		{
			drivetrain.drive(distMetalDetectToIntake, 0);
			intake.pickUpSequenceA();
			coinCount++;
		}  
	}

	drivetrain.drive(23, 0);				//jump across the gray square

	while(coinCount != 12)                  //follow the middle line to the left
	{
		drivetrain.followLineUntilCoin();
		if(intake.coinDetected())
		{
			drivetrain.drive(distMetalDetectToIntake, 0);
			intake.pickUpSequenceA();
			coinCount++;
		}  
	}

								//ends on middle 

	//drive till reach color and drive to all colors and go back to white square
  
	/*
	drivetrain.turnToAngle(180); 
	drivetrain.drive(12, 0);  
	intake.dropOffSequence(gray); 
	drivetrain.turnToAngle(180);
	*/

	drivetrain.drive(30, 0);                                 //3.5' is distance from gray sq of color square, DRIVING to GREEN SQUARE
	intake.dropOffSequence(green);    

	drivetrain.turnToAngle(90);
	drivetrain.drive(42, 0);                                               //3.5' is distance between centers of color squares, DRVING to RED
	intake.dropOffSequence(red);

	drivetrain.turnToAngle(90);
	drivetrain.drive(84, 0);                                               //7' is distance between centers of color squares (skipping WHITE), DRVING to CYAN
	intake.dropOffSequence(cyan);
  
	drivetrain.turnToAngle(90);
	drivetrain.drive(42, 0);                                               //3.5' is distance between centers of color squares, DRVING to PURPLE
	intake.dropOffSequence(purple);
  
	drivetrain.drive(42, 0);                                               //3.5' is distance between centers of color squares, DRVING to YELLOW
	intake.dropOffSequence(yellow);
  
	drivetrain.turnToAngle(90);
	drivetrain.drive(84, 0);                                               //7' is distance between centers of color squares (skipping WHITE), DRVING to BLUE
	intake.dropOffSequence(blue);
  
	drivetrain.turnToAngle(180);
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