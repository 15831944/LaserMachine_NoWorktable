// CDlgDevCfgTabWorktable.cpp: 实现文件
//

//#include "pch.h"
#include "stdafx.h"
#include "LaserMachine.h"
#include "CDlgDevCfgTabWorktable.h"
#include "afxdialogex.h"
#include "DeviceCardWorktable.h"


////////////////////////////////////////////////////////////////////
//相机硬件配置 外部调用
void SetDevWorktableName(WORKTABLE_NAME eWorktableName)
{
	switch (eWorktableName)
	{
	case WORKTABLE_NAME::WORKTABLE_NONE:
		WritePrivateProfileString(_T("DeviceWorktable"), _T("NAME"), _T("WORKTABLE_NONE"), CONFIG_INI_PATH);
		WritePrivateProfileString(_T("DeviceWorktable"), _T("NAME_INDEX"), _T("0"), CONFIG_INI_PATH);
		break;
	case WORKTABLE_NAME::WORKTABLE_MPC2810:
		WritePrivateProfileString(_T("DeviceWorktable"), _T("NAME"), _T("WORKTABLE_MPC2810"), CONFIG_INI_PATH);
		WritePrivateProfileString(_T("DeviceWorktable"), _T("NAME_INDEX"), _T("1"), CONFIG_INI_PATH);
		break;
	default:
		break;
	}
}
WORKTABLE_NAME ReadDevWorktableName()
{
	WORKTABLE_NAME eWorktableName;
	eWorktableName = (WORKTABLE_NAME)GetPrivateProfileInt(_T("DeviceWorktable"), _T("NAME_INDEX"), 0, CONFIG_INI_PATH);
	return eWorktableName;
}

//XY轴参数
void SetDevWorktableAxisXIndex(int nIndex)
{
	CString strTmp;
	strTmp.Format(_T("%d"), nIndex);
	WritePrivateProfileString(_T("DeviceWorktable"), _T("AXIS_X_INDEX"), strTmp, CONFIG_INI_PATH);
}
int ReadDevWorktableAxisXIndex()
{
	int nIndex;
	nIndex = (int)GetPrivateProfileInt(_T("DeviceWorktable"), _T("AXIS_X_INDEX"), DEFAULT_AXIS_X_INDEX, CONFIG_INI_PATH);
	return nIndex;
}

void SetDevWorktableAxisYIndex(int nIndex)
{
	CString strTmp;
	strTmp.Format(_T("%d"), nIndex);
	WritePrivateProfileString(_T("DeviceWorktable"), _T("AXIS_Y_INDEX"), strTmp, CONFIG_INI_PATH);
}
int ReadDevWorktableAxisYIndex()
{
	int nIndex;
	nIndex = (int)GetPrivateProfileInt(_T("DeviceWorktable"), _T("AXIS_Y_INDEX"), DEFAULT_AXIS_Y_INDEX, CONFIG_INI_PATH);
	return nIndex;
}

void SetDevWorktableAxisXReverse(int nReverse)
{
	CString strTmp;
	strTmp.Format(_T("%d"), nReverse);
	WritePrivateProfileString(_T("DeviceWorktable"), _T("AXIS_X_REVERSE"), strTmp, CONFIG_INI_PATH);
}
int ReadDevWorktableAxisXReverse()
{
	int nReverse;
	nReverse = (int)GetPrivateProfileInt(_T("DeviceWorktable"), _T("AXIS_X_REVERSE"), DEFAULT_AXIS_REVERSE, CONFIG_INI_PATH);
	return nReverse;
}
void SetDevWorktableAxisYReverse(int nReverse)
{
	CString strTmp;
	strTmp.Format(_T("%d"), nReverse);
	WritePrivateProfileString(_T("DeviceWorktable"), _T("AXIS_Y_REVERSE"), strTmp, CONFIG_INI_PATH);
}
int ReadDevWorktableAxisYReverse()
{
	int nReverse;
	nReverse = (int)GetPrivateProfileInt(_T("DeviceWorktable"), _T("AXIS_Y_REVERSE"), DEFAULT_AXIS_REVERSE, CONFIG_INI_PATH);
	return nReverse;
}

void SetDevWorktablePulsePerMMXY(double fPulsePerMM)
{
	CString strTmp;
	strTmp.Format(_T("%lf"), fPulsePerMM);
	WritePrivateProfileString(_T("DeviceWorktable"), _T("PULSE_PER_MM_XY"), strTmp, CONFIG_INI_PATH);
}
double ReadDevWorktablePulsePerMMXY()
{
	CString strTmp;
	GetPrivateProfileString(_T("DeviceWorktable"), _T("PULSE_PER_MM_XY"), DEFAULT_PULSE_PER_MM, strTmp.GetBuffer(MAX_DOUBLE_PRECISION), MAX_DOUBLE_PRECISION, CONFIG_INI_PATH);
	return (double)_ttof(strTmp);
}

void SetDevWorktableModeHomeXY(int nModeHome)
{
	CString strTmp;
	strTmp.Format(_T("%d"), nModeHome);
	WritePrivateProfileString(_T("DeviceWorktable"), _T("MODE_HOME_XY"), strTmp, CONFIG_INI_PATH);
}
int ReadDevWorktableModeHomeXY()
{
	int nIndex;
	nIndex = (int)GetPrivateProfileInt(_T("DeviceWorktable"), _T("MODE_HOME_XY"), DEFAULT_MODE_HOME, CONFIG_INI_PATH);
	return nIndex;
}

void SetDevWorktableFlagSoftlimitXY(int nFlagSoftlimit)
{
	CString strTmp;
	strTmp.Format(_T("%d"), nFlagSoftlimit);
	WritePrivateProfileString(_T("DeviceWorktable"), _T("FLAG_SOFTLIMIT_XY"), strTmp, CONFIG_INI_PATH);
}
int ReadDevWorktableFlagSoftlimitXY()
{
	int nFlagSoftlimit;
	nFlagSoftlimit = (int)GetPrivateProfileInt(_T("DeviceWorktable"), _T("FLAG_SOFTLIMIT_XY"), DEFAULT_FLAG_SOFTLIMIT, CONFIG_INI_PATH);
	return nFlagSoftlimit;
}

void SetDevWorktableFlagSlowdownXY(int nFlagSlowdown)
{
	CString strTmp;
	strTmp.Format(_T("%d"), nFlagSlowdown);
	WritePrivateProfileString(_T("DeviceWorktable"), _T("FLAG_SLOWDOWN_XY"), strTmp, CONFIG_INI_PATH);
}
int ReadDevWorktableFlagSlowdownXY()
{
	int nFlagSlowdown;
	nFlagSlowdown = (int)GetPrivateProfileInt(_T("DeviceWorktable"), _T("FLAG_SLOWDOWN_XY"), DEFAULT_FLAG_SLOWDOWN, CONFIG_INI_PATH);
	return nFlagSlowdown;
}

