// by Zachariah, Kaelan, Lyndon, Daddy Parth
const int VELOCITY = 25; //mm/s 200/8
const float TOLERANCE = 0.5;
const tMotor motorY = motorA, motorX = motorD;
const tMotor motorZ1 = motorB, motorZ2 = motorC;
float deX, deY, moX,moY, yTar, xTar, xIni, yIni, xCu, yCu, xEn, yEn;
const float ENC_TO_MM=(float)24/360;
const float MM_TO_ENC=15;
const float LAYERHEIGHT=0.5;
const float MAXLAYER=5*LAYERHEIGHT;
float step;
//typedef int tArray[5][5];
//tArray cubes;
int cubes[5][5];
