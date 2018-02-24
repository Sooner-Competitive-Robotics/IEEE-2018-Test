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

//Debug vars
float left, right, dist;

void encLeftInterrupt() 
{
	drivetrain.getLeftEncoder().process(); 
}
  
void encRightInterrupt() 
{  
	drivetrain.getRightEncoder().process(); 
}

void setup() 
{	
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
	leftEnc.setConstant(rightEncoderConstant);
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

void loop()
{	
	if(!driveComplete)
	{
		updateGyro();
		
		Serial.print(" \tYaw: ");
		Serial.print(yaw);
		Serial.print(" \tPitch: ");
		Serial.print(pitch);
		Serial.print(" \tRoll: ");
		Serial.print(roll);
		
		left = drivetrain.getLeftEncoder().getValue();
		right = drivetrain.getRightEncoder().getValue();
		dist = (right + left) / 2;
		
		Serial.print("\tL: ");
		Serial.print(left);
		Serial.print("\tR:");
		Serial.print(right);
		Serial.print("\tDIST: ");
		Serial.println(dist);
		
		//Drive 12 inches straight
		driveComplete = drivetrain.drive(distances[index], angles[index], yaw, resetDrive);
		resetDrive= false;
	}
	else
	{
		//Reset flags
		resetDrive = true;
		driveComplete = false;
		
		//Onto the next instruction
		index = (index == 9) ? 0 : index + 1;
		
		//Wait a second to assess performance
		delay(1000);
	}
}
