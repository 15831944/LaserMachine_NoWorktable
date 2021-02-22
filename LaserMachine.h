
// LaserMachine.h : LaserMachine 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号
#include "LaserMachineConst.h"	//自定义常数

//配置文件目录
#define CONFIG_INI_PATH _T("./configYL.ini")


// CLaserMachineApp:
// 有关此类的实现，请参阅 LaserMachine.cpp
//


class CLaserMachineApp : public CWinApp
{
public:
	CLaserMachineApp();


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
//	afx_msg void OnFileMruFile1();



};

extern CLaserMachineApp theApp;

