#include <RobotLib.h>
#include <IEEErobot2018.h>

int pickUpState;
Color c("cyan");

void setup()
{
	robotSetup();
}

void loop()
{
	pickUpState = intake.pickUpSequence(c);
	
	Serial.print ("This State: ");
	Serial.print(intake.getStateString());
	Serial.print("\t");
	Serial.print ("This Ticks: ");
	Serial.print(intake.getRackAndPinionEncoder().getTicks());
	Serial.print("\t");
	Serial.print ("This Value: ");
	Serial.print(intake.getRackAndPinionEncoder().getValue());
	Serial.print("\t");
	
	Serial.println(testColor.getColorName());
	
	if(pickUpState == 2)
	{
		Serial.println("Done!");
		delay(5000);
	}
	else
	{
		delay(50);
	}
}