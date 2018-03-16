#include <Servo.h>

Servo servo;
int angle = 90;

void setup()
{
	servo.attach(38);
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
	
	//servo.writeMicroseconds(angle);
	servo.write(angle);
	delay(50);
}

/*
E		935

R1		1030
R2		1135
R3		1245

C4		1360

L1		840
L2		760
L3		680
*/