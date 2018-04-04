#include <RobotLib.h>
#include <IEEErobot2018.h>

void setup() 
{	
	robotSetup();
}

void loop() 
{
	// DO NOT RUN UNTIL INTAKE_CONSTATNS HAVE BEEN TESTED FOR AND ADDED TO INTAKECONSTANTS.H !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	
	while (!intake.getLowSwitch())
	{
		Serial.println("Reseting");
		iMotor.output(-.4);
	}
	
	//updateColorSensor();
		
	while (!intake.coinDetected())
	{
		Serial.print(intake.getStateString());
		Serial.print("LOOKING FOR COIN\n");	
	}
		
	while (intake.getIntakeReturn() != 2)
	{
		Serial.println(intake.getStateString());
		intake.pickUpSequence(currentColor, colorScanned);
				
		if(intake.getIntakeReturn() == 1)
		{
			colorScanned = true;
		}
		else
		{
			delay(50);
		}
	}
	
	colorScanned = false;
	//intake.dropOffSequence(currentColor);
	
	delay(1000);
	
}
