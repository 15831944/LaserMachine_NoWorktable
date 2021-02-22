#include "stdafx.h"
#include "DeviceLaserBellin.h"


CDeviceLaserBellin::CDeviceLaserBellin()
{
	m_bConnected = FALSE;
	m_wnd = NULL;
	m_cSock = 0;
	m_hostname = "";  
	m_ipaddr = "";     
	m_port = 0;           

}
//CDeviceLaserBellin::CDeviceLaserBellin(CWnd* pWnd)
//{
//	m_wnd = pWnd;
//	m_cSock = 0;
//}

CDeviceLaserBellin::~CDeviceLaserBellin()
{
	DisConnectDevLaser();
}

CString CDeviceLaserBellin::GetError()
{
	CString strError(m_cSock->GetError());
	return strError;
}
CString CDeviceLaserBellin::GetReply()
{
	char* buff;
	int len = 0;
	CString sbuff;

	buff = m_cSock->Read();
	len = m_cSock->getlastread();
	for (int i = 0; i < len; i++) {            //get "\r\n" format
		if (buff[i] == '\n' && i > 0 && buff[i - 1] != '\r')
			sbuff.AppendChar('\r');

		sbuff.AppendChar(buff[i]);
	}

	return sbuff;
}

BOOL CDeviceLaserBellin::ConnectDevLaser(CString strIPaddr)
{
	char* err;
	if (m_cSock) 
	{
		delete m_cSock;
		m_cSock = 0;
	}

	m_cSock = new Socket;

	if (err = m_cSock->Create(AF_INET, SOCK_STREAM, IPPROTO_IP)) 
	{
		::MessageBox(m_wnd->m_hWnd, CString(err), _T("Error."), MB_OK | MB_ICONHAND);
		return FALSE;
	}

	if (m_wnd != NULL)
	{
		if (err = m_cSock->Select(m_wnd->m_hWnd, WM_SOCKET_CLIENT, FD_READ | FD_CONNECT | FD_CLOSE))
		{
			//::MessageBox(m_wnd->m_hWnd, CString(err), _T("Error."), MB_OK | MB_ICONHAND);
			return FALSE;
		}
	}

	//char bufIP[128];
	//sprintf_s(bufIP, "%S", strIPaddr.GetBuffer()); //注意%S是大写
	USES_CONVERSION;
	if (err = m_cSock->Connect(T2A(strIPaddr), (WORD)LASER_BELLIN_TELNET_PORT)) {
		//::MessageBox(m_wnd->m_hWnd, CString(err), _T("Error."), MB_OK | MB_ICONHAND);
		return FALSE;
	}


	m_port = m_cSock->getport();
	m_hostname = m_cSock->gethostname();
	m_ipaddr = m_cSock->getaddr();
	m_bConnected = TRUE;

	return TRUE;
}

BOOL CDeviceLaserBellin::DisConnectDevLaser()
{
	if (m_cSock) 
	{
		delete m_cSock;
		m_cSock = 0;
	}

	m_bConnected = FALSE;

	return TRUE;
}


BOOL CDeviceLaserBellin::RequestDevLaserSatus()
{
	if (m_bConnected == FALSE)
		return FALSE;

	CString strTmp;
	strTmp = _T("UserStatus\r\n");
	USES_CONVERSION;
	m_cSock->Send(T2A(strTmp));

	return TRUE;
}

BOOL CDeviceLaserBellin::OpenDevLaser()
{
	CString strTmp;
	strTmp = _T("LaserStart\r\n");
	USES_CONVERSION;
	m_cSock->Send(T2A(strTmp));

	return TRUE;
}
BOOL CDeviceLaserBellin::CloseDevLaser()
{
	CString strTmp;
	strTmp = _T("LaserStop\r\n");
	USES_CONVERSION;
	m_cSock->Send(T2A(strTmp));

	return TRUE;
}
BOOL CDeviceLaserBellin::SetDevLaserEmission(BOOL bEmissionOn)
{
	CString strTmp;

	if (bEmissionOn)
		strTmp = _T("EmissionOn\r\n");
	else
		strTmp = _T("EmissionOff\r\n");

	USES_CONVERSION;
	m_cSock->Send(T2A(strTmp));

	return TRUE;
}
BOOL CDeviceLaserBellin::SetDevLaserExtTrig(BOOL bExtTrig)
{
	CString strTmp;

	if (bExtTrig)
		strTmp = _T("ExtTrigOn\r\n");
	else
		strTmp = _T("ExtTrigOff\r\n");

	USES_CONVERSION;
	m_cSock->Send(T2A(strTmp));

	return TRUE;
}

