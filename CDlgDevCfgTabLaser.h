#pragma once

#define ID_TIMEER_LASER_BELLIN WM_USER+301



extern void SetDevLaserTypeIndex(int nIndex);
extern int ReadDevLaserTypeIndex();
extern void SetDevLaserIPAddress(CString str);
extern CString ReadDevLaserIPAddress();



// CDlgDevCfgTabLaser 对话框

class CDlgDevCfgTabLaser : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgDevCfgTabLaser)

public:
	CDlgDevCfgTabLaser(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgDevCfgTabLaser();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DEVICE_CONFIG_TAB_LASER };
#endif

protected:
	int m_nLaserType;
	CString m_strLaserBellinIP;
	void ChangeLaserType(int nLaserType);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeComboLaserType();
	afx_msg void OnBnClickedButtonLaserBellinConnect();
protected:
	afx_msg LRESULT OnSocketClient(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnBnClickedButtonLaserBellinOpenMachine();
	afx_msg void OnBnClickedButtonLaserBellinEmissionOn();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButtonLaserBellinExtTrigOn();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
};


