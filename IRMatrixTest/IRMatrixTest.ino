#include <RobotLib.h>
#include <IEEErobot2018.h>

void setup() 
{
	robotSetup();
}
  
void loop() 
{	 
	drivetrain.printIRMatrix();
}