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
#define turntableServoPin 0
#define colorServoPin 0
#define pinIbtakeMot1 0
#define pinIbtakeMot2 0
#define pinIbtakeMotEnb 0

Drivetrain drivetrain;
Intake intake;

void setup() {
	//Drivetrain
	Motor leftMot = Motor();
	Motor rightMot = Motor();
	Encoder leftEnc = Encoder(pinLeftEnc1, pinLeftEnc2);
	Encoder rightEnc = Encoder(pinRightEnc1, pinRightEnc2);
	DigitalDevice mDetector = DigitalDevice(pinMetDet, INPUT);
	IRMatrix matrix = IRMatrix(pinIRMatrix1, pinIRMatrix2, pinIRMatrix3, pinIRMatrix4, pinIRMatrix5);
	
	//TODO: Make sure this is declared properly
	Adafruit_BNO055 gyro = Adafruit_BNO055();
  
	//Drivetrain
	leftMot.begin(pinLeftMot1, pinLeftMot2, pinLeftMotEnb);
	rightMot.begin(pinRightMot1, pinRightMot2, pinRightMotEnb);
	matrix.begin(pinIRMatrix1, pinIRMatrix2, pinIRMatrix3, pinIRMatrix4, pinIRMatrix5);
	drivetrain.begin(leftMot, rightMot, leftEnc, rightEnc, gyro, matrix, mDetector);
	
	//Intake
	Encoder tEncoder = Encoder(pinIntakeEnc1, pinIntakeEnc2);
	DigitalDevice lSwitch = DigitalDevice(pinLimSwitch, INPUT);
	Electromagnet eMagnet = Electromagnet(pinElecMag);
	Motor iMotor = Motor();	
	Turntable turntable = Turntable(turntableServoPin);
	
	//ColorSensor declaration
	Adafruit_TCS34725 colorSensor = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
	
	//Intake
	iMotor.begin(pinIbtakeMot1, pinIbtakeMot2, pinIbtakeMotEnb);
	eMagnet.initialize(pinElecMag);
	Intake intake = Intake(iMotor, tEncoder, mDetector, lSwitch, eMagnet, turntable, colorSensor, colorServoPin);
  
	//Interrupts
	attachInterrupt(0, encLeftInterrupt, CHANGE);
	attachInterrupt(0, encRightInterrupt, CHANGE);
	//Interrupt for Turntable Encoder needed + method
	
	Serial.begin(9600);
}
  
void loop() 
{	  
	//drivetrain.drive(5000, 0);	 
	Serial.print("Left: " + drivetrain.getLeftEncoder().getTicks());
	Serial.print("Right: " + drivetrain.getRightEncoder().getTicks());
	
	Serial.print(drivetrain.getGyro().getYaw());
}
  
void encLeftInterrupt() 
{
	drivetrain.getLeftEncoder().process(); 
}
  
void encRightInterrupt() 
{  
	drivetrain.getRightEncoder().process(); 
}

