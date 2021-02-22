
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
BYTE gProcessMode = 0;
float gLaserOnDelay = -80;
float gLaserOffDelay = 150;
float gBeforMarkDelay = 80;
float gAfterMarkDelay = 30;
float gPolylineDelay = 5;