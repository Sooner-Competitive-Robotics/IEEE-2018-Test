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
		
		if(intake.getIntakeReturn() != 2)
		{
			Serial.println(intake.getStateString());
			intake.pickUpSequence(currentColor, colorScanned);
		}
		
		if(intake.getIntakeReturn() == 2)
		{
			colorScanned = false;
			//finishedPickingUp = true;
		}
		else if(intake.getIntakeReturn() == 1)
		{
			colorScanned = true;
		}
		else
		{
			delay(50);
		}
	
	//intake.dropOffSequence(currentColor);
	
	delay(1000);
	
}
