#pragma once
#include <afx.h>
#include "MachineListContainer.h"


class CDeviceCardMark :
	public CObject
{
	// 构造
public:
	CDeviceCardMark();
	virtual ~CDeviceCardMark();

	// 特性
protected:
	BOOL m_bMarkOrRedIsRunning;
	double m_fMarkArcStep;
	//CMachineListContainer* m_pLaserObjList;


	// 实现
public:
	virtual BOOL InitialCardMark() = 0;
	virtual BOOL StartMarkCardMark() = 0;
	virtual BOOL StopMarkCardMark() = 0;
	virtual BOOL WaitForThreadsEnded() = 0;
	virtual BOOL LaserOn() = 0;
	virtual BOOL LaserOff() = 0;
	virtual BOOL ShowDlgCali() = 0;		//暂用
	virtual BOOL SetLenRegion(double fWorksize) = 0;	//暂用

	virtual BOOL SetPensFromAllLayers(CMachineListContainer* pObjList) = 0;	//将listObj中Layer层的加工参数 - 映射到 - 板卡定义的加工参数Pen
	virtual BOOL SetPenFromDefaultProcParm(UINT nPenNo) = 0;
																		//float gProcessSpeed = 100;
	void LoadMachineObj(CMachineObj_Comm* pObj);
	void LoadMachineObjList(CMachineListContainer* pObjList);

	virtual BOOL DeleteALLEntities() = 0;
	virtual BOOL SaveEntityToFile() = 0;	
	virtual BOOL AddEntityLines(int nCount, double ptPos[][2], int nPenNo) = 0;
	virtual BOOL AddEntityCircle(double ptCenterPos[2], double fRadius, double fAngleStart, int nDir, int nPenNo) = 0;
	virtual BOOL AddEntityArc(double ptCenterPos[2], double fRadius, double fAngleStart, double fAngleEnd, int nDir, int nPenNo) = 0;

	virtual BOOL SetScannerXYFlipFlag(int nXYFlip, int nInvertX, int nInvertY) = 0;

};

extern CDeviceCardMark* pDevCardMark;


