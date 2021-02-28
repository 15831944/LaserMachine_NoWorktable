// LaserMachineConst.h 所有常数类定义 2019/06-07 by Cao
//
#pragma once
#include "MachineObjDef.h"

//窗口位置尺寸
#define	MainWindowsWidth		1680
#define MainWindowsHight		1050
#define ControlWindowsWidth		260
#define ObPrtyWindowsWidth		300
#define CamPosWindowsWidth		300

#define MultipeScroll			1.2		//鼠标滚轮缩放倍率
#define MultipeScrollMin		0.0001	//鼠标滚轮缩放倍率
#define MultipeScrollMax		1.2		//鼠标滚轮缩放倍率
#define MultipeDPToLP			10000000
#define InitBound				CRect(-25000, -25000, 25000, 25000)	//初始视窗大小
#define InitOrgPoint			CPoint(0, 0)				//设备和逻辑坐标原点的初始化值
#define ScrollStep				10							//滚动步进当量
#define InitScrollMax			1000						//最大滚动距离初始值
#define OrgRectSize				0.02
#define DetaLineHScroll			1			//滚动倍率
#define DetaPageHScroll			2			//滚动倍率
#define DetaLineVScroll			1			//滚动倍率
#define DetaPageVScroll			2			//滚动倍率

#define DrawType_Default		0
#define DrawType_Zoom			100
#define DrawType_Select			101

//设备硬件定义
#define IPG_Fiber_Laser			1			//IPG光纤激光器

//设备加工参数限定
#define Process_MaxSpeed		50000
#define Process_MinSpeed		0
#define Process_MaxPower		100
#define Process_MinPower		0
#define Process_MaxTime			255
#define Process_MinTime			0
#define Process_MaxFrequncy		50000000
#define Process_MinFrequncy		1
#define Process_MaxPulseWidth	1000000
#define Process_MinPulseWidth	0
#define Process_MaxMode			1
#define Process_MinMode			0
#define Process_MaxDotTime		100000
#define Process_MinDotTime		0

//消息定义
#define WM_CtrlWindows_Size		WM_USER + 10
#define WM_ObPrtyWindows_Size	WM_USER + 11
#define WM_CamPosWindows_Size	WM_USER + 12
#define WM_MainWindows_Resume	WM_USER + 13
#define WM_ObjBound_ReSize		WM_USER + 14
#define WM_Init_ReSize			WM_USER + 15
#define WM_ObjList_Refresh		WM_USER + 16
#define WM_File_MRU_Open		WM_USER + 17

#define WM_GET_CAMERA_HWND		WM_USER + 50


#define WM_START_MARK		WM_USER + 188
#define WM_STOP_MARK		WM_USER + 189
#define ID_TIMEER_MARK_PROCESS_TIME WM_USER+190

