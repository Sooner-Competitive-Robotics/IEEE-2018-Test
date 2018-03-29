#include <RobotLib.h>
#include <IEEErobot2018.h>

//Drive Status Flag
bool driveComplete = false;
bool resetDrive = true;

int coinCount = 0;
int doneThis = 0;

void setup() 
{  
	robotSetup();
}

void loop() {
	
	while(!driveComplete)
	{
		driveComplete = drivetrain.drive(16, 0, yaw, resetDrive);
		Serial.print(drivetrain.getRightOutput());
		Serial.print(drivetrain.getLeftOutput());
		Serial.println("Step 1");
		updateGyro();
		resetDrive = false;
	}
	resetGyro();
	driveComplete = false;
	resetDrive = true;
	
	while(!driveComplete)
	{
		driveComplete = drivetrain.drive(-16, 0, yaw, resetDrive);
		Serial.print(drivetrain.getRightOutput());
		Serial.print(drivetrain.getLeftOutput());
		Serial.println("Step 1");
		updateGyro();
		resetDrive = false;
	}
	resetGyro();
	driveComplete = false;
	resetDrive = true;
	
	delay(3000);
}	
