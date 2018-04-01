#include <RobotLib.h>
#include <IEEErobot2018.h>

void setup()
{
	robotSetup();
}

void loop()
{
	drivetrain.step(1600, 1600);
	
	while(true){}
}