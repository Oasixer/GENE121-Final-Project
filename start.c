#include "global.c"
#include "move.c"
#include "buttons.c"
#include "math.c"

#ifndef START_C
#define START_C

void configureI2C (tSensors port){ // make sure to call function to set up servo
	SensorType[port] = sensorI2CCustom9V;
}

void zero()
{
	float powerX = -50;
	float powerY = -50;
	float powerZ = -100;

	// zero x-axis
	motor[motorX] = 7;
	motor[motorZ1] = 100;
	motor[motorZ2] = 100;
	wait1Msec(2000);
	motor[motorZ1] = motor[motorZ2] = 0;
	time1[T1]=0;
	while (time1[T1]<25000 && !getButtonPress(buttonAny)){}
	motor[motorX] = 0;
	nMotorEncoder(motorX)=0;

	// zero y-axis
	motor[motorY] = powerY;
	while(SensorValue[TOUCH_Y] == 0) {}
	motor[motorY] = 0;
	nMotorEncoder[motorY] = 0;

	// zero z-axis
	motor[motorZ1] = motor[motorZ2] = powerZ;
	while(SensorValue[TOUCH_Z] == 0) {wait1Msec(15)}
	motor[motorZ1] = motor[motorZ2] = 0;
	nMotorEncoder[motorZ1] = 0;
	nMotorEncoder[motorZ2] = 0;

	moveXY(5, 20);
	moveZ(3);

	// zero y-axis at quarter speed
	motor[motorY] = powerY / 4.0;
	while(SensorValue[TOUCH_Y] == 0) {}
	motor[motorY] = 0;
	nMotorEncoder[motorY] = 0;

	// zero z-axis at half
	motor[motorZ1] = motor[motorZ2] = powerZ / 2;
	while(SensorValue[TOUCH_Z] == 0) {}
	motor[motorZ1] = motor[motorZ2] = 0;
	wait1Msec(50);
	nMotorEncoder[motorZ1] = 0;
	nMotorEncoder[motorZ2] = 0;


	wait1Msec(50);
	moveZ(5);
	wait1Msec(50);
	moveXY(31, 52);
	wait1Msec(50);
	moveZ(0);
	nMotorEncoder[motorX] = 0;
	nMotorEncoder[motorY] = 0;
	nMotorEncoder[motorZ1] = 0;
	nMotorEncoder[motorZ2] = 0;


}

int scanColour()
{
	int values[3]; //store 3 colour values
	do{ //loop until all 3 colour values are the same (aka make sure you dont read the wrong colour)
		values[0]=(int)SensorValue[S1];
		wait1Msec(50);
		values[1]=(int)SensorValue[S1];
		wait1Msec(50);
		values[2]=(int)SensorValue[S1];
		wait1Msec(50);
	} while (!(values[0]==values[1]&&values[0]==values[2]));
	return values[2];
}

void scanPaper(){
	step=0;
	SensorType[S1]=sensorEV3_Color;
	wait1Msec(50);
	SensorMode[S1]=modeEV3Color_Color;
	wait1Msec(50);
	for (int x = 0; x < 5; x++){
		for(int y = 0; y < 5; y++){
			step+=1;//DEBUG
			moveXY((float)x*15.0-2.5,(float)y*15.0+37.5);
			step+=1;//DEBUG
			cubes[x][y]=scanColour();
		}
	}

	//FOR TESTING ONLY
	/*
	cubes[0][0]=0;
	cubes[0][2]=0;
	cubes[0][3]=0;
	cubes[0][4]=0;
	cubes[1][0]=0;
	cubes[1][1]=0;
	cubes[1][2]=0;
	cubes[1][3]=0;
	cubes[1][4]=0;
	cubes[2][0]=0;
	cubes[2][1]=0;
	cubes[2][2]=0;
	cubes[2][3]=0;
	cubes[2][4]=0;
	cubes[3][0]=0;
	cubes[3][1]=0;
	cubes[3][2]=0;
	cubes[3][3]=0;
	cubes[3][4]=0;
	cubes[4][1]=0;
	cubes[4][2]=0;
	cubes[4][3]=0;
	cubes[4][4]=0;
	*/
}
#endif
