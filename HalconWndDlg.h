//#if !defined(AFX_HALCONWND_H__41CAF5F2_2DB6_4426_9C62_70B0229EEA12__INCLUDED_)
//#define AFX_HALCONWND_H__41CAF5F2_2DB6_4426_9C62_70B0229EEA12__INCLUDED_
//
//#if _MSC_VER > 1000
#pragma once
//#endif // _MSC_VER > 1000
// HalconWnd.h : header file
//
#include <vector>
#include<HalconCpp.h>
#include<HALCONCpp/HDevThread.h>
#include "HalconModel.h"

using namespace HalconCpp;

/////////////////////////////////////////////////////////////////////////////
// CHalconWndDlg window


class CHalconWndDlg : public CWnd
{
// Construction
public:
	CHalconWndDlg();
	virtual ~CHalconWndDlg();


// Attributes

public:
	//MarkPointModel m_modelMarkPoint;
	HalconModel m_modelMarkPoint;
	HTuple m_hWindow;
	HObject m_hoImage;
	//HObject m_hoXldContour;
	HTuple m_hvImageWidth;
	HTuple m_hvImageHeight;
	double m_dbZoomFactor;
	BOOL m_bDrawingArea;
	int m_nLastHorzPos;
	int m_nLastVertPos;

	enum DRAW_MODE
	{
		DRAW_RECTANGLE1,
		DRAW_RECTANGLE2,
		DRAW_CIRCLE,
		DRAW_ELLIPSE,
		DRAW_POLYGON,
		DRAW_REGION,
	};

// Operations
public:
	BOOL InitHalcon(int x,int y,int w,int h);
	//BOOL LoadImageFromCamera(LPCSTR szImagePath);
	BOOL LoadImageFromCamera(HImage hoImgCamera);
	BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);

	BOOL DrawRectangle1();
	BOOL DrawRectangle2();
	BOOL DrawRectangle2Mod(HTuple hvRowIn, HTuple hvColumnIn, HTuple hvPhiIn,HTuple hvLengthIn, HTuple hvWidthIn, 
							HTuple* hvRowOut, HTuple* hvColumnOut, HTuple* hvPhiOut, HTuple* hvLengthOut, HTuple* hvWidthOut);
	BOOL DrawCircle();
	BOOL DrawCircleMod(HTuple hvRowIn, HTuple hvColumnIn, HTuple hvRaiusIn, 
						HTuple* hvRowOut, HTuple* hvColumnOut, HTuple* hvRadiusOut);
	BOOL DrawEllipse();
	BOOL DrawPolygon();
	BOOL DrawRegion();
	BOOL DrawArea(UINT nMode);
	BOOL IsDrawingArea();

	BOOL ZoomIn();
	BOOL ZoomOut();
	BOOL Zoom(double dbFactor);
	double GetZoomFactor();

	//BOOL DispContour(HObject hoXld, CString strColor, int nLineWidth);

	BOOL NewModelCircleHalcon(double fModelCircleRadiusIn, double* fModelCircleRadiusOut);
	BOOL NewModelCrossHalcon(double fModelCrossLengthIn, double fModelCrossWidthIn, double* fModelCrossLengthOut, double* fModelCrossWidthOut);
	BOOL NewModelRectOutlineHalcon(double fModelRectWidthIn, double fModelRectHeightIn, double* fModelRectWidthOut, double* fModelRectHeightOut);
	int MatchModelHalcon(double fScaleMin, double fScaleMax, double fMinScore, double* fPoxX, double* fPoxY, double fPixelSize);

	void draw_rake(HObject* ho_Regions, HTuple hv_WindowHandle, HTuple hv_Elements,
		HTuple hv_DetectHeight, HTuple hv_DetectWidth, HTuple* hv_Row1, HTuple* hv_Column1,
		HTuple* hv_Row2, HTuple* hv_Column2);
	// Chapter: XLD / Creation
	// Short Description: Creates an arrow shaped XLD contour. 
	void gen_arrow_contour_xld(HObject* ho_Arrow, HTuple hv_Row1, HTuple hv_Column1,
		HTuple hv_Row2, HTuple hv_Column2, HTuple hv_HeadLength, HTuple hv_HeadWidth);
	void pts_to_best_line(HObject* ho_Line, HTuple hv_Rows, HTuple hv_Cols, HTuple hv_ActiveNum,
		HTuple* hv_Row1, HTuple* hv_Col1, HTuple* hv_Row2, HTuple* hv_Col2);
	void rake(HObject ho_Image, HObject* ho_Regions, HTuple hv_Elements, HTuple hv_DetectHeight,
		HTuple hv_DetectWidth, HTuple hv_Sigma, HTuple hv_Threshold, HTuple hv_Transition,
		HTuple hv_Select, HTuple hv_Row1, HTuple hv_Column1, HTuple hv_Row2, HTuple hv_Column2,
		HTuple* hv_ResultRow, HTuple* hv_ResultColumn);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHalconWndDlg)
	//}}AFX_VIRTUAL

	// Generated message map functions
protected:
	//{{AFX_MSG(CHalconWndDlg)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

//#endif // !defined(AFX_HALCONWND_H__41CAF5F2_2DB6_4426_9C62_70B0229EEA12__INCLUDED_)
