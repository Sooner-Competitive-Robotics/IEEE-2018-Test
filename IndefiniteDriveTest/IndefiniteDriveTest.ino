#include <RobotLib.h>
#include <IEEErobot2018.h>					

bool initDrive = true;

void setup() 
{
	robotSetup();
}

void loop() 
{
	if(initDrive)
	{
		initDrive = false;
	}
	
	updateGyro();
	delay(20);
	
	if(millis() > 5000)
	{
		drivetrain.setOutput(0, 0);
	}
	else
	{
		drivetrain.driveIndefinitely(0.35, 0, yaw, initDrive);
	}
}