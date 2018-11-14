#include<global.c>
#include<EV3Servo-lib-UW.c>

float motorPower (float velocity)
{
	const float slope = 1, offset = 0, exponent = 1;
	if (velocity < 0)
		return -slope * pow(abs(velocity), exponent) + offset;
	else
		return slope * pow(abs(velocity), exponent) + offset;
}

void moveXY (float xTarget, float yTarget)
{
	float xCurrent = nMotorEncoder[motorX] * ENC_TO_MM;
	float yCurrent = nMotorEncoder[motorY]*ENC_TO_MM;
	
	float deltaX = xTarget - xCurrent;
	float deltaY = yTarget - yCurrent;
	
	float deltaV = sqrt(deltaX*deltaX + deltaY*deltaY);
	
	display(0, xCurrent, yCurrent);
	display(1, deltaX, deltaY);
	
	// xCur=nMotorEncoder[motorX]*ENC_TO_MM;
	// yCur=nMotorEncoder[motorY]*ENC_TO_MM;
	// xTar=xTarget;
	// yTar=yTarget;
	// deX = xTar-xCur;
	// deY = yTar-yCur;
	
	if (abs(deltaX) > TOLERANCE)
	{
		float powerX = motorPower((float) VELOCITY * deltaX / deltaV);
		step = 1.5;//DEBUG
		if (deltaX < 0)
			powerX *= -1;
		motor[motorX] = powerX;
	}
	if (abs(deltaY) > TOLERANCE)
	{
		step=1.5;//DEBUG
		float powerY = motorPower((float) VELOCITY * deltaY / deltaV);
		
		moY = powerY
		
		if (deltaY < 0)
			powerY *= -1;
		motor[motorY] = powerY;
	}
	
	display(3, powerX, powerY);
	
	while (!(abs(xTarget - xCurrent) < TOLERANCE && abs(yTarget - yCurrent) > TOLERANCE))
	{
		xCurrent = nMotorEncoder[motorX] * ENC_TO_MM;
		yCurrent = nMotorEncoder[motorY] * ENC_TO_MM;
		if (abs(xTarget - xCurrent) < TOLERANCE)
		{
			motor[motorX] = 0;
			moX=0;
		}
		if (abs(yTarget - yCurrent) < TOLERANCE)
		{
			motor[motorY] = 0;
			moY=0;
		}
	}
	motor[motorX]=0;
	moX=0;
	motor[motorY]=0;
	moY=0;
}

void display(int line, float x, float y)
{
	displayString(line, "(%f, %f)", x, y);
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
		setServoPosition(S4, 1, 25);// extrude on
	}
	else {
		setServoPosition(S4, 1, 0);//extrude off
	}
}