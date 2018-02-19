#include <RobotLib.h>
#include <IEEErobot2018.h>

#define pinLeftMot1 24
#define pinLeftMot2 25
#define pinLeftMotEnb 10
#define pinRightMot1 26
#define pinRightMot2 23
#define pinRightMotEnb 11
#define pinLeftEnc1 1
#define pinLeftEnc2 2
#define pinRightEnc1 3
#define pinRightEnc2 4
#define pinMatrix0 A0
#define pinMatrix1 A1
#define pinMatrix2 A2
#define pinMatrix3 A3
#define pinMatrix4 A4

Drivetrain drivetrain;
DigitalDevice mDetector_empty;
Motor leftMot;
Motor rightMot;
Encoder leftEnc(pinLeftEnc1,pinLeftEnc2);
Encoder rightEnc(pinRightEnc1,pinRightEnc2);
IRMatrix matrix(pinMatrix0,pinMatrix1,pinMatrix2,pinMatrix3,pinMatrix4);

void setup() {
	drivetrain.begin(leftMot, rightMot, leftEnc, rightEnc, matrix, mDetector_empty);
	leftMot.begin(pinLeftMot1,pinLeftMot2,pinLeftMotEnb);
	rightMot.begin(pinRightMot1,pinRightMot2,pinRightMotEnb);
	matrix.begin(pinMatrix0,pinMatrix1,pinMatrix2,pinMatrix3,pinMatrix4);
}

void loop() {
	drivetrain.followLine();
}