void SetDevWorktableModeSlowdownXY(int nModeSlowdown)
{
	CString strTmp;
	strTmp.Format(_T("%d"), nModeSlowdown);
	WritePrivateProfileString(_T("DeviceWorktable"), _T("MODE_SLOWDOWN_XY"), strTmp, CONFIG_INI_PATH);
}
int ReadDevWorktableModeSlowdownXY()
{
	int nModeSlowdown;
	nModeSlowdown = (int)GetPrivateProfileInt(_T("DeviceWorktable"), _T("MODE_SLOWDOWN_XY"), DEFAULT_MODE_SLOWDOWN, CONFIG_INI_PATH);
	return nModeSlowdown;
}

void SetDevWorktableFlagLimitXY(int nFlagLimit)
{
	CString strTmp;
	strTmp.Format(_T("%d"), nFlagLimit);
	WritePrivateProfileString(_T("DeviceWorktable"), _T("FLAG_LIMIT_XY"), strTmp, CONFIG_INI_PATH);
}
int ReadDevWorktableFlagLimitXY()
{
	int nFlagLimit;
	nFlagLimit = (int)GetPrivateProfileInt(_T("DeviceWorktable"), _T("FLAG_LIMIT_XY"), DEFAULT_FLAG_LIMIT, CONFIG_INI_PATH);
	return nFlagLimit;
}

void SetDevWorktableModeLimitXY(int nModeLimit)
{
	CString strTmp;
	strTmp.Format(_T("%d"), nModeLimit);
	WritePrivateProfileString(_T("DeviceWorktable"), _T("MODE_LIMIT_XY"), strTmp, CONFIG_INI_PATH);
}
int ReadDevWorktableModeLimitXY()
{
	int nModeLimit;
	nModeLimit = (int)GetPrivateProfileInt(_T("DeviceWorktable"), _T("MODE_LIMIT_XY"), DEFAULT_MODE_LIMIT, CONFIG_INI_PATH);
	return nModeLimit;
}

void SetDevWorktableFlagOrgXY(int nFlagOrg)
{
	CString strTmp;
	strTmp.Format(_T("%d"), nFlagOrg);
	WritePrivateProfileString(_T("DeviceWorktable"), _T("FLAG_ORG_XY"), strTmp, CONFIG_INI_PATH);
}
int ReadDevWorktableFlagOrgXY()
{
	int nFlagOrg;
	nFlagOrg = (int)GetPrivateProfileInt(_T("DeviceWorktable"), _T("FLAG_ORG_XY"), DEFAULT_FLAG_ORG, CONFIG_INI_PATH);
	return nFlagOrg;
}

void SetDevWorktableModeOrgXY(int nModeOrg)
{
	CString strTmp;
	strTmp.Format(_T("%d"), nModeOrg);
	WritePrivateProfileString(_T("DeviceWorktable"), _T("MODE_ORG_XY"), strTmp, CONFIG_INI_PATH);
}
int ReadDevWorktableModeOrgXY()
{
	int nModeOrg;
	nModeOrg = (int)GetPrivateProfileInt(_T("DeviceWorktable"), _T("MODE_ORG_XY"), DEFAULT_MODE_ORG, CONFIG_INI_PATH);
	return nModeOrg;
}

void SetDevWorktableFlagAlmXY(int nFlagAlm)
{
	CString strTmp;
	strTmp.Format(_T("%d"), nFlagAlm);
	WritePrivateProfileString(_T("DeviceWorktable"), _T("FLAG_ALM_XY"), strTmp, CONFIG_INI_PATH);
}
int ReadDevWorktableFlagAlmXY()
{
	int nFlagAlm;
	nFlagAlm = (int)GetPrivateProfileInt(_T("DeviceWorktable"), _T("FLAG_ALM_XY"), DEFAULT_FLAG_ALM, CONFIG_INI_PATH);
	return nFlagAlm;
}

void SetDevWorktableModeAlmXY(int nModeAlm)
{
	CString strTmp;
	strTmp.Format(_T("%d"), nModeAlm);
	WritePrivateProfileString(_T("DeviceWorktable"), _T("MODE_ALM_XY"), strTmp, CONFIG_INI_PATH);
}
int ReadDevWorktableModeAlmXY()
{
	int nModeAlm;
	nModeAlm = (int)GetPrivateProfileInt(_T("DeviceWorktable"), _T("MODE_ALM_XY"), DEFAULT_MODE_ALM, CONFIG_INI_PATH);
	return nModeAlm;
}

void SetDevWorktableSpeedMaxXY(double fSpeedMax)
{
	CString strTmp;
	strTmp.Format(_T("%lf"), fSpeedMax);
	WritePrivateProfileString(_T("DeviceWorktable"), _T("SPEED_MAX_XY"), strTmp, CONFIG_INI_PATH);
}
double ReadDevWorktableSpeedMaxXY()
{
	CString strTmp;
	GetPrivateProfileString(_T("DeviceWorktable"), _T("SPEED_MAX_XY"), DEFAULT_SPEED_MAX, strTmp.GetBuffer(MAX_DOUBLE_PRECISION), MAX_DOUBLE_PRECISION, CONFIG_INI_PATH);
	return (double)_ttof(strTmp);
}

void SetDevWorktableSpeedLowXY(double fSpeedLow)
{
	CString strTmp;
	strTmp.Format(_T("%lf"), fSpeedLow);
	WritePrivateProfileString(_T("DeviceWorktable"), _T("SPEED_LOW_XY"), strTmp, CONFIG_INI_PATH);
}
double ReadDevWorktableSpeedLowXY()
{
	CString strTmp;
	GetPrivateProfileString(_T("DeviceWorktable"), _T("SPEED_LOW_XY"), DEFAULT_SPEED_LOW, strTmp.GetBuffer(MAX_DOUBLE_PRECISION), MAX_DOUBLE_PRECISION, CONFIG_INI_PATH);
	return (double)_ttof(strTmp);
}

void SetDevWorktableSpeedHighXY(double fSpeedHigh)
{
	CString strTmp;
	strTmp.Format(_T("%lf"), fSpeedHigh);
	WritePrivateProfileString(_T("DeviceWorktable"), _T("SPEED_HIGH_XY"), strTmp, CONFIG_INI_PATH);
}
double ReadDevWorktableSpeedHighXY()
{
	CString strTmp;
	GetPrivateProfileString(_T("DeviceWorktable"), _T("SPEED_HIGH_XY"), DEFAULT_SPEED_HIGH, strTmp.GetBuffer(MAX_DOUBLE_PRECISION), MAX_DOUBLE_PRECISION, CONFIG_INI_PATH);
	return (double)_ttof(strTmp);
}

void SetDevWorktableSpeedAccXY(double fSpeedAcc)
{
	CString strTmp;
	strTmp.Format(_T("%lf"), fSpeedAcc);
	WritePrivateProfileString(_T("DeviceWorktable"), _T("SPEED_ACC_XY"), strTmp, CONFIG_INI_PATH);
}
double ReadDevWorktableSpeedAccXY()
{
	CString strTmp;
	GetPrivateProfileString(_T("DeviceWorktable"), _T("SPEED_ACC_XY"), DEFAULT_SPEED_ACC, strTmp.GetBuffer(MAX_DOUBLE_PRECISION), MAX_DOUBLE_PRECISION, CONFIG_INI_PATH);
	return (double)_ttof(strTmp);
}

