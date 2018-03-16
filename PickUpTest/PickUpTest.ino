#include <RobotLib.h>
#include <IEEErobot2018.h>

int pickUpState;
Color c("cyan");
bool aBool = true;

void setup()
{
	robotSetup();
}

void loop()
{
	if (aBool)
	{
		//intake.resetRack();
		aBool = false;
	}
	
	pickUpState = intake.pickUpSequence(c);
	
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
		aBool = true;
		Serial.println("Done!");
		delay(5000);
	}
	else
	{
		delay(50);
	}
}