#pragma once


////////////////////////////////////////////////////////////////////
//相机硬件配置 外部调用
#define DEFAULT_AXIS_X_INDEX 1
#define DEFAULT_AXIS_Y_INDEX 2
#define DEFAULT_AXIS_Z_INDEX 3
#define DEFAULT_AXIS_REVERSE 0
#define DEFAULT_PULSE_PER_MM _T("2000")
#define DEFAULT_PULSE_PER_MM_MIN _T("0")
#define DEFAULT_PULSE_PER_MM_MAX _T("20000")
#define MAX_DOUBLE_PRECISION 10
#define DEFAULT_MODE_HOME 0
#define DEFAULT_FLAG_SOFTLIMIT 0
#define DEFAULT_FLAG_SLOWDOWN 0
#define DEFAULT_MODE_SLOWDOWN 0
#define DEFAULT_FLAG_LIMIT 0
#define DEFAULT_MODE_LIMIT 0
#define DEFAULT_FLAG_ORG 0
#define DEFAULT_MODE_ORG 0
#define DEFAULT_FLAG_ALM 0
#define DEFAULT_MODE_ALM 0
#define DEFAULT_SPEED_MAX _T("1000")
#define DEFAULT_SPEED_MAX_MIN _T("0")
#define DEFAULT_SPEED_MAX_MAX _T("2000")
#define DEFAULT_SPEED_LOW _T("0")
#define DEFAULT_SPEED_LOW_MIN _T("0")
#define DEFAULT_SPEED_LOW_MAX _T("2000")
#define DEFAULT_SPEED_HIGH _T("500")
#define DEFAULT_SPEED_HIGH_MIN _T("0")
#define DEFAULT_SPEED_HIGH_MAX _T("2000")
#define DEFAULT_SPEED_ACC _T("10000")
#define DEFAULT_SPEED_ACC_MIN _T("0")
#define DEFAULT_SPEED_ACC_MAX _T("10000")
#define DEFAULT_SPEED_HAND _T("500")
#define DEFAULT_SPEED_HAND_MIN _T("0")
#define DEFAULT_SPEED_HAND_MAX _T("2000")
#define DEFAULT_SPEED_PROC _T("500")
#define DEFAULT_SPEED_PROC_MIN _T("0")
#define DEFAULT_SPEED_PROC_MAX _T("2000")


enum class WORKTABLE_NAME
{
	WORKTABLE_NONE = 0,
	WORKTABLE_MPC2810 = 1,
};
extern void SetDevWorktableName(WORKTABLE_NAME eWorktableName);
extern WORKTABLE_NAME ReadDevWorktableName();

//XY轴参数读写
extern void SetDevWorktableAxisXIndex(int nIndex);
extern int ReadDevWorktableAxisXIndex();
extern void SetDevWorktableAxisYIndex(int nIndex);
extern int ReadDevWorktableAxisYIndex();
extern void SetDevWorktableAxisXReverse(int nReverse);
extern int ReadDevWorktableAxisXReverse();
extern void SetDevWorktableAxisYReverse(int nReverse);
extern int ReadDevWorktableAxisYReverse();
extern void SetDevWorktablePulsePerMMXY(double fPulsePerMM);
extern double ReadDevWorktablePulsePerMMXY();
extern void SetDevWorktableModeHomeXY(int nModeHome);
extern int ReadDevWorktableModeHomeXY();
extern void SetDevWorktableFlagSoftlimitXY(int nFlagSoftlimit);
extern int ReadDevWorktableFlagSoftlimitXY();
extern void SetDevWorktableFlagSlowdownXY(int nFlagSlowdown);
extern int ReadDevWorktableFlagSlowdownXY();
extern void SetDevWorktableModeSlowdownXY(int nModeSlowdown);
extern int ReadDevWorktableModeSlowdownXY();
extern void SetDevWorktableFlagLimitXY(int nFlagLimit);
extern int ReadDevWorktableFlagLimitXY();
extern void SetDevWorktableModeLimitXY(int nModeLimit);
extern int ReadDevWorktableModeLimitXY();
extern void SetDevWorktableFlagOrgXY(int nFlagOrg);
extern int ReadDevWorktableFlagOrgXY();
extern void SetDevWorktableModeOrgXY(int nModeOrg);
extern int ReadDevWorktableModeOrgXY();
extern void SetDevWorktableFlagAlmXY(int nFlagAlm);
extern int ReadDevWorktableFlagAlmXY();
extern void SetDevWorktableModeAlmXY(int nModeAlm);
extern int ReadDevWorktableModeAlmXY();
extern void SetDevWorktableSpeedMaxXY(double fSpeedMax);
extern double ReadDevWorktableSpeedMaxXY();
extern void SetDevWorktableSpeedLowXY(double fSpeedLow);
extern double ReadDevWorktableSpeedLowXY();
extern void SetDevWorktableSpeedHighXY(double fSpeedHigh);
extern double ReadDevWorktableSpeedHighXY();
extern void SetDevWorktableSpeedAccXY(double fSpeedAcc);
extern double ReadDevWorktableSpeedAccXY();
extern void SetDevWorktableSpeedHandXY(double fSpeedHand);
extern double ReadDevWorktableSpeedHandXY();
extern void SetDevWorktableSpeedProcXY(double fSpeedProc);
extern double ReadDevWorktableSpeedProcXY();

