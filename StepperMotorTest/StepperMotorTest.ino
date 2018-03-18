#include <RobotLib.h>

int ENABLE = 4;
int STEP = 49;
int DIR = 50;

StepperMotor stepperMotor;

void setup() 
{
	Serial.begin(9600);
	
	stepperMotor.begin(STEP, DIR);
	stepperMotor.setRPM(50);
}

void loop() 
{
	Serial.println("100 forwards");
	stepperMotor.step(100);
	
	delay(500);
	
	Serial.println("100 back");
	stepperMotor.step(-100);
	
	delay(10000);
}