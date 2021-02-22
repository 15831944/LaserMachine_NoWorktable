#pragma once
#include "CDlgDevCfgTabLaser.h"
#include "CDlgDevCfgTabCamera.h"
#include "CDlgDevCfgTabScanner.h"
#include "CDlgDevCfgTabWorktable.h"

// CDevCfgDlg �Ի���

class CDevCfgDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDevCfgDlg)

public:
	CDevCfgDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDevCfgDlg();

// �Ի�������
	enum { IDD = IDD_DEVICE_CONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedCancel();
protected:
	afx_msg LRESULT OnMainwindowsResume(WPARAM wParam, LPARAM lParam);
public:
//	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBtnSave();

protected:
	CTabCtrl m_tab;
	int m_CurSelTab;
	CDlgDevCfgTabLaser m_dlgDevCfgTabLASER;
	CDlgDevCfgTabScanner m_dlgDevCfgTabScanner;
	CDlgDevCfgTabWorktable m_dlgDevCfgTabWorktable;
	CDlgDevCfgTabCamera m_dlgDevCfgTabCamera;
	CDialog* pDialog[4];  //��������Ի������ָ��
	virtual BOOL OnInitDialog();
	afx_msg void OnTcnSelchangeTabDeviceConfig(NMHDR* pNMHDR, LRESULT* pResult);
};
