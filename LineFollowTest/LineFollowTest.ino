#include <RobotLib.h>
#include <IEEErobot2018.h>					

//Drive Status Flag
bool driveComplete = false;
bool resetDrive = true;

void setup() 
{
	robotSetup();
}

void loop() 
{
	//Serial.println("Following Line");
	drivetrain.followLine();
}