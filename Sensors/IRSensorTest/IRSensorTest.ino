#define IR_PIN1 A0
#define IR_PIN2 A1
#define IR_PIN3 A2
#define IR_PIN4 A3
#define IR_PIN5 A4
#define IR_PIN6 A5

void printIR(int pin)
{
	Serial.print(analogRead(pin));
}

void setup()
{
	Serial.begin(9600);
}

void loop()
{
	printIR(IR_PIN1);
	Serial.print("\t");
	printIR(IR_PIN2);
	Serial.print("\t");
	printIR(IR_PIN3);
	Serial.print("\t");
	printIR(IR_PIN4);
	Serial.print("\t");
	printIR(IR_PIN5);
	Serial.print("\t");
	printIR(IR_PIN6);
	
	Serial.println();
	delay(100);
}