#define PIN 19

void setup()
{
	Serial.begin(9600);
	
	pinMode(PIN, INPUT);
	digitalWrite(PIN, HIGH);
}

void loop()
{
	Serial.println(digitalRead(PIN));
}