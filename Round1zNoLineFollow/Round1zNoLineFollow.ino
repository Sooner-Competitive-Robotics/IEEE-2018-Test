#include <RobotLib.h>
#include <IEEErobot2018.h>

//Drive Status Flag
bool driveComplete = false;
bool resetDrive = true;

int coinCount = 0;
int doneThis = 0;

void setup() 
{  
	robotSetup();
}

void loop() {
	
	// put your main code here, to run repeatedly:
	while(!driveComplete)
	{
		driveComplete = drivetrain.drive(16, 0, yaw, resetDrive);
		Serial.print(drivetrain.getRightOutput());
		Serial.print(drivetrain.getLeftOutput());
		Serial.println("Step 1");
		updateGyro();
		resetDrive = false;
	}
	resetGyro();
	driveComplete = false;
	resetDrive = true;
	
	while (!driveComplete)
	{
		driveComplete = drivetrain.searchForward(lineFollower.getDensity(), yaw);
		Serial.println("Step 2");
		updateGyro();
		Serial.println("Step 2-1");
		resetDrive = false;
		Serial.println("Step 2-2");
	}
	resetGyro();
	Serial.println("Step 2-3");
	driveComplete = false;
	Serial.println("Step 2-4");
	resetDrive = true;
	Serial.println("Step 2-5");
	
	while (!driveComplete)
	{
		Serial.println("Step 3");
		driveComplete = drivetrain.drive(0, 90, yaw, resetDrive);
		updateGyro();
		resetDrive = false;
	}
	resetGyro();
	driveComplete = false;
	resetDrive = true;
	
	while(!intake.coinDetected())
	{
		updateGyro();
		Serial.println("Step 4");
		drivetrain.driveIndefinitely(0.25, 0, yaw, true);		
	}
	drivetrain.driveIndefinitely(0,0,yaw,true);
	
	while (!driveComplete)
	{
		driveComplete = drivetrain.drive(distMetalDetectToIntake, 0, yaw, resetDrive);
		updateGyro();
		resetDrive = false;
	}
	resetGyro();
	driveComplete = false;
	resetDrive = true;
	
	while(intake.getIntakeReturn() != 2)
	{
		updateColorSensor();
			
			if(!finishedPickingUp)
			{
				intake.pickUpSequence(currentColor, colorScanned);
			}
			
			if(intake.getIntakeReturn() == 2)
			{
				colorScanned = false;
				finishedPickingUp = true;
			}
			else if(intake.getIntakeReturn() == 1)
			{
				colorScanned = true;
			}
			else
			{
				delay(50);
			}
	}
	
	//sitStillPickup();
	
	delay(3000);
	
	/*
	while(!driveComplete)
	{
		Serial.println("Step 5");
		driveComplete = drivetrain.drive(0, -135, yaw, resetDrive);
		updateGyro();
		resetDrive = false;
	}
	resetGyro();
	driveComplete = false;
	resetDrive = true;

	while(!intake.coinDetected())
	{
		updateGyro();
		drivetrain.driveIndefinitely(0.25, 0, yaw, true);		
	}
	
	sitStillPickup();
	resetGyro();
	driveComplete = false;
	resetDrive = true;
	
	driveCoinDetected();
	resetGyro();
	driveComplete = false;
	resetDrive = true;
	
	sitStillPickup();
	resetGyro();
	driveComplete = false;
	resetDrive = true;
	
	driveCoinDetected();
	resetGyro();
	driveComplete = false;
	resetDrive = true;
	
	sitStillPickup();
	resetGyro();
	driveComplete = false;
	resetDrive = true;
	
	while(!driveComplete)
	{
		driveComplete = drivetrain.drive(0, -135, yaw, resetDrive);
		updateGyro();
		resetDrive = false;
	}
	resetGyro();
	driveComplete = false;
	resetDrive = true;
	
	driveCoinDetected();
	resetGyro();
	driveComplete = false;
	resetDrive = true;
	
	sitStillPickup();
	resetGyro();
	driveComplete = false;
	resetDrive = true;
	
	while(!driveComplete)
	{
		driveComplete = drivetrain.drive(0, -90, yaw, resetDrive);
		updateGyro();
		resetDrive = false;
	}
	resetGyro();
	driveComplete = false;
	resetDrive = true;
	
	driveCoinDetected();
	resetGyro();
	driveComplete = false;
	resetDrive = true;
	
	sitStillPickup();
	resetGyro();
	driveComplete = false;
	resetDrive = true;
	
	driveCoinDetected();
	resetGyro();
	driveComplete = false;
	resetDrive = true;
	
	sitStillPickup();
	resetGyro();
	driveComplete = false;
	resetDrive = true;
	
	while(!driveComplete)
	{
		driveComplete = drivetrain.drive(0, -90, yaw, resetDrive);
		updateGyro();
		resetDrive = false;
	}
	resetGyro();
	driveComplete = false;
	resetDrive = true;
	
	driveCoinDetected();
	resetGyro();
	driveComplete = false;
	resetDrive = true;
	
	sitStillPickup();
	resetGyro();
	driveComplete = false;
	resetDrive = true;
	
	while(!driveComplete)
	{
		driveComplete = drivetrain.drive(0, -135, yaw, resetDrive);
		updateGyro();
		resetDrive = false;
	}
	resetGyro();
	driveComplete = false;
	resetDrive = true;
	
	driveCoinDetected();
	resetGyro();
	driveComplete = false;
	resetDrive = true;
	
	sitStillPickup();
	resetGyro();
	driveComplete = false;
	resetDrive = true;
	
	driveCoinDetected();
	resetGyro();
	driveComplete = false;
	resetDrive = true;
	
	sitStillPickup();
	resetGyro();
	driveComplete = false;
	resetDrive = true;
	
	driveCoinDetected();
	resetGyro();
	driveComplete = false;
	resetDrive = true;
	
	sitStillPickup();
	resetGyro();
	driveComplete = false;
	resetDrive = true;
	
	while(!driveComplete)
	{
		updateGyro();
		driveComplete = drivetrain.drive(25.4, 0, yaw, resetDrive);
		resetDrive = false;
	}
	resetGyro();
	driveComplete = false;
	resetDrive = true;
	
	intake.dropOffSequence(blue);
	
	while(!driveComplete)
	{
		updateGyro();
		driveComplete = drivetrain.drive(0, 135, yaw, resetDrive);
		resetDrive = false;
	}
	resetGyro();
	driveComplete = false;
	resetDrive = true;
	
	while(!driveComplete)
	{
		updateGyro();
		driveComplete = drivetrain.drive(42, 0, yaw, resetDrive);
		resetDrive = false;
	}
	resetGyro();
	driveComplete = false;
	resetDrive = true;
	
	intake.dropOffSequence(green);
	
	while(!driveComplete)
	{
		updateGyro();
		driveComplete = drivetrain.drive(42, 0, yaw, resetDrive);
		resetDrive = false;
	}
	resetGyro();
	driveComplete = false;
	resetDrive = true;
	
	intake.dropOffSequence(red);
	
	while(!driveComplete)
	{
		updateGyro();
		driveComplete = drivetrain.drive(0, 135, yaw, resetDrive);
		resetDrive = false;
	}
	resetGyro();
	driveComplete = false;
	resetDrive = true;
	
	while(!driveComplete)
	{
		updateGyro();
		driveComplete = drivetrain.drive(118.79, 0, yaw, resetDrive);
		resetDrive = false;
	}
	resetGyro();
	driveComplete = false;
	resetDrive = true;
	
	intake.dropOffSequence(yellow);
	
	while(!driveComplete)
	{
		updateGyro();
		driveComplete = drivetrain.drive(0, -135, yaw, resetDrive);
		resetDrive = false;
	}
	resetGyro();
	driveComplete = false;
	resetDrive = true;
	
	while(!driveComplete)
	{
		updateGyro();
		driveComplete = drivetrain.drive(42, 0, yaw, resetDrive);
		resetDrive = false;
	}
	resetGyro();
	driveComplete = false;
	resetDrive = true;
	
	intake.dropOffSequence(magenta);
	
	while(!driveComplete)
	{
		updateGyro();
		driveComplete = drivetrain.drive(42, 0, yaw, resetDrive);
		resetDrive = false;
	}
	resetGyro();
	driveComplete = false;
	resetDrive = true;
	
	intake.dropOffSequence(cyan);
	
	while(!driveComplete)
	{
		updateGyro();
		driveComplete = drivetrain.drive(0, -90, yaw, resetDrive);
		resetDrive = false;
	}
	resetGyro();
	driveComplete = false;
	resetDrive = true;
	
	while(!driveComplete)
	{
		updateGyro();
		driveComplete = drivetrain.drive(42, 0, yaw, resetDrive);
		resetDrive = false;
	}
	resetGyro();
	driveComplete = false;
	resetDrive = true;
	
	while ( true )
	{
		drivetrain.driveIndefinitely(0,0,yaw,true);
	}
	
}

void driveCoinDetected()
{
	while(!intake.coinDetected())
	{
		updateGyro();
		drivetrain.driveIndefinitely(0.25, 0, yaw, true);	
		resetDrive = false;		
	}
}