#include <RobotLib.h>
#include <IEEErobot2018.h>

//Drive Status Flag
bool driveComplete = false;
bool resetDrive = true;

float distances[10] = {12, 0, 24, 0, 12, 0, 24, 0, 24, 0};
float angles[10] = {0, -90, -90, 0, 0, 90, 90, 180, 180, 0};
int index = 0;

//Debug vars
float left, right, dist;

void setup() 
{	
	robotSetup();
}

void loop()
{	
	if(!driveComplete)
	{
		Serial.print("Drive Command ID: ");
		Serial.print(index);
		
		//updateGyro();
		
		Serial.print(" \tYaw: ");
		Serial.print(yaw);
		Serial.print(" \tPitch: ");
		Serial.print(pitch);
		Serial.print(" \tRoll: ");
		Serial.print(roll);
		
		left = drivetrain.getLeftEncoder().getValue();
		right = drivetrain.getRightEncoder().getValue();
		dist = (right + left) / 2;
		
		//Serial.print("\tL: ");
		//Serial.print(left);
		//Serial.print("\tR:");
		//Serial.print(right);
		Serial.print("\tDIST: ");
		Serial.print(dist);
		
		//Drive 12 inches straight
		driveComplete = drivetrain.drive(distances[index], angles[index], yaw, resetDrive);
		resetDrive= false;
		
		Serial.print("\tStatus: ");
		Serial.print(driveComplete);
		
		Serial.print("\n");
	}
	else
	{
		//Reset flags
		resetDrive = true;
		driveComplete = false;
		
		drivetrain.setOutput(0, 0);
		//Onto the next instruction
		//index = (index == 9) ? 0 : index + 1;
		
		//Wait a second to assess performance
		delay(1000);
	}
}
