
// LaserMachine.h : LaserMachine Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������
#include "LaserMachineConst.h"	//�Զ��峣��

//�����ļ�Ŀ¼
#define CONFIG_INI_PATH _T("./configYL.ini")


// CLaserMachineApp:
// �йش����ʵ�֣������ LaserMachine.cpp
//


class CLaserMachineApp : public CWinApp
{
public:
	CLaserMachineApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
//	afx_msg void OnFileMruFile1();



};

extern CLaserMachineApp theApp;

