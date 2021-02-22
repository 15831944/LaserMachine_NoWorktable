#pragma once

#include "HalconWndDlg.h"
#include "PointF.h"

// CDlgCameraPositionSetRealMarkPoint 对话框

class CDlgCameraPositionSetRealMarkPoint : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgCameraPositionSetRealMarkPoint)

public:
	CDlgCameraPositionSetRealMarkPoint(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgCameraPositionSetRealMarkPoint();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CAMERA_POSITION_SET_REAL_MARK_POINT };
#endif

//public:
//	CDlgCameraPositionSetRealMarkPointInner m_dlgInnerHalcon;
protected:
	int m_nCBIndexModelType;
	double m_fModelCircleRadius;
	double m_fModelCrossLength;
	double m_fModelCrossWidth;
	double m_fModelRectWidth;
	double m_fModelRectHeight;
	double m_fModelParamScaleMin;
	double m_fModelParamScaleMax;
	double m_fModelParamMinScore;
	CPointF m_ptPosMatched;

public:
	CHalconWndDlg m_wndHalconDlg;
	
	BOOL NewModelCircle();
	BOOL NewModelCross();
	BOOL NewModelRectOutline();

	CPointF GetMatchedPtPos();
	//MarkPointModel GetMatchedModel();
	HalconModel GetMatchedModel();

	
	//TestDxf
	void gen_model_image_of_bright_object_with_holes_COPY_1(HObject ho_Contours, HObject* ho_ModelImage,
		HTuple hv_Scale, HTuple hv_Width, HTuple hv_Height);
	

	//BOOL MatchModelCircle();
	//BOOL MatchModelCross();
	//BOOL MatchModelRectOutline();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnBnClickedButtonPositionModelNew();
	afx_msg void OnBnClickedButtonPositionModelMatch();
	afx_msg void OnCbnSelchangeComboPositionModelType();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButtonFindTestDxf();
};
