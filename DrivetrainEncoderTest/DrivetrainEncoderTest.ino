#include <RobotLib.h>
#include <IEEErobot2018.h>
#include <RobotPins.h> //found in IEEErobot2018, but left out of IEEErobot2018.h for now

Drivetrain drivetrain;
Intake intake;						
Adafruit_BNO055 gyro;
Adafruit_TCS34725 colorSensor(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

Color color;
float redRaw;
float greenRaw;
float blueRaw;
float pitch;
float roll;
float yaw;

void setup() {
	
	Serial.begin(9600);
	Serial.print(" -Has Begun- ");
	
	//Drivetrain drivetrain;
	//Intake intake;
	
	//--Drivetrain
	Motor leftMot;
	Motor rightMot;
	Encoder leftEnc(pinLeftEnc1, pinLeftEnc2);
	Encoder rightEnc(pinRightEnc1, pinRightEnc2);
	DigitalDevice mDetector(pinMetDet, INPUT);
	IRMatrix mat(pinIRMatrix1, pinIRMatrix2, pinIRMatrix3, pinIRMatrix4, pinIRMatrix5);
	
	//--Gyro declaration
	Adafruit_BNO055 gyro;
  
	//--ColorSensor declaration
	Adafruit_TCS34725 colorSensor(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
  
	//--Drivetrain
	leftMot.begin(pinLeftMot1, pinLeftMot2, pinLeftMotEnb);
	rightMot.begin(pinRightMot1, pinRightMot2, pinRightMotEnb);
	//mat.begin(pinIRMatrix1, pinIRMatrix2, pinIRMatrix3, pinIRMatrix4, pinIRMatrix5);
	//drivetrain.begin(leftMot, rightMot, leftEnc, rightEnc, gyro, mat, mDetector);				//ERROR HERE in Matrix reference inside begin
	
	Serial.print(" -Drive Has Begun- ");
	
	//--Intake
	Encoder tEncoder(pinIntakeEnc1, pinIntakeEnc2);
	DigitalDevice lSwitch(pinLimSwitch, INPUT);
	Electromagnet eMagnet(pinElecMag);
	Motor iMotor;	
	Turntable turntable(turntableServoPin);
	
	//--Intake
	iMotor.begin(pinIbtakeMot1, pinIbtakeMot2, pinIbtakeMotEnb);
	eMagnet.initialize(pinElecMag);
	//intake.begin(iMotor, tEncoder, mDetector, lSwitch, eMagnet, turntable, colorSensor, colorServoPin);	
  
	Serial.print(" -Intake Has Begun- ");
	
	//--Interrupts
	attachInterrupt(2, encLeftInterrupt, CHANGE);
	attachInterrupt(3, encRightInterrupt, CHANGE);
	
	attachInterrupt(0, updateGyro, CHANGE);
	attachInterrupt(0, updateColorSensor, CHANGE);
	
	//Interrupt for Turntable Encoder needed + method
	
	Serial.print(" -Interrupts- ");
}
  
void loop() 
{	 
	Serial.print("12");
	Serial.print("Left: " + drivetrain.getLeftEncoder().getTicks());
	Serial.print("Right: " + drivetrain.getRightEncoder().getTicks());
}

void encLeftInterrupt() 
{
	drivetrain.getLeftEncoder().process(); 
}
  
void encRightInterrupt() 
{  
	drivetrain.getRightEncoder().process(); 
}

void updateGyro()
{
	delay(60);  // takes 50ms to read 
	
	//Get the data from the gyro
	imu::Vector<3> euler = gyro.getVector(Adafruit_BNO055::VECTOR_EULER);
	
	pitch = euler.x();
	roll = euler.y();
	yaw = euler.z();

	drivetrain.setYaw(yaw);
}

void updateColorSensor()
{
	uint16_t clear, red, green, blue;

	delay(60);  // takes 50ms to read 
	
	//Get the data from the color sensor
	colorSensor.getRawData(&red, &green, &blue, &clear);	
	
	redRaw = red;
	greenRaw = green;
	blueRaw = blue;	
	
	color = Color(red,green,blue);
	//return c;
}


Color returnColor()	//Use to pass into intake
{
	//Color c(redRaw,greenRaw,blueRaw);
	return color;
}
