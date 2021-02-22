#pragma once

#include "PointF.h"
#include <vector>
#include "HalconWndDlg.h"


extern int g_nCountMarkPoints;
extern std::vector <CPointF> g_vPtPosDestinedMark;
extern std::vector <CPointF> g_vPtPosRealMark;
extern std::vector <HalconModel> g_vMarkPointModel;


// CCameraPosition 窗体视图

class CCameraPosition : public CFormView
{
	DECLARE_DYNCREATE(CCameraPosition)

protected:
	CCameraPosition();           // 动态创建所使用的受保护的构造函数
	virtual ~CCameraPosition();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CAMERA_POSITION };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedButtonPositionCountMarkPoints();
	afx_msg void OnBnClickedButtonPositionSetDestinedMark1();
	afx_msg void OnBnClickedButtonPositionSetDestinedMark2();
	afx_msg void OnBnClickedButtonPositionSetDestinedMark3();
	afx_msg void OnBnClickedButtonPositionSetDestinedMark4();
	

public:
	int m_nCountMarkPoints;
	std::vector <CPointF> m_vPtPosDestinedMark;
	std::vector <CPointF> m_vPtPosRealMark;
	std::vector <HalconModel> m_vMarkPointModel;
	BOOL RefreshMarkPoints();
	void RefreshUI(int nCtMarkPoints);
	afx_msg void OnBnClickedButtonPositionSetRealMark1();
	afx_msg void OnBnClickedButtonPositionSetRealMark2();
	afx_msg void OnBnClickedButtonPositionSetRealMark3();
	afx_msg void OnBnClickedButtonPositionSetRealMark4();
	afx_msg void OnBnClickedButtonPositionCheck();
	afx_msg void OnBnClickedButtonPositionTestDxf();
};

extern std::vector<std::vector<double>> g_vecTestDXF;

