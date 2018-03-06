#include <RobotLib.h>
#include <IEEErobot2018.h>	

#define PIN_A 22
#define PIN_B 23
#define PIN_EN 13

Motor motor;
float out = 0.0;
int userInput = 0;

void setup()
{
	robotSetup();
	
	//Start the Serial
	//Serial.begin(9600);
	
	//Setup the motor
	//motor.begin(PIN_A, PIN_B, PIN_EN);
	
	//Prompt user
	Serial.println("Enter an integer value for % speed (-100 to 100):");
	
	
}

void loop()
{
	//Is there anything new on the Serial buffer?
	if(Serial.available() > 0)
	{
		//Read user input
		userInput = Serial.parseInt();
		
		//Constrain to -100 - 100, where 100 is max forward output and -100 is backwards full speed
		userInput = userInput > 100 ? 100 : userInput;
		userInput = userInput < -100 ? -100 : userInput;
		
		//Calculate output
		out = userInput / 100.;
		
		//Set the motor's output
		//motor.output(out);	
		intake.raiseRackAndPinion().output(out);
		
		//Indicate output
		Serial.print("Output: ");
		Serial.println(out);
		Serial.println();
		
		//Prompt user again
		Serial.println("Enter an integer value for % speed (-100 to 100):");
		
		Serial.print("\tTicks: ");
		Serial.print(intake.getRackAndPinionEncoder().getTicks());
	
		Serial.print("\tValue: ");
		Serial.println(intake.getRackAndPinionEncoder().getValue());
	}
	
	delay(20);
}