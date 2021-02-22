// CDlgDevCfgTabLaser.cpp: 实现文件
//

//#include "pch.h"
#include "stdafx.h"
#include "LaserMachine.h"
#include "CDlgDevCfgTabLaser.h"
#include "afxdialogex.h"
#include "DeviceLaserBellin.h"


//激光器参数
void SetDevLaserTypeIndex(int nIndex)
{
	CString strTmp;
	strTmp.Format(_T("%d"), nIndex);
	WritePrivateProfileString(_T("DeviceLaser"), _T("LASER_TYPE"), strTmp, CONFIG_INI_PATH);
}
int ReadDevLaserTypeIndex()
{
	int nIndex;
	nIndex = (int)GetPrivateProfileInt(_T("DeviceLaser"), _T("LASER_TYPE"), 0, CONFIG_INI_PATH);
	return nIndex;
}
void SetDevLaserIPAddress(CString str)
{
	WritePrivateProfileString(_T("DeviceLaser"), _T("IP_ADDRESS"), str, CONFIG_INI_PATH);
}
CString ReadDevLaserIPAddress()
{
	CString strTmp;
	GetPrivateProfileString(_T("DeviceLaser"), _T("IP_ADDRESS"), _T("0.0.0.0"), strTmp.GetBuffer(20), 20, CONFIG_INI_PATH);
	return strTmp;
}


// CDlgDevCfgTabLaser 对话框

IMPLEMENT_DYNAMIC(CDlgDevCfgTabLaser, CDialogEx)

CDlgDevCfgTabLaser::CDlgDevCfgTabLaser(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DEVICE_CONFIG_TAB_LASER, pParent)
	, m_nLaserType(0)
{
	m_strLaserBellinIP = "";
}

CDlgDevCfgTabLaser::~CDlgDevCfgTabLaser()
{
}

void CDlgDevCfgTabLaser::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_COMBO_LASER_TYPE, m_nLaserType);
}


BEGIN_MESSAGE_MAP(CDlgDevCfgTabLaser, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO_LASER_TYPE, &CDlgDevCfgTabLaser::OnCbnSelchangeComboLaserType)
	ON_BN_CLICKED(IDC_BUTTON_LASER_BELLIN_CONNECT, &CDlgDevCfgTabLaser::OnBnClickedButtonLaserBellinConnect)
	ON_MESSAGE(WM_SOCKET_CLIENT, &CDlgDevCfgTabLaser::OnSocketClient)
	ON_BN_CLICKED(IDC_BUTTON_LASER_BELLIN_OPEN_MACHINE, &CDlgDevCfgTabLaser::OnBnClickedButtonLaserBellinOpenMachine)
	ON_BN_CLICKED(IDC_BUTTON_LASER_BELLIN_EMISSION_ON, &CDlgDevCfgTabLaser::OnBnClickedButtonLaserBellinEmissionOn)
	ON_BN_CLICKED(IDC_BUTTON_LASER_BELLIN_EXT_TRIG_ON, &CDlgDevCfgTabLaser::OnBnClickedButtonLaserBellinExtTrigOn)
	ON_WM_TIMER()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CDlgDevCfgTabLaser 消息处理程序


BOOL CDlgDevCfgTabLaser::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
		//初始化界面
	((CComboBox*)GetDlgItem(IDC_COMBO_LASER_TYPE))->InsertString(0, (_T("通用光纤激光器")));
	((CComboBox*)GetDlgItem(IDC_COMBO_LASER_TYPE))->InsertString(1, (_T("苏州贝林Amber NX系列")));
	m_nLaserType = ReadDevLaserTypeIndex();
	ChangeLaserType(m_nLaserType);

	//if (pDevLaser)
	//{
	//	if (1 == m_nLaserType)
	//	{
	//		pDevLaser->AttachWnd(this);
	//		((CIPAddressCtrl*)GetDlgItem(IDC_IPADDRESS_LASER_BELLIN_IP))->SetWindowTextW(m_strLaserBellinIP);
	//		SetTimer(ID_TIMEER_LASER_BELLIN, 500, NULL);
	//	}
	//}

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
					// 异常: OCX 属性页应返回 FALSE

}


