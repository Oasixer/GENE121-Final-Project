#include "global.c"
#include "EV3Servo-lib-UW.c"

#ifndef MOVE_C
#define MOVE_C

void display(int line, float x, float y)
{
	displayString(line, "(%f, %f)", x, y);
}

float motorPower (float velocity)
{
	const float slope = 1, offset = 0, exponent = 1;
	// if (velocity < 0)
		// return -slope * pow(abs(velocity), exponent) + offset;
	// else
	//return 

	
	return constrain(velocity, -100, 100);
}

void moveXY (float xTarget, float yTarget)
{
	xCurrent = nMotorEncoder[motorX]*ENC_TO_MM;
	yCurrent = nMotorEncoder[motorY]*ENC_TO_MM;
	
	deltaX = xTarget - xCurrent;
	deltaY = yTarget - yCurrent;
	
	float deltaV = sqrt(deltaX*deltaX + deltaY*deltaY);

	if (abs(deltaX) > TOLERANCE)
	{
		float powerX = motorPower((float) VELOCITY * deltaX / deltaV);
		motor[motorX] = powerX;
	}
	if (abs(deltaY) > TOLERANCE)
	{
		float powerY = motorPower((float) VELOCITY * deltaY / deltaV);
		motor[motorY] = powerY;
	}

	while (!(abs(xTarget - xCurrent) < TOLERANCE && abs(yTarget - yCurrent) < TOLERANCE))
	{
		xCurrent = nMotorEncoder[motorX] * ENC_TO_MM;
		yCurrent = nMotorEncoder[motorY] * ENC_TO_MM;
		
		if (abs(xTarget - xCurrent) < TOLERANCE)
			motor[motorX] = 0;
		
		if (abs(yTarget - yCurrent) < TOLERANCE)
			motor[motorY] = 0;
	}
}

void moveZ (float zTarget)
{
	float zCur = nMotorEncoder[motorZ1]*ENC_TO_MM;
	int direction = 1;
	if (zTarget < zCur)
		direction = -1;
	motor[motorZ1] = motor[motorZ2] = 100*direction;
	while(zTarget > zCur*direction)
	{
		zCur = nMotorEncoder[motorZ1]*ENC_TO_MM;
	}
	motor[motorZ1] = motor[motorZ2] = 0;
}

void extrude (bool input)
{
	if (input){
		setServoPosition(S4, 1, 100);// extrude on
	}
	else {
		setServoPosition(S4, 1, 50);//extrude off
	}
}

#endif
