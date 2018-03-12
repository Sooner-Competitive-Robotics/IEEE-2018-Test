#include <RobotLib.h>
#include <IEEErobot2018.h>					

//Drive Status Flag
bool driveComplete = false;
bool resetDrive = true;

float distances[10] = {12, 0, 24, 0, 12, 0, 24, 0, 24, 0};
float angles[10] = {0, -90, -90, 0, 0, 90, 90, 180, 180, 0};
int index = 0;

void setup() 
{
	robotSetup();
}

void loop() 
{
	Serial.println("Following Line");
	drivetrain.followLine();
}