void CDlgDevCfgTabLaser::OnCbnSelchangeComboLaserType()
{
	// TODO: 在此添加控件通知处理程序代码
	int nLaserTypeTmp = m_nLaserType;
	UpdateData(TRUE);

	if (nLaserTypeTmp == m_nLaserType)
		return;
	SetDevLaserTypeIndex(m_nLaserType);
	ChangeLaserType(m_nLaserType);
}

void CDlgDevCfgTabLaser::ChangeLaserType(int nLaserType)
{
	switch (nLaserType)
	{
	case 1:

		if (pDevLaser == NULL)
			pDevLaser = new CDeviceLaserBellin;

		m_strLaserBellinIP = ReadDevLaserIPAddress();
		((CIPAddressCtrl*)GetDlgItem(IDC_IPADDRESS_LASER_BELLIN_IP))->SetWindowTextW(m_strLaserBellinIP);
		pDevLaser->AttachWnd(this);
		//pDevLaser->ConnectDevLaser(m_strLaserBellinIP);
		SetTimer(ID_TIMEER_LASER_BELLIN, 800, NULL);

		GetDlgItem(IDC_IPADDRESS_LASER_BELLIN_IP)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_LASER_BELLIN_CONNECT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_LASER_BELLIN_INFO)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_LASER_BELLIN_INFO_TITLE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_LASER_BELLIN_REPLY)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_LASER_BELLIN_REPLY_TITLE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_LASER_BELLIN_OUTPUT_POWER)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_LASER_BELLIN_OUTPUT_POWER_TITLE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_LASER_BELLIN_SET_FREQ)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_LASER_BELLIN_SET_FREQ_TITLE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_LASER_BELLIN_SET_DIVIDER)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_LASER_BELLIN_SET_DIVIDER_TITLE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_LASER_BELLIN_SET_BURST_NUM)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_LASER_BELLIN_SET_BURST_NUM_TITLE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_LASER_BELLIN_SET_POWER_FACTOR)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATICIDC_STATIC_LASER_BELLIN_SET_POWER_FACTOR_TITLE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_LASER_BELLIN_OPEN_MACHINE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_LASER_BELLIN_EMISSION_ON)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_LASER_BELLIN_EXT_TRIG_ON)->ShowWindow(SW_SHOW);
		break;

	default:

		if (pDevLaser)
		{
			delete pDevLaser;
			pDevLaser = NULL;
		}
		KillTimer(ID_TIMEER_LASER_BELLIN);

		GetDlgItem(IDC_IPADDRESS_LASER_BELLIN_IP)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_LASER_BELLIN_CONNECT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_LASER_BELLIN_INFO)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_LASER_BELLIN_INFO_TITLE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_LASER_BELLIN_REPLY)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_LASER_BELLIN_REPLY_TITLE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_LASER_BELLIN_OUTPUT_POWER)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_LASER_BELLIN_OUTPUT_POWER_TITLE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_LASER_BELLIN_SET_FREQ)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_LASER_BELLIN_SET_FREQ_TITLE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_LASER_BELLIN_SET_DIVIDER)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_LASER_BELLIN_SET_DIVIDER_TITLE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_LASER_BELLIN_SET_BURST_NUM)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_LASER_BELLIN_SET_BURST_NUM_TITLE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_LASER_BELLIN_SET_POWER_FACTOR)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATICIDC_STATIC_LASER_BELLIN_SET_POWER_FACTOR_TITLE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_LASER_BELLIN_OPEN_MACHINE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_LASER_BELLIN_EMISSION_ON)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_LASER_BELLIN_EXT_TRIG_ON)->ShowWindow(SW_HIDE);
		break;
	}
}


