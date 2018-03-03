#include <RobotLib.h>
#include <IEEErobot2018.h>

Drivetrain drivetrain;
Intake intake;						

void setup() {
	
	Serial.begin(9600);
	Serial.print(" -Has Begun- \n");
	
	//--Drivetrain
	Motor leftMot;
	Motor rightMot;
	Encoder leftEnc(pinLeftEnc1, pinLeftEnc2);
	Encoder rightEnc(pinRightEnc1, pinRightEnc2);
	DigitalDevice mDetector(pinMetDet, INPUT);
	IRMatrix mat(pinIRMatrix1, pinIRMatrix2, pinIRMatrix3, pinIRMatrix4, pinIRMatrix5, pinIRMatrix6);

	//--Drivetrain
	leftMot.begin(pinLeftMot1, pinLeftMot2, pinLeftMotEnb);
	rightMot.begin(pinRightMot1, pinRightMot2, pinRightMotEnb);
	drivetrain.begin(leftMot, rightMot, leftEnc, rightEnc, mat, mDetector);
	
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
  
	Serial.print(" -Intake Has Begun- \n");
	
	//--Interrupts
	attachInterrupt(0, encLeftInterrupt, CHANGE);
	attachInterrupt(1, encRightInterrupt, CHANGE);
	
	//Interrupt for Turntable Encoder needed + method
	Serial.print(" -Interrupts- \n");
}
  
void loop() 
{	 
	//Serial.print("Value: ");
	//Serial.println(drivetrain.getIRMatrixValue());
	
	drivetrain.printIRMatrix();
}
void encLeftInterrupt() 
{
	drivetrain.getLeftEncoder().process(); 
}
  
void encRightInterrupt() 
{  
	drivetrain.getRightEncoder().process(); 
}
