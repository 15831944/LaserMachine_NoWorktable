#pragma once
#include "DeviceLaser.h"
#include "Socket.h"

#define LASER_BELLIN_TELNET_PORT 4000
#define WM_SOCKET_CLIENT WM_USER + 300

class CDeviceLaserBellin :
    public CDeviceLaser
{
	// 构造
public:
	CDeviceLaserBellin();
	//CDeviceLaserBellin(CWnd* pWnd);
	virtual ~CDeviceLaserBellin();

	// 特性
protected:
	BOOL m_bConnected;
	Socket* m_cSock;

	CString m_hostname;   //inet addr to which we get connected
	CString m_ipaddr;     //IP
	int m_port;           //host port

	// 实现
public:
	virtual CString GetError();
	virtual CString GetReply();

	virtual BOOL ConnectDevLaser(CString strIPadd);
	virtual BOOL DisConnectDevLaser();

	virtual BOOL RequestDevLaserSatus();
	virtual BOOL OpenDevLaser();
	virtual BOOL CloseDevLaser();

	virtual BOOL SetDevLaserEmission(BOOL bEmissionOn);
	virtual BOOL SetDevLaserExtTrig(BOOL bExtTrig);

	virtual BOOL SetDevLaserFrequency(int nFrequency);
	virtual BOOL SetDevLaserOutputDivider(int fDivider);
	virtual BOOL SetDevLaserBurstNumber(int nBurstNum);
	virtual BOOL SetDevLaserOutputPower(int nPowerPercent);

	virtual CString GetDevLaserReply(CString strStatus = _T(""));
	virtual CString GetDevLaserInfo(CString strStatus = _T(""));
	virtual int GetDevLaserEmission(CString strStatus = _T(""));
	virtual int GetDevLaserExtTrig(CString strStatus = _T(""));
	virtual double GetDevLaserOutputPower(CString strStatus = _T(""));

};