void CDlgDevCfgTabLaser::OnBnClickedButtonLaserBellinConnect()
{
	// TODO: 在此添加控件通知处理程序代码
	((CIPAddressCtrl*)GetDlgItem(IDC_IPADDRESS_LASER_BELLIN_IP))->GetWindowText(m_strLaserBellinIP);
	pDevLaser->ConnectDevLaser(m_strLaserBellinIP);
}


afx_msg LRESULT CDlgDevCfgTabLaser::OnSocketClient(WPARAM wParam, LPARAM lParam)
{
	CString strRead, strReply, strInfo, strPower;
	int nState = -1;
	double fOutputPower = -1;

	switch (LOWORD(lParam)) 
	{
	case FD_CONNECT:
		if (HIWORD(lParam)) 
		{        //error
			WSASetLastError(HIWORD(lParam));
			::MessageBox(m_hWnd, pDevLaser->GetError(), _T("Connection Error."), MB_OK | MB_ICONHAND);
			return 0;
		}
		SetDevLaserIPAddress(m_strLaserBellinIP);
		break;

	case FD_READ:
		strRead = pDevLaser->GetReply();

		strReply = pDevLaser->GetDevLaserReply(strRead);
		if (_T("") != strReply)
		{
			this->SetDlgItemText(IDC_STATIC_LASER_BELLIN_REPLY, strReply);
			break;
		}

		strInfo = pDevLaser->GetDevLaserInfo(strRead);
		if (_T("") != strInfo)
			this->SetDlgItemText(IDC_STATIC_LASER_BELLIN_INFO, strInfo);

		nState = pDevLaser->GetDevLaserEmission(strRead);
		if(0 == nState)
			((CButton*)GetDlgItem(IDC_BUTTON_LASER_BELLIN_EMISSION_ON))->SetWindowText(_T("Emmision On"));
		else if(1 == nState)
			((CButton*)GetDlgItem(IDC_BUTTON_LASER_BELLIN_EMISSION_ON))->SetWindowText(_T("Emmision Off"));

		nState = pDevLaser->GetDevLaserExtTrig(strRead);
		if (0 == nState)
			((CButton*)GetDlgItem(IDC_BUTTON_LASER_BELLIN_EXT_TRIG_ON))->SetWindowText(_T("ExtTrig On"));
		else if (1 == nState)
			((CButton*)GetDlgItem(IDC_BUTTON_LASER_BELLIN_EXT_TRIG_ON))->SetWindowText(_T("ExtTrig Off"));

		fOutputPower = pDevLaser->GetDevLaserOutputPower(strRead);
		if (fOutputPower >= 0)
		{
			strPower.Format(_T("%.2f"), fOutputPower);
			this->SetDlgItemText(IDC_STATIC_LASER_BELLIN_OUTPUT_POWER, strPower);
		}

		//this->SetDlgItemText(IDC_STATIC_LASER_BELLIN_INFO, strTmp);
		//::MessageBox(m_hWnd, strTmp, _T("Get Reply."), MB_OK | MB_ICONHAND);
		break;

	case FD_CLOSE:
		pDevLaser->CloseDevLaser();
		pDevLaser->DisConnectDevLaser();
		break;
	}

	return 0;
}


void CDlgDevCfgTabLaser::OnBnClickedButtonLaserBellinOpenMachine()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strCap;
	((CButton*)GetDlgItem(IDC_BUTTON_LASER_BELLIN_OPEN_MACHINE))->GetWindowText(strCap);

	if (strCap == _T("Turn On"))
	{
		((CButton*)GetDlgItem(IDC_BUTTON_LASER_BELLIN_OPEN_MACHINE))->SetWindowText(_T("Turn Off"));
		pDevLaser->OpenDevLaser();
	}
	else if (strCap == _T("Turn Off"))
	{
		((CButton*)GetDlgItem(IDC_BUTTON_LASER_BELLIN_OPEN_MACHINE))->SetWindowText(_T("Turn On"));
		pDevLaser->CloseDevLaser();
	}
	else
		return;
}


