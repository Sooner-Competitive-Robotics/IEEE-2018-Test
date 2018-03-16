#include <RobotLib.h>
#include <IEEErobot2018.h>

void setup() 
{  
	robotSetup();
}

void loop() 
{
	//Check idle position
	Serial.println("IDLE check");
	intake.turnTable.setPosition(); // IDLE_ANGLE
	delay(50);
	
/*	delay(1000);

	//Check colors
	Serial.println("BLUE check");
	intake.turnTable.setPosition(blue);
	delay(1000);
	Serial.println("GREEN check");
	intake.turnTable.setPosition(green);
	delay(1000);
	Serial.println("RED check");
	intake.turnTable.setPosition(red);
	delay(1000);
	Serial.println("CYAN check");
	intake.turnTable.setPosition(cyan);
	delay(1000);
	Serial.println("MAGENTA check");
	intake.turnTable.setPosition(magenta);
	delay(1000);
	Serial.println("YELLOW check");
	intake.turnTable.setPosition(yellow);
	delay(1000);
	Serial.println("GRAY check");
	intake.turnTable.setPosition(gray);
	delay(1000);
	
*/
}
