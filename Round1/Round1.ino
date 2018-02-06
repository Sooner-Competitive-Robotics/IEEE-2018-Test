#include <RobotLib.h>
#include <IEEErobot2018.h>

#define pinLeftMot1 24
#define pinLeftMot2 25
#define pinLeftMotEnb 10
#define pinRightMot1 26
#define pinRightMot2 23
#define pinRightMotEnb 11
#define pinColor1 0		//should have same pin on i2c chain
#define pinColor2 0
#define pinGyro1 0	 	//should have same pin on i2c chain
#define pinGyro2 0
#define pinLeftEnc1 1
#define pinLeftEnc2 2
#define pinRightEnc1 3
#define pinRightEnc2 4
#define pinIntakeEnc1 0
#define pinIntakeEnc2 0
#define pinMetDet 0 //make sure it's giving an output
#define pinElecMag 0 //make sure it's giving an output
#define pinLimSwitch 0
#define pinIRMatrix1 0
#define pinIRMatrix2 0
#define pinIRMatrix3 0
#define pinIRMatrix4 0
#define pinIRMatrix5 0
#define colorServoPin 0

#define distMetalDetectToIntake;		//Make these #define's
#define distIntakeToIRMatrix;

Drivetrain drivetrain;

void setup() {
	// put your setup code here, to run once:
	//Drivetrain
	Motor leftMot = Motor();
	Motor rightMot = Motor();
	Encoder leftEnc = Encoder(pinLeftEnc1, pinLeftEnc2);
	Encoder rightEnc = Encoder(pinRightEnc1, pinRightEnc2);
	
	Gyro gyro = Gyro();
	
	DigitalDevice mDetector = DigitalDevice(pinMetDet, INPUT);
	IRMatrix matrix = IRMatrix(pinIRMatrix1, pinIRMatrix2, pinIRMatrix3, pinIRMatrix4, pinIRMatrix5);
  
	//Drivetrain
	leftMot.begin(pinLeftMot1, pinLeftMot2, pinLeftMotEnb);
	rightMot.begin(pinRightMot1, pinRightMot2, pinRightMotEnb);
	matrix.begin(pinIRMatrix1, pinIRMatrix2, pinIRMatrix3, pinIRMatrix4, pinIRMatrix5);
	
	//leftEnc.begin(pinLeftEnc1, pinLeftEnc2, 1);
	//rightEnc.begin(pinRightEnc1, pinRightEnc2 1);
	//gyro.begin(pinGyro1, pinGyro2);                                                              //make sure gyro is correct
  
	//Drivetrain
	drivetrain.begin(leftMot, rightMot, leftEnc, rightEnc, gyro, matrix, mDetector);
  
	//Intake
	Encoder tEncoder = Encoder(pinIntakeEncoder1, pinIntakeEncoder2);
  
	//Intake
	DigitalDevice lSwitch;
	Electromagnet eMagnet;
	Servo tServo;                                    //remember to instantiate winch servo
	Turntable turntable;
	ColorSensor colorSensor;

	eMagnet.initialize(pinElecMag); 

	lSwitch.initialize(pinLimSwitch);
	turntable.begin(tServo);
  
	//Intake
	Intake intake = new Intake(tEncoder, mDetector, lSwitch, eMagnet, turntable, colorSensor, colorServoPin);

	//Colors
	Color blue("blue");
	Color green("green");
	Color red("red");
	Color cyan("cyan");
	Color magenta("magenta");
	Color yellow("yellow");
	Color gray("gray");
  
	int coinCount = 0;
	//int distMetalDetectToIntake;		//Make these #define's
	//int distIntakeToIRMatrix;
  
	//Encoder Interrupts
	attachInterrupt(0, encLeftInterrupt, CHANGE);
	attachInterrupt(0, encRightInterrupt, CHANGE);
	
	//Encoder Constants.........Need testing to change
	leftEnc.setConstant(1);
	rightEnc.setConstant(1);
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