#pragma once

#include "CGridListCtrlEx/CGridListCtrlGroups.h"
#include <vector>


extern std::vector<double> vecGridX, vecGridY;

extern void SetGridUnitX(double fGridUnitX);
extern double ReadGridUnitX();
extern void SetGridUnitY(double fGridUnitY);
extern double ReadGridUnitY();




// CDlgSetParaGrid 对话框

class CDlgSetParaGrid : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgSetParaGrid)

public:
	CDlgSetParaGrid(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgSetParaGrid();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SETPARA_GRID };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
protected:
	CGridListCtrlGroups m_ListCtrl;
	CImageList m_ImageList;

	void GenGridListControl(double fBorderRangeX, double fBorderRangeY);	//用振镜加工幅面直接分格
	void GenGridListControl(double fGridUnitX, double fGridUnitY, double fBorderRangeX, double fBorderRangeY);
	void GenGridListControl(std::vector<double> vecGridX, std::vector<double> vecGridY);

public:
	afx_msg void OnBnClickedButtonSerGridPresetting();
	double m_fGridUnitX;
	double m_fGridUnitY;
	double m_fScannerRegion;
	double m_fWktableRegion;

	afx_msg void OnBnClickedOk();
	double m_fBorderRangeX;
	double m_fBorderRangeY;
};

