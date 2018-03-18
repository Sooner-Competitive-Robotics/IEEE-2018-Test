#include <RobotLib.h>
#include <IEEErobot2018.h>

int pickUpState;
bool colorScanned = false;
Color c("gray");

void setup()
{
	robotSetup();
}

void loop()
{
	updateColorSensor();
	
	pickUpState = intake.pickUpSequence(currentColor, colorScanned);
/*	
	Serial.print ("This State: ");
	Serial.print(intake.getStateString());
	Serial.print("\t");
	Serial.print ("This Ticks: ");
	Serial.print(intake.getRackAndPinionEncoder().getTicks());
	Serial.print("\t");
	Serial.print ("This Value: ");
	Serial.print(intake.getRackAndPinionEncoder().getValue());
	Serial.print("\t");
*/	
	Serial.print("R: ");
	Serial.print(currentColor.getRed());
	Serial.print("\tG: ");
	Serial.print(currentColor.getGreen());
	Serial.print("\tB: ");
	Serial.print(currentColor.getBlue());
	Serial.print("\t");
	Serial.println(currentColor.getColorName());
	
	if(pickUpState == 2)
	{
		Serial.println("Done!");
		colorScanned = false;
		delay(2500);
	}
	else if (pickUpState == 1)
	{
		colorScanned = true;
	}
	else
	{
		delay(50);
	}
}
