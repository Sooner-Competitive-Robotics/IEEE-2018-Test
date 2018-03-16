#include <Servo.h>

Servo servo;
int angle = 1000;

void setup()
{
	servo.attach(7);
	Serial.begin(9600);
}

void loop()
{
	if(Serial.available() > 0)
	{
		angle = Serial.parseInt();

		Serial.print("Writing to angle: ");
		Serial.println(angle);
	}
	
	servo.writeMicroseconds(angle);
	delay(50);
}