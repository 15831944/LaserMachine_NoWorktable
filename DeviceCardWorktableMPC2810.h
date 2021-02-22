#pragma once
#include "DeviceCardWorktable.h"


class CDeviceCardWorktableMPC2810 :
    public CDeviceCardWorktable
{
	// 构造
public:
	CDeviceCardWorktableMPC2810();
	virtual ~CDeviceCardWorktableMPC2810();

	// 特性
protected:
	int m_nTotalAxes, m_nTotalCards;


	// 实现
public:
	//板卡初始化
	virtual BOOL InitialCardWorktable();
	virtual BOOL ResetZeroWorktable();

	//运动参数设置

	//运动指令 - 独立运动函数 - 点位
	virtual BOOL PosMoveXY(double fPosX, double fPosY, BOOL bCheckPos = FALSE);
	virtual BOOL PosMoveXYHand(double fPosX, double fPosY);
	//BOOL PosMoveXYProc(double fPosX, double fPosY);
	virtual BOOL PosMoveZ(double fPos);
	virtual BOOL PosMoveZHand(double fPos);
	//运动指令 - 独立运动函数 - 连续
	virtual BOOL JogMoveX(int nDir);
	virtual BOOL JogMoveY(int nDir);
	virtual BOOL JogMoveZ(int nDir);
	//运动指令 - 独立运动函数 - 回原点
	virtual BOOL HomeMoveXY(int nDirX, int nDirY);
	virtual BOOL HomeMoveZ(int nDir);
	//运动指令 - 插补运动函数 - 线性插补
	//BOOL LineMoveXY(double fPosX, double fPosY);
	//运动指令 - 插补运动函数 - 圆弧插补
	//BOOL ArcMoveXY(double fCenterX, double fCenterY, double fAngle);

	//制动指令
	virtual BOOL StopMoveXY(BOOL bSudden, BOOL bCheckPos = FALSE);
	virtual BOOL StopMoveX(BOOL bSudden, BOOL bCheckPos = FALSE);
	virtual BOOL StopMoveY(BOOL bSudden, BOOL bCheckPos = FALSE);
	virtual BOOL StopMoveZ(BOOL bSudden, BOOL bCheckPos = FALSE);

	//I/O操作


	//位置和状态设置
	virtual BOOL WaitForMoveEndedXY();
	virtual BOOL WaitForMoveEndedZ();
	virtual BOOL GetAbsPosXY(double* fAbsPosX, double* fAbsPosY);
	virtual BOOL GetAbsPosZ(double* fAbsPos);


	//MPC2810
protected:

	////////////////////////////////////////////////////
	//板卡初始化
	//控制器初始化
	BOOL InitialBoard();
	//控制轴初始化
	BOOL InitialAxis();
	//编码器初始化
	BOOL InitialEncoder();
	//专用输入信号初始化
	BOOL InitialDedicatedInput();
	//运动参数初始化
	BOOL InitialParamMove();
	//板卡初始化
	///////////////////////////////////////////////////


	////////////////////////////////////////////////////
	//运动参数设置
	//运动参数设置
	///////////////////////////////////////////////////


	////////////////////////////////////////////////////
	//运动指令
	//运动指令
	///////////////////////////////////////////////////


	////////////////////////////////////////////////////
	//制动指令
	//制动指令
	///////////////////////////////////////////////////


	////////////////////////////////////////////////////
	//I/O操作
	int ReadInputAll(int nCardNo);
	int ReadInputBit(int nCardNo, int nBitNo);
	BOOL WriteOutput(int nCardNo, int nByteData);
	BOOL WriteOutput(int nCardNo, int nBitNo, int nStatus);
	//I/O操作
	///////////////////////////////////////////////////


	////////////////////////////////////////////////////
	//位置和状态设置
	//位置和状态设置
	///////////////////////////////////////////////////
	

	////////////////////////////////////////////////////
	//错误代码处理
	//错误代码处理
	///////////////////////////////////////////////////

};