void SetDevWorktableSpeedHandXY(double fSpeedHand)
{
	CString strTmp;
	strTmp.Format(_T("%lf"), fSpeedHand);
	WritePrivateProfileString(_T("DeviceWorktable"), _T("SPEED_HAND_XY"), strTmp, CONFIG_INI_PATH);
}
double ReadDevWorktableSpeedHandXY()
{
	CString strTmp;
	GetPrivateProfileString(_T("DeviceWorktable"), _T("SPEED_HAND_XY"), DEFAULT_SPEED_HAND, strTmp.GetBuffer(MAX_DOUBLE_PRECISION), MAX_DOUBLE_PRECISION, CONFIG_INI_PATH);
	return (double)_ttof(strTmp);
}

void SetDevWorktableSpeedProcXY(double fSpeedProc)
{
	CString strTmp;
	strTmp.Format(_T("%lf"), fSpeedProc);
	WritePrivateProfileString(_T("DeviceWorktable"), _T("SPEED_PROC_XY"), strTmp, CONFIG_INI_PATH);
}
double ReadDevWorktableSpeedProcXY()
{
	CString strTmp;
	GetPrivateProfileString(_T("DeviceWorktable"), _T("SPEED_PROC_XY"), DEFAULT_SPEED_PROC, strTmp.GetBuffer(MAX_DOUBLE_PRECISION), MAX_DOUBLE_PRECISION, CONFIG_INI_PATH);
	return (double)_ttof(strTmp);
}

//Z轴参数
void SetDevWorktableAxisZIndex(int nIndex)
{
	CString strTmp;
	strTmp.Format(_T("%d"), nIndex);
	WritePrivateProfileString(_T("DeviceWorktable"), _T("AXIS_Z_INDEX"), strTmp, CONFIG_INI_PATH);
}
int ReadDevWorktableAxisZIndex()
{
	int nIndex;
	nIndex = (int)GetPrivateProfileInt(_T("DeviceWorktable"), _T("AXIS_Z_INDEX"), DEFAULT_AXIS_Z_INDEX, CONFIG_INI_PATH);
	return nIndex;
}

void SetDevWorktableAxisZReverse(int nReverse)
{
	CString strTmp;
	strTmp.Format(_T("%d"), nReverse);
	WritePrivateProfileString(_T("DeviceWorktable"), _T("AXIS_Z_REVERSE"), strTmp, CONFIG_INI_PATH);
}
int ReadDevWorktableAxisZReverse()
{
	int nReverse;
	nReverse = (int)GetPrivateProfileInt(_T("DeviceWorktable"), _T("AXIS_Z_REVERSE"), DEFAULT_AXIS_REVERSE, CONFIG_INI_PATH);
	return nReverse;
}

void SetDevWorktablePulsePerMMZ(double fPulsePerMM)
{
	CString strTmp;
	strTmp.Format(_T("%lf"), fPulsePerMM);
	WritePrivateProfileString(_T("DeviceWorktable"), _T("PULSE_PER_MM_Z"), strTmp, CONFIG_INI_PATH);
}
double ReadDevWorktablePulsePerMMZ()
{
	CString strTmp;
	GetPrivateProfileString(_T("DeviceWorktable"), _T("PULSE_PER_MM_Z"), DEFAULT_PULSE_PER_MM, strTmp.GetBuffer(MAX_DOUBLE_PRECISION), MAX_DOUBLE_PRECISION, CONFIG_INI_PATH);
	return (double)_ttof(strTmp);
}

void SetDevWorktableModeHomeZ(int nModeHome)
{
	CString strTmp;
	strTmp.Format(_T("%d"), nModeHome);
	WritePrivateProfileString(_T("DeviceWorktable"), _T("MODE_HOME_Z"), strTmp, CONFIG_INI_PATH);
}
int ReadDevWorktableModeHomeZ()
{
	int nIndex;
	nIndex = (int)GetPrivateProfileInt(_T("DeviceWorktable"), _T("MODE_HOME_Z"), DEFAULT_MODE_HOME, CONFIG_INI_PATH);
	return nIndex;
}

void SetDevWorktableFlagSoftlimitZ(int nFlagSoftlimit)
{
	CString strTmp;
	strTmp.Format(_T("%d"), nFlagSoftlimit);
	WritePrivateProfileString(_T("DeviceWorktable"), _T("FLAG_SOFTLIMIT_Z"), strTmp, CONFIG_INI_PATH);
}
int ReadDevWorktableFlagSoftlimitZ()
{
	int nFlagSoftlimit;
	nFlagSoftlimit = (int)GetPrivateProfileInt(_T("DeviceWorktable"), _T("FLAG_SOFTLIMIT_Z"), DEFAULT_FLAG_SOFTLIMIT, CONFIG_INI_PATH);
	return nFlagSoftlimit;
}

void SetDevWorktableFlagSlowdownZ(int nFlagSlowdown)
{
	CString strTmp;
	strTmp.Format(_T("%d"), nFlagSlowdown);
	WritePrivateProfileString(_T("DeviceWorktable"), _T("FLAG_SLOWDOWN_Z"), strTmp, CONFIG_INI_PATH);
}
int ReadDevWorktableFlagSlowdownZ()
{
	int nFlagSlowdown;
	nFlagSlowdown = (int)GetPrivateProfileInt(_T("DeviceWorktable"), _T("FLAG_SLOWDOWN_Z"), DEFAULT_FLAG_SLOWDOWN, CONFIG_INI_PATH);
	return nFlagSlowdown;
}

void SetDevWorktableModeSlowdownZ(int nModeSlowdown)
{
	CString strTmp;
	strTmp.Format(_T("%d"), nModeSlowdown);
	WritePrivateProfileString(_T("DeviceWorktable"), _T("MODE_SLOWDOWN_Z"), strTmp, CONFIG_INI_PATH);
}
int ReadDevWorktableModeSlowdownZ()
{
	int nModeSlowdown;
	nModeSlowdown = (int)GetPrivateProfileInt(_T("DeviceWorktable"), _T("MODE_SLOWDOWN_Z"), DEFAULT_MODE_SLOWDOWN, CONFIG_INI_PATH);
	return nModeSlowdown;
}

void SetDevWorktableFlagLimitZ(int nFlagLimit)
{
	CString strTmp;
	strTmp.Format(_T("%d"), nFlagLimit);
	WritePrivateProfileString(_T("DeviceWorktable"), _T("FLAG_LIMIT_Z"), strTmp, CONFIG_INI_PATH);
}
int ReadDevWorktableFlagLimitZ()
{
	int nFlagLimit;
	nFlagLimit = (int)GetPrivateProfileInt(_T("DeviceWorktable"), _T("FLAG_LIMIT_Z"), DEFAULT_FLAG_LIMIT, CONFIG_INI_PATH);
	return nFlagLimit;
}