BOOL CDeviceLaserBellin::SetDevLaserFrequency(int nFrequency)
{
	if (nFrequency < 50 || nFrequency > 2000)
	{
		AfxMessageBox(_T("激光频率超限"));
		return FALSE;
	}

	CString strTmp;
	strTmp.Format(_T("LaserFrequency=%dkHz\r\n"), nFrequency);

	USES_CONVERSION;
	m_cSock->Send(T2A(strTmp));

	return TRUE;
}
BOOL CDeviceLaserBellin::SetDevLaserOutputDivider(int fDivider)
{
	if (fDivider < 1 || fDivider > 1000000)
	{
		AfxMessageBox(_T("输出频率分频因子超限"));
		return FALSE;
	}

	CString strTmp;
	strTmp.Format(_T("OutputDivider=%d\r\n"), fDivider);

	USES_CONVERSION;
	m_cSock->Send(T2A(strTmp));

	return TRUE;
}
BOOL CDeviceLaserBellin::SetDevLaserBurstNumber(int nBurstNum)
{
	if (nBurstNum < 0 || nBurstNum > 15)
	{
		AfxMessageBox(_T("脉冲数超限"));
		return FALSE;
	}

	CString strTmp;
	strTmp.Format(_T("BurstNumber=%d\r\n"), nBurstNum);

	USES_CONVERSION;
	m_cSock->Send(T2A(strTmp));

	return TRUE;
}
BOOL CDeviceLaserBellin::SetDevLaserOutputPower(int nPowerPercent)
{
	if (nPowerPercent < 0 || nPowerPercent > 100)
	{
		AfxMessageBox(_T("功率因子超限"));
		return FALSE;
	}

	CString strTmp;
	strTmp.Format(_T("OutputPower=%d\r\n"), nPowerPercent);

	USES_CONVERSION;
	m_cSock->Send(T2A(strTmp));
	return TRUE;
}

CString CDeviceLaserBellin::GetDevLaserReply(CString strStatus)
{
	if (-1 != strStatus.Find(_T("setsucceed"), 0))
		return strStatus;
	if( -1 != strStatus.Find(_T("Please Input Command"), 0))
		return _T("Please Input Command");

	return _T("");
}
CString CDeviceLaserBellin::GetDevLaserInfo(CString strStatus)
{
	CString strInfo, strTmp;
	int nPos = -1;
	nPos = strStatus.Find(_T("Info="), 0);
	if (-1 != nPos)
	{
		strTmp = strStatus.Mid(nPos);
		strInfo = strTmp.Left(strTmp.Find(_T("\n"), 0) + 1);
		return strInfo;
	}

	return _T("");
}
int CDeviceLaserBellin::GetDevLaserEmission(CString strStatus)
{
	CString strIntTrig, strTmp;
	int nPos = -1;
	nPos = strStatus.Find(_T("Internal_Trigger_state="), 0);
	if (-1 != nPos)
	{
		strTmp = strStatus.Mid(nPos);
		strIntTrig = strTmp.Left(strTmp.Find(_T("\r"), 0));
		return _ttoi(strIntTrig.Right(1));
	}

	return -1;
}
int CDeviceLaserBellin::GetDevLaserExtTrig(CString strStatus)
{
	CString strExtTrig, strTmp;
	int nPos = -1;
	nPos = strStatus.Find(_T("External_Trigger_state="), 0);
	if (-1 != nPos)
	{
		strTmp = strStatus.Mid(nPos);
		strExtTrig = strTmp.Left(strTmp.Find(_T("\r"), 0));
		return _ttoi(strExtTrig.Right(1));
	}

	return -1;
}
double CDeviceLaserBellin::GetDevLaserOutputPower(CString strStatus)
{
	CString strPower, strTmp, strNum;
	int nPos = -1;
	nPos = strStatus.Find(_T("OutputPower="), 0);
	if (-1 != nPos)
	{
		strTmp = strStatus.Mid(nPos);
		strPower = strTmp.Left(strTmp.Find(_T("\r"), 0) - 1);
		strNum = strPower.Mid(strPower.Find(_T("="), 0) + 1);
		return _ttof(strNum);
	}

	return -1;
}
