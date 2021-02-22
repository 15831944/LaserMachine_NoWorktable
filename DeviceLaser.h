#pragma once
#include <afx.h>
class CDeviceLaser :
    public CObject
{
	// 构造
public:
	CDeviceLaser();
	virtual ~CDeviceLaser();

	// 特性
protected:
	CWnd* m_wnd;


	// 实现
public:
	virtual void AttachWnd(CWnd* pWnd) { m_wnd = pWnd; };

	virtual CString GetError() = 0;
	virtual CString GetReply() = 0;

	virtual BOOL ConnectDevLaser(CString strFlag = NULL) = 0;
	virtual BOOL DisConnectDevLaser() = 0;

	virtual BOOL RequestDevLaserSatus() = 0;
	virtual BOOL OpenDevLaser() = 0;				
	virtual BOOL CloseDevLaser() = 0;

	virtual BOOL SetDevLaserEmission(BOOL bEmissionOn) = 0;
	virtual BOOL SetDevLaserExtTrig(BOOL bExtTrig) = 0;

	virtual BOOL SetDevLaserFrequency(int nFrequency) = 0;
	virtual BOOL SetDevLaserOutputDivider(int fDivider) = 0;
	virtual BOOL SetDevLaserBurstNumber(int nBurstNum) = 0;
	virtual BOOL SetDevLaserOutputPower(int nPowerPercent) = 0;

	virtual CString GetDevLaserReply(CString strStatus = _T("")) = 0;
	virtual CString GetDevLaserInfo(CString strStatus = _T("")) = 0;
	virtual int GetDevLaserEmission(CString strStatus = _T("")) = 0;
	virtual int GetDevLaserExtTrig(CString strStatus = _T("")) = 0;
	virtual double GetDevLaserOutputPower(CString strStatus = _T("")) = 0;




};

extern CDeviceLaser* pDevLaser;
