#include <RobotLib.h>
#include <IEEErobot2018.h>
#define pin 5

Turntable turnTable;

void setup() 
{  
	robotSetup();
	turnTable = intake.getTurnTable();
}

void loop() 
{
	//Check idle position
	turnTable.setPosition(); // IDLE_ANGLE
	delay(1000);
	
	//Check basic degrees
	turnTable.setPosition(0);
	delay(1000);
	turnTable.setPosition(90);
	delay(1000);
	turnTable.setPosition(180);
	delay(1000);
	turnTable.setPosition(0);
	delay(1000);
	turnTable.setPosition(-90); //Servo might not be able to go this far I wasn't sure
	delay(1000);
	turnTable.setPosition(-180); //Servo might not be able to go this far I wasn't sure
	delay(1000);
	
	//Check colors
	turnTable.setPosition(blue);
	delay(1000);
	turnTable.setPosition(green);
	delay(1000);
	turnTable.setPosition(red);
	delay(1000);
	turnTable.setPosition(cyan);
	delay(1000);
	turnTable.setPosition(magenta);
	delay(1000);
	turnTable.setPosition(yellow);
	delay(1000);
	turnTable.setPosition(gray);
	delay(1000);
}
