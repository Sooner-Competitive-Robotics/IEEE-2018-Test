#include <RobotLib.h>
#include <IEEErobot2018.h>

//Colors
Color blue("blue");
Color green("green");
Color red("red");	
Color cyan("cyan");
Color magenta("magenta");
Color yellow("yellow");
Color gray("gray");

Drivetrain drivetrain;
Intake intake;						

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