void SetDevWorktableModeLimitZ(int nModeLimit)
{
	CString strTmp;
	strTmp.Format(_T("%d"), nModeLimit);
	WritePrivateProfileString(_T("DeviceWorktable"), _T("MODE_LIMIT_Z"), strTmp, CONFIG_INI_PATH);
}
int ReadDevWorktableModeLimitZ()
{
	int nModeLimit;
	nModeLimit = (int)GetPrivateProfileInt(_T("DeviceWorktable"), _T("MODE_LIMIT_Z"), DEFAULT_MODE_LIMIT, CONFIG_INI_PATH);
	return nModeLimit;
}

void SetDevWorktableFlagOrgZ(int nFlagOrg)
{
	CString strTmp;
	strTmp.Format(_T("%d"), nFlagOrg);
	WritePrivateProfileString(_T("DeviceWorktable"), _T("FLAG_ORG_Z"), strTmp, CONFIG_INI_PATH);
}
int ReadDevWorktableFlagOrgZ()
{
	int nFlagOrg;
	nFlagOrg = (int)GetPrivateProfileInt(_T("DeviceWorktable"), _T("FLAG_ORG_Z"), DEFAULT_FLAG_ORG, CONFIG_INI_PATH);
	return nFlagOrg;
}

void SetDevWorktableModeOrgZ(int nModeOrg)
{
	CString strTmp;
	strTmp.Format(_T("%d"), nModeOrg);
	WritePrivateProfileString(_T("DeviceWorktable"), _T("MODE_ORG_Z"), strTmp, CONFIG_INI_PATH);
}
int ReadDevWorktableModeOrgZ()
{
	int nModeOrg;
	nModeOrg = (int)GetPrivateProfileInt(_T("DeviceWorktable"), _T("MODE_ORG_Z"), DEFAULT_MODE_ORG, CONFIG_INI_PATH);
	return nModeOrg;
}

void SetDevWorktableFlagAlmZ(int nFlagAlm)
{
	CString strTmp;
	strTmp.Format(_T("%d"), nFlagAlm);
	WritePrivateProfileString(_T("DeviceWorktable"), _T("FLAG_ALM_Z"), strTmp, CONFIG_INI_PATH);
}
int ReadDevWorktableFlagAlmZ()
{
	int nFlagAlm;
	nFlagAlm = (int)GetPrivateProfileInt(_T("DeviceWorktable"), _T("FLAG_ALM_Z"), DEFAULT_FLAG_ALM, CONFIG_INI_PATH);
	return nFlagAlm;
}

void SetDevWorktableModeAlmZ(int nModeAlm)
{
	CString strTmp;
	strTmp.Format(_T("%d"), nModeAlm);
	WritePrivateProfileString(_T("DeviceWorktable"), _T("MODE_ALM_Z"), strTmp, CONFIG_INI_PATH);
}
int ReadDevWorktableModeAlmZ()
{
	int nModeAlm;
	nModeAlm = (int)GetPrivateProfileInt(_T("DeviceWorktable"), _T("MODE_ALM_Z"), DEFAULT_MODE_ALM, CONFIG_INI_PATH);
	return nModeAlm;
}

void SetDevWorktableSpeedMaxZ(double fSpeedMax)
{
	CString strTmp;
	strTmp.Format(_T("%lf"), fSpeedMax);
	WritePrivateProfileString(_T("DeviceWorktable"), _T("SPEED_MAX_Z"), strTmp, CONFIG_INI_PATH);
}
double ReadDevWorktableSpeedMaxZ()
{
	CString strTmp;
	GetPrivateProfileString(_T("DeviceWorktable"), _T("SPEED_MAX_Z"), DEFAULT_SPEED_MAX, strTmp.GetBuffer(MAX_DOUBLE_PRECISION), MAX_DOUBLE_PRECISION, CONFIG_INI_PATH);
	return (double)_ttof(strTmp);
}

void SetDevWorktableSpeedLowZ(double fSpeedLow)
{
	CString strTmp;
	strTmp.Format(_T("%lf"), fSpeedLow);
	WritePrivateProfileString(_T("DeviceWorktable"), _T("SPEED_LOW_Z"), strTmp, CONFIG_INI_PATH);
}
double ReadDevWorktableSpeedLowZ()
{
	CString strTmp;
	GetPrivateProfileString(_T("DeviceWorktable"), _T("SPEED_LOW_Z"), DEFAULT_SPEED_LOW, strTmp.GetBuffer(MAX_DOUBLE_PRECISION), MAX_DOUBLE_PRECISION, CONFIG_INI_PATH);
	return (double)_ttof(strTmp);
}

void SetDevWorktableSpeedHighZ(double fSpeedHigh)
{
	CString strTmp;
	strTmp.Format(_T("%lf"), fSpeedHigh);
	WritePrivateProfileString(_T("DeviceWorktable"), _T("SPEED_HIGH_Z"), strTmp, CONFIG_INI_PATH);
}
double ReadDevWorktableSpeedHighZ()
{
	CString strTmp;
	GetPrivateProfileString(_T("DeviceWorktable"), _T("SPEED_HIGH_Z"), DEFAULT_SPEED_HIGH, strTmp.GetBuffer(MAX_DOUBLE_PRECISION), MAX_DOUBLE_PRECISION, CONFIG_INI_PATH);
	return (double)_ttof(strTmp);
}

void SetDevWorktableSpeedAccZ(double fSpeedAcc)
{
	CString strTmp;
	strTmp.Format(_T("%lf"), fSpeedAcc);
	WritePrivateProfileString(_T("DeviceWorktable"), _T("SPEED_ACC_Z"), strTmp, CONFIG_INI_PATH);
}
double ReadDevWorktableSpeedAccZ()
{
	CString strTmp;
	GetPrivateProfileString(_T("DeviceWorktable"), _T("SPEED_ACC_Z"), DEFAULT_SPEED_ACC, strTmp.GetBuffer(MAX_DOUBLE_PRECISION), MAX_DOUBLE_PRECISION, CONFIG_INI_PATH);
	return (double)_ttof(strTmp);
}

void SetDevWorktableSpeedHandZ(double fSpeedHand)
{
	CString strTmp;
	strTmp.Format(_T("%lf"), fSpeedHand);
	WritePrivateProfileString(_T("DeviceWorktable"), _T("SPEED_HAND_Z"), strTmp, CONFIG_INI_PATH);
}
double ReadDevWorktableSpeedHandZ()
{
	CString strTmp;
	GetPrivateProfileString(_T("DeviceWorktable"), _T("SPEED_HAND_Z"), DEFAULT_SPEED_HAND, strTmp.GetBuffer(MAX_DOUBLE_PRECISION), MAX_DOUBLE_PRECISION, CONFIG_INI_PATH);
	return (double)_ttof(strTmp);
}

