// by Zachariah, Kaelan, Lyndon, Daddy Parth
#include<global.c>
#include<move.c>
#include<start.c>
#include<print.c>
#include<buttons.c>

task main ()
{
configureI2C(S4);
extrude(true);
waitForButtonPress();
zero();
scanPaper();
waitForButtonPress();
zero();
runPrint();
}
