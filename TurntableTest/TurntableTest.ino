#include <RobotLib.h>
#include <IEEErobot2018.h>
#define pin 5

void setup() 
{  
	robotSetup();
}

void loop() 
{
	//Check idle position
	Serial.println("IDLE check");
	intake.turnTable.setPosition(); // IDLE_ANGLE
	delay(1000);
	
	//Check basic degrees
	Serial.println("0 check");
	intake.turnTable.setPosition(0);
	delay(1000);
	Serial.println("90 check");
	intake.turnTable.setPosition(90);
	delay(1000);
	Serial.println("180 check");
	intake.turnTable.setPosition(180);
	delay(1000);
	Serial.println("0 check");
	intake.turnTable.setPosition(0);
	delay(1000);
	Serial.println("-90 check");
	intake.turnTable.setPosition(-90); //Servo might not be able to go this far I wasn't sure
	delay(1000);
	Serial.println("-180 check");
	intake.turnTable.setPosition(-180); //Servo might not be able to go this far I wasn't sure
	delay(1000);
	
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
}
