#include <Electromagnet.h>

Electromagnet magnet(5);

void setup() {

}

void loop() {

	magnet.pickUp();

	delay(5000);

	magnet.drop();
	
	delay(5000);
}