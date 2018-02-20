#include <RobotLib.h>
#include <IEEErobot2018.h>

IRMatrix mat, otherMat;

void setup()
{
	mat.begin(A0, A1, A2, A3, A4);
	otherMat = mat;

	Serial.begin(9600);
}

void loop()
{
	//Serial.println(otherMat.readToBinary());
	otherMat.printRawToSerial();
	
	delay(100);
}