//Z轴参数读写
extern void SetDevWorktableAxisZIndex(int nIndex);
extern int ReadDevWorktableAxisZIndex();
extern void SetDevWorktableAxisZReverse(int nReverse);
extern int ReadDevWorktableAxisZReverse();
extern void SetDevWorktablePulsePerMMZ(double fPulsePerMM);
extern double ReadDevWorktablePulsePerMMZ();
extern void SetDevWorktableModeHomeZ(int nModeHome);
extern int ReadDevWorktableModeHomeZ();
extern void SetDevWorktableFlagSoftlimitZ(int nFlagSoftlimit);
extern int ReadDevWorktableFlagSoftlimitZ();
extern void SetDevWorktableFlagSlowdownZ(int nFlagSlowdown);
extern int ReadDevWorktableFlagSlowdownZ();
extern void SetDevWorktableModeSlowdownZ(int nModeSlowdown);
extern int ReadDevWorktableModeSlowdownZ();
extern void SetDevWorktableFlagLimitZ(int nFlagLimit);
extern int ReadDevWorktableFlagLimitZ();
extern void SetDevWorktableModeLimitZ(int nModeLimit);
extern int ReadDevWorktableModeLimitZ();
extern void SetDevWorktableFlagOrgZ(int nFlagOrg);
extern int ReadDevWorktableFlagOrgZ();
extern void SetDevWorktableModeOrgZ(int nModeOrg);
extern int ReadDevWorktableModeOrgZ();
extern void SetDevWorktableFlagAlmZ(int nFlagAlm);
extern int ReadDevWorktableFlagAlmZ();
extern void SetDevWorktableModeAlmZ(int nModeAlm);
extern int ReadDevWorktableModeAlmZ();
extern void SetDevWorktableSpeedMaxZ(double fSpeedMax);
extern double ReadDevWorktableSpeedMaxZ();
extern void SetDevWorktableSpeedLowZ(double fSpeedLow);
extern double ReadDevWorktableSpeedLowZ();
extern void SetDevWorktableSpeedHighZ(double fSpeedHigh);
extern double ReadDevWorktableSpeedHighZ();
extern void SetDevWorktableSpeedAccZ(double fSpeedAcc);
extern double ReadDevWorktableSpeedAccZ();
extern void SetDevWorktableSpeedHandZ(double fSpeedHand);
extern double ReadDevWorktableSpeedHandZ();
extern void SetDevWorktableSpeedProcZ(double fSpeedProc);
extern double ReadDevWorktableSpeedProcZ();

//相机硬件配置 外部调用
////////////////////////////////////////////////////////////////////



// CDlgDevCfgTabWorktable 对话框

class CDlgDevCfgTabWorktable : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgDevCfgTabWorktable)

public:
	CDlgDevCfgTabWorktable(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgDevCfgTabWorktable();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DEVICE_CONFIG_TAB_WORKTABLE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonWorktableApply();


//工作台参数列表
protected:
	int m_nCardWorktableNameIndex;

	int m_nAxisXIndex, m_nAxisYIndex, m_nAxisZIndex;
	int m_nAxisXReverse, m_nAxisYReverse, m_nAxisZReverse;
	double m_fPulsePerMMXY, m_fPulsePerMMZ;
	int m_nModeHomeXY, m_nModeHomeZ;
	int m_nFlagSoftlimitXY, m_nFlagSoftlimitZ;
	int m_nFlagSlowdownXY, m_nFlagSlowdownZ;
	int m_nModeSlowdownXY, m_nModeSlowdownZ;
	int m_nFlagLimitXY, m_nFlagLimitZ;
	int m_nModeLimitXY, m_nModeLimitZ;
	int m_nFlagOrgXY, m_nFlagOrgZ;
	int m_nModeOrgXY, m_nModeOrgZ;
	int m_nFlagAlmXY, m_nFlagAlmZ;
	int m_nModeAlmXY, m_nModeAlmZ;
	double m_fSpeedMaxXY, m_fSpeedMaxZ;
	double m_fSpeedLowXY, m_fSpeedLowZ;
	double m_fSpeedHighXY, m_fSpeedHighZ;
	double m_fSpeedAccXY, m_fSpeedAccZ;
	double m_fSpeedHandXY, m_fSpeedHandZ;
	double m_fSpeedProcXY, m_fSpeedProcZ;

};
