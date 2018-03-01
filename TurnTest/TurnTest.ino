#include <RobotLib.h>
#include <IEEErobot2018.h>

//Drive Status Flag
bool driveComplete = false;
bool resetDrive = true;

int index = 0;

//Debug vars
float left, right, dist;

int angleInput = 0;

void setup() 
{	
	robotSetup();
}

void loop()
{	
	if(!driveComplete)
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
		
		Serial.print("\tL: ");
		Serial.print(left);
		Serial.print("\tR:");
		Serial.print(right);
		Serial.print("\tDIST: ");
		Serial.print(dist);
		
		//Drive 12 inches straight
		driveComplete = drivetrain.drive(0, angleInput, yaw, resetDrive);
		resetDrive= false;
		
		Serial.print("\tStatus: ");
		Serial.print(driveComplete);
		
		Serial.print("\n");
	}
	else
	{
		if(Serial.available() > 0)
		{
			//Get new angle
			angleInput = Serial.read();
			
			//Reset flags
			resetDrive = true;
			driveComplete = false;
		}
		
		//Wait a second to assess performance
		delay(1000);
	}
}
