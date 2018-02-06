#include <RobotLib.h>
#include <IEEErobot2018.h>

#define pinLeftMot1 
#define pinLeftMot2 
#define pinRightMot1
#define pinRightMot2
#define pinColor1 //should have same pin on i2c chain
#define pinColor2
#define pinGyro1 //should have same pin on i2c chain
#define pinGyro2
#define pinLeftEnc1
#define pinLeftEnc2
#define pinRightEnc1
#define pinRightEnc2
#define pinIntakeEnc1
#define pinIntakeEnc2
#define pinMetDet //make sure it's giving an output
#define pinElecMag //make sure it's giving an output
#define pinLimSwitch 
#define pinIRMatrix1
#define pinIRMatrix2
#define pinIRMatrix3
#define pinIRMatrix4
#define pinIRMatrix5
#define colorServoPin 

#define distMetalDetectToIntake;		//Make these #define's
#define distIntakeToIRMatrix;

void setup() {
	// put your setup code here, to run once:
	//Drivetrain
	Motor leftMot = new Motor();
	Motor rightMot = new Motor();
	Encoder leftEnc = new Encoder();
	Encoder rightEnc = new Encoder();
	Gyro gyro = new Gyro();
	DigitalDevice mDetector = new DigitalDevice();
	IRMatrix matrix = new IRMatrix(pinIRMatrix1, pinIRMatrix2, pinIRMatrix3, pinIRMatrix4, pinIRMatrix5);
  
	//Drivetrain
	leftMot.begin(pinLeftMot1, pinLeftMot2, 1);
	rightMot.begin(pinRightMot1, pinRightMot2, 1);
	leftEnc.begin(pinLeftEnc1, pinLeftEnc2, 1);
	rightEnc.begin(pinRightEnc1, pinRightEnc2 1);
	gyro.begin(pinGyro1, pinGyro2);                                                              //make sure gyro is correct
	mDetector.initialize(pinMetDet);
	matrix.begin(pinIRMatrix1, pinIRMatrix2, pinIRMatrix3, pinIRMatrix4, pinIRMatrix5);
  
	//Drivetrain
	Drivetrain drivetrain;
	drivetrain.begin(leftMot, rightMot, leftEnc, rightEnc, gyro, matrix, mDetector);
  
	Encoder tEncoder;
  
	//Intake
	DigitalDevice lSwitch;
	Electromagnet eMagnet;
	Servo tServo;                                    //remember to instantiate winch servo
	Turntable turntable;
	ColorSensor colorSensor;

	tEncoder.begin(pinIntakeEncoder1, pinIntakeEncoder2);
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