void SetDevWorktableSpeedProcZ(double fSpeedProc)
{
	CString strTmp;
	strTmp.Format(_T("%lf"), fSpeedProc);
	WritePrivateProfileString(_T("DeviceWorktable"), _T("SPEED_PROC_Z"), strTmp, CONFIG_INI_PATH);
}
double ReadDevWorktableSpeedProcZ()
{
	CString strTmp;
	GetPrivateProfileString(_T("DeviceWorktable"), _T("SPEED_PROC_Z"), DEFAULT_SPEED_PROC, strTmp.GetBuffer(MAX_DOUBLE_PRECISION), MAX_DOUBLE_PRECISION, CONFIG_INI_PATH);
	return (double)_ttof(strTmp);
}


//相机硬件配置 外部调用
////////////////////////////////////////////////////////////////////



// CDlgDevCfgTabWorktable 对话框

IMPLEMENT_DYNAMIC(CDlgDevCfgTabWorktable, CDialogEx)

CDlgDevCfgTabWorktable::CDlgDevCfgTabWorktable(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DEVICE_CONFIG_TAB_WORKTABLE, pParent)
	, m_nCardWorktableNameIndex(0)
	, m_nAxisXIndex(DEFAULT_AXIS_X_INDEX)
	, m_nAxisYIndex(DEFAULT_AXIS_Y_INDEX)
	, m_nAxisZIndex(DEFAULT_AXIS_Z_INDEX)
	, m_nAxisXReverse(DEFAULT_AXIS_REVERSE)
	, m_nAxisYReverse(DEFAULT_AXIS_REVERSE)
	, m_nAxisZReverse(DEFAULT_AXIS_REVERSE)
	, m_fPulsePerMMXY(_ttof(DEFAULT_PULSE_PER_MM))
	, m_fPulsePerMMZ(_ttof(DEFAULT_PULSE_PER_MM))
	, m_nModeHomeXY(DEFAULT_MODE_HOME)
	, m_nModeHomeZ(DEFAULT_MODE_HOME)
	, m_nFlagSoftlimitXY(DEFAULT_FLAG_SOFTLIMIT)
	, m_nFlagSoftlimitZ(DEFAULT_FLAG_SOFTLIMIT)
	, m_nFlagSlowdownXY(DEFAULT_FLAG_SLOWDOWN)
	, m_nFlagSlowdownZ(DEFAULT_FLAG_SLOWDOWN)
	, m_nModeSlowdownXY(DEFAULT_MODE_SLOWDOWN)
	, m_nModeSlowdownZ(DEFAULT_MODE_SLOWDOWN)
	, m_nFlagLimitXY(DEFAULT_FLAG_LIMIT)
	, m_nFlagLimitZ(DEFAULT_FLAG_LIMIT)
	, m_nModeLimitXY(DEFAULT_MODE_LIMIT)
	, m_nModeLimitZ(DEFAULT_MODE_LIMIT)
	, m_nFlagOrgXY(DEFAULT_FLAG_ORG)
	, m_nFlagOrgZ(DEFAULT_FLAG_ORG)
	, m_nModeOrgXY(DEFAULT_MODE_ORG)
	, m_nModeOrgZ(DEFAULT_MODE_ORG)
	, m_nFlagAlmXY(DEFAULT_FLAG_ALM)
	, m_nFlagAlmZ(DEFAULT_FLAG_ALM)
	, m_nModeAlmXY(DEFAULT_MODE_ALM)
	, m_nModeAlmZ(DEFAULT_MODE_ALM)
	, m_fSpeedMaxXY(_ttof(DEFAULT_SPEED_MAX))
	, m_fSpeedMaxZ(_ttof(DEFAULT_SPEED_MAX))
	, m_fSpeedLowXY(_ttof(DEFAULT_SPEED_LOW))
	, m_fSpeedLowZ(_ttof(DEFAULT_SPEED_LOW))
	, m_fSpeedHighXY(_ttof(DEFAULT_SPEED_HIGH))
	, m_fSpeedHighZ(_ttof(DEFAULT_SPEED_HIGH))
	, m_fSpeedAccXY(_ttof(DEFAULT_SPEED_ACC))
	, m_fSpeedAccZ(_ttof(DEFAULT_SPEED_ACC))
	, m_fSpeedHandXY(_ttof(DEFAULT_SPEED_HAND))
	, m_fSpeedHandZ(_ttof(DEFAULT_SPEED_HAND))
	, m_fSpeedProcXY(_ttof(DEFAULT_SPEED_PROC))
	, m_fSpeedProcZ(_ttof(DEFAULT_SPEED_PROC))
{

}

CDlgDevCfgTabWorktable::~CDlgDevCfgTabWorktable()
{
}

