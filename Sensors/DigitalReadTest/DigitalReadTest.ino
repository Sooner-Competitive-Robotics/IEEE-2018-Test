#define PIN 20

void setup()
{
	Serial.begin(9600);
	
	pinMode(21, INPUT);
	//digitalWrite(PIN, HIGH);
}

void loop()
{
	Serial.println(digitalRead(21));
}
