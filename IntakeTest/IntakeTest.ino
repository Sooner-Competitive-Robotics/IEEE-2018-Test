#include <RobotLib.h>
#include <IEEErobot2018.h>

void setup() 
{	
	robotSetup();
}

void loop() 
{
	// DO NOT RUN UNTIL INTAKE_CONSTATNS HAVE BEEN TESTED FOR AND ADDED TO INTAKECONSTANTS.H !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	
	updateColorSensor();
	
	delay(100);
	
	intake.pickUpSequenceA(currentColor);
	
	delay(100);
	
	intake.dropOffSequence(currentColor);
	
	delay(1000);
	
}