void CDlgDevCfgTabWorktable::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//XY轴参数
	DDX_CBIndex(pDX, IDC_COMBO_WORKTABLE_CARD, m_nCardWorktableNameIndex);
	DDX_CBIndex(pDX, IDC_COMBO_WORKTABLE_AXIS_X_INDEX, m_nAxisXIndex);
	DDX_CBIndex(pDX, IDC_COMBO_WORKTABLE_AXIS_Y_INDEX, m_nAxisYIndex);
	DDX_Check(pDX, IDC_CHECK_WORKTABLE_AXIS_X_REVERSE, m_nAxisXReverse);
	DDX_Check(pDX, IDC_CHECK_WORKTABLE_AXIS_Y_REVERSE, m_nAxisYReverse);
	DDX_Text(pDX, IDC_EDIT_WORKTABLE_PULSE_PER_MM_XY, m_fPulsePerMMXY);
	DDV_MinMaxDouble(pDX, m_fPulsePerMMXY, _ttof(DEFAULT_PULSE_PER_MM_MIN), _ttof(DEFAULT_PULSE_PER_MM_MAX));
	DDX_CBIndex(pDX, IDC_COMBO_WORKTABLE_HOME_MODE_XY, m_nModeHomeXY);
	DDX_Check(pDX, IDC_CHECK_WORKTABLE_FLAG_SOFTLIMIT_XY, m_nFlagSoftlimitXY);

	DDX_Check(pDX, IDC_CHECK_WORKTABLE_FLAG_SLOWDOWN_XY, m_nFlagSlowdownXY);
	DDX_Radio(pDX, IDC_RADIO_WORKTABLE_MODE_SLOWDOWN_LOW_XY, m_nModeSlowdownXY);
	DDX_Check(pDX, IDC_CHECK_WORKTABLE_FLAG_LIMIT_XY, m_nFlagLimitXY);
	DDX_Radio(pDX, IDC_RADIO_WORKTABLE_MODE_LIMIT_LOW_XY, m_nModeLimitXY);
	DDX_Check(pDX, IDC_CHECK_WORKTABLE_FLAG_ORG_XY, m_nFlagOrgXY);
	DDX_Radio(pDX, IDC_RADIO_WORKTABLE_MODE_ORG_LOW_XY, m_nModeOrgXY);
	DDX_Check(pDX, IDC_CHECK_WORKTABLE_FLAG_ALM_XY, m_nFlagAlmXY);
	DDX_Radio(pDX, IDC_RADIO_WORKTABLE_MODE_ALM_LOW_XY, m_nModeAlmXY);

	DDX_Text(pDX, IDC_EDIT_WORKTABLE_SPEED_MAX_XY, m_fSpeedMaxXY);
	DDV_MinMaxDouble(pDX, m_fSpeedMaxXY, _ttof(DEFAULT_SPEED_MAX_MIN), _ttof(DEFAULT_SPEED_MAX_MAX));
	DDX_Text(pDX, IDC_EDIT_WORKTABLE_SPEED_LOW_XY, m_fSpeedLowXY);
	DDV_MinMaxDouble(pDX, m_fSpeedLowXY, _ttof(DEFAULT_SPEED_LOW_MIN), _ttof(DEFAULT_SPEED_LOW_MAX));
	DDX_Text(pDX, IDC_EDIT_WORKTABLE_SPEED_HIGH_XY, m_fSpeedHighXY);
	DDV_MinMaxDouble(pDX, m_fSpeedHighXY, _ttof(DEFAULT_SPEED_HIGH_MIN), _ttof(DEFAULT_SPEED_HIGH_MAX));
	DDX_Text(pDX, IDC_EDIT_WORKTABLE_SPEED_ACC_XY, m_fSpeedAccXY);
	DDV_MinMaxDouble(pDX, m_fSpeedAccXY, _ttof(DEFAULT_SPEED_ACC_MIN), _ttof(DEFAULT_SPEED_ACC_MAX));
	DDX_Text(pDX, IDC_EDIT_WORKTABLE_SPEED_HAND_XY, m_fSpeedHandXY);
	DDV_MinMaxDouble(pDX, m_fSpeedHandXY, _ttof(DEFAULT_SPEED_HAND_MIN), _ttof(DEFAULT_SPEED_HAND_MAX));
	DDX_Text(pDX, IDC_EDIT_WORKTABLE_SPEED_PROC_XY, m_fSpeedProcXY);
	DDV_MinMaxDouble(pDX, m_fSpeedProcXY, _ttof(DEFAULT_SPEED_PROC_MIN), _ttof(DEFAULT_SPEED_PROC_MAX));

	//Z轴参数
	DDX_CBIndex(pDX, IDC_COMBO_WORKTABLE_AXIS_Z_INDEX, m_nAxisZIndex);
	DDX_Check(pDX, IDC_CHECK_WORKTABLE_AXIS_Z_REVERSE, m_nAxisZReverse);
	DDX_Text(pDX, IDC_EDIT_WORKTABLE_PULSE_PER_MM_Z, m_fPulsePerMMZ);
	DDV_MinMaxDouble(pDX, m_fPulsePerMMZ, _ttof(DEFAULT_PULSE_PER_MM_MIN), _ttof(DEFAULT_PULSE_PER_MM_MAX));
	DDX_CBIndex(pDX, IDC_COMBO_WORKTABLE_HOME_MODE_Z, m_nModeHomeZ);
	DDX_Check(pDX, IDC_CHECK_WORKTABLE_FLAG_SOFTLIMIT_Z, m_nFlagSoftlimitZ);

	DDX_Check(pDX, IDC_CHECK_WORKTABLE_FLAG_SLOWDOWN_Z, m_nFlagSlowdownZ);
	DDX_Radio(pDX, IDC_RADIO_WORKTABLE_MODE_SLOWDOWN_LOW_Z, m_nModeSlowdownZ);
	DDX_Check(pDX, IDC_CHECK_WORKTABLE_FLAG_LIMIT_Z, m_nFlagLimitZ);
	DDX_Radio(pDX, IDC_RADIO_WORKTABLE_MODE_LIMIT_LOW_Z, m_nModeLimitZ);
	DDX_Check(pDX, IDC_CHECK_WORKTABLE_FLAG_ORG_Z, m_nFlagOrgZ);
	DDX_Radio(pDX, IDC_RADIO_WORKTABLE_MODE_ORG_LOW_Z, m_nModeOrgZ);
	DDX_Check(pDX, IDC_CHECK_WORKTABLE_FLAG_ALM_Z, m_nFlagAlmZ);
	DDX_Radio(pDX, IDC_RADIO_WORKTABLE_MODE_ALM_LOW_Z, m_nModeAlmZ);

	DDX_Text(pDX, IDC_EDIT_WORKTABLE_SPEED_MAX_Z, m_fSpeedMaxZ);
	DDV_MinMaxDouble(pDX, m_fSpeedMaxZ, _ttof(DEFAULT_SPEED_MAX_MIN), _ttof(DEFAULT_SPEED_MAX_MAX));
	DDX_Text(pDX, IDC_EDIT_WORKTABLE_SPEED_LOW_Z, m_fSpeedLowZ);
	DDV_MinMaxDouble(pDX, m_fSpeedLowZ, _ttof(DEFAULT_SPEED_LOW_MIN), _ttof(DEFAULT_SPEED_LOW_MAX));
	DDX_Text(pDX, IDC_EDIT_WORKTABLE_SPEED_HIGH_Z, m_fSpeedHighZ);
	DDV_MinMaxDouble(pDX, m_fSpeedHighZ, _ttof(DEFAULT_SPEED_HIGH_MIN), _ttof(DEFAULT_SPEED_HIGH_MAX));
	DDX_Text(pDX, IDC_EDIT_WORKTABLE_SPEED_ACC_Z, m_fSpeedAccZ);
	DDV_MinMaxDouble(pDX, m_fSpeedAccZ, _ttof(DEFAULT_SPEED_ACC_MIN), _ttof(DEFAULT_SPEED_ACC_MAX));
	DDX_Text(pDX, IDC_EDIT_WORKTABLE_SPEED_HAND_Z, m_fSpeedHandZ);
	DDV_MinMaxDouble(pDX, m_fSpeedHandZ, _ttof(DEFAULT_SPEED_HAND_MIN), _ttof(DEFAULT_SPEED_HAND_MAX));
	DDX_Text(pDX, IDC_EDIT_WORKTABLE_SPEED_PROC_Z, m_fSpeedProcZ);
	DDV_MinMaxDouble(pDX, m_fSpeedProcZ, _ttof(DEFAULT_SPEED_PROC_MIN), _ttof(DEFAULT_SPEED_PROC_MAX));

}


BEGIN_MESSAGE_MAP(CDlgDevCfgTabWorktable, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_WORKTABLE_APPLY, &CDlgDevCfgTabWorktable::OnBnClickedButtonWorktableApply)
END_MESSAGE_MAP()


// CDlgDevCfgTabWorktable 消息处理程序


