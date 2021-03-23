
// stdafx.cpp : 只包括标准包含文件的源文件
// LaserMachine.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"
#include "LaserMachineConst.h"
#include "MachineObjDef.h"

BYTE gLaserType = IPG_Fiber_Laser;
float gProcessSpeed = 1000;
float gProcessPower = 50.0;
float gProcessPulseWidth = (float)0.1;
float gProcessWaitTime = 10.0;
UINT gProcessFrequncy = 10000;
BYTE gProcessTimes = 1;
BYTE gProcessMode = 1;
float gLaserOnDelay = -80;
float gLaserOffDelay = 150;
float gBeforMarkDelay = 80;
float gAfterMarkDelay = 30;
float gPolylineDelay = 5;
int	gDupNumber = 1;
float gGapDistance = (float)0.1;
byte gFillOutlinePrior = 1;
bool gFillEnable0 = 1;
double gFillAngle0 = 0;
double gFillGap0 = 1;
byte gGapMode0 = 0;
byte gFillMode0 = 0;
double gCurtail0 = 0;
bool gFillEnable1 = 0;
double gFillAngle1 = 0;
double gFillGap1 = 1;
byte gGapMode1 = 0;
byte gFillMode1 = 0;
double gCurtail1 = 0;
bool gFillEnable2 = 0;
double gFillAngle2 = 0;
double gFillGap2 = 1;
byte gGapMode2 = 0;
byte gFillMode2 = 0;
double gCurtail2 = 0;
bool gFillEnable3 = 0;
double gFillAngle3 = 0;
double gFillGap3 = 1;
byte gGapMode3 = 0;
byte gFillMode3 = 0;
double gCurtail3 = 0;