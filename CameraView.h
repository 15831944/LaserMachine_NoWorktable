#pragma once
#include "HalconWnd.h"

#define WM_LOCATE WM_USER+200

// CCameraView 视图

class CCameraView : public CScrollView
{
	DECLARE_DYNCREATE(CCameraView)

protected:
	CCameraView();           
	virtual ~CCameraView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif


protected:
	// ClassWizard generated virtual function overrides.
	//{{AFX_VIRTUAL(CScrollWnd)
	virtual void PostNcDestroy();
	virtual void OnDraw(CDC* pDC);      // 重写以绘制该视图
	virtual void OnInitialUpdate();     // 构造后的第一次
	//}}AFX_VIRTUAL
	DECLARE_MESSAGE_MAP()

public:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnOpenCamera();
	afx_msg void OnCloseCamera();
	afx_msg void OnSetparaCamera();
	//afx_msg void OnTestCreateModel();
	afx_msg void OnTestFindModel();
	afx_msg void OnTestHalconFindCircle();
	afx_msg void OnTestHalconFindCircleHand();
	afx_msg void OnPaint();

public:
	CHalconWnd* m_pHalconWnd;
protected:
	afx_msg LRESULT OnLocate(WPARAM wParam, LPARAM lParam);
};


