#define FRONT_LEFT A1
#define FRONT_RIGHT A0
#define BACK_LEFT A2
#define BACK_RIGHT A3


void setup()
{
	Serial.begin(9600);
}

void loop()
{
	Serial.print("FL: ");
	Serial.print(analogRead(FRONT_LEFT));
	Serial.print("\tFR: ");
	Serial.print(analogRead(FRONT_RIGHT));
	Serial.print("\tBL: ");
	Serial.print(analogRead(BACK_LEFT));
	Serial.print("\tBR: ");
	Serial.print(analogRead(BACK_RIGHT));
	Serial.println();
}