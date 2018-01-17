#define IR_PIN A0

int val = 0;

void setup()
{
	Serial.begin(9600);
}

void loop()
{
	val = analogRead(IR_PIN);
	Serial.println(val);
	
	delay(100);
}