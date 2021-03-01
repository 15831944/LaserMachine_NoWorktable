#pragma once
#include "PointF.h"
#include <vector>

extern void SetScannerLenRegion(double fScannerCaliRegion);
extern double ReadScannerLenRegion();
extern void SetScannerCaliRegion(double fScannerCaliRegion);
extern double ReadScannerCaliRegion();
extern void SetScannerXYFlip(int nScannerXYFlip);
extern int ReadScannerXYFlip();
extern void SetScannerInvertX(int nScannerInvertX);
extern int ReadScannerInvertX();
extern void SetScannerInvertY(int nScannerInvertY);
extern int ReadScannerInvertY();




// CDlgDevCfgTabScanner 对话框

class CDlgDevCfgTabScanner : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgDevCfgTabScanner)

public:
	CDlgDevCfgTabScanner(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgDevCfgTabScanner();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DEVICE_CONFIG_TAB_SCANNER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonShowDlgCali();
	afx_msg void OnBnClickedButtonScannerMarkCaliPoint();
	afx_msg void OnBnClickedButtonScannerAutoFindCaliPoint();
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeComboScannerMatrixCaliPoint();

protected:
	double m_fLenRegion;
	double m_fCaliRegion;
	double m_fCaliRadius;
	double m_fCaliFindScaleMin;
	double m_fCaliFindScaleMax;
	double m_fCaliFindMinScore;
	int m_nIndexMatrixCaliPoint;
	int GetCountMatrixCaliPointFromIndex();
public:
	afx_msg void OnEnChangeEditScannerCaliRegion();

	void WriteTxtCor(CString strCor, std::vector <CPointF>* vPtPos);
	//void ReadTxtCor();

	//CPointF GetPtPosFromIndex(int nIndex, int nCtMatrix, double fStepMatrix);

	afx_msg void OnEnChangeEditScannerCaliRadius();
	afx_msg void OnEnChangeEditScannerFindScaleMin();
	afx_msg void OnEnChangeEditScannerFindScaleMax();
	afx_msg void OnEnChangeEditScannerFindMinScore();
	afx_msg void OnBnClickedCheckidcScannerXyFlip();
	afx_msg void OnBnClickedCheckidcScannerInvertX();
	afx_msg void OnBnClickedCheckidcScannerInvertY();
protected:
	int m_nScannerXYFlip;
	int m_nScannerInvertX;
	int m_nScannerInvertY;

public:
	afx_msg void OnEnChangeEditScannerLenRegion();
	afx_msg void OnBnClickedButtonScannerFindAllCaliPoints();
};