BOOL CDlgDevCfgTabWorktable::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	//初始化界面
	((CComboBox*)GetDlgItem(IDC_COMBO_WORKTABLE_CARD))->InsertString(0, (_T("无")));
	((CComboBox*)GetDlgItem(IDC_COMBO_WORKTABLE_CARD))->InsertString(1, (_T("MPC2810")));

	((CComboBox*)GetDlgItem(IDC_COMBO_WORKTABLE_AXIS_X_INDEX))->InsertString(0, (_T("无")));
	((CComboBox*)GetDlgItem(IDC_COMBO_WORKTABLE_AXIS_X_INDEX))->InsertString(1, (_T("轴1")));
	((CComboBox*)GetDlgItem(IDC_COMBO_WORKTABLE_AXIS_X_INDEX))->InsertString(2, (_T("轴2")));
	((CComboBox*)GetDlgItem(IDC_COMBO_WORKTABLE_AXIS_X_INDEX))->InsertString(3, (_T("轴3")));
	((CComboBox*)GetDlgItem(IDC_COMBO_WORKTABLE_AXIS_X_INDEX))->InsertString(4, (_T("轴4")));

	((CComboBox*)GetDlgItem(IDC_COMBO_WORKTABLE_AXIS_Y_INDEX))->InsertString(0, (_T("无")));
	((CComboBox*)GetDlgItem(IDC_COMBO_WORKTABLE_AXIS_Y_INDEX))->InsertString(1, (_T("轴1")));
	((CComboBox*)GetDlgItem(IDC_COMBO_WORKTABLE_AXIS_Y_INDEX))->InsertString(2, (_T("轴2")));
	((CComboBox*)GetDlgItem(IDC_COMBO_WORKTABLE_AXIS_Y_INDEX))->InsertString(3, (_T("轴3")));
	((CComboBox*)GetDlgItem(IDC_COMBO_WORKTABLE_AXIS_Y_INDEX))->InsertString(4, (_T("轴4")));

	((CComboBox*)GetDlgItem(IDC_COMBO_WORKTABLE_AXIS_Z_INDEX))->InsertString(0, (_T("无")));
	((CComboBox*)GetDlgItem(IDC_COMBO_WORKTABLE_AXIS_Z_INDEX))->InsertString(1, (_T("轴1")));
	((CComboBox*)GetDlgItem(IDC_COMBO_WORKTABLE_AXIS_Z_INDEX))->InsertString(2, (_T("轴2")));
	((CComboBox*)GetDlgItem(IDC_COMBO_WORKTABLE_AXIS_Z_INDEX))->InsertString(3, (_T("轴3")));
	((CComboBox*)GetDlgItem(IDC_COMBO_WORKTABLE_AXIS_Z_INDEX))->InsertString(4, (_T("轴4")));

	//	0：检测到原点接近开关信号轴立即停止运动；
	//	1：检测到出现编码器 Z 相脉冲信号时立即停止运动。
	//	2：检测到原点接近开关信号轴立即反向，遇 Z 脉冲立即停止。
	//	3：梯形速度模式时，减速信号有效减速，当原点接近开关信号有效停止运动。
	//	4：梯形速度模式下作回原点运动，原点信号有效时，控制轴按快速运动方式设置的加速度逐渐减速至低速，直到 Z 脉冲有效立即停止运动。
	//	5：梯形速度模式下作回原点运动，原点信号有效时，控制轴按快速运动方式设置的加速度减速停止。再反向运动，遇 Z 脉冲停止反向运动。
	((CComboBox*)GetDlgItem(IDC_COMBO_WORKTABLE_HOME_MODE_XY))->InsertString(0, (_T("原点")));
	((CComboBox*)GetDlgItem(IDC_COMBO_WORKTABLE_HOME_MODE_XY))->InsertString(1, (_T("Z相脉冲")));
	((CComboBox*)GetDlgItem(IDC_COMBO_WORKTABLE_HOME_MODE_XY))->InsertString(2, (_T("-Z相脉冲")));
	((CComboBox*)GetDlgItem(IDC_COMBO_WORKTABLE_HOME_MODE_XY))->InsertString(3, (_T("梯/原点")));
	((CComboBox*)GetDlgItem(IDC_COMBO_WORKTABLE_HOME_MODE_XY))->InsertString(4, (_T("梯/Z相脉冲")));
	((CComboBox*)GetDlgItem(IDC_COMBO_WORKTABLE_HOME_MODE_XY))->InsertString(5, (_T("梯/-Z相脉冲")));

	((CComboBox*)GetDlgItem(IDC_COMBO_WORKTABLE_HOME_MODE_Z))->InsertString(0, (_T("原点")));
	((CComboBox*)GetDlgItem(IDC_COMBO_WORKTABLE_HOME_MODE_Z))->InsertString(1, (_T("Z相脉冲")));
	((CComboBox*)GetDlgItem(IDC_COMBO_WORKTABLE_HOME_MODE_Z))->InsertString(2, (_T("-Z相脉冲")));
	((CComboBox*)GetDlgItem(IDC_COMBO_WORKTABLE_HOME_MODE_Z))->InsertString(3, (_T("梯/原点")));
	((CComboBox*)GetDlgItem(IDC_COMBO_WORKTABLE_HOME_MODE_Z))->InsertString(4, (_T("梯/Z相脉冲")));
	((CComboBox*)GetDlgItem(IDC_COMBO_WORKTABLE_HOME_MODE_Z))->InsertString(5, (_T("梯/-Z相脉冲")));


	//初始化数值
	m_nCardWorktableNameIndex = (int)ReadDevWorktableName();
	m_nAxisXIndex = ReadDevWorktableAxisXIndex();
	m_nAxisYIndex = ReadDevWorktableAxisYIndex();
	m_nAxisZIndex = ReadDevWorktableAxisZIndex();
	m_nAxisXReverse = ReadDevWorktableAxisXReverse();
	m_nAxisYReverse = ReadDevWorktableAxisYReverse();
	m_nAxisZReverse = ReadDevWorktableAxisZReverse();

	m_fPulsePerMMXY = ReadDevWorktablePulsePerMMXY();
	m_nModeHomeXY = ReadDevWorktableModeHomeXY();
	m_nFlagSoftlimitXY = ReadDevWorktableFlagSlowdownXY();
	m_nFlagSlowdownXY = ReadDevWorktableFlagSlowdownXY();
	m_nModeSlowdownXY = ReadDevWorktableModeSlowdownXY();
	m_nFlagLimitXY = ReadDevWorktableFlagLimitXY();
	m_nModeLimitXY = ReadDevWorktableModeLimitXY();
	m_nFlagOrgXY = ReadDevWorktableFlagOrgXY();
	m_nModeOrgXY = ReadDevWorktableModeOrgXY();
	m_nFlagAlmXY = ReadDevWorktableFlagAlmXY();
	m_nModeAlmXY = ReadDevWorktableModeAlmXY();
	m_fSpeedMaxXY = ReadDevWorktableSpeedMaxXY();
	m_fSpeedLowXY = ReadDevWorktableSpeedLowXY();
	m_fSpeedHighXY = ReadDevWorktableSpeedHighXY();
	m_fSpeedAccXY = ReadDevWorktableSpeedAccXY();
	m_fSpeedHandXY = ReadDevWorktableSpeedHandXY();
	m_fSpeedProcXY = ReadDevWorktableSpeedProcXY();

	m_fPulsePerMMZ = ReadDevWorktablePulsePerMMZ();
	m_nModeHomeZ = ReadDevWorktableModeHomeZ();
	m_nFlagSoftlimitZ = ReadDevWorktableFlagSlowdownZ();
	m_nFlagSlowdownZ = ReadDevWorktableFlagSlowdownZ();
	m_nModeSlowdownZ = ReadDevWorktableModeSlowdownZ();
	m_nFlagLimitZ = ReadDevWorktableFlagLimitZ();
	m_nModeLimitZ = ReadDevWorktableModeLimitZ();
	m_nFlagOrgZ = ReadDevWorktableFlagOrgZ();
	m_nModeOrgZ = ReadDevWorktableModeOrgZ();
	m_nFlagAlmZ = ReadDevWorktableFlagAlmZ();
	m_nModeAlmZ = ReadDevWorktableModeAlmZ();
	m_fSpeedMaxZ = ReadDevWorktableSpeedMaxZ();
	m_fSpeedLowZ = ReadDevWorktableSpeedLowZ();
	m_fSpeedHighZ = ReadDevWorktableSpeedHighZ();
	m_fSpeedAccZ = ReadDevWorktableSpeedAccZ();
	m_fSpeedHandZ = ReadDevWorktableSpeedHandZ();
	m_fSpeedProcZ = ReadDevWorktableSpeedProcZ();

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDlgDevCfgTabWorktable::OnBnClickedButtonWorktableApply()
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(TRUE);

	//写ini
	SetDevWorktableName((WORKTABLE_NAME)m_nCardWorktableNameIndex);
	SetDevWorktableAxisXIndex(m_nAxisXIndex);
	SetDevWorktableAxisYIndex(m_nAxisYIndex);
	SetDevWorktableAxisZIndex(m_nAxisZIndex);
	SetDevWorktableAxisXReverse(m_nAxisXReverse);
	SetDevWorktableAxisYReverse(m_nAxisYReverse);
	SetDevWorktableAxisZReverse(m_nAxisZReverse);

	SetDevWorktablePulsePerMMXY(m_fPulsePerMMXY);
	SetDevWorktableModeHomeXY(m_nModeHomeXY);
	SetDevWorktableFlagSoftlimitXY(m_nFlagSoftlimitXY);
	SetDevWorktableFlagSlowdownXY(m_nFlagSlowdownXY);
	SetDevWorktableModeSlowdownXY(m_nModeSlowdownXY);
	SetDevWorktableFlagLimitXY(m_nFlagLimitXY);
	SetDevWorktableModeLimitXY(m_nModeLimitXY);
	SetDevWorktableFlagOrgXY(m_nFlagOrgXY);
	SetDevWorktableModeOrgXY(m_nModeOrgXY);
	SetDevWorktableFlagAlmXY(m_nFlagAlmXY);
	SetDevWorktableModeAlmXY(m_nModeAlmXY);
	SetDevWorktableSpeedMaxXY(m_fSpeedMaxXY);
	SetDevWorktableSpeedLowXY(m_fSpeedLowXY);
	SetDevWorktableSpeedHighXY(m_fSpeedHighXY);
	SetDevWorktableSpeedAccXY(m_fSpeedAccXY);
	SetDevWorktableSpeedHandXY(m_fSpeedHandXY);
	SetDevWorktableSpeedProcXY(m_fSpeedProcXY);

	SetDevWorktablePulsePerMMZ(m_fPulsePerMMZ);
	SetDevWorktableModeHomeZ(m_nModeHomeZ);
	SetDevWorktableFlagSoftlimitZ(m_nFlagSoftlimitZ);
	SetDevWorktableFlagSlowdownZ(m_nFlagSlowdownZ);
	SetDevWorktableModeSlowdownZ(m_nModeSlowdownZ);
	SetDevWorktableFlagLimitZ(m_nFlagLimitZ);
	SetDevWorktableModeLimitZ(m_nModeLimitZ);
	SetDevWorktableFlagOrgZ(m_nFlagOrgZ);
	SetDevWorktableModeOrgZ(m_nModeOrgZ);
	SetDevWorktableFlagAlmZ(m_nFlagAlmZ);
	SetDevWorktableModeAlmZ(m_nModeAlmZ);
	SetDevWorktableSpeedMaxZ(m_fSpeedMaxZ);
	SetDevWorktableSpeedLowZ(m_fSpeedLowZ);
	SetDevWorktableSpeedHighZ(m_fSpeedHighZ);
	SetDevWorktableSpeedAccZ(m_fSpeedAccZ);
	SetDevWorktableSpeedHandZ(m_fSpeedHandZ);
	SetDevWorktableSpeedProcZ(m_fSpeedProcZ);

	//写工作台参数
	if (NULL == pDevCardWorktable)
		return;

	pDevCardWorktable->	m_axisX.SetParamAxis(m_nAxisXIndex, m_nAxisXReverse, m_fPulsePerMMXY, m_nModeHomeXY, m_nFlagSoftlimitXY,
		m_nFlagSlowdownXY, m_nModeSlowdownXY, m_nFlagLimitXY, m_nModeLimitXY, m_nFlagOrgXY, m_nModeOrgXY, m_nFlagAlmXY, m_nModeAlmXY,
		m_fSpeedMaxXY, m_fSpeedLowXY, m_fSpeedHighXY, m_fSpeedAccXY, m_fSpeedHandXY, m_fSpeedProcXY);
	pDevCardWorktable->m_axisY.SetParamAxis(m_nAxisYIndex, m_nAxisYReverse, m_fPulsePerMMXY, m_nModeHomeXY, m_nFlagSoftlimitXY,
		m_nFlagSlowdownXY, m_nModeSlowdownXY, m_nFlagLimitXY, m_nModeLimitXY, m_nFlagOrgXY, m_nModeOrgXY, m_nFlagAlmXY, m_nModeAlmXY,
		m_fSpeedMaxXY, m_fSpeedLowXY, m_fSpeedHighXY, m_fSpeedAccXY, m_fSpeedHandXY, m_fSpeedProcXY);
	pDevCardWorktable->m_axisZ.SetParamAxis(m_nAxisZIndex, m_nAxisZReverse, m_fPulsePerMMZ, m_nModeHomeZ, m_nFlagSoftlimitZ,
		m_nFlagSlowdownZ, m_nModeSlowdownZ, m_nFlagLimitZ, m_nModeLimitZ, m_nFlagOrgZ, m_nModeOrgZ, m_nFlagAlmZ, m_nModeAlmZ,
		m_fSpeedMaxZ, m_fSpeedLowZ, m_fSpeedHighZ, m_fSpeedAccZ, m_fSpeedHandZ, m_fSpeedProcZ);


}


