#include <Adafruit_TCS34725.h>

Adafruit_TCS34725 colorSensor(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

float rrrr, gggg, bbbb;

void updateColorSensor()
{
	uint16_t clear, red, green, blue;

	delay(50);  //takes 50ms to read 
	
	//Get the data from the color sensor
	colorSensor.getRawData(&red, &green, &blue, &clear);	
		
	//Do calculations on raw colors to convert to more readable values
	float r = (int)(((float)red/(float)clear) * 256);
	float rr = r / 255;
	float rrr = pow(rr, 2.5);
	rrrr = (int)(rrr * 255);
	
	float g = (int)(((float)green/(float)clear) * 256);
	float gg = g / 255;
	float ggg = pow(gg, 2.5);
	gggg = (int)(ggg * 255);
	
	float b = (int)(((float)blue/(float)clear) * 256);
	float bb = b / 255;
	float bbb = pow(bb, 2.5);
	bbbb = (int)(bbb * 255);	
	
	//set the current color reference to color currently reading
	//currentColor.setColor(rrrr, gggg, bbbb);
	//currentColor = Color(rrrr, gggg, bbbb);
}

void setup()
{
	Serial.begin(9600);
	Serial.println("Initializing...");
	
	if(!colorSensor.begin())
	{
		Serial.println("Connection Error!");
	}
	
	Serial.println("Starting Program");
}

void loop()
{
	updateColorSensor();
	
	Serial.print(rrrr);
	Serial.print("\t");
	Serial.print(gggg);
	Serial.print("\t");
	Serial.print(bbbb);
	Serial.println();
}