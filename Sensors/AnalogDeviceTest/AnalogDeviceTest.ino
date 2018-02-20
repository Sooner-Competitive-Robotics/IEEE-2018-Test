#include <RobotLib.h>

AnalogDevice device1, device2;

void setup()
{
	device1.update(A0, INPUT);
	device2 = device1;
	
	Serial.begin(9600);
}

void loop()
{
	Serial.println(device2.read());
}