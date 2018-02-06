#include <RobotLib.h>
#include <IEEErobot2018.h>

#define pinLeftMot1 24
#define pinLeftMot2 25
#define pinLeftMotEnb 10
#define pinRightMot1 26
#define pinRightMot2 23
#define pinRightMotEnb 11
#define pinColor1 		//should have same pin on i2c chain
#define pinColor2
#define pinGyro1 		//should have same pin on i2c chain
#define pinGyro2
#define pinLeftEnc1 1
#define pinLeftEnc2 2
#define pinRightEnc1 3
#define pinRightEnc2 4
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
  drivetrain.drive(47, 0);                        //drive 1' to 2nd line
  drivetrain.searchForward();

  drivetrain.turnToAngle(90);
  drivetrain.followLineUntilCoin();                         
  if(intake.coinDetected())
  {
    drivetrain.drive(distMetalDetectToIntake, 0);
    intake.pickUpSequenceA();
    coinCount++;
  }
  drivetrain.drive(distIntakeToMatrix, 0);        //on bottom right 6' sq
  drivetrain.turnToAngle(-135);                   //turn onto diagonal (from top left to bottom right)
  
  while(coinCount != 3)                           //follow diagonal and pick up coins
  {
    drivetrain.followLineUntilCoin();
    if(intake.coinDetected())
    {
      drivetrain.drive(distMetalDetectToIntake, 0);
      intake.pickUpSequenceA();
      coinCount++;
    }  
  }                                               //bottom right corner of 2x2' square
  
  drivetrain.drive(25.5,0);                       //drive across gray square  
  
  while(coinCount != 6)                           //follow diagonal and pick up coins
  {
    drivetrain.followLineUntilCoin();
    if(intake.coinDetected())
    {
      drivetrain.drive(distMetalDetectToIntake, 0);
      intake.pickUpSequenceA();
      coinCount++;
    }  
  } 
  
  drivetrain.drive(distIntakeToMatrix, 0);
  drivetrain.turnToAngle(-135);                   //turn to face down on left side 5' sq

  while(coinCount != 7)                           //follow left side 5' sq down 
  {
    drivetrain.followLineUntilCoin();
    if(intake.coinDetected())
    {
      drivetrain.drive(distMetalDetectToIntake, 0);
      intake.pickUpSequenceA();
      coinCount++;
    }  
  }                                               //ends on middle of 5' sq outside
  
  drivetrain.drive(distIntakeToMatrix, 0);
  drivetrain.turnToAngle(-90);                    //turn to horizontal

    while(coinCount != 9)                        //follow horizontal and pick up coins
  {
    drivetrain.followLineUntilCoin();
    if(intake.coinDetected())
    {
      drivetrain.drive(distMetalDetectToIntake, 0);
      intake.pickUpSequenceA();
      coinCount++;
    }  
  }                                               //left side of 2x2' sq
  
  drivetrain.drive(23,0);                         //drive across gray square
  
  while(coinCount != 12)                          //follow horizontal and pick up coins
  {
    drivetrain.followLineUntilCoin();
    if(intake.coinDetected())
    {
      drivetrain.drive(distMetalDetectToIntake, 0);
      intake.pickUpSequenceA();
      coinCount++;
    }  
  } 
  
  drivetrain.turn(-90);                           //on right side of 5x5' sq facing up
  
  while(coinCount != 13)                          //follow vertical and pick up coins
  {
    drivetrain.followLineUntilCoin();
    if(intake.coinDetected())
    {
      drivetrain.drive(distMetalDetectToIntake, 0);
      intake.pickUpSequenceA();
      coinCount++;
    }  
  }                    
           
  drivetrain.drive(distIntakeToMatrix, 0);
  drivetrain.turnToAngle(-135);                   //top right corner of 5x5' sq    

  while(coinCount != 15)                  
  {
    drivetrain.followLineUntilCoin();
    if(intake.coinDetected())
    {
      drivetrain.drive(distMetalDetectToIntake, 0);
      intake.pickUpSequenceA();
      coinCount++;
    }  
  }                             
  
  drivetrain.drive(25.5,0);                       //Skip Gray Square

  while(coinCount != 18)                          //Follow to bottom left corner
  {
    drivetrain.followLineUntilCoin();
    if(intake.coinDetected())
    {
      drivetrain.drive(distMetalDetectToIntake, 0);
      intake.pickUpSequenceA();
      coinCount++;
    }  
  }                                               //ends on bottom left 

  drivetrain.drive(25.4,0);                         //drive till reach dark blue color and drive to all colors and go back to white square

  intake.dropOffSequence(blue);   

  drivetrain.turnToAngle(135);
  drivetrain.drive(42, 0);                        //3.5' is distance between centers of color squares, DRVING to green
  intake.dropOffSequence(green);

  drivetrain.drive(42, 0);                        //3.5' is distance between centers of color squares, Driving to Red
  intake.dropOffSequence(red);
  
  drivetrain.turnToAngle(135);
  drivetrain.drive(59.4, 0);                      //Going diagonal to Gray. Doing Z
  intake.dropOffSequence(gray);
  
  drivetrain.drive(59.4, 0);                      //Going diagonal to Yellow. Doing Z
  intake.dropOffSequence(yellow);
    
  drivetrain.turn(-135);
  drivetrain.drive(42, 0);                        //3.5' is distance between centers of color squares, DRVING to Purple
  intake.dropOffSequence(magenta);
  
  drivetrain.drive(42, 0);                        //3.5' is distance between centers of color squares, DRVING to Cyan
  intake.dropOffSequence(cyan);
  
  drivetrain.turnToAngle(-90);
  drivetrain.drive(42, 0);                        //3.5' is distance between centers of color squares, RETURN to WHITE SQUARE
  
}

void encLeftInterrupt() 
{
	leftEnc.process(); 
}
  
void encRightInterrupt() 
{  
	rightEnc.process(); 
}