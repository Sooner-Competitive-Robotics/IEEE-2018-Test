#include <RobotLib.h>

BasicDrive basicDrive;

void setup()
{
	Collection<int> leftM(3), leftE(2), rightM(3), rightE(2);
	
	leftM.add(24); //A
	leftM.add(25); //B
	leftM.add(10); //Enable
	
	leftE.add(1); //A
	leftE.add(2); //B
	
	rightM.add(26); //A
	rightM.add(23); //B
	rightM.add(9); //Enable
	
	rightE.add(3); //A
	rightE.add(4); //B
	
	Serial.begin(9600); //Open up serial communications
	
	basicDrive.begin(leftM,leftE,rightM,rightE);
}

void loop()
{
	basicDrive.setOutput(0, 0);
}
