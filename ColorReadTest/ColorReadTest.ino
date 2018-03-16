#include <RobotLib.h>
#include <IEEErobot2018.h>

Color testColor;

void setup() {
	
	robotSetup();
}

void loop() {
	
	uint16_t clear, red, green, blue;
	delay(60);  //takes 50ms to read 
	//Get the data from the color sensor
	colorSensor.getRawData(&red, &green, &blue, &clear);	
	
	float r = (int)(((float)red/(float)clear) * 256);
	float rr = r / 255;
	float rrr = pow(rr, 2.5);
	float rrrr = (int)(rrr * 255);
	
	float g = (int)(((float)green/(float)clear) * 256);
	float gg = g / 255;
	float ggg = pow(gg, 2.5);
	float gggg = (int)(ggg * 255);
	
	float b = (int)(((float)blue/(float)clear) * 256);
	float bb = b / 255;
	float bbb = pow(bb, 2.5);
	float bbbb = (int)(bbb * 255);
	
	Serial.print(clear);
	
	Serial.print("\tR: ");
	Serial.print(rrrr);
	Serial.print("\tG: ");
	Serial.print(gggg);
	Serial.print("\tB: ");
	Serial.print(bbbb);
	
	testColor.setColor(rrrr, gggg, bbbb);
	Serial.print("\t\t");
	Serial.println(testColor.getColorName());
}
