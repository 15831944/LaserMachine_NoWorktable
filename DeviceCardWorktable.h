#pragma once
#include <afx.h>
#include "CDlgDevCfgTabWorktable.h"


class CDeviceCardWorktable :
    public CObject
{
	// 构造
public:
	CDeviceCardWorktable();
	virtual ~CDeviceCardWorktable();

	// 特性
protected:


	// 实现
public:
	class paramAxis
	{
	public:
		paramAxis() {};

		int nIndex;					//轴序号
		int nReverse;				//只影响手动上/下/左/右移动工作台时轴的方向，不影响基于坐标的点位运动
		double fPulsePerMM;			//脉冲当量
		int nModeHome;				//运动控制器提供六种回原点模式：
									//	0：检测到原点接近开关信号轴立即停止运动；
									//	1：检测到出现编码器 Z 相脉冲信号时立即停止运动。
									//	2：检测到原点接近开关信号轴立即反向，遇 Z 脉冲立即停止。
									//	3：梯形速度模式时，减速信号有效减速，当原点接近开关信号有效停止运动。
									//	4：梯形速度模式下作回原点运动，原点信号有效时，控制轴按快速运动方式设置的加速度逐渐减速至低速，直到 Z 脉冲有效立即停止运动。
									//	5：梯形速度模式下作回原点运动，原点信号有效时，控制轴按快速运动方式设置的加速度减速停止。再反向运动，遇 Z 脉冲停止反向运动。
		int nFlagSoftlimit;			//使能软件限位

		int nFlagSlowdown;			//使能专用输入：减速/限位/原点/报警 - nFlag=0 关闭 - nFlag=1 开启
		int nModeSlowdown;			//减速/限位/原点/报警 - nMode=0 低电平有效 - nMode=1 高电平有效
		int nFlagLimit;
		int nModeLimit;
		int nFlagOrg;
		int nModeOrg;
		int nFlagAlm;
		int nModeAlm;

		double fSpeedMax;			//速度参数
		double fSpeedLow;
		double fSpeedHigh;			//默认空跳速度，包括分隔加工时的速度
		double fSpeedAcc;
		double fSpeedHand;			//手动移动工作台速度
		double fSpeedDefaultProc;	//用工作台加工时的默认速度

		void SetParamAxis(int nIndex, int nReverse, double fPulsePerMM, int nModeHome, int nFlagSoftlimit,
			int nFlagSlowdown, int nModeSlowdown, int nFlagLimit, int nModeLimit, int nFlagOrg, int nModeOrg, int nFlagAlm, int nModeAlm,
			double fSpeedMax, double fSpeedLow, double fSpeedHigh, double fSpeedAcc, double fSpeedHand, double fSpeedDefaultProc)
		{
			this->nIndex = nIndex;
			this->nReverse = nReverse;
			this->fPulsePerMM = fPulsePerMM;
			this->nModeHome = nModeHome;
			this->nFlagSoftlimit = nFlagSoftlimit;

			this->nFlagSlowdown = nFlagSlowdown;
			this->nModeSlowdown = nModeSlowdown;
			this->nFlagLimit = nFlagLimit;
			this->nModeLimit = nModeLimit;
			this->nFlagOrg = nFlagOrg;
			this->nModeOrg = nModeOrg;
			this->nFlagAlm = nFlagAlm;
			this->nModeAlm = nModeAlm;

			this->fSpeedMax = fSpeedMax;
			this->fSpeedLow = fSpeedLow;
			this->fSpeedHigh = fSpeedHigh;
			this->fSpeedAcc = fSpeedAcc;
			this->fSpeedHand = fSpeedHand;
			this->fSpeedDefaultProc = fSpeedDefaultProc;
		}

	};
	paramAxis m_axisX, m_axisY, m_axisZ;

public:
	//板卡初始化
	virtual BOOL InitialCardWorktable() = 0;
	virtual BOOL ResetZeroWorktable() = 0;

	//运动参数设置

	//运动指令 - 独立运动函数 - 点位
	virtual BOOL PosMoveXY(double fPosX, double fPosY, BOOL bCheckPos = FALSE) = 0;
	virtual BOOL PosMoveXYHand(double fPosX, double fPosY) = 0;
	//BOOL PosMoveXYProc(double fPosX, double fPosY) = 0;
	virtual BOOL PosMoveZ(double fPos) = 0;
	virtual BOOL PosMoveZHand(double fPos) = 0;
	//运动指令 - 独立运动函数 - 连续
	virtual BOOL JogMoveX(int nDir) = 0;
	virtual BOOL JogMoveY(int nDir) = 0;
	virtual BOOL JogMoveZ(int nDir) = 0;
	//运动指令 - 独立运动函数 - 回原点
	virtual BOOL HomeMoveXY(int nDirX, int nDirY) = 0;
	virtual BOOL HomeMoveZ(int nDir) = 0;
	//运动指令 - 插补运动函数 - 线性插补
	//BOOL LineMoveXY(double fPosX, double fPosY);
	//运动指令 - 插补运动函数 - 圆弧插补
	//BOOL ArcMoveXY(double fCenterX, double fCenterY, double fAngle);

	//制动指令
	virtual BOOL StopMoveXY(BOOL bSudden, BOOL bCheckPos = FALSE) = 0;
	virtual BOOL StopMoveX(BOOL bSudden, BOOL bCheckPos = FALSE) = 0;
	virtual BOOL StopMoveY(BOOL bSudden, BOOL bCheckPos = FALSE) = 0;
	virtual BOOL StopMoveZ(BOOL bSudden, BOOL bCheckPos = FALSE) = 0;

	//I/O操作


	//位置和状态设置
	virtual BOOL WaitForMoveEndedXY() = 0;
	virtual BOOL WaitForMoveEndedZ() = 0;
	virtual BOOL GetAbsPosXY(double* fAbsPosX, double* fAbsPosY) = 0;
	virtual BOOL GetAbsPosZ(double* fAbsPos) = 0;

};

extern CDeviceCardWorktable* pDevCardWorktable;

