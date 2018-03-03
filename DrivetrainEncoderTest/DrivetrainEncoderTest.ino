#include <RobotLib.h>
#include <IEEErobot2018.h>					

void setup() {	
	robotSetup();
}
  
void loop() 
{	 
	Serial.print("Left: ");
	Serial.print(drivetrain.getLeftEncoder().getTicks());
	Serial.print("\tRight: ");
	Serial.print(drivetrain.getRightEncoder().getTicks());
	
	Serial.print("\tLeft: ");
	Serial.print(drivetrain.getLeftEncoder().getValue());
	Serial.print("\tRight: ");
	Serial.println(drivetrain.getRightEncoder().getValue());
}
