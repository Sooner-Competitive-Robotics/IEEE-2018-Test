#include <Servo.h>

Servo servo;
int userInput;
void setup()
{
	servo.attach(7);
  Serial.begin(9600);
  servo.write(0);
  
  //Prompt user
  Serial.println("Enter an integer value for angle 0 to 180");
  
}

void loop()
{

  //Is there anything new on the Serial buffer?
  if(Serial.available() > 0)
  {
    //Read user input
    userInput = Serial.parseInt();
    
    //Constrain to -180 - 180, where 100 is max forward output and -100 is backwards full speed
    userInput = userInput > 180 ? 180 : userInput;
    userInput = userInput < 0 ? -0 : userInput;

    servo.write(userInput);
    
    //Indicate output
    Serial.print("Output: ");
    Serial.println(userInput);
    Serial.println();
    
    //Prompt user again
    Serial.println("Enter an integer value for angle 0 to 180");
  }
  delay(20);
}
