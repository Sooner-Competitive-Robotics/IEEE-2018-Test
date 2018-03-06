#include <RobotLib.h>
#include <IEEErobot2018.h>

//Drive Status Flag
bool turnComplete = false;
bool resetDrive = true;

int index = 0;

//Debug vars
float left, right, dist;

int angleInput = 90;

void setup() 
{	
	robotSetup();
}

void loop()
{	
	if(!turnComplete)
	{		
		updateGyro();
		
		Serial.print(" Yaw: ");
		Serial.print(yaw);
		Serial.print(" \tPitch: ");
		Serial.print(pitch);
		Serial.print(" \tRoll: ");
		Serial.print(roll);
		
		
		left = drivetrain.getLeftEncoder().getValue();
		right = drivetrain.getRightEncoder().getValue();
		dist = (right + left) / 2;
		
		/*
		Serial.print("\tL: ");
		Serial.print(left);
		Serial.print("\tR:");
		Serial.print(right);
		Serial.print("\tDIST: ");
		Serial.print(dist);
		*/
		
		//Turn to angle straight
		turnComplete = drivetrain.drive(0, angleInput, yaw, resetDrive);
		resetDrive= false;
		
		Serial.print("\tStatus: ");
		Serial.print(turnComplete);
		
		Serial.print("\n");
	}
	else
	{
		/*
		if(Serial.available() > 0)
		{
			//Get new angle
			angleInput = Serial.read();
			
			//Reset flags
			resetDrive = true;
			driveComplete = false;
		}*/
		
		resetDrive = true;
		turnComplete = false;
		
		//Wait a second to assess performance
		//delay(10000);
	}
}
