#include <RobotLib.h>
#include <IEEErobot2018.h>					

//Define the states that the decision making machines uses:
#define IDLE_STATE 0
#define READ_LINE 1
#define GO_FORWARD 2
#define GO_LEFT 3
#define GO_RIGHT 4

bool initDrive = true;

uint8_t state;

void setup() 
{
	robotSetup();
}

void loop() 
{
	Serial.println(lineFollower.getRaw());
	//Serial.println("Following Line");
	drivetrain.followLine(lineFollower.getDensity(), lineFollower.getPosition());
 
  /*uint8_t nextState = state;
  switch (state) {
  case IDLE_STATE:
    drivetrain.driveIndefinitely(0, 0, yaw, initDrive);       // Stops both motors
    nextState = READ_LINE;
    break;
  case READ_LINE:
    if( lineFollower.getDensity() < 7 )
    {
      nextState = GO_FORWARD;
      if( lineFollower.getPosition() < -50 )
      {
        nextState = GO_LEFT;
      }
      if( lineFollower.getPosition() > 50 )
      {
        nextState = GO_RIGHT;
      }
    }
    else
    {
      nextState = IDLE_STATE;
    }
    break;
  case GO_FORWARD:
    drivetrain.driveIndefinitely(0.175, 0, yaw, initDrive);
    nextState = READ_LINE;
    break;
  case GO_LEFT:
    drivetrain.driveIndefinitely(0.175, -30, yaw, initDrive);
    nextState = READ_LINE;
    break;
  case GO_RIGHT:
    drivetrain.driveIndefinitely(0.175, 30, yaw, initDrive);
    nextState = READ_LINE;
    break;
  default:
    drivetrain.driveIndefinitely(0, 0, yaw, initDrive);       // Stops both motors
    break;
  }
  state = nextState;*/
}
