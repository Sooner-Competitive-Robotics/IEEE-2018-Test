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
	
	pickUpState = intake.pickUpSequence(currentColor);
	
	Serial.print ("This State: ");
	Serial.print(intake.getStateString());
	Serial.print("\t");
	Serial.print ("This Ticks: ");
	Serial.print(intake.getRackAndPinionEncoder().getTicks());
	Serial.print("\t");
	Serial.print ("This Value: ");
	Serial.print(intake.getRackAndPinionEncoder().getValue());
	Serial.println("\n");
	
	if(pickUpState == 2)
	{
		Serial.println("Done!");
		delay(5000);
	}
	else
	{
		delay(50);
	}
	
	//intake.dropOffSequence(currentColor);
	
	delay(1000);
	
}