void CDlgDevCfgTabLaser::OnBnClickedButtonLaserBellinEmissionOn()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strCap;
	((CButton*)GetDlgItem(IDC_BUTTON_LASER_BELLIN_EMISSION_ON))->GetWindowText(strCap);

	if (strCap == _T("Emmision On"))
	{
		((CButton*)GetDlgItem(IDC_BUTTON_LASER_BELLIN_EMISSION_ON))->SetWindowText(_T("Emmision Off"));
		pDevLaser->SetDevLaserEmission(TRUE);
	}
	else if (strCap == _T("Emmision Off"))
	{
		((CButton*)GetDlgItem(IDC_BUTTON_LASER_BELLIN_EMISSION_ON))->SetWindowText(_T("Emmision On"));
		pDevLaser->SetDevLaserEmission(FALSE);
	}
	else
		return;

}

void CDlgDevCfgTabLaser::OnBnClickedButtonLaserBellinExtTrigOn()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strCap;
	((CButton*)GetDlgItem(IDC_BUTTON_LASER_BELLIN_EXT_TRIG_ON))->GetWindowText(strCap);

	if (strCap == _T("ExtTrig On"))
	{
		((CButton*)GetDlgItem(IDC_BUTTON_LASER_BELLIN_EXT_TRIG_ON))->SetWindowText(_T("ExtTrig Off"));
		pDevLaser->SetDevLaserExtTrig(TRUE);
	}
	else if (strCap == _T("ExtTrig Off"))
	{
		((CButton*)GetDlgItem(IDC_BUTTON_LASER_BELLIN_EXT_TRIG_ON))->SetWindowText(_T("ExtTrig On"));
		pDevLaser->SetDevLaserExtTrig(FALSE);
	}
	else
		return;

}


BOOL CDlgDevCfgTabLaser::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类

	//根据不同控件焦点判断是那个在执行 
	if (WM_KEYDOWN == pMsg->message && VK_RETURN == pMsg->wParam)
	{
		CString strEdit;
		if (GetFocus() == GetDlgItem(IDC_EDIT_LASER_BELLIN_SET_FREQ)) 
		{
			((CEdit*)GetDlgItem(IDC_EDIT_LASER_BELLIN_SET_FREQ))->GetWindowText(strEdit);
			pDevLaser->SetDevLaserFrequency((int)_ttoi(strEdit));
		}
		else if (GetFocus() == GetDlgItem(IDC_EDIT_LASER_BELLIN_SET_DIVIDER))
		{
			((CEdit*)GetDlgItem(IDC_EDIT_LASER_BELLIN_SET_DIVIDER))->GetWindowText(strEdit);
			pDevLaser->SetDevLaserOutputDivider((int)_ttoi(strEdit));
		}
		else if (GetFocus() == GetDlgItem(IDC_EDIT_LASER_BELLIN_SET_BURST_NUM))
		{
			((CEdit*)GetDlgItem(IDC_EDIT_LASER_BELLIN_SET_BURST_NUM))->GetWindowText(strEdit);
			pDevLaser->SetDevLaserBurstNumber((int)_ttoi(strEdit));
		}
		else if (GetFocus() == GetDlgItem(IDC_EDIT_LASER_BELLIN_SET_POWER_FACTOR))
		{
			((CEdit*)GetDlgItem(IDC_EDIT_LASER_BELLIN_SET_POWER_FACTOR))->GetWindowText(strEdit);
			pDevLaser->SetDevLaserOutputPower((int)_ttoi(strEdit));
		}

		return TRUE;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CDlgDevCfgTabLaser::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nIDEvent)
	{
	case ID_TIMEER_LASER_BELLIN:
		if (pDevLaser)
			pDevLaser->RequestDevLaserSatus();
		break;
	default:
		break;
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CDlgDevCfgTabLaser::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	KillTimer(ID_TIMEER_LASER_BELLIN);
	if (pDevLaser)
	{
		pDevLaser->SetDevLaserEmission(FALSE);
		pDevLaser->SetDevLaserExtTrig(TRUE);
	}
}
