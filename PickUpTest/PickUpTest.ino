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
	
	Serial.print(pickUpState);
	Serial.print("\t");
	Serial.println(tEncoder.getValue());
	Serial.print("\n");
	
	if(pickUpState == 2)
	{
		Serial.println("Done!");
		delay(2000);
	}
	else
	{
		delay(50);
	}
}