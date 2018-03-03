#include <RobotLib.h>
#include <IEEErobot2018.h>
#define pin //SET THIS
Turntable tt(pin);
/*
Color blue("blue");
Color green("green");
Color red("red");
Color cyan("cyan");
Color magenta("magenta");
Color yellow("yellow");
Color gray("gray");
*/
void setup() 
{  
}

void loop() 
{

 //Check idle position
  tt.setPosition(); // IDLE_ANGLE
  delay(1000);

  //Check basic degrees
  tt.setPosition(0);
   delay(1000);
  tt.setPosition(90);
   delay(1000);
  tt.setPosition(180);
   delay(1000);
  tt.setPosition(0);
   delay(100
  tt.setPosition(-90); //Servo might not be able to go this far I wasn't sure
   delay(1000);
  tt.setPosition(-180); //Servo might not be able to go this far I wasn't sure
  delay(1000);
  
  //Check colors
   tt.setPosition(blue);
   delay(1000);
   tt.setPosition(green);
   delay(1000);
   tt.setPosition(red);
   delay(1000);
   tt.setPosition(cyan);
   delay(1000);
   tt.setPosition(magenta);
   delay(1000);
   tt.setPosition(yellow);
   delay(1000);
   tt.setPosition(gray);
   delay(1000);
}
