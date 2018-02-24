#include <RobotLib.h>
#include <IEEErobot2018.h>

//Colors
Color blue("blue");
Color green("green");
Color red("red");	
Color cyan("cyan");
Color magenta("magenta");
Color yellow("yellow");
Color gray("gray");

Color testColor;

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
	//attachInterrupt(0, encLeftInterrupt, CHANGE);
	//attachInterrupt(1, encRightInterrupt, CHANGE);
	
	//Interrupt for Turntable Encoder needed + method
	Serial.print(" -Interrupts- \n");
}

void loop() {
	
	uint16_t clear, red, green, blue;
	delay(60);  //takes 50ms to read 
	//Get the data from the color sensor
	colorSensor.getRawData(&red, &green, &blue, &clear);	
	
	float r = (int)(((float)red/(float)clear) * 256);
	float rr = r / 255;
	float rrr = pow(rr, 2.5);
	float rrrr = (int)(rrr * 255);
	
	float g = (int)(((float)green/(float)clear) * 256);
	float gg = g / 255;
	float ggg = pow(gg, 2.5);
	float gggg = (int)(ggg * 255);
	
	float b = (int)(((float)blue/(float)clear) * 256);
	float bb = b / 255;
	float bbb = pow(bb, 2.5);
	float bbbb = (int)(bbb * 255);
	
	Serial.print(clear);
	
	Serial.print("\tR: ");
	Serial.print(rrrr);
	Serial.print("\tG: ");
	Serial.print(gggg);
	Serial.print("\tB: ");
	Serial.print(bbbb);
	
	testColor.setColor(rrrr, gggg, bbbb);
	Serial.print("\t\t");
	Serial.println(testColor.getColorName());
}
