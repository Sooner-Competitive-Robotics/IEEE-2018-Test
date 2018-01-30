#include <RobotLib.h>
#include <IEEErobot2018.h>

#define pinLeftMot1 
#define pinLeftMot2 
#define pinRightMot1
#define pinRightMot2
#define pinGyro1 //should have same pin on i2c chain
#define pinGyro2
#define pinLeftEnc1
#define pinLeftEnc2
#define pinRightEnc1
#define pinRightEnc2
#define pinIRMatrix1
#define pinIRMatrix2
#define pinIRMatrix3
#define pinIRMatrix4
#define pinIRMatrix5 

void setup() {
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
  
	attachInterrupt(0, encLeftInterrupt, CHANGE);
	attachInterrupt(0, encRightInterrupt, CHANGE);
	
	leftEnc.setConstant(1);
	rightEnc.setConstant(1);
}
  
void loop() 
{	  
	drivetrain.drive(5000, 0);	  
}
  
void encLeftInterrupt() 
{
	leftEnc.process(); 
}
  
void encRightInterrupt() 
{  
	rightEnc.process(); 
}

