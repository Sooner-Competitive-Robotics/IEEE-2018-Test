#include <RobotLib.h>
#include <IEEErobot2018.h>					

void setup() 
{
	robotSetup();
}

void loop() 
{
	Serial.println(lineFollower.getRaw());
	//Serial.println("Following Line");
	drivetrain.followLine(lineFollower.getDensity(), lineFollower.getPosition());
}